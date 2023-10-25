struct Echo_SendInfo {
  1:i32 id,
  2:string info
}

struct Echo_RecvInfo {
  1:i32 id,
  2:string info,
  3:string time
}

service Echo{
  Echo_RecvInfo Echo_Send(1: Echo_SendInfo info)
}