struct Echo_SendInfo {
  1:i32 id,
  2:string info,
  3:i32 sendtime
}

struct Echo_RecvInfo {
  1:i32 id,
  2:string info,
  3:string time,
  4:i32 sendtime
}

service Echo{
  Echo_RecvInfo Echo_Send(1: Echo_SendInfo info)
}

