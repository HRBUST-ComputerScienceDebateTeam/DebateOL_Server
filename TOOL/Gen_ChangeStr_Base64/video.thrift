struct Video_Upload_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:string info,
  8:i32 sendtime
}

struct Video_Upload_RecvInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:i32 status,
  8:i32 sendtime
}

struct Video_Download_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:i32 sendtime
}

struct Video_Download_RecvInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:i32 status,
  8:string info,
  9:i32 sendtime 
}

struct Video_Clean_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 sendtime
}

service Video{
  Video_Upload_RecvInfo Video_Upload(1: Video_Upload_SendInfo info),
  Video_Download_RecvInfo Video_Download(1: Video_Download_SendInfo info),
  void Video_Clean(1: Video_Clean_SendInfo info)
}