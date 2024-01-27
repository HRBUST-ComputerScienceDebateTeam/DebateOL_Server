#include "../../../pkg/DB/DB_MYSQL.h"
#include "../../../pkg/JsonChange/jsonchange.h"
#include "dal_roomconfig.h"
#include <bits/stdc++.h>
#include <string>
using namespace std;

#define SettoMap( x ) mp[ #x ] = to_string( this->x )
#define SettoClass( x ) SettoClass_getval( ret.x, mp[ #x ] )
#define ToBeSQLString( x ) #x
std::string to_string( string x );
void        SettoClass_getval( int& a, string& s );
void        SettoClass_getval( string& a, string& s );

// DB中Room base的结构体 - 记录房间本身的基本信息 id 密码 创建时间
typedef class DAL_Room_Base {
public:
    int    Roomid;          // Roomid
    string Roomnum;         // Roomnum
    string Passwd;          // Room密码
    string RoomCreatetime;  // Room注册时间
    string Salt;            //盐 sha256
public:
    map< string, string > toMap();
    static DAL_Room_Base  ToClass( map< string, string > );

public:
    DAL_Room_Base();

public:
    static vector< string > title_DAL_Room_Base;
} DAL_Room_Base;

// DB中Room Extra的结构体 - 对外展示的部分
typedef class DAL_Room_Extra {
public:
    int    Roomid;            // Roomid
    string Roomnum;           // Roomnum
    string Roomname;          // Room名
    string Signature;         // Room简介
    int    Islocking;         //是否上锁
    int    Debate_posbitmap;  //位图的方式记录辩位情况
    string Debate_name;       //辩题名称
public:
    map< string, string > toMap();
    static DAL_Room_Extra ToClass( map< string, string > );

public:
    DAL_Room_Extra();

public:
    static vector< string > title_DAL_Room_Extra;
} DAL_Room_Extra;

// DB中user - Room关系的结构体
typedef class DAL_UR_relation {
public:
    int Userid;       //用户id
    int Roomid;       // Roomid
    int Debate_pos;   //辩位
    int Permissions;  //权限等级 0 1
public:
    map< string, string >  toMap();
    static DAL_UR_relation ToClass( map< string, string > );

public:
    DAL_UR_relation();

public:
    static vector< string > title_DAL_UR_relation;
} DAL_UR_relation;

//--function
/* 连接 */
class DB_MYSQL_OFROOM : public DB_MYSQL {
public:
    static bool init_title();
    static bool connect_tomysql();
    static bool connect_toredis();

    /* 查询 */
    static DAL_Room_Base  get_Room_base( int roomid );  //通过roomid查表
    static DAL_Room_Extra get_Room_extra( int roomid );

    static string get_UserinRoom_Debatepos( int roomid );    //查询Room中都有哪些用户 - 序列化的map (user - 辩位)
    static string get_UserinRoom_permissions( int roomid );  //查询Room中都有哪些用户 - 序列化的map (user - 权限)
    static int    get_RootOfRoom( int roomid );              //获取房间的管理员用户id

    static int get_Roomid_fromRoomnum( string Roomnum );  // Roomnum  to roomid
    static int get_Roomid_fromUserid( int uid );          // userid  to roomid
    static int get_Debatepos_fromUserid( int uid );       // userid   to debatepos

    static string get_RoomSalt( int roomid );  //查询密码和盐
    static string get_RoomPasswd( int roomid );
    static int    getnextroomid();  //获取下一次的roomid

    /* 创建 */
    static bool AddRoom( DAL_Room_Base t1, DAL_Room_Extra t2, DAL_UR_relation urr );
    static bool AddRoom_t1( DAL_Room_Base t1 );        //为避免并发 内部数据库设置触发器
    static bool AddRoom_t2( DAL_Room_Extra t2 );       //为避免并发 内部数据库设置触发器
    static bool AddURrelation( DAL_UR_relation urr );  //添加用户房间关系

    /* 删除 */
    static bool DelRoom_t1( int roomid );              //删除对应房间
    static bool DelRoom_t2( int roomid );              //删除对应房间
    static bool DelURrelation( int uid, int roomid );  //删除uid roomid关系

    /* 更改 */
    static bool updata_Room_base( int roomid, DAL_Room_Base t );  //整表更改
    static bool updata_Room_extra( int roomid, DAL_Room_Extra t );
    static bool updata_RoomURrelation( int uid, int roomid, int pos, int newlevel );  //更改关系
public:
    static DB_MYSQL DB_mysql;
};
