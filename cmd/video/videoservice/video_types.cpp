/**
 * Autogenerated by Thrift Compiler (0.19.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "video_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




Video_Upload_SendInfo::~Video_Upload_SendInfo() noexcept {
}


void Video_Upload_SendInfo::__set_type(const int32_t val) {
  this->type = val;
}

void Video_Upload_SendInfo::__set_userId(const int32_t val) {
  this->userId = val;
}

void Video_Upload_SendInfo::__set_roomId(const int32_t val) {
  this->roomId = val;
}

void Video_Upload_SendInfo::__set_min(const int32_t val) {
  this->min = val;
}

void Video_Upload_SendInfo::__set_sec(const int32_t val) {
  this->sec = val;
}

void Video_Upload_SendInfo::__set_msec(const int32_t val) {
  this->msec = val;
}

void Video_Upload_SendInfo::__set_info(const std::string& val) {
  this->info = val;
}
std::ostream& operator<<(std::ostream& out, const Video_Upload_SendInfo& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Video_Upload_SendInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->type);
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->userId);
          this->__isset.userId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->roomId);
          this->__isset.roomId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->min);
          this->__isset.min = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->sec);
          this->__isset.sec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->msec);
          this->__isset.msec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->info);
          this->__isset.info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Video_Upload_SendInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Video_Upload_SendInfo");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("userId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->userId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("roomId", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->roomId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("min", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->min);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sec", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->sec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("msec", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->msec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("info", ::apache::thrift::protocol::T_STRING, 7);
  xfer += oprot->writeString(this->info);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Video_Upload_SendInfo &a, Video_Upload_SendInfo &b) {
  using ::std::swap;
  swap(a.type, b.type);
  swap(a.userId, b.userId);
  swap(a.roomId, b.roomId);
  swap(a.min, b.min);
  swap(a.sec, b.sec);
  swap(a.msec, b.msec);
  swap(a.info, b.info);
  swap(a.__isset, b.__isset);
}

Video_Upload_SendInfo::Video_Upload_SendInfo(const Video_Upload_SendInfo& other0) {
  type = other0.type;
  userId = other0.userId;
  roomId = other0.roomId;
  min = other0.min;
  sec = other0.sec;
  msec = other0.msec;
  info = other0.info;
  __isset = other0.__isset;
}
Video_Upload_SendInfo& Video_Upload_SendInfo::operator=(const Video_Upload_SendInfo& other1) {
  type = other1.type;
  userId = other1.userId;
  roomId = other1.roomId;
  min = other1.min;
  sec = other1.sec;
  msec = other1.msec;
  info = other1.info;
  __isset = other1.__isset;
  return *this;
}
void Video_Upload_SendInfo::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Video_Upload_SendInfo(";
  out << "type=" << to_string(type);
  out << ", " << "userId=" << to_string(userId);
  out << ", " << "roomId=" << to_string(roomId);
  out << ", " << "min=" << to_string(min);
  out << ", " << "sec=" << to_string(sec);
  out << ", " << "msec=" << to_string(msec);
  out << ", " << "info=" << to_string(info);
  out << ")";
}


Video_Upload_RecvInfo::~Video_Upload_RecvInfo() noexcept {
}


void Video_Upload_RecvInfo::__set_type(const int32_t val) {
  this->type = val;
}

void Video_Upload_RecvInfo::__set_userId(const int32_t val) {
  this->userId = val;
}

void Video_Upload_RecvInfo::__set_roomId(const int32_t val) {
  this->roomId = val;
}

void Video_Upload_RecvInfo::__set_min(const int32_t val) {
  this->min = val;
}

void Video_Upload_RecvInfo::__set_sec(const int32_t val) {
  this->sec = val;
}

void Video_Upload_RecvInfo::__set_msec(const int32_t val) {
  this->msec = val;
}

void Video_Upload_RecvInfo::__set_status(const int32_t val) {
  this->status = val;
}
std::ostream& operator<<(std::ostream& out, const Video_Upload_RecvInfo& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Video_Upload_RecvInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->type);
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->userId);
          this->__isset.userId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->roomId);
          this->__isset.roomId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->min);
          this->__isset.min = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->sec);
          this->__isset.sec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->msec);
          this->__isset.msec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->status);
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Video_Upload_RecvInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Video_Upload_RecvInfo");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("userId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->userId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("roomId", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->roomId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("min", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->min);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sec", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->sec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("msec", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->msec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Video_Upload_RecvInfo &a, Video_Upload_RecvInfo &b) {
  using ::std::swap;
  swap(a.type, b.type);
  swap(a.userId, b.userId);
  swap(a.roomId, b.roomId);
  swap(a.min, b.min);
  swap(a.sec, b.sec);
  swap(a.msec, b.msec);
  swap(a.status, b.status);
  swap(a.__isset, b.__isset);
}

Video_Upload_RecvInfo::Video_Upload_RecvInfo(const Video_Upload_RecvInfo& other2) noexcept {
  type = other2.type;
  userId = other2.userId;
  roomId = other2.roomId;
  min = other2.min;
  sec = other2.sec;
  msec = other2.msec;
  status = other2.status;
  __isset = other2.__isset;
}
Video_Upload_RecvInfo& Video_Upload_RecvInfo::operator=(const Video_Upload_RecvInfo& other3) noexcept {
  type = other3.type;
  userId = other3.userId;
  roomId = other3.roomId;
  min = other3.min;
  sec = other3.sec;
  msec = other3.msec;
  status = other3.status;
  __isset = other3.__isset;
  return *this;
}
void Video_Upload_RecvInfo::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Video_Upload_RecvInfo(";
  out << "type=" << to_string(type);
  out << ", " << "userId=" << to_string(userId);
  out << ", " << "roomId=" << to_string(roomId);
  out << ", " << "min=" << to_string(min);
  out << ", " << "sec=" << to_string(sec);
  out << ", " << "msec=" << to_string(msec);
  out << ", " << "status=" << to_string(status);
  out << ")";
}


Video_Download_SendInfo::~Video_Download_SendInfo() noexcept {
}


void Video_Download_SendInfo::__set_type(const int32_t val) {
  this->type = val;
}

void Video_Download_SendInfo::__set_userId(const int32_t val) {
  this->userId = val;
}

void Video_Download_SendInfo::__set_roomId(const int32_t val) {
  this->roomId = val;
}

void Video_Download_SendInfo::__set_min(const int32_t val) {
  this->min = val;
}

void Video_Download_SendInfo::__set_sec(const int32_t val) {
  this->sec = val;
}

void Video_Download_SendInfo::__set_msec(const int32_t val) {
  this->msec = val;
}
std::ostream& operator<<(std::ostream& out, const Video_Download_SendInfo& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Video_Download_SendInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->type);
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->userId);
          this->__isset.userId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->roomId);
          this->__isset.roomId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->min);
          this->__isset.min = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->sec);
          this->__isset.sec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->msec);
          this->__isset.msec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Video_Download_SendInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Video_Download_SendInfo");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("userId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->userId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("roomId", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->roomId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("min", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->min);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sec", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->sec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("msec", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->msec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Video_Download_SendInfo &a, Video_Download_SendInfo &b) {
  using ::std::swap;
  swap(a.type, b.type);
  swap(a.userId, b.userId);
  swap(a.roomId, b.roomId);
  swap(a.min, b.min);
  swap(a.sec, b.sec);
  swap(a.msec, b.msec);
  swap(a.__isset, b.__isset);
}

Video_Download_SendInfo::Video_Download_SendInfo(const Video_Download_SendInfo& other4) noexcept {
  type = other4.type;
  userId = other4.userId;
  roomId = other4.roomId;
  min = other4.min;
  sec = other4.sec;
  msec = other4.msec;
  __isset = other4.__isset;
}
Video_Download_SendInfo& Video_Download_SendInfo::operator=(const Video_Download_SendInfo& other5) noexcept {
  type = other5.type;
  userId = other5.userId;
  roomId = other5.roomId;
  min = other5.min;
  sec = other5.sec;
  msec = other5.msec;
  __isset = other5.__isset;
  return *this;
}
void Video_Download_SendInfo::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Video_Download_SendInfo(";
  out << "type=" << to_string(type);
  out << ", " << "userId=" << to_string(userId);
  out << ", " << "roomId=" << to_string(roomId);
  out << ", " << "min=" << to_string(min);
  out << ", " << "sec=" << to_string(sec);
  out << ", " << "msec=" << to_string(msec);
  out << ")";
}


Video_Download_RecvInfo::~Video_Download_RecvInfo() noexcept {
}


void Video_Download_RecvInfo::__set_type(const int32_t val) {
  this->type = val;
}

void Video_Download_RecvInfo::__set_userId(const int32_t val) {
  this->userId = val;
}

void Video_Download_RecvInfo::__set_roomId(const int32_t val) {
  this->roomId = val;
}

void Video_Download_RecvInfo::__set_min(const int32_t val) {
  this->min = val;
}

void Video_Download_RecvInfo::__set_sec(const int32_t val) {
  this->sec = val;
}

void Video_Download_RecvInfo::__set_msec(const int32_t val) {
  this->msec = val;
}

void Video_Download_RecvInfo::__set_status(const int32_t val) {
  this->status = val;
}

void Video_Download_RecvInfo::__set_info(const std::string& val) {
  this->info = val;
}
std::ostream& operator<<(std::ostream& out, const Video_Download_RecvInfo& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Video_Download_RecvInfo::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->type);
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->userId);
          this->__isset.userId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->roomId);
          this->__isset.roomId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->min);
          this->__isset.min = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->sec);
          this->__isset.sec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->msec);
          this->__isset.msec = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->status);
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->info);
          this->__isset.info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Video_Download_RecvInfo::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Video_Download_RecvInfo");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("userId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->userId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("roomId", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->roomId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("min", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->min);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sec", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->sec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("msec", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->msec);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("info", ::apache::thrift::protocol::T_STRING, 8);
  xfer += oprot->writeString(this->info);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Video_Download_RecvInfo &a, Video_Download_RecvInfo &b) {
  using ::std::swap;
  swap(a.type, b.type);
  swap(a.userId, b.userId);
  swap(a.roomId, b.roomId);
  swap(a.min, b.min);
  swap(a.sec, b.sec);
  swap(a.msec, b.msec);
  swap(a.status, b.status);
  swap(a.info, b.info);
  swap(a.__isset, b.__isset);
}

Video_Download_RecvInfo::Video_Download_RecvInfo(const Video_Download_RecvInfo& other6) {
  type = other6.type;
  userId = other6.userId;
  roomId = other6.roomId;
  min = other6.min;
  sec = other6.sec;
  msec = other6.msec;
  status = other6.status;
  info = other6.info;
  __isset = other6.__isset;
}
Video_Download_RecvInfo& Video_Download_RecvInfo::operator=(const Video_Download_RecvInfo& other7) {
  type = other7.type;
  userId = other7.userId;
  roomId = other7.roomId;
  min = other7.min;
  sec = other7.sec;
  msec = other7.msec;
  status = other7.status;
  info = other7.info;
  __isset = other7.__isset;
  return *this;
}
void Video_Download_RecvInfo::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Video_Download_RecvInfo(";
  out << "type=" << to_string(type);
  out << ", " << "userId=" << to_string(userId);
  out << ", " << "roomId=" << to_string(roomId);
  out << ", " << "min=" << to_string(min);
  out << ", " << "sec=" << to_string(sec);
  out << ", " << "msec=" << to_string(msec);
  out << ", " << "status=" << to_string(status);
  out << ", " << "info=" << to_string(info);
  out << ")";
}


