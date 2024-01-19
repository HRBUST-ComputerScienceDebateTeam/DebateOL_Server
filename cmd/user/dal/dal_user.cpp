//提供访问数据库的方法
#include "dal_user.h"
#include "dal_userconfig.h"
#include <bits/stdc++.h>


//建立连接 - 数据库(TODO:redis)

//提供交互函数

//完善tomap函数
map<string , string> DAL_User_Base::toMap(){
    map<string , string>mp;
    SettoMap(Userid)          ;         
    SettoMap(Usernum)         ;          
    SettoMap(Passwd)          ;         
    SettoMap(Tel)             ;      
    SettoMap(UserRegtime)     ;              
    SettoMap(UserLasttime)    ;               
    SettoMap(Salt)            ;       
    return mp;
}

map<string , string> DAL_User_Social::toMap(){
    map<string , string>mp;
    SettoMap(Userid)   ;                            
    SettoMap(Username) ;                              
    SettoMap(Headshot) ;                              
    SettoMap(Sex)      ;                         
    SettoMap(Signature);                               
    SettoMap(Contact)  ;     
    return mp;
}

map<string , string> DAL_User_Extra::toMap(){
    map<string , string>mp;
    SettoMap(Userid)             ;       
    SettoMap(IntentionToArgue)   ;                 
    SettoMap(MatcheNum)          ;          
    SettoMap(BestPlayerNum)      ;              
    SettoMap(VectoryNum)         ;           
    SettoMap(OnePosNum)          ;          
    SettoMap(TwoPosNum)          ;          
    SettoMap(ThreePosNum)        ;            
    SettoMap(FourPosNum)         ;
    return mp;
}