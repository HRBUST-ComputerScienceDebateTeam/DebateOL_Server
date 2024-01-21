//提供访问数据库的方法
#include "dal_user.h"
#include <regex>
#include <string>



void SettoClass_getval(int &a    , string &s){a = stoi(s);}
void SettoClass_getval(string& a , string &s){a =  s;};
std::string to_string(string x){return x;};


vector<string> DAL_User_Base::title_DAL_User_Base;
vector<string> DAL_User_Social::title_DAL_User_Social;
vector<string> DAL_User_Extra::title_DAL_User_Extra;
vector<string> DAL_UU_relation::title_DAL_UU_relation;

DB_MYSQL DB_MYSQL_OFUSER::DB_mysql;
//建立连接 - 数据库(TODO:redis)
bool DB_MYSQL_OFUSER::connect_tomysql(){
    DBRES * res;
    res = DB_MYSQL_OFUSER::DB_mysql.DB_init(User_host, User_user ,  User_passwd ,User_db,User_port);
    if(res->OKflag != true){
        cout<< "mysql connnect err"<< res->errinfo << endl;
        return false;
    }

    string sql = "use DebateOL;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->OKflag != true){
        cout<< "mysql use DebateOL err"<< res->errinfo << endl;
        return false;
    }
    return true;
}
bool DB_MYSQL_OFUSER::connect_toredis(){};

using namespace std;
//提供交互函数


//初始化 
DAL_User_Base::DAL_User_Base(){
    Userid = -1;
}
DAL_User_Social::DAL_User_Social(){
    Userid = -1;
}
DAL_User_Extra::DAL_User_Extra(){
    Userid = -1;
}
DAL_UU_relation::DAL_UU_relation(){
    UseridA =UseridB =  -1;
}

bool DB_MYSQL_OFUSER::init_title(){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout << "DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES * res;

    string sql1 = "show columns from DAL_User_Base;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    if(res->checkerr(sql1) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_User_Base::title_DAL_User_Base.push_back(res->v[i][0]);
        }
    }

    string sql2 = "show columns from DAL_User_Social;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql2);
    if(res->checkerr(sql2) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_User_Social::title_DAL_User_Social.push_back(res->v[i][0]);
        }
    }

    string sql3 = "show columns from DAL_User_Extra;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql3);
    if(res->checkerr(sql3) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_User_Extra::title_DAL_User_Extra.push_back(res->v[i][0]);
        }
    }

    string sql4 = "show columns from DAL_UU_relation;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql4);
    if(res->checkerr(sql4) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_UU_relation::title_DAL_UU_relation.push_back(res->v[i][0]);
        }
    }
    

    return true;
}
//--function
/* 连接 */

/* 查询 */
DAL_User_Base   DB_MYSQL_OFUSER::get_user_base  (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_User_Base();
    }
    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_User_Base();
    }

    DBRES  * res;
    string sql = " select * from DAL_User_Base where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_User_Base();
    }
    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return DAL_User_Base();
    }
    
    if(res->num_fields != DAL_User_Base::title_DAL_User_Base.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_User_Base();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_User_Base::title_DAL_User_Base[i]] = res->v[0][i];
    }
    return DAL_User_Base::ToClass(mp);
}
DAL_User_Extra  DB_MYSQL_OFUSER::get_user_extra (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_User_Extra();
    }
    if(DAL_User_Extra::title_DAL_User_Extra.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_User_Extra();
    }

    DBRES  * res;
    string sql = " select * from DAL_User_Extra where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_User_Extra();
    }
    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return DAL_User_Extra();
    }
    
    if(res->num_fields != DAL_User_Extra::title_DAL_User_Extra.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_User_Extra();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_User_Extra::title_DAL_User_Extra[i]] = res->v[0][i];
    }
    return DAL_User_Extra::ToClass(mp);
}
DAL_User_Social DB_MYSQL_OFUSER::get_user_social(int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_User_Social();
    }
    if(DAL_User_Social::title_DAL_User_Social.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_User_Social();
    }

    DBRES  * res;
    string sql = " select * from DAL_User_Social where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_User_Social();
    }
    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return DAL_User_Social();
    }
    
    if(res->num_fields != DAL_User_Social::title_DAL_User_Social.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_User_Social();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_User_Social::title_DAL_User_Social[i]] = res->v[0][i];
    }
    return DAL_User_Social::ToClass(mp);
}
DAL_UU_relation DB_MYSQL_OFUSER::get_uulevel    (int uidA , int uidB){//查询用户关系
    if(uidA >uidB){
        swap(uidA , uidB);
    }else if(uidA == uidB){
        cout <<__func__ << "同一个人"<<endl;
        return DAL_UU_relation();
    }
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_UU_relation();
    }
    if(DAL_UU_relation::title_DAL_UU_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_UU_relation();
    }

    DBRES  * res;
    string sql = " select * from DAL_UU_relation where UseridA = " + to_string(uidA) + " and UseridB = "+ to_string(uidB) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_UU_relation();
    }
    if(res->num_row == 0){
        DAL_UU_relation ret;
        ret.UseridA = uidA;
        ret.UseridB = uidB;
        ret.UULevel = 0 ;
        return ret;
    }
    
    if(res->num_fields != DAL_UU_relation::title_DAL_UU_relation.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_UU_relation();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_UU_relation::title_DAL_UU_relation[i]] = res->v[0][i];
    }
    return DAL_UU_relation::ToClass(mp);
} 

