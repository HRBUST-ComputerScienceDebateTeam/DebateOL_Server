// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "User.h"
#include "../../conf.hh"
#include "../dal/dal_user.h"
#include "../dal/dal_userconfig.h"
#include "../../../pkg/JsonChange/jsonchange.h"
#include "../../../pkg/JWT/jwt.h"
#include "../../../pkg/Openssl/openssl.h"
#include "../dal/dal_userconfig.h"
#include <bits/types/time_t.h>
#include <cstdint>
#include <mysql/mysql.h>
#include <regex>
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

class UserHandler : virtual public UserIf {
 public:
  map<string, int>mp_User_GetBaseInfo_level  ;
  map<string, int>mp_User_GetSocialInfo_level;
  map<string, int>mp_User_GetExInfo_level    ;

  map<string, int>mp_User_ModifyBaseInfo_level  ;
  map<string, int>mp_User_ModifySocialInfo_level;
  map<string, int>mp_User_ModifyExInfo_level    ;

  void AcLevel_Init_user(){ // Ac 等级设定 
    SetAclevel(mp_User_GetBaseInfo_level ,Userid)         = level_black_uu;        
    SetAclevel(mp_User_GetBaseInfo_level ,Usernum)        = level_stranger_uu;         
    SetAclevel(mp_User_GetBaseInfo_level ,Passwd)         = level_self_uu;        
    SetAclevel(mp_User_GetBaseInfo_level ,Tel)            = level_self_uu;     
    SetAclevel(mp_User_GetBaseInfo_level ,UserRegtime)    = level_stranger_uu;             
    SetAclevel(mp_User_GetBaseInfo_level ,UserLasttime)   = level_friend_uu;              
    SetAclevel(mp_User_GetBaseInfo_level ,Salt)           = level_self_uu; 
  
    SetAclevel(mp_User_GetSocialInfo_level , Userid)      = level_black_uu;                         
    SetAclevel(mp_User_GetSocialInfo_level , Username)    = level_stranger_uu;                           
    SetAclevel(mp_User_GetSocialInfo_level , Headshot)    = level_stranger_uu;                           
    SetAclevel(mp_User_GetSocialInfo_level , Sex)         = level_stranger_uu;                      
    SetAclevel(mp_User_GetSocialInfo_level , Signature)   = level_stranger_uu;                            
    SetAclevel(mp_User_GetSocialInfo_level , Contact)     = level_friend_uu;

    SetAclevel(mp_User_GetExInfo_level ,Userid)           = level_black_uu;         
    SetAclevel(mp_User_GetExInfo_level ,IntentionToArgue) = level_stranger_uu;                   
    SetAclevel(mp_User_GetExInfo_level ,MatcheNum)        = level_stranger_uu;            
    SetAclevel(mp_User_GetExInfo_level ,BestPlayerNum)    = level_follow_uu;                
    SetAclevel(mp_User_GetExInfo_level ,VectoryNum)       = level_follow_uu;             
    SetAclevel(mp_User_GetExInfo_level ,OnePosNum)        = level_self_uu;            
    SetAclevel(mp_User_GetExInfo_level ,TwoPosNum)        = level_self_uu;            
    SetAclevel(mp_User_GetExInfo_level ,ThreePosNum)      = level_self_uu;              
    SetAclevel(mp_User_GetExInfo_level ,FourPosNum)       = level_self_uu;             

    SetAclevel(mp_User_ModifyBaseInfo_level ,Userid)         = level_never_uu;        
    SetAclevel(mp_User_ModifyBaseInfo_level ,Usernum)        = level_never_uu;         
    SetAclevel(mp_User_ModifyBaseInfo_level ,Passwd)         = level_self_uu;        
    SetAclevel(mp_User_ModifyBaseInfo_level ,Tel)            = level_self_uu;     
    SetAclevel(mp_User_ModifyBaseInfo_level ,UserRegtime)    = level_never_uu;             
    SetAclevel(mp_User_ModifyBaseInfo_level ,UserLasttime)   = level_never_uu;              
    SetAclevel(mp_User_ModifyBaseInfo_level ,Salt)           = level_never_uu; 
  
    SetAclevel(mp_User_ModifySocialInfo_level , Userid)      = level_never_uu;                         
    SetAclevel(mp_User_ModifySocialInfo_level , Username)    = level_self_uu;                           
    SetAclevel(mp_User_ModifySocialInfo_level , Headshot)    = level_self_uu;                           
    SetAclevel(mp_User_ModifySocialInfo_level , Sex)         = level_self_uu;                      
    SetAclevel(mp_User_ModifySocialInfo_level , Signature)   = level_self_uu;                            
    SetAclevel(mp_User_ModifySocialInfo_level , Contact)     = level_self_uu;

    SetAclevel(mp_User_ModifyExInfo_level ,Userid)           = level_never_uu;         
    SetAclevel(mp_User_ModifyExInfo_level ,IntentionToArgue) = level_self_uu;                   
    SetAclevel(mp_User_ModifyExInfo_level ,MatcheNum)        = level_never_uu;            
    SetAclevel(mp_User_ModifyExInfo_level ,BestPlayerNum)    = level_never_uu;                
    SetAclevel(mp_User_ModifyExInfo_level ,VectoryNum)       = level_never_uu;             
    SetAclevel(mp_User_ModifyExInfo_level ,OnePosNum)        = level_never_uu;            
    SetAclevel(mp_User_ModifyExInfo_level ,TwoPosNum)        = level_never_uu;            
    SetAclevel(mp_User_ModifyExInfo_level ,ThreePosNum)      = level_never_uu;              
    SetAclevel(mp_User_ModifyExInfo_level ,FourPosNum)       = level_never_uu;    

    //初始化mysql

    DB_MYSQL_OFUSER::DB_mysql.DB_init(User_host, User_user, User_passwd, User_db, User_port);  
    if(DB_MYSQL_OFUSER::DB_mysql.isinit()){
      if(DB_MYSQL_OFUSER::init_title() == false){
        cout << "[x]user服务没有开启 - title初始化有误 " << endl;
      }else{
        cout << "[*]user服务开启"<<endl;
      }
    }else{
      cout << "[x]user服务没有开启 - 数据库连接出现问题 " << endl;
    }
    
  }
 public:
  UserHandler() {
    AcLevel_Init_user();
  }

