#include <bits/stdc++.h>
#include <pthread.h>
#include <vector>

//任务对象
typedef class task_t {
public:
    void* ( *business )( void* );  //任务指针
    void* arg;                     //参数指针
public:
    task_t( void* ( *business )( void* ), void* arg );
    task_t(){};
} task_t;

//线程池对象
typedef class pthread_pool_t {

private:
    //需要管理线程数量
    int MAX_ThreadNum;
    int MIN_ThreadNum;
    int Alive_ThreadNum;
    int Working_ThreadNum;
    int Ready_ThreadNum;
    //线程数组 -tid数组
    std::vector< pthread_t > threadarray;
    //线程池开关
    bool IsOpen;
    //管理者tid
    pthread_t managertid;
    //缩减码
    int EXIT_NUM;
    //管理者时间
    int manager_sleeptime;

private:
    //内置一个任务环形队列
    std::vector< task_t > taskqueue;
    int                   taskqueue_head;     //头部表示下一个生成位置
    int                   taskqueue_tail;     //尾部表示下一个执行位置
    int                   taskqueue_maxsize;  //最大任务数量
    int                   taskqueue_nowsize;  //任务数量

private:
    //锁 条件变量
    pthread_cond_t  cd_customer;
    pthread_cond_t  cd_producer;
    pthread_mutex_t lock;

private:
    static void* thread_manager_work( void* );
    static void* thread_customer_work( void* );

private:
    void init( int thread_max, int thread_min, int queue_max );
    void destroy();

public:
    int finishwork;

public:
    void addwork( task_t task );
    void status();
    void Change_checks_frequency( int );
    void open();

public:
    pthread_pool_t( int thread_max, int thread_min, int queue_max );
    ~pthread_pool_t();
} pthread_pool_t;