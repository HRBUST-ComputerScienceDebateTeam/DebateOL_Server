#include "jsonchange.h"

std::map< std::string, std::string > JsonstringToMap( std::string s ) {
    //每一排切割
    //正则 非贪心
    std::regex                           reg( "\"(.+?)\":\"(.*?)\"" );
    std::map< std::string, std::string > mpret;
    std::cmatch                          m;
    bool                                 ret    = 1;
    int                                  offlen = 0;
    while ( ret ) {
        std::smatch m;
        std::string snow = s.substr( offlen );
        ret              = std::regex_search( snow, m, reg );
        if ( ret != 0 ) {
            mpret[ m[ 1 ].str() ] = m[ 2 ].str();
            offlen += m.position( 0 ) + m.length( 0 );
        }
    }
    return mpret;
}
std::string MapToJsonstring( std::map< std::string, std::string > mp ) {
    // map->json
    std::string ret = "{";
    for ( auto it : mp ) {
        ret += "\"";
        ret += it.first;
        ret += "\":";

        ret += "\"";
        ret += it.second;
        ret += "\",";
    }
    ret[ ret.length() - 1 ] = '}';
    return ret;
}