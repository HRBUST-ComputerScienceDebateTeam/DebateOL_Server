struct Audio_Upload_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:string info
}

struct Audio_Upload_RecvInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:i32 status
}

struct Audio_Download_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec
}

struct Audio_Download_RecvInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId,
  4:i32 min,
  5:i32 sec,
  6:i32 msec,
  7:i32 status,
  8:string info  
}

struct Audio_Clean_SendInfo {
  1:i32 type,
  2:i32 userId,
  3:i32 roomId
}

service Audio{
  Audio_Upload_RecvInfo Audio_Upload(1: Audio_Upload_SendInfo info),
  Audio_Download_RecvInfo Audio_Download(1: Audio_Download_SendInfo info),
  void Audio_Clean(1: Audio_Clean_SendInfo info)
}