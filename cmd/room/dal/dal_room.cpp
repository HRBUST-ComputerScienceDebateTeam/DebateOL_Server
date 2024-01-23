//提供访问数据库的方法
#include "dal_room.h"
#include "dal_roomconfig.h"
#include <bits/stdc++.h>
#include <string>

void SettoClass_getval(int &a    , string &s){a = stoi(s);}
void SettoClass_getval(string& a , string &s){a =  s;};
std::string to_string(string x){return x;};

#define INT_DEFAULT -1
#define STR_DEFAULT ""

//建立连接 - 数据库(TODO:redis)
//提供交互函数
//完善tomap函数
DB_MYSQL DB_MYSQL_OFROOM::DB_mysql;
bool DB_MYSQL_OFROOM::connect_tomysql(){
    DBRES * res;
    res = DB_MYSQL_OFROOM::DB_mysql.DB_init(Room_host, Room_user ,  Room_passwd ,Room_db,Room_port);
    if(res->OKflag != true){
        cout<< "mysql connnect err"<< res->errinfo << endl;
        return false;
    }

    string sql = "use DebateOL;";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    if(res->OKflag != true){
        cout<< "mysql use DebateOL err"<< res->errinfo << endl;
        return false;
    }
    return true;
}
bool DB_MYSQL_OFROOM::connect_toredis(){}

vector<string> DAL_Room_Base::title_DAL_Room_Base;
vector<string> DAL_Room_Extra::title_DAL_Room_Extra;
vector<string> DAL_UR_relation::title_DAL_UR_relation;

//初始化
DAL_Room_Base::DAL_Room_Base(){
  Roomid          = INT_DEFAULT;
  Roomnum         = STR_DEFAULT;                            
  Passwd          = STR_DEFAULT;           
  RoomCreatetime  = STR_DEFAULT;                   
  Salt            = STR_DEFAULT;         
}

//DB中Room Extra的结构体 - 对外展示的部分
DAL_Room_Extra::DAL_Room_Extra(){

  Roomid            =INT_DEFAULT;              
  Islocking         =INT_DEFAULT;                 
  Debate_posbitmap  =INT_DEFAULT;                        

  Roomnum       =STR_DEFAULT;           
  Roomname      =STR_DEFAULT;            
  Signature     =STR_DEFAULT;             
  Debate_name   =STR_DEFAULT;               

};

//DB中user - Room关系的结构体
DAL_UR_relation::DAL_UR_relation(){
  Userid       = INT_DEFAULT;          
  Roomid       = INT_DEFAULT;          
  Debate_pos   = INT_DEFAULT;              
  Permissions  = INT_DEFAULT;               
}

bool DB_MYSQL_OFROOM::init_title(){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout << "DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES * res;

    string sql1 = "show columns from DAL_Room_Base;";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql1);
    if(res->checkerr(sql1) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_Room_Base::title_DAL_Room_Base.push_back(res->v[i][0]);
        }
    }

    string sql2 = "show columns from DAL_Room_Extra;";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql2);
    if(res->checkerr(sql2) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_Room_Extra::title_DAL_Room_Extra.push_back(res->v[i][0]);
        }
    }

    string sql3 = "show columns from DAL_UR_relation;";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql3);
    if(res->checkerr(sql3) == false){
        return false;
    }else{
        for(int i = 0;i<res->num_row;i++){
            DAL_UR_relation::title_DAL_UR_relation.push_back(res->v[i][0]);
        }
    }

    return true;
}

/* 查询 */
//通过roomid查表
DAL_Room_Base   DB_MYSQL_OFROOM::get_Room_base   (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_Room_Base();
    }
    if(DAL_Room_Base::title_DAL_Room_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_Room_Base();
    }

    DBRES  * res;
    string sql = " select * from DAL_Room_Base where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_Room_Base();
    }
    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return DAL_Room_Base();
    }
    
    if(res->num_fields != DAL_Room_Base::title_DAL_Room_Base.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_Room_Base();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_Room_Base::title_DAL_Room_Base[i]] = res->v[0][i];
    }
    return DAL_Room_Base::ToClass(mp);
}

DAL_Room_Extra  DB_MYSQL_OFROOM::get_Room_extra  (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return DAL_Room_Extra();
    }
    if(DAL_Room_Extra::title_DAL_Room_Extra.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return DAL_Room_Extra();
    }

    DBRES  * res;
    string sql = " select * from DAL_Room_Extra where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return DAL_Room_Extra();
    }
    if(res->num_row != 1){
        cout <<__func__ <<  " 没有找到正确数据" <<endl;
        return DAL_Room_Extra();
    }
    
    if(res->num_fields != DAL_Room_Extra::title_DAL_Room_Extra.size() ){
        cout <<__func__ <<  " 找到的数量不符合" <<endl;
        return DAL_Room_Extra();
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_fields;i++){
        mp[DAL_Room_Extra::title_DAL_Room_Extra[i]] = res->v[0][i];
    }
    return DAL_Room_Extra::ToClass(mp);
}

