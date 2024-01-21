// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Room.h"
#include "../../conf.hh"
#include "../dal/dal_room.h"
#include "../dal/dal_roomconfig.h"
#include "../../../pkg/JsonChange/jsonchange.h"
#include "../../../pkg/JWT/jwt.h"
#include "../../../pkg/Openssl/openssl.h"
#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

#define SetAclevel(mpname , x ) mpname[#x]
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
    
class RoomHandler : virtual public RoomIf {
 public:
  map<string, int>mp_Room_get_Room_base_level  ;
  map<string, int>mp_Room_get_Room_extra_level  ;
  map<string, int>mp_Room_Modify_Room_base_level  ;
  map<string, int>mp_Room_Modify_Room_extra_level;
 public:
  RoomHandler() {
    // Your initialization goes here
    //初始化mysql
        SetAclevel(mp_Room_get_Room_base_level , Roomid    )         = level_black_ur;   
        SetAclevel(mp_Room_get_Room_base_level , Roomnum  )          = level_black_ur;     
        SetAclevel(mp_Room_get_Room_base_level , Passwd  )           = level_root_ur;     
        SetAclevel(mp_Room_get_Room_base_level , RoomCreatetime)     = level_inroom_ur;
        SetAclevel(mp_Room_get_Room_base_level , Salt )              = level_root_ur;      

        SetAclevel(mp_Room_get_Room_extra_level , Roomid    )        = level_black_ur;
        SetAclevel(mp_Room_get_Room_extra_level , Roomnum  )         = level_notinroom_ur;          
        SetAclevel(mp_Room_get_Room_extra_level , Roomname         ) = level_notinroom_ur;   
        SetAclevel(mp_Room_get_Room_extra_level , Signature     )    = level_notinroom_ur;       
        SetAclevel(mp_Room_get_Room_extra_level , Islocking     )    = level_notinroom_ur;    
        SetAclevel(mp_Room_get_Room_extra_level , Debate_posbitmap)  = level_notinroom_ur;   
        SetAclevel(mp_Room_get_Room_extra_level , Debate_name   )    = level_notinroom_ur;   
        
        
        SetAclevel(mp_Room_Modify_Room_base_level , Roomid    )      = level_never_ur;   
        SetAclevel(mp_Room_Modify_Room_base_level , Roomnum  )       = level_never_ur;     
        SetAclevel(mp_Room_Modify_Room_base_level , Passwd  )        = level_root_ur;     
        SetAclevel(mp_Room_Modify_Room_base_level , RoomCreatetime)  = level_never_ur;
        SetAclevel(mp_Room_Modify_Room_base_level , Salt )           = level_never_ur;      
        
        
        SetAclevel(mp_Room_Modify_Room_extra_level , Roomid          )  = level_never_ur;
        SetAclevel(mp_Room_Modify_Room_extra_level , Roomnum  )         = level_never_ur;          
        SetAclevel(mp_Room_Modify_Room_extra_level , Roomname         ) = level_root_ur;   
        SetAclevel(mp_Room_Modify_Room_extra_level , Signature     )    = level_root_ur;       
        SetAclevel(mp_Room_Modify_Room_extra_level , Islocking        ) = level_root_ur;    
        SetAclevel(mp_Room_Modify_Room_extra_level , Debate_posbitmap)  = level_never_ur;   
        SetAclevel(mp_Room_Modify_Room_extra_level , Debate_name   )    = level_root_ur;   
    
    DB_MYSQL_OFROOM::DB_mysql.DB_init(Room_host, Room_user, Room_passwd, Room_db, Room_port);  
    if(DB_MYSQL_OFROOM::DB_mysql.isinit()){
      if(DB_MYSQL_OFROOM::init_title() == false){
        cout << "[x]Room服务没有开启 - title初始化有误 " << endl;
      }else{
        cout << "[*]Room服务开启"<<endl;
      }
    }else{
      cout << "[x]Room服务没有开启 - 数据库连接出现问题 " << endl;
    }
  }

