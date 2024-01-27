#include <bits/stdc++.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
using namespace std;

string sha256( string str );

std::string Base64Encode( std::string data );
std::string Base64Decode( std::string src );
std::string Base64toBase64URL( std::string s );
std::string Base64URLtoBase64( std::string s );
//-lssl -lcrypto