int DB_MYSQL_OFUSER::get_userid_fromUsernum  (string Usernum  ){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Userid from DAL_User_Base where Usernum = " + Usernum + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return -1;

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return -1;
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  -1;
    }

    return stoi(res->v[0][0]);
};//Usernum  to uid
int DB_MYSQL_OFUSER::get_userid_fromTel      (string Tel      ){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Userid from DAL_User_Base where Tel = " + Tel + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return -1;

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return -1;
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  -1;
    }

    return stoi(res->v[0][0]);
};//Tel      to uid
int DB_MYSQL_OFUSER::get_userid_fromUsername (string Username ){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Userid from DAL_User_Social where Username = " + Username + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return -1;

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return -1;
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  -1;
    }


    return stoi(res->v[0][0]);
};//Username to uid

string DB_MYSQL_OFUSER::get_UserLasttime (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }

    DBRES  * res;
    string sql = " select UserLasttime from DAL_User_Base where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return "";

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return "";
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  "";
    }

    return res->v[0][0];
};  //查询上一次在线时间
string DB_MYSQL_OFUSER::get_UserSalt     (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }

    DBRES  * res;
    string sql = " select Salt from DAL_User_Base where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return "";

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return "";
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  "";
    }

    return res->v[0][0];
};  //查询密码和盐
string get_UserPasswd   (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }

    DBRES  * res;
    string sql = " select Passwd from DAL_User_Base where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return "";

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return "";
    }

    if(res->num_fields != 1 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  "";
    }

    return res->v[0][0];
};  
int DB_MYSQL_OFUSER::getnextuid(){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " show create table DAL_User_Base;";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false) return -1;

    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return -1;
    }

    if(res->num_fields != 2 ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return  -1;
    }

    std::regex reg("AUTO_INCREMENT=(\\d.+?) ");
    string text = res->v[0][1];
    smatch results;
    regex_search(text ,results ,reg);
    if(results.size() != 2) {
        cout << __func__ << "匹配失败没有找到自增" <<endl;
        return -1;
    }
    return stoi(results[1]);
    

};//获取下一次的uid

//获得列表
string DB_MYSQL_OFUSER::get_UUrelation  (int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }
    if(DAL_UU_relation::title_DAL_UU_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return "";
    }

    DBRES  * res;
    string sql = " select * from DAL_UU_relation where UseridA = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return "";
    }
    
    if(res->num_fields != DAL_UU_relation::title_DAL_UU_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return "";
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_row;i++){
        mp[res->v[i][1]] = res->v[i][2];
    }

    string sql2 = " select * from DAL_UU_relation where UseridB = " + to_string(uid) + ";";
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return "";
    }
    
    if(res->num_fields != DAL_UU_relation::title_DAL_UU_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return "";
    }
    for(int i = 0; i<res->num_row;i++){
        int flag1 = (stoi(res->v[i][2]))&1;
        int flag2 = (stoi(res->v[i][2]))&2;
        int flag3 = (stoi(res->v[i][2]))&4;
        int flag4 = (stoi(res->v[i][2]))&8;

        string rets = to_string(flag3*8+flag4*4 + flag1*2 + flag2);
        mp[res->v[i][1]] = rets;
    }
    return MapToJsonstring(mp);
};

