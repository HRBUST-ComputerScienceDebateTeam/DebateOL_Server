#include "openssl.h"

string sha256(string str){
    char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::string NewString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf,"%02x",hash[i]);
        NewString = NewString + buf;
    }
    return NewString;
}

std::string Base64Encode(string data)
{
    int size = data.length();
    size_t base64_len = (size + 2) / 3 * 4;
    if (base64_len == 0)
    {
        return "";
    }
    std::string ret;
    ret.resize(base64_len);
    EVP_EncodeBlock((unsigned char*)ret.data(), (const unsigned char *)data.data(), size);
    return std::move(ret);
}


std::string Base64Decode(std::string src)
{
    string out;
    size_t srcLen = src.size();
    if (srcLen % 4 != 0)
    {
        return "";
    }

    size_t destLen = (srcLen / 4) * 3;
    out.resize(destLen);

    //todo: 判断返回值
    int ret = EVP_DecodeBlock((unsigned char*)out.data(), (const unsigned char*)src.c_str(), (int)src.size());
    if (ret == -1)
    {
        //base64 decode failed
        return "";
    }
    int i = 0;
    while (src.at(--srcLen) == '=')
    {
        ret--;
        if (++i > 2)
        {
            // input maybe not base64 str;
            return "";
        }
    }
    out.resize(ret);
    return out;
}


std::string Base64toBase64URL(std::string s){
    //变符号 去除等号
    int len = s.length();
    string ret = s;
    for(int i = 0 ;i<len;i++){
        if(ret[i] == '+'){
            ret[i] = '-';
        }
        if(ret[i] == '/'){
            ret[i] = '_';
        }
        if(ret[i] == '='){
            ret = ret.substr(0 , i);
            break;
        }
    }
    return ret;
}

std::string Base64URLtoBase64(std::string s){
    //变符号 去除等号
    int len = s.length();
    string ret = s;
    for(int i = 0 ;i<len;i++){
        if(ret[i] == '-'){
            ret[i] = '+';
        }
        if(ret[i] == '_'){
            ret[i] = '/';
        }
    }

    //补齐长度为4的倍数
    if((len %4) == 0){
        return ret;
    }else if((len %4) == 1){
        ret+= "===";
        return ret;       
    }else if((len %4) == 2){
        ret+= "==";
        return ret;       
    }else{
        ret+= "=";
        return ret;       
    }
}