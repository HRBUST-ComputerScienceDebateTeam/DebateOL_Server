#include <bits/stdc++.h>
#include <string>
using namespace std;

std::string to_string(string x);
#define SettoMap(x) mp[#x] = to_string(this->x)
#define SettoClass(x)  SettoClass_getval(ret.x , mp[#x])
void SettoClass_getval(int &a    , string &s);
void SettoClass_getval(string& a , string &s);

//DB中用户base的结构体
typedef class DAL_User_Base{
public:
    int     Userid;             //用户id
    string  Usernum;            //用户注册号码
    string  Passwd;             //用户密码
    string  Tel;                //用户电话号
    string  UserRegtime;        //用户注册时间
    string  UserLasttime;       //用户最近登陆时间 - 0 现在在线
    string  Salt;               //盐 sha256
public:
    map<string , string> toMap();
    static DAL_User_Base ToClass(map<string , string> );
}DAL_User_Base;

//DB中用户social的结构体
typedef class DAL_User_Social{
public:
    int     Userid;             //用户id
    string  Username;           //用户名
    string  Headshot;           //用户头像
    int     Sex;                //用户性别
    string  Signature;          //用户个性签名
    string  Contact;            //用户联系方式
public:
    map<string , string> toMap();
    static DAL_User_Social ToClass(map<string , string> );
}DAL_User_Social;


//DB中用户extra的结构体
typedef class DAL_User_Extra{
public:
    int     Userid;             // 用户id
    int     IntentionToArgue;   // 意向辩位
    string  MatcheNum;          // 比赛次数
    string  BestPlayerNum;      // 最佳辩手次数
    int     VectoryNum;         // 胜利次数
    int     OnePosNum;          // 各个辩位场次
    int     TwoPosNum;
    int     ThreePosNum;
    int     FourPosNum;
public:
    map<string , string> toMap();
    static DAL_User_Extra ToClass(map<string , string> );
}DAL_User_Extra;

//DB中用户关系的结构体
typedef class DAL_UU_relation{
public:
    int     UseridA;             //用户idA
    int     UseridB;             //用户idB
    int     UULevel;             //用户AB 之间的关系
public:
    map<string , string> toMap();
    static DAL_UU_relation ToClass(map<string , string> );
}DAL_UU_relation;



//--function
/* 连接 */
void connect_tomysql();
void connect_toredis();


/* 查询 */
DAL_User_Base   get_user_base  (int uid); //通过uid查表
DAL_User_Extra  get_user_extra (int uid);
DAL_User_Social get_user_social(int uid);
DAL_UU_relation get_uulevel    (int uidA , int uidB); //查询用户关系

int get_userid_fromUsernum  (string Usernum  );//Usernum  to uid
int get_userid_fromTel      (string Tel      );//Tel      to uid
int get_userid_fromUsername (string Username );//Username to uid

string get_UserLasttime (int uid);  //查询上一次在线时间
string get_UserSalt     (int uid);  //查询密码和盐
string get_UserPasswd   (int uid);  
int getnextuid();//获取下一次的uid

string get_UUrelation  (int uid);

/* 创建 */
bool AddUser    (DAL_User_Base t1);//为避免并发 内部数据库设置触发器
bool AddUUlevel (DAL_UU_relation uulevel);

/* 删除 */
bool DelUser(int uid);
bool DelUUlevel (int uidA , int uidB);


/* 更改 */
bool updata_user_base    (int uid , DAL_User_Base   t); //整表更改
bool updata_user_extra   (int uid , DAL_User_Extra  t);
bool updata_user_social  (int uid , DAL_User_Social t);
bool updata_UserLasttime (int uid , string s);  //更改在线时间
bool updata_UserUUlevel  (int uidA , int uidB , int newlevel);  //更改关系