/* 创建 */
bool DB_MYSQL_OFUSER::AddUser_t1    (DAL_User_Base t1){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = t1.toMap();

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_User_Base::title_DAL_User_Base.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_User_Base::title_DAL_User_Base.size()" << DAL_User_Base::title_DAL_User_Base.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_User_Base::title_DAL_User_Base.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_User_Base::title_DAL_User_Base[i])];
        Insertinfo+= '\"';
        if(i!= DAL_User_Base::title_DAL_User_Base.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_User_Base values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFUSER::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
bool DB_MYSQL_OFUSER::AddUser_t2    (DAL_User_Social t2){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = t2.toMap();

    if(DAL_User_Social::title_DAL_User_Social.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_User_Social::title_DAL_User_Social.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_User_Social::title_DAL_User_Social.size()" << DAL_User_Social::title_DAL_User_Social.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_User_Social::title_DAL_User_Social.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_User_Social::title_DAL_User_Social[i])];
        Insertinfo+= '\"';
        if(i!= DAL_User_Social::title_DAL_User_Social.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_User_Social values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFUSER::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
bool DB_MYSQL_OFUSER::AddUser_t3    (DAL_User_Extra t3){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = t3.toMap();

    if(DAL_User_Extra::title_DAL_User_Extra.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_User_Extra::title_DAL_User_Extra.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_User_Extra::title_DAL_User_Extra.size()" << DAL_User_Extra::title_DAL_User_Extra.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_User_Extra::title_DAL_User_Extra.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_User_Extra::title_DAL_User_Extra[i])];
        Insertinfo+= '\"';
        if(i!= DAL_User_Extra::title_DAL_User_Extra.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_User_Extra values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFUSER::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
bool DB_MYSQL_OFUSER::AddUUlevel (DAL_UU_relation uulevel){
    if(uulevel.UseridA >= uulevel.UseridB){
        cout << __func__ << "错误的输入" <<endl;
        return false;
    }
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = uulevel.toMap();

    if(DAL_UU_relation::title_DAL_UU_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_UU_relation::title_DAL_UU_relation.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_UU_relation::title_DAL_UU_relation.size()" << DAL_UU_relation::title_DAL_UU_relation.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_UU_relation::title_DAL_UU_relation.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_UU_relation::title_DAL_UU_relation[i])];
        Insertinfo+= '\"';
        if(i!= DAL_UU_relation::title_DAL_UU_relation.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_UU_relation values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFUSER::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}

/* 删除 */
bool DB_MYSQL_OFUSER::DelUser(int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;
    bool doflag2 = 0;
    bool doflag3 = 0;
    bool doflag4 = 0;

    string sql1 = "delete from DAL_User_Base where Userid = " + to_string(uid) + ";"; 
    string sql2 = "delete from DAL_User_Social where Userid = " + to_string(uid) + ";";
    string sql3 = "delete from DAL_User_Extra where Userid = " + to_string(uid) + ";";
    string sql4 = "delete from DAL_UU_relation where UseridA = " + to_string(uid) + " or " +"UseridA ="  + to_string(uid) +";";
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql2);
    doflag2 = res->checkerr(sql2);
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql3);
    doflag3 = res->checkerr(sql3);

    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql4);
    doflag4 = res->checkerr(sql4);

    return doflag1 && doflag2 &&doflag3 && doflag4;
}
bool DB_MYSQL_OFUSER::DelUser_t1(int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;

    string sql1 = "delete from DAL_User_Base where Userid = " + to_string(uid) + ";"; 
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}
bool DB_MYSQL_OFUSER::DelUser_t2(int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;

    string sql1 = "delete from DAL_User_Social where Userid = " + to_string(uid) + ";";
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}
bool DB_MYSQL_OFUSER::DelUser_t3(int uid){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;

    string sql1 = "delete from DAL_User_Extra where Userid = " + to_string(uid) + ";";
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}

bool DB_MYSQL_OFUSER::DelUUlevel (int uidA , int uidB){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_User_Base::title_DAL_User_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;
    string sql1 = "delete from DAL_UU_relation where UseridA = " + to_string(uidA) + " and " +"UseridB ="  + to_string(uidB) +";";
    
    res = DB_MYSQL_OFUSER::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
};


/* 更改 */
bool DB_MYSQL_OFUSER::updata_user_base    (int uid , DAL_User_Base   t){ //整表更改
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    int flag1 = DelUser_t1(uid);
    int flag2 = AddUser_t1(t);
    return flag1 && flag2;
};
bool DB_MYSQL_OFUSER::updata_user_extra   (int uid , DAL_User_Extra  t){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    int flag1 = DelUser_t3(uid);
    int flag2 = AddUser_t3(t);
    return flag1 && flag2;
};
bool DB_MYSQL_OFUSER::updata_user_social  (int uid , DAL_User_Social t){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    int flag1 = DelUser_t2(uid);
    int flag2 = AddUser_t2(t);
    return flag1 && flag2;
};


bool DB_MYSQL_OFUSER::updata_UserLasttime (int uid , string s){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    string sql = "update DAL_User_Base set UserLasttime = \"" + s + "\" where Userid = " + to_string(uid) + ";";
    DBRES * res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false){
        cout << __func__ << " err " <<endl;
        return false;
    }else{
        if(res->affected_rows == 0){
            cout <<__func__ << "没有这行 或者 数据没变" <<endl;
            return false;
        }
        return true;
    }
};  //更改在线时间

bool DB_MYSQL_OFUSER::updata_UserUUlevel  (int uidA , int uidB , int newlevel){
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    string sql = "update DAL_UU_relation set UULevel  = " + to_string(newlevel) + \
                " where UseridA = " + to_string(uidA) + \
                " and UseridB = " + to_string(uidB) + ";";
    DBRES * res = DB_MYSQL_OFUSER::DB_mysql.exec(sql);
    if(res->checkerr(sql) == false){
        cout << __func__ << " err " <<endl;
        return false;
    }else{
        if(res->affected_rows == 0){
            cout <<__func__ << "没有这行 或者 数据没变" <<endl;
            return false;
        }
        return true;
    }
};  //更改关系






//提供dal类和map的转换方式
//完善tomap函数
//完善toclass
map<string , string> DAL_User_Base::toMap(){
    map<string , string>mp;
    SettoMap(Userid)          ;         
    SettoMap(Usernum)         ;          
    SettoMap(Passwd)          ;         
    SettoMap(Tel)             ;      
    SettoMap(UserRegtime)     ;              
    SettoMap(UserLasttime)    ;               
    SettoMap(Salt)            ;       
    return mp;
}
DAL_User_Base DAL_User_Base::ToClass(map<string , string> mp){
    DAL_User_Base ret;
    SettoClass(Userid)          ;         
    SettoClass(Usernum)         ;          
    SettoClass(Passwd)          ;         
    SettoClass(Tel)             ;      
    SettoClass(UserRegtime)     ;              
    SettoClass(UserLasttime)    ;               
    SettoClass(Salt)            ;       
    return ret;
}

map<string , string> DAL_User_Social::toMap(){
    map<string , string>mp;
    SettoMap(Userid)   ;                            
    SettoMap(Username) ;                              
    SettoMap(Headshot) ;                              
    SettoMap(Sex)      ;                         
    SettoMap(Signature);                               
    SettoMap(Contact)  ;     
    return mp;
}

DAL_User_Social DAL_User_Social::ToClass(map<string , string>mp ){
    DAL_User_Social ret;
    SettoClass(Userid)   ;                            
    SettoClass(Username) ;                              
    SettoClass(Headshot) ;                              
    SettoClass(Sex)      ;                         
    SettoClass(Signature);                               
    SettoClass(Contact)  ; 
    return ret;
}


map<string , string> DAL_User_Extra::toMap(){
    map<string , string>mp;
    SettoMap(Userid)             ;       
    SettoMap(IntentionToArgue)   ;                 
    SettoMap(MatcheNum)          ;          
    SettoMap(BestPlayerNum)      ;              
    SettoMap(VectoryNum)         ;           
    SettoMap(OnePosNum)          ;          
    SettoMap(TwoPosNum)          ;          
    SettoMap(ThreePosNum)        ;            
    SettoMap(FourPosNum)         ;
    return mp;
}

DAL_User_Extra DAL_User_Extra::ToClass(map<string , string>mp ){
    DAL_User_Extra ret;
    SettoClass(Userid)             ;       
    SettoClass(IntentionToArgue)   ;                 
    SettoClass(MatcheNum)          ;          
    SettoClass(BestPlayerNum)      ;              
    SettoClass(VectoryNum)         ;           
    SettoClass(OnePosNum)          ;          
    SettoClass(TwoPosNum)          ;          
    SettoClass(ThreePosNum)        ;            
    SettoClass(FourPosNum)         ;
    return ret;
}

map<string , string> DAL_UU_relation::toMap(){
    map<string , string>mp;
    SettoMap(UseridA)          ;       
    SettoMap(UseridB)          ;                 
    SettoMap(UULevel)          ;          
    return mp;
}

DAL_UU_relation DAL_UU_relation::ToClass(map<string , string>mp ){
    DAL_UU_relation ret;
    SettoClass(UseridA)          ;       
    SettoClass(UseridB)          ;                 
    SettoClass(UULevel)          ;          
    return ret;
}
