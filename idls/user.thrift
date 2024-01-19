//用户
//用户有以下功能（这里出现的都是客户端向服务器的请求 返回给客户端）
//获取用户的 基本信息 中的某些属性
//获取用户的 社交信息 中的某些属性
//获取用户的 扩展信息 中的某些属性
//登陆
//注册
//下线
//更新jwt 
//修改个人信息
//获取好友列表 - 关注同时被关注
//获取我关注的
//获取关注我的


//注销用户 - 暂时不支持
//修改密码 - 暂时不支持
//找回密码 - 暂时不支持


//用户信息获取请求 - 基本信息
struct User_GetBaseInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 Aim_usernum,
  5:string info
}

struct User_GetBaseInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//用户信息获取请求 - 社交信息
struct User_GetSocialInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 Aim_usernum,
  5:string info
}

struct User_GetSocialInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//用户信息获取请求 - 扩展信息
struct User_GetExInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 Aim_usernum,
  5:string info
}

struct User_GetExInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//用户注册请求
struct User_reg_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:string tel,
  4:string usernum,
  5:string passwd
}
struct User_reg_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}


//用户登陆请求 - tel
struct User_login_Tel_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:string tel,
  4:string passwd
}
//用户登陆请求 - num
struct User_login_num_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:string usernum,
  4:string passwd
}
struct User_login_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string jwt_token,
  5:string refresh_jwt_token
}


//用户下线请求
struct User_logoff_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 uid
}
struct User_logoff_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}


//刷新jwt1
struct User_refresh_jwt1_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:string jwt_token
}
struct User_refresh_jwt1_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string jwt_token
}

//刷新jwt2
struct User_refresh_jwt2_SendInfo {
  1:i32 type,
  2:i32 sendtime,
  3:string jwt_token,
  4:string refresh_jwt_token
}
struct User_refresh_jwt2_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string jwt_token,
  5:string refresh_jwt_token
}


// 获取好友列表
struct User_friend_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
}
struct User_friend_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}
// 获取我关注的
struct User_follow_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
}
struct User_follow_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}
// 获取关注我的
struct User_followed_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
}
struct User_followed_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//修改个人信息 - 签名同数据库结构体相同 对应函数需要进行校验
struct User_ModifyBaseInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string modifyinfo
}
struct User_ModifyBaseInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}
//修改个人信息 - 签名同数据库结构体相同 对应函数需要进行校验
struct User_ModifySocialInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string modifyinfo
}
struct User_ModifySocialInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}
//修改个人信息 - 签名同数据库结构体相同 对应函数需要进行校验
struct User_ModifyExInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string modifyinfo
}
struct User_ModifyExInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}



service User{
  User_GetBaseInfo_RecvInfo User_GetBaseInfo(1: User_GetBaseInfo_SendInfo info),
  User_GetSocialInfo_RecvInfo User_GetSocialInfo(1: User_GetSocialInfo_SendInfo info),
  User_GetExInfo_RecvInfo User_GetExInfo(1: User_GetExInfo_SendInfo info),
  User_login_RecvInfo User_login_num(1: User_login_num_SendInfo info),
  User_login_RecvInfo User_login_Tel(1: User_login_Tel_SendInfo info),
  User_reg_RecvInfo User_reg(1: User_reg_SendInfo info),
  User_logoff_RecvInfo User_logoff(1: User_logoff_SendInfo info),
  User_refresh_jwt1_RecvInfo User_refresh_jwt1(1: User_refresh_jwt1_SendInfo info),
  User_refresh_jwt2_RecvInfo User_refresh_jwt2(1: User_refresh_jwt2_SendInfo info),
  User_ModifyBaseInfo_RecvInfo User_ModifyBaseInfo(1: User_ModifyBaseInfo_SendInfo info)
  User_ModifySocialInfo_RecvInfo User_ModifySocialInfo(1: User_ModifySocialInfo_SendInfo info)
  User_ModifyExInfo_RecvInfo User_ModifyExInfo(1: User_ModifyExInfo_SendInfo info)
  User_follow_RecvInfo User_follow(1: User_follow_SendInfo info),
  User_followed_RecvInfo User_followed(1: User_followed_SendInfo info),
  User_friend_RecvInfo User_friend(1: User_friend_SendInfo info)
}