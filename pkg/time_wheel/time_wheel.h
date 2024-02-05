#ifndef TIME_WHEEL
#define TIME_WHEEL
#include <bits/stdc++.h>
#include <tuple>
#include <vector>
using namespace std;

class Time_Wheel {
private:
    class WORK {
    public:
        int time_hour;
        int time_min;
        int time_sec;
        void* ( *workfn )( void* );
        void* arg;
        int   index;

    public:
        //生成work
        WORK( int index, int time, void* ( *workfn )( void* ), void* arg );
        void set_time( int time );
        ~WORK();
    };

private:
    //定时器相关的属性
    list< WORK* >     wheel_hour[ 24 ];
    list< WORK* >     wheel_min[ 60 ];
    list< WORK* >     wheel_sec[ 60 ];
    map< int, WORK* > work_mp;
    int               now_sec;
    int               now_min;
    int               now_hour;

private:
    //给出相隔时间 指定轮上时间
    int gen_wheel_time( int basetime, int time );
    //给出现在时间轮的时间戳
    int NowWheeltime();

public:
    //时间转换函数
    static tuple< int, int, int > time_decode( int );
    static int                    time_encode( tuple< int, int, int > );

public:
    //构造函数
    Time_Wheel();
    //析构函数
    ~Time_Wheel();

    //向下计时一秒
    //同时高层的任务会降落到低层
    //检查有没有任务 如果有执行任务
    void time_go();

    //添加任务
    void add_work( int index, int time, void* ( *workfn )( void* ), void* arg );

    //修改任务时间
    // int下表记录的信息 - timeoff为时间偏移量
    void change_work( int index, int timeoff );

    //删除任务
    void del_work( int index );

    //做任务
    void do_work( int index );

    //查看是否有这个任务记载
    bool find_work( int index );

    //查看任务人数
    int size();
};
#endif
