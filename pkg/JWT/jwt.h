#include "../JsonChange/jsonchange.h"
#include "../Openssl/openssl.h"
#include "./secret.h"  //secret密钥
#include <bits/stdc++.h>
#include <cstdint>
#include <regex>
#include <string>
using namespace std;

/* 错误定义 */
#define JWT_NOLABELEXP 2
#define JWT_HASHERR 1
#define JWT_TIMEOUT 1
#define JWT_TIME_OK 0
#define JWT_HASH_OK 0

//定义类型
typedef class JWT_token {

private:
    // header 存放类型以及加密方法
    std::map< std::string, std::string > header;

    // payload
    std::map< std::string, std::string > payload;

    // Signature
    std::string signature;

private:
    // iss（JWT的签发者）, iat(issued at，签发时间) , exp（expires,到期时间）,aud（JWT接收者）
    //可以有更多的
    JWT_token( const JWT_token& ){};
    JWT_token( const JWT_token&& ) noexcept {};
    JWT_token( JWT_token&& ) noexcept {};
    JWT_token( JWT_token& ){};
    JWT_token(){};
    bool operator=( JWT_token& that ){};

public:
    //无需密码
    // getmap 返回payload
    map< string, string > getpayloadmap();
    map< string, string > getheadermap();

    //反序列化
    // xxxx.yyyy.zzz -> JWT_token
    static JWT_token jwt_decode( std::string s );

    //检验时间是否过期
    static int jwt_check_time( std::string str_jwt_token );

    //需要密码
    //创建一个序列化之后的jwt
    static string jwt_create( const string secret, string iss, string aud, string iat, string exp, map< string, string > mp = map< string, string >() );

    //创建延时的jwt_token给回去 //单位是s
    static string jwt_extratime( const string secret, std::string str_jwt_token, int tim );

    //整个串变成jwt要求的字符串
    // xxxx.yyyy.zzz -> JWT_token
    static std::string jwt_encode( const string secret, JWT_token& ret );

    //检查标签合法化 指第三部分
    static bool jwt_check_hash( const string secret, string s );

} JWT_token;

//用户鉴权
//三部分 ： 头部 负载 签名
//签名 ： sha(头部 base64 + '.' + 负载 base64 + '.' + 密钥);
// jwt 头部base64 + '.' + 负载 base64 (时间) + 签名