//查询Room中都有哪些用户 - 序列化的map (user - 辩位)
string DB_MYSQL_OFROOM::get_UserinRoom_Debatepos    (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }
    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return "";
    }

    DBRES  * res;
    string sql = " select * from DAL_UR_relation where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return "";
    }
    
    if(res->num_fields != DAL_UR_relation::title_DAL_UR_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return "";
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_row;i++){
        mp[res->v[i][0]] = res->v[i][2];
    }

    return MapToJsonstring(mp);
}

//查询Room中都有哪些用户 - 序列化的map (user - 权限)
string DB_MYSQL_OFROOM::get_UserinRoom_permissions  (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }
    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return "";
    }

    DBRES  * res;
    string sql = " select * from DAL_UR_relation where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return "";
    }
    
    if(res->num_fields != DAL_UR_relation::title_DAL_UR_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return "";
    }
    map<string , string>mp;
    for(int i = 0; i<res->num_row;i++){
        mp[res->v[i][0]] = res->v[i][3];
    }

    return MapToJsonstring(mp);
}    

//获取房间的管理员用户id
int DB_MYSQL_OFROOM::get_RootOfRoom   (int roomid){
    int ans = -1;
    string ret = get_UserinRoom_permissions(roomid);
    if(ret == ""){
        return -1;
    }
    map<string , string > mp = JsonstringToMap(ret);
    for(auto it : mp){
        if(stoi(it.second) == 1){
            if(ans == -1){
                ans = stoi(it.first);
            }else{
                return -1;
            }
        }
    }
    return ans;
}    

int DB_MYSQL_OFROOM::get_Roomid_fromUserid(int uid  ){
     if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }
    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Roomid from DAL_UR_relation where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return -1;
    }
    
    if(res->num_fields != DAL_UR_relation::title_DAL_UR_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return -1;
    }

    return stoi(res->v[0][0]);

}  //Userid  to roomid

int  DB_MYSQL_OFROOM::get_Debatepos_fromUserid  (int uid  ){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }
    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Debate_pos from DAL_UR_relation where Userid = " + to_string(uid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
    
    if(res->OKflag == false){
        cout<<__func__ <<  " 执行sql : " << sql <<endl;
        cout<< __func__ <<" mysql use DebateOL err"<< res->errinfo << endl;
        return -1;
    }
    
    if(res->num_fields != DAL_UR_relation::title_DAL_UR_relation.size() ){
        cout <<__func__ <<  " 找到的列数不符合" <<endl;
        return -1;
    }

    return stoi(res->v[0][0]);
};  //userid   to debatepos

//Roomnum  to roomid
int DB_MYSQL_OFROOM::get_Roomid_fromRoomnum  (string Roomnum  ){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " select Roomid from DAL_Room_Base where Roomnum = " + Roomnum + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
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
}  

//查询密码和盐
string DB_MYSQL_OFROOM::get_RoomSalt     (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }

    DBRES  * res;
    string sql = " select Salt from DAL_Room_Base where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
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
}  
string DB_MYSQL_OFROOM::get_RoomPasswd   (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return "";
    }

    DBRES  * res;
    string sql = " select Passwd from DAL_Room_Base where Roomid = " + to_string(roomid) + ";";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
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
}  

//获取下一次的roomid
int    DB_MYSQL_OFROOM::getnextroomid(){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return -1;
    }

    DBRES  * res;
    string sql = " show create table DAL_Room_Base;";
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql);
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
}             


