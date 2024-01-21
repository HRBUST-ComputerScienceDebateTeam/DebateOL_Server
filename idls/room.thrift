//房间
//房间有以下功能（这里出现的都是客户端向服务器的请求 返回给客户端）
//获取房间信息
//获取房间扩展信息
//获取该房间的其他用户和对应辩位和对应权限


//创建房间 - 创建两个表base和room 同时添加表项在ur关系里面
  //创建同时创建者进入房间 - 因为房间的删除逻辑是根据引用计数
//进入房间 - 密码 辩位 等级-等级的定义在conf里面

//退出房间

//修改房间密码
//设置房间扩展信息
//更改辩位


//移交管理员权限 - 暂时不支持


//房间信息获取请求 - 基本信息
struct Room_GetBaseInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string Aim_Roomnum,
  5:string info
}

struct Room_GetBaseInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//房间信息获取请求 - 社交信息
struct Room_GetExInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string Aim_Roomnum,
  5:string info
}

struct Room_GetExInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info
}

//房间信息获取请求 - 扩展信息
struct Room_GetURrelation_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string Aim_Roomnum,
  5:string info
}

struct Room_GetURrelation_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status,
  4:string info_UR_pos,
  5:string info_UR_per
}

//创建房间请求
struct Room_Create_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 Roomnum,
  5:i32 Islocking,
  6:string Roomname,
  7:string passwd,
  8:i32 Debate_pos
}
struct Room_Create_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}


//进入房间请求
struct Room_Joinroom_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string roomnum,
  5:i32 Debate_pos
}
struct Room_Joinroom_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}

//退出房间请求
struct Room_Exitroom_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string roomnum
}
struct Room_Exitroom_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}

struct Room_ChangePasswd_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:string Opasswd,
  5:string Npasswd
}
struct Room_ChangePasswd_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}

struct Room_ChangeExtraInfo_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 roomnum,
  5:string info
}
struct Room_ChangeExtraInfo_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}

struct Room_ChangeDebatePos_SendInfo {
  1:i32 type,
  2:string jwt_token,
  3:i32 sendtime,
  4:i32 Debate_pos
}
struct Room_ChangeDebatePos_RecvInfo {
  1:i32 type,
  2:i32 sendtime,
  3:i32 status
}


service Room{
  Room_ChangeDebatePos_RecvInfo Room_ChangeDebatePos(1: Room_ChangeDebatePos_SendInfo info),
  Room_ChangeExtraInfo_RecvInfo Room_ChangeExtraInfo(1: Room_ChangeExtraInfo_SendInfo info),
  Room_ChangePasswd_RecvInfo Room_ChangePasswd(1: Room_ChangePasswd_SendInfo info),
  Room_Exitroom_RecvInfo Room_Exitroom(1: Room_Exitroom_SendInfo info),
  Room_Joinroom_RecvInfo Room_Joinroom(1: Room_Joinroom_SendInfo info),
  Room_Create_RecvInfo Room_Create(1: Room_Create_SendInfo info),
  Room_GetURrelation_RecvInfo Room_GetURrelation(1: Room_GetURrelation_SendInfo info),
  Room_GetExInfo_RecvInfo Room_GetExInfo(1: Room_GetExInfo_SendInfo info),
  Room_GetBaseInfo_RecvInfo Room_GetBaseInfo(1: Room_GetBaseInfo_SendInfo info),
}