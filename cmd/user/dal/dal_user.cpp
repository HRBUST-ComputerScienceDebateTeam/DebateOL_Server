//提供访问数据库的方法
#include "dal_user.h"
#include "dal_userconfig.h"
#include <bits/stdc++.h>
#include <mysql/mysql.h>

void SettoClass_getval(int &a    , string &s){a = stoi(s);}
void SettoClass_getval(string& a , string &s){a =  s;};
std::string to_string(string x){return x;};
//建立连接 - 数据库(TODO:redis)

//提供交互函数

//--function
/* 连接 */
const char * User_host   = "127.0.0.1";
const char * User_user   = "DebateOL_userservice";
const char * User_passwd = "HRBUST_CSDT";
const char * User_db     = "DebateOL";
unsigned int User_port   = 3306;


void connect_tomysql(){
    MYSQL * mysql;
    mysql = mysql_init(NULL);
    if(mysql==nullptr)
    {
        cout<<"Error:"<<mysql_error(mysql);
        exit(1);
    }
    //MYSQL *mysql_real_connect(MYSQL *mysql, \
    const char *host, const char *user, const char *passwd, \
    const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
    mysql = mysql_real_connect(mysql ,User_host, User_user ,  User_passwd ,User_db,User_port , NULL , 0);
    if(mysql==nullptr)
    {
        cout<<"Error:"<<mysql_error(mysql);
        exit(1);
    }
}
void connect_toredis(){};


/* 查询 */
DAL_User_Base   get_user_base  (int uid){}; //通过uid查表
DAL_User_Extra  get_user_extra (int uid){};
DAL_User_Social get_user_social(int uid){};
DAL_UU_relation get_uulevel    (int uidA , int uidB){}; //查询用户关系

int get_userid_fromUsernum  (string Usernum  ){};//Usernum  to uid
int get_userid_fromTel      (string Tel      ){};//Tel      to uid
int get_userid_fromUsername (string Username ){};//Username to uid

string get_UserLasttime (int uid){};  //查询上一次在线时间
string get_UserSalt     (int uid){};  //查询密码和盐
string get_UserPasswd   (int uid){};  
int getnextuid(){};//获取下一次的uid

string get_UUrelation  (int uid){};

/* 创建 */
bool AddUser    (DAL_User_Base t1){};//为避免并发 内部数据库设置触发器
bool AddUUlevel (DAL_UU_relation uulevel){};

/* 删除 */
bool DelUser(int uid){};
bool DelUUlevel (int uidA , int uidB){};


/* 更改 */
bool updata_user_base    (int uid , DAL_User_Base   t){}; //整表更改
bool updata_user_extra   (int uid , DAL_User_Extra  t){};
bool updata_user_social  (int uid , DAL_User_Social t){};
bool updata_UserLasttime (int uid , string s){};  //更改在线时间
bool updata_UserUUlevel  (int uidA , int uidB , int newlevel){};  //更改关系






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
