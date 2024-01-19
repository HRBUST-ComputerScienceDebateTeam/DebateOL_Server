#include "jwt.h"

string JWT_token::jwt_create(const string secret , string iss , string aud , string iat , string exp ,map<string , string>mp ){
    JWT_token ret;
    ret.header["alg"] = "HS256";
    ret.header["typ"] = "jwt";

    ret.payload["iss"] = iss;//JWT 签发者
    ret.payload["iat"] = iat;//JWT 签发时间
    ret.payload["exp"] = exp;//JWT 过期时间
    ret.payload["aud"] = aud;//JWT 接收者

    if(mp.size() != 0){
        ret.payload.insert(mp.begin(), mp.end());
    }

    ret.signature = "";

    return jwt_encode(secret , ret);
}

//生成jwt token
string JWT_token::jwt_encode(const string secret , JWT_token ret  ){
    string s1 = Base64toBase64URL(Base64Encode(MapToJsonstring(ret.header)));
    string s2 = Base64toBase64URL(Base64Encode(MapToJsonstring(ret.payload)));
    ret.signature = sha256( s1 + '.' + s2 + '.' + secret );
    return s1 + '.' + s2 + '.' + ret.signature;
}


JWT_token JWT_token::jwt_decode(std::string s){
    //阶段
    JWT_token jwt_token;
    
    //找到分割符
    int pos1 = s.find('.');
    int pos2 = s.find('.' , pos1+1);

    //反序列化
    jwt_token.header  = JsonstringToMap(Base64Decode(Base64URLtoBase64(s.substr(0 , pos1))));
    jwt_token.payload = JsonstringToMap(Base64Decode(Base64URLtoBase64(s.substr(pos1+1 , pos2 - pos1 -1 ))));
    
    return jwt_token;
}



bool JWT_token::jwt_check_hash(const string secret , string s){
    //找到分割符
    int pos1 = s.find('.');
    int pos2 = s.find('.' , pos1+1);

    //进行base64的比较
    if(sha256(s.substr(0 , pos1) + "." + s.substr(pos1+1 , pos2-pos1 -1)+"." + secret) == s.substr(pos2+1)){
        return JWT_HASH_OK;
    }else{
        return JWT_HASHERR;
    }
}


int JWT_token::jwt_check_time(std::string str_jwt_token){
    time_t timnow ;
    time(&timnow);
    JWT_token jwt_token = jwt_decode(str_jwt_token);
    auto it = jwt_token.payload.find("exp");
    if( it != jwt_token.payload.end()){
            if((int64_t)timnow >= stoi(it->second)){
                /* 超时 - jwt已经不可用了 */
                return JWT_TIMEOUT;
            }else{
                return JWT_TIME_OK;
            }
    }else{
        //错误的jwt
        return JWT_NOLABELEXP;
    }
}

//创建延时的jwt_token给回去 //单位是s
std::string JWT_token::jwt_extratime( const string secret , std::string str_jwt_token , int tim ){
    //拆包 拿自己的钥匙哈希
    JWT_token jwt_token = jwt_decode(str_jwt_token);
    time_t timnow ;
    time(&timnow);
    jwt_token.payload["iat"] = std::to_string( (int64_t)timnow);
    jwt_token.payload["exp"] = std::to_string( (int64_t)timnow+ tim);
    return jwt_encode(secret,jwt_token);
}

map<string , string> JWT_token::getpayloadmap(){
    return this->payload;
}