  //获取部分BaseInfo
  void User_GetBaseInfo(User_GetBaseInfo_RecvInfo& _return, const User_GetBaseInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = DB_MYSQL_OFUSER::get_userid_fromUsernum(info.Aim_usernum);
    int truelevel = -1;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    truelevel = DB_MYSQL_OFUSER::get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.info);
    for(auto &it : info_mp){
      if(mp_User_GetBaseInfo_level.find(it.first) != mp_User_GetBaseInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_GetBaseInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_GetBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Base dal_user_base = DB_MYSQL_OFUSER::get_user_base(uidB);
    map<string , string >ret ;
    map<string , string> dal_user_base_mp = dal_user_base.toMap();
    for(auto &it : info_mp){
      //如何取出对应名字的元素
      ret[it.first] = dal_user_base_mp[it.first];
    }

    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_GetBaseInfo_RecvInfo_TypeId;
    _return.info = MapToJsonstring(ret);
    cout << "UserServer : User_GetBaseInfo Success!\n" <<endl;
    return;

  }

  void User_GetSocialInfo(User_GetSocialInfo_RecvInfo& _return, const User_GetSocialInfo_SendInfo& info) {
     /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = DB_MYSQL_OFUSER::get_userid_fromUsernum(info.Aim_usernum);
    int truelevel = -1;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    truelevel = DB_MYSQL_OFUSER::get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.info);
    for(auto &it : info_mp){
      if(mp_User_GetSocialInfo_level.find(it.first) != mp_User_GetSocialInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_GetSocialInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_GetSocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Social dal_user_social = DB_MYSQL_OFUSER::get_user_social(uidB);
    map<string , string >ret ;
    map<string , string> dal_user_social_mp = dal_user_social.toMap();
    for(auto &it : info_mp){
      //如何取出对应名字的元素
      ret[it.first] = dal_user_social_mp[it.first];
    }

    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_GetSocialInfo_RecvInfo_TypeId;
    _return.info = MapToJsonstring(ret);
    cout << "UserServer : User_GetSocialInfo Success!\n" <<endl;
  }

  void User_GetExInfo(User_GetExInfo_RecvInfo& _return, const User_GetExInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

   //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = DB_MYSQL_OFUSER::get_userid_fromUsernum(info.Aim_usernum);
    int truelevel = -1;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    truelevel = DB_MYSQL_OFUSER::get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.info);
    for(auto &it : info_mp){
      if(mp_User_GetExInfo_level.find(it.first) != mp_User_GetExInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_GetExInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_GetExtraInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Extra dal_user_ex = DB_MYSQL_OFUSER::get_user_extra(uidB);
    map<string , string >ret ;
    map<string , string> dal_user_ex_mp = dal_user_ex.toMap();
    for(auto &it : info_mp){
      //如何取出对应名字的元素
      ret[it.first] = dal_user_ex_mp[it.first];
    }

    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_GetExtraInfo_RecvInfo_TypeId;
    _return.info = MapToJsonstring(ret);
    cout << "UserServer : User_GetExInfo Success!\n" <<endl;
  }

  void User_login_num(User_login_RecvInfo& _return, const User_login_num_SendInfo& info) {
    std::regex reg_Usernum("^[1-9]\\d{5,12}$");//6-13个数字
    if(regex_match(info.usernum,reg_Usernum) != true){
      _return.status = USER_ERR_REQINFO;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //首先 根据usernum找到 对应的id
    int uid = DB_MYSQL_OFUSER::get_userid_fromUsernum(info.usernum);
    if(uid == INT_DEFAULT){
      _return.status = USER_LOGIN_ERRINFO ;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //取出对应的信息 进行校验
    string truepasswd = DB_MYSQL_OFUSER::get_UserPasswd(uid);
    string truesalt   = DB_MYSQL_OFUSER::get_UserSalt(uid);
    
    //密码核对
    if(sha256(info.passwd + truesalt) == truepasswd){
      //成功
      time_t timnow;
      time(&timnow);

      //更新在线时间
      bool updatatime = DB_MYSQL_OFUSER::updata_UserLasttime(uid,to_string(0));
      if(updatatime == false){
        _return.type              = User_Login_RecvInfo_TypeId;
        _return.status            = USER_DAL_ERR;
        _return.type = User_Login_RecvInfo_TypeId;
        _return.sendtime = info.sendtime;
        return;
      }

      _return.type              = User_Login_RecvInfo_TypeId;
      _return.status            = USER_ACTION_OK;
      _return.sendtime          = info.sendtime;
      _return.jwt_token         = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + jwt_time) );
      _return.refresh_jwt_token = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + refresh_jwt_time) );
      return;
    }else{
      _return.status            = USER_LOGIN_ERRINFO;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    printf("User_login_num Success!\n");
  }

  void User_login_Tel(User_login_RecvInfo& _return, const User_login_Tel_SendInfo& info) {

    //检测各个字段的合法性
    //正则匹配
    std::regex reg_tel("^[1]+[3,8]+\\d{9}$");
    if(regex_match(info.tel,reg_tel) != true){
      _return.status = USER_ERR_REQINFO;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //首先 根据usernum找到 对应的id
    int uid = DB_MYSQL_OFUSER::get_userid_fromTel(info.tel);
    if(uid == INT_DEFAULT){
      _return.status = USER_LOGIN_ERRINFO ;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    

    //取出对应的信息 进行校验
    string truepasswd = DB_MYSQL_OFUSER::get_UserPasswd(uid);
    string truesalt   = DB_MYSQL_OFUSER::get_UserSalt(uid);
    
    //密码核对
    if(sha256((info.passwd) + truesalt) == truepasswd){
      //成功
      time_t timnow;
      time(&timnow);
      
      //更新在线时间
      bool updatatime = DB_MYSQL_OFUSER::updata_UserLasttime(uid,to_string(0));
      if(updatatime == false){
        _return.type              = User_Login_RecvInfo_TypeId;
        _return.status            = USER_DAL_ERR;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
        return;
      }
      
      _return.type              = User_Login_RecvInfo_TypeId;
      _return.status            = USER_ACTION_OK;
      _return.sendtime          = info.sendtime;
      _return.jwt_token         = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + jwt_time) );
      _return.refresh_jwt_token = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + refresh_jwt_time) );
      printf("[→]User_login_Tel Success  Userid: %d !\n" , uid);
      return;
    }else{
      _return.status            = USER_LOGIN_ERRINFO;
      _return.type = User_Login_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
  }

  void User_reg(User_reg_RecvInfo& _return, const User_reg_SendInfo& info) {
    //检测各个字段的合法性
    //正则匹配
    std::regex reg_tel("^[1]+[3,8]+\\d{9}$");
    if(regex_match(info.tel,reg_tel) != true){
      _return.status = USER_ERR_REQINFO;
      _return.type = User_Reg_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    std::regex reg_Usernum("^[1-9]\\d{5,12}$");//6-13个数字
    if(regex_match(info.usernum,reg_Usernum) != true){
      _return.status = USER_ERR_REQINFO;
      _return.type = User_Reg_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    // 密码是base64+sha的
    // std::regex reg_passwd("^[a-zA-Z0-9_]{6,13}$");//6-13个长的大写小写下划线数字构成
    // if(regex_match(info.passwd,reg_passwd) != true){
    //   _return.status = USER_ERR_REQINFO;
    //   return;
    // }

    //检测重复性
    if(DB_MYSQL_OFUSER::get_userid_fromTel(info.tel) != INT_DEFAULT){
      _return.status = User_Reg_Havethistel;
      _return.type = User_Reg_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(DB_MYSQL_OFUSER::get_userid_fromUsernum(info.usernum) != INT_DEFAULT){
      _return.status = User_Reg_Havethisnum;
      _return.type = User_Reg_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //时间
    time_t timenow;
    time(&timenow);
    srand(time(0));
    //写入数据库
    DAL_User_Base t1;
    t1.Userid         = DB_MYSQL_OFUSER::getnextuid();
    t1.Usernum        = info.usernum;
    t1.UserRegtime    = to_string((int64_t)timenow);
    t1.UserLasttime   = to_string((int64_t)timenow);
    t1.Salt           = sha256((to_string(rand())));
    t1.Passwd         = sha256((info.passwd) + t1.Salt); 
    t1.Tel = info.tel;
    DB_MYSQL_OFUSER::AddUser_t1(t1);
    _return.status = USER_ACTION_OK;
    _return.sendtime = info.sendtime;
    _return.type = User_Reg_RecvInfo_TypeId;
    printf("[+]User_reg Success  Userid: %d !\n" , t1.Userid);
  }

  void User_logoff(User_logoff_RecvInfo& _return, const User_logoff_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_logoff_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时 // 下线请求受理超时请求
    // if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
    //   //丢掉
    //   cout << "UserServer : 超时的jwt" <<endl;
    //   _return.type = User_logoff_RecvInfo_TypeId;
    //   _return.sendtime = info.sendtime;
    //   _return.status = USER_TIMEOUT_JWT;
    //   return;
    // }


    /* 第二步 处理逻辑 */

    //获取id
    int uid = stoi(jwt_payload_mp["aud"]);

    //判断在线
    if(stoi(DB_MYSQL_OFUSER::get_UserLasttime(uid))  != 0){
      //不在线
      _return.status = User_Logoff_notonline;
      _return.type = User_logoff_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //在线
    time_t timenow;
    time(&timenow);
    if(DB_MYSQL_OFUSER::updata_UserLasttime(uid,to_string((int64_t)timenow)) == false){
      _return.status = USER_DAL_ERR;
      _return.type = User_logoff_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    _return.type = User_logoff_RecvInfo_TypeId;
    _return.status = USER_ACTION_OK;
    _return.sendtime = info.sendtime;

    printf("[←]User_logoff Success  Userid: %d !\n" , uid);
  }

  void User_refresh_jwt1(User_refresh_jwt1_RecvInfo& _return, const User_refresh_jwt1_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_refresh_jwt1_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIME_OK){
      //丢掉
      cout << "UserServer : jwt延时时遇到没有过期的jwt" <<endl;
      _return.type = User_refresh_jwt1_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      _return.status = User_JWT_NOTOUTTIME;
      return;
    }

    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.refresh_jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt_refresh鉴权 哈希未通过" <<endl;
      _return.type = User_refresh_jwt1_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : jwt延时时遇到过期的refresh jwt" <<endl;
      _return.type = User_refresh_jwt1_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      _return.status = User_REJWT_HAVEOUTTIME;
      return;
    }



    /* 之后再处理逻辑 */
    //创建个新的给他
    _return.status = USER_ACTION_OK;
    _return.type = User_refresh_jwt1_RecvInfo_TypeId;
    _return.jwt_token = JWT_token::jwt_extratime(jwt_secret ,  info.jwt_token , jwt_time);
    _return.sendtime = info.sendtime;
    printf("User_refresh_jwt1\n");
  }

  void User_refresh_jwt2(User_refresh_jwt2_RecvInfo& _return, const User_refresh_jwt2_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_refresh_jwt2_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIME_OK){
      //丢掉
      cout << "UserServer : rejwt延时时遇到没有过期的jwt" <<endl;
      _return.type = User_refresh_jwt2_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      _return.status = User_JWT_NOTOUTTIME;
      return;
    }

    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.refresh_jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt_refresh鉴权 哈希未通过" <<endl;
      _return.type = User_refresh_jwt2_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIME_OK){
      //丢掉
      cout << "UserServer : rejwt延时时遇到没有过期的refresh jwt" <<endl;
      _return.type = User_refresh_jwt2_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      _return.status = User_REJWT_NOTOUTTIME;
      return;
    }



    /* 之后再处理逻辑 */
    //创建个新的给他
    _return.status = USER_ACTION_OK;
    _return.type = User_refresh_jwt2_RecvInfo_TypeId;
    _return.jwt_token = JWT_token::jwt_extratime(jwt_secret ,  info.jwt_token , jwt_time);
    _return.refresh_jwt_token = JWT_token::jwt_extratime(jwt_secret ,  info.jwt_token , refresh_jwt_time);
    _return.sendtime = info.sendtime;
    printf("User_refresh_jwt2\n");
  }

  void User_ModifyBaseInfo(User_ModifyBaseInfo_RecvInfo& _return, const User_ModifyBaseInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int truelevel = 0;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.modifyinfo);
    for(auto &it : info_mp){
      if(mp_User_ModifyBaseInfo_level.find(it.first) != mp_User_ModifyBaseInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_ModifyBaseInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Base dal_user_base =DB_MYSQL_OFUSER::get_user_base(uidA);
    map<string , string> dal_user_base_mp = dal_user_base.toMap();
    for(auto &it : info_mp){
      //暂无校验机制
      dal_user_base_mp[it.first] = it.second;
    }
    DB_MYSQL_OFUSER::updata_user_base(uidA, DAL_User_Base::ToClass(dal_user_base_mp));
    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_ModifyBaseInfo_RecvInfo_TypeId;
    printf("User_ModifyBaseInfo\n");
    return;
    
  }

  void User_ModifySocialInfo(User_ModifySocialInfo_RecvInfo& _return, const User_ModifySocialInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int truelevel = 0;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.modifyinfo);
    for(auto &it : info_mp){
      if(mp_User_ModifySocialInfo_level.find(it.first) != mp_User_ModifySocialInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_ModifySocialInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Social dal_user_social =DB_MYSQL_OFUSER::get_user_social(uidA);
    map<string , string> dal_user_social_mp = dal_user_social.toMap();
    for(auto &it : info_mp){
      //暂无校验机制
      dal_user_social_mp[it.first] = it.second;
    }
    DB_MYSQL_OFUSER::updata_user_social(uidA, DAL_User_Social::ToClass(dal_user_social_mp));
    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_ModifySocialInfo_RecvInfo_TypeId;
    printf("User_ModifySocialInfo\n");
    return;
    
  }

  void User_ModifyExInfo(User_ModifyExInfo_RecvInfo& _return, const User_ModifyExInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int truelevel = 0;
    int aimlevel = level_black_uu;

    if(uidA <=0 || uidA >= MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    /* 第二步 查看数据内容 确定访问等级 */
    map<string , string > info_mp = JsonstringToMap(info.modifyinfo);
    for(auto &it : info_mp){
      if(mp_User_ModifyExInfo_level.find(it.first) != mp_User_ModifyExInfo_level.end()){
        aimlevel = min(aimlevel , mp_User_ModifyExInfo_level[it.first]);
      }else{
        aimlevel = -1;
      }
    }
    if(aimlevel == -1){
      _return.status=USER_ERR_REQINFO;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWACLevel;
      _return.type = User_ModifyExInfo_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    
    //获得对应数据
    DAL_User_Extra dal_user_ex =DB_MYSQL_OFUSER::get_user_extra(uidA);
    map<string , string> dal_user_ex_mp = dal_user_ex.toMap();
    for(auto &it : info_mp){
      //暂无校验机制
      dal_user_ex_mp[it.first] = it.second;
    }
    DB_MYSQL_OFUSER::updata_user_extra(uidA, DAL_User_Extra::ToClass(dal_user_ex_mp));
    _return.sendtime = info.sendtime;
    _return.status = USER_ACTION_OK;
    _return.type = User_ModifyExInfo_RecvInfo_TypeId;
    printf("User_ModifyexInfo\n");
    return;
  }

  void User_follow(User_follow_RecvInfo& _return, const User_follow_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_follow_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_follow_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    int uid = stoi(jwt_payload_mp["aud"]);

    string dbinfo = DB_MYSQL_OFUSER::get_UUrelation(uid);
    map<string , string> dbmp = JsonstringToMap(dbinfo);

    map<string , string>ret;
    for(auto& it:dbmp){
      if((stoi(it.second) & 2) ==2 ){
        ret[it.first] = '1';
      }
    }
    _return.info = MapToJsonstring(ret);
    _return.type = User_follow_RecvInfo_TypeId;
    _return.status = USER_ACTION_OK;
    printf("User_follow\n");
    return;
  }

  void User_followed(User_followed_RecvInfo& _return, const User_followed_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_followed_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_followed_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    int uid = stoi(jwt_payload_mp["aud"]);

    string dbinfo = DB_MYSQL_OFUSER::get_UUrelation(uid);
    map<string , string> dbmp = JsonstringToMap(dbinfo);

    map<string , string>ret;
    for(auto& it:dbmp){
      if((stoi(it.second) & 1) ==1 ){
        ret[it.first] = '1';
      }
    }
    _return.info = MapToJsonstring(ret);
    _return.type = User_followed_RecvInfo_TypeId;
    _return.status = USER_ACTION_OK;
    printf("User_followed\n");
  }

  void User_friend(User_friend_RecvInfo& _return, const User_friend_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.jwt_token).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.jwt_token) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      _return.type = User_friend_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.jwt_token) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      _return.type = User_friend_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      return;
    }
    int uid = stoi(jwt_payload_mp["aud"]);

    string dbinfo = DB_MYSQL_OFUSER::get_UUrelation(uid);
    map<string , string> dbmp = JsonstringToMap(dbinfo);

    map<string , string>ret;
    for(auto& it:dbmp){
      if((stoi(it.second) & 3) ==3 ){
        ret[it.first] = '1';
      }
    }
    _return.info = MapToJsonstring(ret);
    _return.type = User_friend_RecvInfo_TypeId;
    _return.status = USER_ACTION_OK;
    printf("User_friend\n");
  }
};

int main(int argc, char **argv) {
  int port = USER_PORT;
  ::std::shared_ptr<UserHandler> handler(new UserHandler());
  ::std::shared_ptr<TProcessor> processor(new UserProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

