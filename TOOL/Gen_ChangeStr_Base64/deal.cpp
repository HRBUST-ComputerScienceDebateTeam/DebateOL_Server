





//输入的是 thrift里面的结构体 
//输出的转换函数 make_json_struct 里面的结构体 
//第一个文件是头文件 gen_code1
//第一个文件是cpp文件 gen_code2

// struct Echo_SendInfo {
//     1:i32 id,
//     2:string info
// }
// Echo_Send ChangeStr_decodebase64(Echo_Send & a){
//     a.info = Base64Decode(a.info)
// }
// Echo_Send ChangeStr_encodebase64(Echo_Send & a){
//     a.info = Base64Encode(a.info)
// }

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;


int main(int argc , char ** argv){
    if(argc != 2){
        cerr << "input one file" <<endl;
        return 0;
    }
    fstream input;
    input.open(argv[1] , ios::out | ios::in );
    fstream output1 , output2 , output3;
    output1.open("./gen-code1.txt" , ios::out | ios::in |ios::trunc);
    output2.open("./gen-code2.txt" , ios::out | ios::in |ios::trunc);
    output3.open("./gen-code3.txt" , ios::out | ios::in |ios::trunc);


    string unused;
    string s;
    string struct_name;
    while(input>>unused){
        if(unused == "service") break;
		if(unused != "struct") continue;//处理备注 备注只能单行位于结构体上面
        //处理第一行
        input >> struct_name;
        input >> unused;
        // Echo_Send ChangeStr_decodebase64(Echo_Send & x){
        output1 << struct_name  << " ChangeStr_decodebase64(" <<struct_name <<  " & x"  << "){\n";
        output2 << struct_name  << " ChangeStr_encodebase64(" <<struct_name <<  " & x"  << "){\n";
        output3 << struct_name  << " ChangeStr_encodebase64(" <<struct_name <<  " & x"  << ");\n";
        output3 << struct_name  << " ChangeStr_decodebase64(" <<struct_name <<  " & x"  << ");\n";
        while(input >> s){
            if(s == "}"){//结束
                break;
            }
            int pos = s.find(":");
            //获取id
            string s1 = s.substr(0,pos);
            
            //获取类型
            string s2 = s.substr(pos+1,s.length() - pos);
            
            //获取名称
            input >> s;
            if(s[s.size()-1] == ','){
                s =s.substr(0,s.size()-1);
            }
            if(s2 == "string"){
                output1 << "\tx." << s << " = Base64Decode(" << "x." << s << ");\n";
                output2 << "\tx." << s << " = Base64Encode(" << "x." << s << ");\n";   
            }
        }
        output1 << "\treturn x;\n";
        output2 << "\treturn x;\n";
        output1<<"}\n\n";
        output2<<"}\n\n";
    }
    
    input.close();
    output1.close();
    output2.close();
    output3.close();
}
