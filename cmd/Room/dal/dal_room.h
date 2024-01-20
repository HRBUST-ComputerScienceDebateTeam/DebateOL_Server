#include <bits/stdc++.h>
#include <string>
using namespace std;

std::string to_string(string x){return x;};
#define SettoMap(x) mp[#x] = to_string(this->x)

//DB中Room base的结构体 - 记录房间本身的基本信息 id 密码 创建时间
typedef struct DAL_Room_Base{
    int     Roomid;                //Roomid
    int     Roomnum;               //Roomnum
    string  Passwd;                //Room密码
    string  RoomCreatetime;        //Room注册时间
    string  Salt;                  //盐 sha256
    map<string , string> toMap();
}DAL_Room_Base;

//DB中Room Extra的结构体 - 对外展示的部分
typedef struct DAL_Room_Extra{
    int     Roomid;             //Roomid
    int     Roomnum;            //Roomnum
    string  Roomname;           //Room名
    string  Signature;          //Room简介
    int     Islocking;          //是否上锁
    int     Debate_posbitmap;   //位图的方式记录辩位情况
    string  Debate_name;        //辩题名称
    map<string , string> toMap();
}DAL_Room_Extra;

//DB中user - Room关系的结构体
typedef struct DAL_UR_relation{
    int     Userid;              //用户id
    int     Roomid;              //Roomid
    int     Debate_pos;          //辩位
    int     Permissions;         //权限等级
    map<string , string> toMap();
}DAL_UR_relation;


//--function
/* 连接 */
void connect_tomysql();
void connect_toredis();


/* 查询 */
DAL_Room_Base   get_Room_base   (int roomid);        //通过roomid查表
DAL_Room_Extra  get_Room_sextra (int roomid);

string get_UserinRoom_Debatepos    (int roomid);    //查询Room中都有哪些用户 - 序列化的map (user - 辩位)
string get_UserinRoom_permissions  (int roomid);    //查询Room中都有哪些用户 - 序列化的map (user - 权限)
int    get_RootOfRoom              (int roomid);    //获取房间的管理员用户id

int    get_Roomid_fromRoomnum  (string Roomnum  );  //Roomnum  to roomid

string get_RoomSalt     (int uid);  //查询密码和盐
string get_RoomPasswd   (int uid);  
int    getnextroomid();             //获取下一次的roomid


/* 创建 */
bool AddRoom       (DAL_Room_Base    t1);//为避免并发 内部数据库设置触发器
bool AddURrelation (DAL_UR_relation urr);//添加用户房间关系

/* 删除 */
bool DelRoom          (int roomid);          //删除对应房间
bool DelURrelation    (int uid , int roomid);//删除uid roomid关系


/* 更改 */
bool updata_Room_base       (int roomid , DAL_Room_Base   t); //整表更改
bool updata_Room_extra      (int roomid , DAL_Room_Extra  t);
bool updata_RoomURrelation  (int uid    , int roomid , int pos , int newlevel);  //更改关系