  void Room_ChangeDebatePos(Room_ChangeDebatePos_RecvInfo& _return, const Room_ChangeDebatePos_SendInfo& info) {
     //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "ROOMrServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "ROOMServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取uid
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    int uidA = stoi(jwt_payload_mp["aud"]);

    bool err;
    //获取在的房间
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromUserid(uidA);
    if(roomid == INT_DEFAULT){
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //获取旧的位置
    int opos = DB_MYSQL_OFROOM::get_Debatepos_fromUserid(uidA);
    int npos = info.Debate_pos;
    if(opos == INT_DEFAULT){
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(npos == INT_DEFAULT){
      _return.status = ROOM_ERR_REQINFO;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //修改ur数据
    err = DB_MYSQL_OFROOM::updata_RoomURrelation(uidA, roomid, npos, INT_DEFAULT);
    if(!err){
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //设置位图
    DAL_Room_Extra t;
    int nowbitmap = t.Debate_posbitmap;
    if((nowbitmap &( 1<<(8-opos)))== 0) {
      _return.status = ROOM_Changepos_Havepeo;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if((nowbitmap &( 1<<(8-npos)))!= 0) {
      _return.status = ROOM_Changepos_Havepeo;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    nowbitmap ^= ( 1<<(8-opos));
    nowbitmap ^= ( 1<<(8-npos));
    t.Debate_posbitmap = nowbitmap;

    err = DB_MYSQL_OFROOM::updata_Room_extra(roomid, t);
    if(!err){
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_ChangeDebatePos_RecvInfo_TypeId;
    printf("Room_ChangePasswd\n");
    return;
  }

  void Room_ChangeExtraInfo(Room_ChangeExtraInfo_RecvInfo& _return, const Room_ChangeExtraInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "RoomServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "RoomServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取更改信息
    map<string , string >modifyinfo = JsonstringToMap(info.info);
    //获取用户在房间里面的权限
    int uidA = stoi(jwt_payload_mp["aud"]);

    if(modifyinfo.find("Roomid") == modifyinfo.end()){
      _return.status = ROOM_ERR_REQINFO;
      _return.sendtime = info.sendtime;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      return;
    }
    int roomid = stoi(modifyinfo["Roomid"]);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    string relation_str = DB_MYSQL_OFROOM::get_UserinRoom_permissions(roomid);
    int truelevel = -1;
    int aimlevel = level_notinroom_ur;
    map<string , string> mp = JsonstringToMap(relation_str);
    if(mp.find(to_string(uidA)) == mp.end()){
      aimlevel = level_notinroom_ur;
    }else{
      aimlevel = stoi(mp[to_string(uidA)]);
    }

    /* 第二步 查看数据内容 确定访问等级 */
    for(auto &it : modifyinfo){
      if(mp_Room_Modify_Room_extra_level.find(it.first) != mp_Room_Modify_Room_extra_level.end()){
        aimlevel = min(aimlevel , mp_Room_Modify_Room_extra_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }

    if(aimlevel == -1){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = ROOM_LOWACLevel;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_Room_Extra dre = DAL_Room_Extra::ToClass(modifyinfo);
    bool err = DB_MYSQL_OFROOM::updata_Room_extra(roomid,dre);
    if(!err){
      _return.status=ROOM_DAL_ERR;
      _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    _return.status = ROOM_ACTION_OK;
    _return.sendtime = info.sendtime;
    _return.type = Room_ChangeExtraInfo_RecvInfo_TypeId;
    printf("Room_ChangeExtraInfo\n");
    return;

  }

  void Room_ChangePasswd(Room_ChangePasswd_RecvInfo& _return, const Room_ChangePasswd_SendInfo& info) {
     //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "ROOMrServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "ROOMServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_ChangePasswd_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //改变密码
    //获取uid
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    int uidA = stoi(jwt_payload_mp["aud"]);

    //获取目标房间号
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_ChangePasswd_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //TODO;黑名单

    //对比密码
    //取盐 取密码
    DAL_Room_Base rb = DB_MYSQL_OFROOM::get_Room_base(roomid);
    if(sha256(info.Opasswd+ rb.Salt) != rb.Passwd){
      //不正确
      _return.status = ROOM_JOINROOM_ERRPASSWD; 
      _return.sendtime = info.sendtime;
      _return.type = Room_ChangePasswd_RecvInfo_TypeId;
      return;
    }
    //新的密码
    DAL_Room_Base t;
    t.Passwd = sha256(info.Opasswd+ rb.Salt);
    bool err = DB_MYSQL_OFROOM::updata_Room_base(roomid,  t);
    if(!err){
      _return.sendtime = info.sendtime;
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_ChangePasswd_RecvInfo_TypeId;
      return;
    }
    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_ChangePasswd_RecvInfo_TypeId;
    printf("Room_ChangePasswd\n");
    return;

    

  
  }

  void Room_Exitroom(Room_Exitroom_RecvInfo& _return, const Room_Exitroom_SendInfo& info) {
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "ROOMrServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "ROOMServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_Exitroom_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取uid
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    int uidA = stoi(jwt_payload_mp["aud"]);

    //获取目标房间号
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_Exitroom_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    bool err = false;
    //删除 - t3
    //获取列表
    string pre = DB_MYSQL_OFROOM::get_UserinRoom_permissions(roomid);
    if(pre == STR_DEFAULT){
      _return.sendtime = info.sendtime;
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_Exitroom_RecvInfo_TypeId;
      return;
    }
    map<string, string>mp_pre = JsonstringToMap(pre);

    err = DB_MYSQL_OFROOM::DelURrelation(uidA, roomid);
    if(!err){
      _return.sendtime = info.sendtime;
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_Exitroom_RecvInfo_TypeId;
      return;
    }

    //如果是房主要转移权力
    if(mp_pre.size() == 1){
      //关闭房间 
    }else{
      if(mp_pre[to_string(uidA)] == "1"){//是房主
        //移交权力
        int aim_peo = INT_DEFAULT;
        for(auto it : mp_pre){
          if(it.first != to_string(uidA)){
              aim_peo = stoi(it.first);
          }
        }
        if(aim_peo == INT_DEFAULT){
          _return.sendtime = info.sendtime;
          _return.status = ROOM_DAL_ERR;
          _return.type = Room_Exitroom_RecvInfo_TypeId;
          return;
        }else{
          err = DB_MYSQL_OFROOM::updata_RoomURrelation(aim_peo , roomid , INT_DEFAULT , 1);
          if(!err){
            _return.sendtime = info.sendtime;
            _return.status = ROOM_DAL_ERR;
            _return.type = Room_Exitroom_RecvInfo_TypeId;
            return;
          }
        }
      }
    }



    //修改位图
    DAL_Room_Extra t;
    int debate_pos;
    t.Debate_posbitmap =( t.Debate_posbitmap ^ (1<<(8-debate_pos)) );
    err = DB_MYSQL_OFROOM::updata_Room_extra(roomid, t);
    if(!err){
      _return.sendtime = info.sendtime;
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_Exitroom_RecvInfo_TypeId;
      return;
    }
    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_Exitroom_RecvInfo_TypeId;
    return;


    printf("Room_Exitroom\n");
  }

  void Room_Joinroom(Room_Joinroom_RecvInfo& _return, const Room_Joinroom_SendInfo& info) {
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "ROOMServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "ROOMServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_Joinroom_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    

    //获取uid
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    int uidA = stoi(jwt_payload_mp["aud"]);

    //获取目标房间号
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_GetURrelation_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //TODO;黑名单

    //对比密码
    //取盐 取密码
    DAL_Room_Base rb = DB_MYSQL_OFROOM::get_Room_base(roomid);
    if(sha256(info.passwd + rb.Salt) != rb.Passwd){
      //不正确
      _return.status = ROOM_JOINROOM_ERRPASSWD; 
      _return.sendtime = info.sendtime;
      _return.type = Room_Joinroom_RecvInfo_TypeId;
      return;
    }

    //添加信息
    DAL_UR_relation urr;
    urr.Userid = uidA;
    urr.Roomid = roomid;
    urr.Debate_pos = info.Debate_pos;
    urr.Permissions = 0;
    DB_MYSQL_OFROOM::AddURrelation(urr);


    //修改位图
    DAL_Room_Extra t;
    t.Debate_posbitmap =( t.Debate_posbitmap | (1<<(8-info.Debate_pos)));
    bool err = DB_MYSQL_OFROOM::updata_Room_extra(roomid, t);
    if(!err){
      _return.sendtime = info.sendtime;
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_Joinroom_RecvInfo_TypeId;
      return;
    }
    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_Joinroom_RecvInfo_TypeId;
    return;


    printf("Room_Joinroom\n");
  }

  void Room_Create(Room_Create_RecvInfo& _return, const Room_Create_SendInfo& info) {
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "RoomServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "RoomServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_Create_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
     //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    
    //检测各个字段的合法性
    //正则匹配
    std::regex reg_Roomnum("^[1-9]\\d{5,12}$");//6-13个数字
    if(regex_match(info.Roomnum,reg_Roomnum) != true){
      _return.status = ROOM_ERR_REQINFO;
      _return.type = Room_Create_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //找重复的
    if(DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.Roomnum)!= INT_DEFAULT){
      _return.status = ROOM_Create_Havethisnum;
      _return.type = Room_Create_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取用户在房间里面的权限
    int uidA = stoi(jwt_payload_mp["aud"]);
    
    time_t timenow;
    time(&timenow);
    srand(time(0));
    int roomid = DB_MYSQL_OFROOM::getnextroomid();

    DAL_Room_Base t1;
    DAL_Room_Extra t2;
    DAL_UR_relation t3;
    
    if(roomid == -1 ){
      _return.status = ROOM_DAL_ERR;
      _return.type = Room_Create_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    t1.Roomid = roomid;
    t1.Roomnum = info.Roomnum;
    t1.RoomCreatetime = std::to_string((int64_t)timenow);
    if(info.Islocking == false)
      t1.Passwd = "";
    else 
      t1.Passwd = info.passwd;
    t1.Salt = sha256(Base64Encode(to_string(rand())));

    t2.Roomid = roomid;
    t2.Roomnum = info.Roomnum;
    t2.Roomname = info.Roomname;
    t2.Signature = "还没有介绍哦";
    t2.Islocking = info.Islocking;
    t2.Debate_posbitmap = 1<<(8-info.Debate_pos);
    t2.Debate_name = "暂无";

    t3.Userid = uidA;
    t3.Roomid = roomid;
    t3.Debate_pos = info.Debate_pos;
    t3.Permissions = 1;

    int err = DB_MYSQL_OFROOM::AddRoom(t1,t2,t3);
    if(!err){
      _return.status = ROOM_Create_Havethisnum;
      _return.type = Room_Create_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_Create_RecvInfo_TypeId;
    _return.sendtime = info.sendtime;
    printf("Room_Create\n");
    return;
  }

  void Room_GetURrelation(Room_GetURrelation_RecvInfo& _return, const Room_GetURrelation_SendInfo& info) {
     //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "RoomServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "RoomServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = Room_GetURrelation_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.Aim_Roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_GetURrelation_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    string res_pos = DB_MYSQL_OFROOM::get_UserinRoom_Debatepos(roomid);
    if(res_pos == STR_DEFAULT){
      _return.status= ROOM_NoSuchRoomInfo;
      _return.type = Room_GetURrelation_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    string res_pre = DB_MYSQL_OFROOM::get_UserinRoom_permissions(roomid);
    if(res_pre == STR_DEFAULT){
      _return.status= ROOM_NoSuchRoomInfo;
      _return.type = Room_GetURrelation_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    _return.status = ROOM_ACTION_OK;
    _return.sendtime = info.sendtime;
    _return.type = Room_GetURrelation_RecvInfo_TypeId;
    _return.info_UR_per = res_pre;
    _return.info_UR_pos = res_pos;
    printf("Room_GetURrelation\n");
    return;
  }

  void Room_GetExInfo(Room_GetExInfo_RecvInfo& _return, const Room_GetExInfo_SendInfo& info) {
    
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "RoomServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }
     //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "RoomServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取用户在房间里面的权限
    int uidA = stoi(jwt_payload_mp["aud"]);
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.Aim_Roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    string relation_str = DB_MYSQL_OFROOM::get_UserinRoom_permissions(roomid);
    int truelevel = -1;
    int aimlevel = level_notinroom_ur;
    map<string , string> mp = JsonstringToMap(relation_str);
    if(mp.find(to_string(uidA)) == mp.end()){
      aimlevel = level_notinroom_ur;
    }else{
      aimlevel = stoi(mp[to_string(uidA)]);
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.info);
    for(auto &it : info_mp){
      if(mp_Room_get_Room_extra_level.find(it.first) != mp_Room_get_Room_extra_level.end()){
        aimlevel = min(aimlevel , mp_Room_get_Room_extra_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = ROOM_LOWACLevel;
      _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_Room_Extra dal_room_extra = DB_MYSQL_OFROOM::get_Room_extra(uidA);
    map<string , string >ret ;
    map<string , string> dal_room_extra_mp = dal_room_extra.toMap();
    for(auto &it : info_mp){
      //如何取出对应名字的元素
      ret[it.first] = dal_room_extra_mp[it.first];
    }

    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
    _return.info = MapToJsonstring(ret);
    cout << "RoomServer : Room_GetBaseInfo Success!\n" <<endl;
    return;

    printf("Room_GetExInfo\n");
  }

  void Room_GetBaseInfo(Room_GetBaseInfo_RecvInfo& _return, const Room_GetBaseInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "RoomServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "RoomServer : 超时的jwt" <<endl;
      _return.status = ROOM_TIMEOUT_JWT;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取用户在房间里面的权限
    int uidA = stoi(jwt_payload_mp["aud"]);
    //获取房间id 
    int roomid = DB_MYSQL_OFROOM::get_Roomid_fromRoomnum(info.Aim_Roomnum);
    if(roomid == INT_DEFAULT){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    string relation_str = DB_MYSQL_OFROOM::get_UserinRoom_permissions(roomid);
    int truelevel = -1;
    int aimlevel = level_notinroom_ur;
    map<string , string> mp = JsonstringToMap(relation_str);
    if(mp.find(to_string(uidA)) == mp.end()){
      aimlevel = level_notinroom_ur;
    }else{
      aimlevel = stoi(mp[to_string(uidA)]);
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.info);
    for(auto &it : info_mp){
      if(mp_Room_get_Room_base_level.find(it.first) != mp_Room_get_Room_base_level.end()){
        aimlevel = min(aimlevel , mp_Room_get_Room_base_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=ROOM_ERR_REQINFO;
      _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = ROOM_LOWACLevel;
      _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_Room_Base dal_room_base = DB_MYSQL_OFROOM::get_Room_base(uidA);
    map<string , string >ret ;
    map<string , string> dal_room_base_mp = dal_room_base.toMap();
    for(auto &it : info_mp){
      //如何取出对应名字的元素
      ret[it.first] = dal_room_base_mp[it.first];
    }

    _return.sendtime = info.sendtime;
    _return.status = ROOM_ACTION_OK;
    _return.type = Room_GetBaseInfo_RecvInfo_TypeId;
    _return.info = MapToJsonstring(ret);
    cout << "RoomServer : Room_GetBaseInfo Success!\n" <<endl;
    return;

    printf("Room_GetBaseInfo\n");
  }

};

int main(int argc, char **argv) {
  int port = ROOM_PORT;
  ::std::shared_ptr<RoomHandler> handler(new RoomHandler());
  ::std::shared_ptr<TProcessor> processor(new RoomProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