/* 创建 */
//为避免并发 内部数据库设置触发器
bool DB_MYSQL_OFROOM::AddRoom_t1       (DAL_Room_Base    t1){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = t1.toMap();

    if(DAL_Room_Base::title_DAL_Room_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_Room_Base::title_DAL_Room_Base.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_Room_Base::title_DAL_Room_Base.size()" << DAL_Room_Base::title_DAL_Room_Base.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_Room_Base::title_DAL_Room_Base.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_Room_Base::title_DAL_Room_Base[i])];
        Insertinfo+= '\"';
        if(i!= DAL_Room_Base::title_DAL_Room_Base.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_Room_Base values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFROOM::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
bool DB_MYSQL_OFROOM::AddRoom_t2       (DAL_Room_Extra   t2){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = t2.toMap();

    if(DAL_Room_Extra::title_DAL_Room_Extra.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_Room_Extra::title_DAL_Room_Extra.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_Room_Extra::title_DAL_Room_Extra.size()" << DAL_Room_Extra::title_DAL_Room_Extra.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_Room_Extra::title_DAL_Room_Extra.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_Room_Extra::title_DAL_Room_Extra[i])];
        Insertinfo+= '\"';
        if(i!= DAL_Room_Extra::title_DAL_Room_Extra.size() -1){
            Insertinfo+= ',';
        }
    }
    
    sprintf(outsql ,"Insert DAL_Room_Extra values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFROOM::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
//添加用户房间关系
bool DB_MYSQL_OFROOM::AddURrelation    (DAL_UR_relation urr){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;
    map<string , string > mp = urr.toMap();

    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    if(mp.size() != DAL_UR_relation::title_DAL_UR_relation.size() ){
        cout <<__func__ << " num_fields : " << res->num_fields <<endl;
        cout << __func__<< " DAL_UR_relation::title_DAL_UR_relation.size()" << DAL_UR_relation::title_DAL_UR_relation.size() <<endl;
        cout <<__func__ <<  " MAP不符合" <<endl;
        return false;
    }

    string Insertinfo;
    char outsql[1005];
    for(int i= 0 ;i<DAL_UR_relation::title_DAL_UR_relation.size() ; i++){
        Insertinfo+= '\"';
        Insertinfo += mp[to_string(DAL_UR_relation::title_DAL_UR_relation[i])];
        Insertinfo+= '\"';
        if(i!= DAL_UR_relation::title_DAL_UR_relation.size() -1){
            Insertinfo+= ',';
        }
    }

    sprintf(outsql ,"Insert DAL_UR_relation values(%s);" ,Insertinfo.data() );
    string s_outsql(outsql);
    res = DB_MYSQL_OFROOM::DB_mysql.exec(s_outsql);
    if(res->checkerr(s_outsql) == false ){
        return false;
    }else{
        return true;
    }
}
bool DB_MYSQL_OFROOM::AddRoom (DAL_Room_Base    t1,DAL_Room_Extra   t2,DAL_UR_relation urr){
    //TODO: 原子
    bool flag1 = AddRoom_t1(t1);
    bool flag2 = AddRoom_t2(t2);
    bool flag3 = AddURrelation(urr);
    return flag1&&flag2&&flag3;
}
/* 删除 */
//删除对应房间
bool DB_MYSQL_OFROOM::DelRoom_t1          (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_Room_Base::title_DAL_Room_Base.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;

    string sql1 = "delete from DAL_Room_Base where Roomid = " + to_string(roomid) + ";"; 
    
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}          
//删除对应房间
bool DB_MYSQL_OFROOM::DelRoom_t2          (int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_Room_Extra::title_DAL_Room_Extra.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;

    string sql1 = "delete from DAL_Room_Extra where Roomid = " + to_string(roomid) + ";"; 
    
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}          
//删除uid roomid关系
bool DB_MYSQL_OFROOM::DelURrelation    (int uid , int roomid){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    DBRES  * res;

    if(DAL_UR_relation::title_DAL_UR_relation.size() == 0){
        cout <<__func__ <<  " title 没有初始化" << endl;
        return false;
    }
    bool doflag1 = 0;
    string sql1 = "delete from DAL_UR_relation where Roomid = " + to_string(roomid) + " and " +"Userid ="  + to_string(uid) +";";
    
    res = DB_MYSQL_OFROOM::DB_mysql.exec(sql1);
    doflag1 = res->checkerr(sql1);
    
    return (doflag1);
}


/* 更改 */
//整表更改
bool DB_MYSQL_OFROOM::updata_Room_base       (int roomid , DAL_Room_Base   t){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    //取出原表
    DAL_Room_Base baset = get_Room_base (roomid);
    map<string , string >mp_indb = baset.toMap();

    map<string , string >mp_modify = t.toMap();
    for(int i = 0;i<DAL_Room_Base::title_DAL_Room_Base.size();i++){
        if(mp_modify[DAL_Room_Base::title_DAL_Room_Base[i]] == to_string(INT_DEFAULT)\
         || mp_modify[DAL_Room_Base::title_DAL_Room_Base[i]] == STR_DEFAULT){
            //没被填写
            continue;          
        }else{
            //TODO 检测
            mp_indb[DAL_Room_Base::title_DAL_Room_Base[i]] = mp_modify[DAL_Room_Base::title_DAL_Room_Base[i]];
        }
        
    }
    int flag1 = DelRoom_t1(roomid);
    int flag2 = AddRoom_t1(DAL_Room_Base::ToClass(mp_indb));
    return flag1 && flag2;
};

bool DB_MYSQL_OFROOM::updata_Room_extra      (int roomid , DAL_Room_Extra  t){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    //取出原表
    DAL_Room_Extra baset = get_Room_extra (roomid);
    map<string , string >mp_indb = baset.toMap();

    map<string , string >mp_modify = t.toMap();
    for(int i = 0;i<DAL_Room_Extra::title_DAL_Room_Extra.size();i++){
        if(mp_modify[DAL_Room_Extra::title_DAL_Room_Extra[i]] == to_string(INT_DEFAULT)\
         || mp_modify[DAL_Room_Extra::title_DAL_Room_Extra[i]] == STR_DEFAULT){
            //没被填写
            continue;          
        }else{
            //TODO 检测
            mp_indb[DAL_Room_Extra::title_DAL_Room_Extra[i]] = mp_modify[DAL_Room_Extra::title_DAL_Room_Extra[i]];
        }
        
    }
    int flag1 = DelRoom_t2(roomid);
    int flag2 = AddRoom_t2(DAL_Room_Extra::ToClass(mp_indb));
    return flag1 && flag2;
}
bool DB_MYSQL_OFROOM::updata_RoomURrelation  (int uid    , int roomid , int pos , int newlevel){
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()== false){
        cout <<__func__ <<  " DB_Mysql 没有初始化"<<endl;
        return false;
    }
    //取出原址
    if(to_string(pos) == to_string(INT_DEFAULT)){
        string rets = get_UserinRoom_Debatepos(roomid);
        map<string , string>mp  = JsonstringToMap(rets);
        pos = stoi(mp[to_string(uid)]);
    }
    if(to_string(newlevel) != to_string(INT_DEFAULT)){
        string rets = get_UserinRoom_Debatepos(roomid);
        map<string , string>mp  = JsonstringToMap(rets);
        newlevel = stoi(mp[to_string(uid)]);
    }
    int flag1 = DelURrelation(uid , roomid);
    DAL_UR_relation t;
    t.Userid = uid;
    t.Roomid = roomid;
    t.Debate_pos = pos;
    t.Permissions = newlevel;
    int flag2 = AddURrelation(t);
    return flag1 && flag2;
}  //更改关系

//提供dal类和map的转换方式
//完善tomap函数
//完善toclass
map<string , string> DAL_Room_Base::toMap(){
    map<string , string>mp;
    SettoMap(Roomid)          ;         
    SettoMap(Roomnum)         ;          
    SettoMap(Passwd)          ;         
    SettoMap(Salt)            ;      
    SettoMap(RoomCreatetime)  ;     
    return mp;
}
DAL_Room_Base DAL_Room_Base::ToClass(map<string , string> mp){
    DAL_Room_Base ret;
    SettoClass(Roomid)          ;         
    SettoClass(Roomnum)         ;          
    SettoClass(Passwd)          ;                   
    SettoClass(RoomCreatetime)  ;               
    SettoClass(Salt)            ;       
    return ret;
}

map<string , string> DAL_Room_Extra::toMap(){
    map<string , string>mp;
    SettoMap(Roomid)               ;       
    SettoMap(Roomnum)              ;                 
    SettoMap(Roomname)             ;          
    SettoMap(Signature)            ;              
    SettoMap(Islocking)            ;           
    SettoMap(Debate_posbitmap)     ;          
    SettoMap(Debate_name)          ;  
    return mp;
}

DAL_Room_Extra DAL_Room_Extra::ToClass(map<string , string>mp ){
    DAL_Room_Extra ret;
    SettoClass(Roomid)               ;       
    SettoClass(Roomnum)              ;                 
    SettoClass(Roomname)             ;          
    SettoClass(Signature)            ;              
    SettoClass(Islocking)            ;           
    SettoClass(Debate_posbitmap)     ;          
    SettoClass(Debate_name)          ;  
    return ret;
}

map<string , string> DAL_UR_relation::toMap(){
    map<string , string>mp;
    SettoMap(Userid)               ;       
    SettoMap(Roomid)               ;                 
    SettoMap(Debate_pos)           ;  
    SettoMap(Permissions)          ;            
    return mp;
}

DAL_UR_relation DAL_UR_relation::ToClass(map<string , string>mp ){
    DAL_UR_relation ret;
    SettoClass(Userid)               ;       
    SettoClass(Roomid)               ;                 
    SettoClass(Debate_pos)           ;   
    SettoClass(Permissions)          ;        
    return ret;
}
