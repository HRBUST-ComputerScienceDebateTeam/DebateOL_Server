#pragma once
#include <bits/stdc++.h>
#include <mysql/mysql.h>
//类型1 mysql的封装
//类型2 mysql结果集合的封装
class DBRES {
public:
    int OKflag;
    int num_row;        //行
    int num_fields;     //列
    int affected_rows;  //影响的行数
public:
    std::string                               errinfo;
    std::vector< std::vector< std::string > > v;

public:
    bool checkerr( std::string& sql );
};

class DB_MYSQL {
public:
    MYSQL* mysql;
    DBRES* res;
    bool   initflag;
    bool   trxflag;

public:
    DB_MYSQL();
    ~DB_MYSQL();
    bool   isinit();
    DBRES* DB_init( const char* host, const char* user, const char* passwd, const char* db, unsigned int port );
    DBRES* exec( std::string s );
    bool   start_transaction();     //开启事务
    bool   commit_transaction();    //提交事务
    bool   rollback_transaction();  //回滚事务
    bool   Is_transactioning();     //是否在事务中
};
