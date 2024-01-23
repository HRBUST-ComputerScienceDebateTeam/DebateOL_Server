#include "DB_MYSQL.h"
#include <mysql/mysql.h>



DB_MYSQL::DB_MYSQL(){
    mysql = new MYSQL;
    res = new DBRES;
    this->mysql = mysql_init(NULL);
    if(this->mysql == nullptr){
        std::cout << "err init" <<std::endl;
        initflag = false;
        return;
    }else{
        initflag = true;
    }

};

bool DB_MYSQL::isinit(){
    return initflag;
}

DB_MYSQL::~DB_MYSQL(){
    //delete mysql;
    delete res;
}

using namespace std;
DBRES * DB_MYSQL::DB_init(const char* host, const char * user , const  char * passwd ,const char * db,unsigned int port){
    this->mysql = mysql_real_connect(this->mysql ,host, user ,  passwd ,db,port , NULL , 0);
    if(this->mysql == nullptr)
    {
        res->OKflag = false;
        res->errinfo = mysql_error(this->mysql);
    }else{
        res->OKflag = 1;
        //cout << "DB_init_ok" <<endl;
    }
    return res;
}

//错误返回 false
bool DBRES::checkerr(std::string &sql){
    if(this->OKflag == false){
        cout<< "执行sql : " << sql <<endl;
        cout<< "mysql err:"<< this->errinfo << endl;
        return false;
    }else{
        return true;
    }
}

DBRES * DB_MYSQL::exec(std::string sql)
{
    res->v.clear();
    res->errinfo.clear();
    res->OKflag = false;
    //mysql_query()执行成功返回0,执行失败返回非0值。
    if (mysql_query(mysql,sql.c_str()))
    {
        res->errinfo = std::string(mysql_error(mysql));
        this->res->OKflag = false;
        return this->res;
    }
    else // 查询成功
    {
        this->res->OKflag = true;
        MYSQL_RES * tmpres = new MYSQL_RES;
        MYSQL_ROW row;
        tmpres = mysql_store_result(mysql);  //获取结果集
        if (tmpres){
            
           int num_fields = mysql_num_fields(tmpres);   //获取结果集中总共的字段数，即列数
           int num_rows = mysql_num_rows(tmpres);       //获取结果集中总共的行数
           this->res->num_fields = num_fields;
           this->res->num_row = num_rows;
           this->res->affected_rows = 0;

           for(int i=0;i<num_rows;i++) //输出每一行
            {
                //获取下一行数据
                row=mysql_fetch_row(tmpres);
                std::vector<std::string>tmprow;
                for(int j=0;j<num_fields;j++)  //输出每一字段
                {
                    if(row[j] != nullptr)
                        tmprow.push_back(row[j]);
                    else
                        tmprow.push_back("");
                }
                res->v.push_back(tmprow);
            }
        }else{
            this->res->num_fields = 0;   //获取结果集中总共的字段数，即列数
            this->res->num_row    = 0; 
            this->res->affected_rows =mysql_affected_rows(mysql);
        }
        mysql_free_result(tmpres);
    }
    return res;

}

