// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "User.h"
#include "../../conf.hh"
#include "../dal/dal_user.h"
#include "../../../pkg/JsonChange/jsonchange.h"
#include "../../../pkg/JWT/jwt.h"
#include "../../../pkg/Openssl/openssl.h"
#include "../dal/dal_userconfig.h"
#include <cstdint>
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

  void AcLevel_Init_user(){ // Ac 等级设定 
    SetAclevel(mp_User_GetBaseInfo_level ,Userid)         = level_black;        
    SetAclevel(mp_User_GetBaseInfo_level ,Usernum)        = level_stranger;         
    SetAclevel(mp_User_GetBaseInfo_level ,Passwd)         = level_self;        
    SetAclevel(mp_User_GetBaseInfo_level ,Tel)            = level_self;     
    SetAclevel(mp_User_GetBaseInfo_level ,UserRegtime)    = level_stranger;             
    SetAclevel(mp_User_GetBaseInfo_level ,UserLasttime)   = level_friend;              
    SetAclevel(mp_User_GetBaseInfo_level ,Salt)           = level_self; 
  
    SetAclevel(mp_User_GetSocialInfo_level , Userid)      = level_black;                         
    SetAclevel(mp_User_GetSocialInfo_level , Username)    = level_stranger;                           
    SetAclevel(mp_User_GetSocialInfo_level , Headshot)    = level_stranger;                           
    SetAclevel(mp_User_GetSocialInfo_level , Sex)         = level_stranger;                      
    SetAclevel(mp_User_GetSocialInfo_level , Signature)   = level_stranger;                            
    SetAclevel(mp_User_GetSocialInfo_level , Contact)     = level_friend;

    SetAclevel(mp_User_GetExInfo_level ,Userid)           = level_black;         
    SetAclevel(mp_User_GetExInfo_level ,IntentionToArgue) = level_stranger;                   
    SetAclevel(mp_User_GetExInfo_level ,MatcheNum)        = level_stranger;            
    SetAclevel(mp_User_GetExInfo_level ,BestPlayerNum)    = level_follow;                
    SetAclevel(mp_User_GetExInfo_level ,VectoryNum)       = level_follow;             
    SetAclevel(mp_User_GetExInfo_level ,OnePosNum)        = level_self;            
    SetAclevel(mp_User_GetExInfo_level ,TwoPosNum)        = level_self;            
    SetAclevel(mp_User_GetExInfo_level ,ThreePosNum)      = level_self;              
    SetAclevel(mp_User_GetExInfo_level ,FourPosNum)       = level_self;             
  }
 public:
  UserHandler() {
    AcLevel_Init_user();
  }

  //获取部分BaseInfo
  void User_GetBaseInfo(User_GetBaseInfo_RecvInfo& _return, const User_GetBaseInfo_SendInfo& info) {
    /* 第一步 用户鉴权 */

    //拆包
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.info).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.info) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.info) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = info.Aim_usernum;
    int truelevel = -1;
    int aimlevel = level_black;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      return;
    }
    truelevel = get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
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
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWLEVEL_JWT;
      return;
    }
    
    //获得对应数据
    DAL_User_Base dal_user_base = get_user_base(uidB);
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
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.info).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.info) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.info) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = info.Aim_usernum;
    int truelevel = -1;
    int aimlevel = level_black;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      return;
    }
    truelevel = get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
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
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWLEVEL_JWT;
      return;
    }
    
    //获得对应数据
    DAL_User_Social dal_user_social = get_user_social(uidB);
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
    map<string , string > jwt_payload_mp = JWT_token::jwt_decode(info.info).getpayloadmap();
    //检查哈希 - 哈希失败没有返回报文
    if(JWT_token::jwt_check_hash(jwt_secret , info.info) == JWT_HASHERR){
      //丢掉
      cout << "UserServer : 收到了异常的jwt鉴权 哈希未通过" <<endl;
      return;
    }

    //检查超时 - 超时返回超时
    if(JWT_token::jwt_check_time(info.info) == JWT_TIMEOUT){
      //丢掉
      cout << "UserServer : 超时的jwt" <<endl;
      _return.status = USER_TIMEOUT_JWT;
      return;
    }

    //获取好友关系
    int uidA = stoi(jwt_payload_mp["aud"]);
    int uidB = info.Aim_usernum;
    int truelevel = -1;
    int aimlevel = level_black;

    if(uidA <=0 || uidA >= MAX_USER && uidB<=0 || uidB>=MAX_USER){//申请数据检查
      _return.status=USER_ERR_REQINFO;
      return;
    }
    truelevel = get_uulevel(uidA,uidB).UULevel;
    //返回数据检查
    if(truelevel != -1){
      _return.status = USER_DAL_ERR;
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
      return;
    }
    if(aimlevel<truelevel ){
      _return.status = USER_LOWLEVEL_JWT;
      return;
    }
    
    //获得对应数据
    DAL_User_Extra dal_user_ex = get_user_extra(uidB);
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
    //首先 根据usernum找到 对应的id
    int uid = get_userid_fromUsernum(info.usernum);
    if(uid == No_such_usernum){
      _return.status = USER_ERR_REQINFO ;
      return;
    }

    //取出对应的信息 进行校验
    DAL_User_Base dubase = get_user_base(uid);
    
    //密码核对
    if(sha256(info.passwd + dubase.Salt) == dubase.Passwd){
      //成功
      time_t timnow;
      time(&timnow);
      _return.type              = User_Login_RecvInfo_TypeId;
      _return.status            = USER_ACTION_OK;
      _return.sendtime          = info.sendtime;
      _return.jwt_token         = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + jwt_time) );
      _return.refresh_jwt_token = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + refresh_jwt_time) );
      return;
    }else{
      _return.status            = USER_LOGIN_ERRINFO;
      return;
    }

    printf("User_login_num Success!\n");
  }

  void User_login_Tel(User_login_RecvInfo& _return, const User_login_Tel_SendInfo& info) {
    //首先 根据usernum找到 对应的id
    int uid = get_userid_fromTel(info.tel);
    if(uid == No_such_tel){
      _return.status = USER_ERR_REQINFO ;
      return;
    }

    //取出对应的信息 进行校验
    DAL_User_Base dubase = get_user_base(uid);
    
    //密码核对
    if(sha256(info.passwd + dubase.Salt) == dubase.Passwd){
      //成功
      time_t timnow;
      time(&timnow);
      _return.type              = User_Login_RecvInfo_TypeId;
      _return.status            = USER_ACTION_OK;
      _return.sendtime          = info.sendtime;
      _return.jwt_token         = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + jwt_time) );
      _return.refresh_jwt_token = JWT_token::jwt_create(jwt_secret,"ljy",to_string(uid), to_string((int64_t)timnow),to_string((int64_t)timnow + refresh_jwt_time) );
      return;
    }else{
      _return.status            = USER_LOGIN_ERRINFO;
      return;
    }
    printf("User_login_Tel Success!\n");
  }

  void User_reg(User_reg_RecvInfo& _return, const User_reg_SendInfo& info) {
    //检测各个字段的合法性
    //正则匹配
    std::regex reg_tel("^[1]+[3,8]+\\d{9}$");
    if(regex_match(info.tel,reg_tel) != true){
      _return.status = USER_ERR_REQINFO;
      return;
    }

    std::regex reg_Usernum("^[1-9]\\d{5,12}$");//6-13个数字
    if(regex_match(info.usernum,reg_Usernum) != true){
      _return.status = USER_ERR_REQINFO;
      return;
    }
    
    // 密码是base64+sha的
    // std::regex reg_passwd("^[a-zA-Z0-9_]{6,13}$");//6-13个长的大写小写下划线数字构成
    // if(regex_match(info.passwd,reg_passwd) != true){
    //   _return.status = USER_ERR_REQINFO;
    //   return;
    // }

    //检测重复性
    if(get_userid_fromTel(info.tel) != No_such_tel){
      _return.status = User_Reg_Havethistel;
      return;
    }
    if(get_userid_fromUsernum(info.usernum) != No_such_username){
      _return.status = User_Reg_Havethisnum;
      return;
    }

    //时间
    time_t timenow;
    time(&timenow);
    srand(time(0));
    //写入数据库
    DAL_User_Base t1;
    t1.Userid = getnextuid();
    t1.Usernum = info.usernum;
    t1.UserRegtime = to_string((int64_t)timenow);
    t1.Salt = sha256(Base64Encode(to_string(rand())));
    t1.Passwd = sha256(info.passwd + t1.Salt); 
    t1.Tel = info.tel;
    AddUser(t1);
    _return.status = USER_ACTION_OK;
    _return.sendtime = info.sendtime;
    _return.type = User_Reg_TypeId;
    printf("User_reg Success!\n");
  }

  void User_logoff(User_logoff_RecvInfo& _return, const User_logoff_SendInfo& info) {
    // Your implementation goes here
    printf("User_logoff\n");
  }

  void User_refresh_jwt1(User_refresh_jwt1_RecvInfo& _return, const User_refresh_jwt1_SendInfo& info) {
    // Your implementation goes here
    printf("User_refresh_jwt1\n");
  }

  void User_refresh_jwt2(User_refresh_jwt2_RecvInfo& _return, const User_refresh_jwt2_SendInfo& info) {
    // Your implementation goes here
    printf("User_refresh_jwt2\n");
  }

  void User_ModifyBaseInfo(User_ModifyBaseInfo_RecvInfo& _return, const User_ModifyBaseInfo_SendInfo& info) {
    // Your implementation goes here
    printf("User_ModifyBaseInfo\n");
  }

  void User_ModifySocialInfo(User_ModifySocialInfo_RecvInfo& _return, const User_ModifySocialInfo_SendInfo& info) {
    // Your implementation goes here
    printf("User_ModifySocialInfo\n");
  }

  void User_ModifyExInfo(User_ModifyExInfo_RecvInfo& _return, const User_ModifyExInfo_SendInfo& info) {
    // Your implementation goes here
    printf("User_ModifyExInfo\n");
  }

  void User_follow(User_follow_RecvInfo& _return, const User_follow_SendInfo& info) {
    // Your implementation goes here
    printf("User_follow\n");
  }

  void User_followed(User_followed_RecvInfo& _return, const User_followed_SendInfo& info) {
    // Your implementation goes here
    printf("User_followed\n");
  }

  void User_friend(User_friend_RecvInfo& _return, const User_friend_SendInfo& info) {
    // Your implementation goes here
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
