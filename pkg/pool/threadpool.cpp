#include <asm-generic/errno-base.h>
#include <bits/stdc++.h>
#include <cstring>
#include <pthread.h>
#include "./threadpool.h"
using namespace std;

//任务
task_t::task_t(void* (*business)(void *) ,void* arg ){
    this->business = business;
    this->arg = arg;
}

pthread_pool_t::pthread_pool_t(int thread_max , int thread_min , int queue_max){
    init(thread_max,thread_min , queue_max);
}

pthread_pool_t::~pthread_pool_t(){
    destroy();
}

void* pthread_pool_t::thread_manager_work(void*arg ){
    pthread_pool_t* ptr = (pthread_pool_t*)arg;    
    // //监视 - 扩容缩容
    while(true){
        pthread_mutex_lock(&ptr->lock);
        //ptr->status();
    //     //cout << "debug: maneger get lock" <<endl;
    //     //扩容
        if(ptr->taskqueue_nowsize >= ptr->Alive_ThreadNum){
            //cout << "debug: manger 准备扩容1" <<endl <<endl <<endl <<endl;
            int ADDNUM = min(ptr->MAX_ThreadNum , ptr->Alive_ThreadNum*2) - ptr->Alive_ThreadNum;
            //cout << "debug: manger 扩容 " << ADDNUM << "个线程" <<endl;
            for(int i = 1;(i<=ptr->MAX_ThreadNum) && (ADDNUM>0);i++){
                if((ptr->threadarray[i-1] == 0 )||(pthread_kill(ptr->threadarray[i-1], 0) != 0) ){
                    ADDNUM -- ;
                    ptr->Alive_ThreadNum++;
                    ptr->Ready_ThreadNum++;
                    int err = pthread_create(&ptr->threadarray[i-1], NULL,&pthread_pool_t::thread_customer_work,arg);    
                    if(err != 0){
                        switch(err){
                            case EAGAIN:
                                cerr << "管理员扩充失败： 创建线程-系统资源不足" << endl;
                                break;
                            case EINVAL:
                                cerr << "管理员扩充失败： 创建线程-传入参数无效" << endl;
                                break;
                            case EPERM:
                                cerr << "管理员扩充失败： 创建线程-参数某些值非法" <<endl;
                                break;
                            default:
                                cerr << "管理员扩充失败： 创建线程-未知错误" <<endl;
                                break;
                        }
                        exit(0);
                    }
                }
            }
        }else if((ptr->Alive_ThreadNum< ptr->MAX_ThreadNum )&&( ptr->Working_ThreadNum >= ptr->Alive_ThreadNum*0.7 )){
            //cout << "debug: manger 准备扩容2" <<endl <<endl <<endl <<endl;
            //当前忙线程占到了70% 
            //扩容到50%
            int ADDNUM = min(ptr->MAX_ThreadNum , ptr->Working_ThreadNum*2) - ptr->Alive_ThreadNum;
            //cout << "debug: manger 扩容 " << ADDNUM << "个线程" <<endl;
            for(int i = 1;(i<=ptr->MAX_ThreadNum) && (ADDNUM>0);i++){
                if((ptr->threadarray[i-1] == 0 )||(pthread_kill(ptr->threadarray[i-1], 0) != 0) ){
                    ADDNUM -- ;
                    ptr->Alive_ThreadNum++;
                    ptr->Ready_ThreadNum++;
                    int err = pthread_create(&ptr->threadarray[i-1], NULL,&pthread_pool_t::thread_customer_work,arg);    
                    if(err != 0){
                        switch(err){
                            case EAGAIN:
                                cerr << "管理员扩充失败： 创建线程-系统资源不足" << endl;
                                break;
                            case EINVAL:
                                cerr << "管理员扩充失败： 创建线程-传入参数无效" << endl;
                                break;
                            case EPERM:
                                cerr << "管理员扩充失败： 创建线程-参数某些值非法" <<endl;
                                break;
                            default:
                                cerr << "管理员扩充失败： 创建线程-未知错误" <<endl;
                                break;
                        }
                        exit(0);
                    }
                }
            }
        }else if((ptr->Alive_ThreadNum> ptr->MIN_ThreadNum )&&( ptr->Ready_ThreadNum >= ptr->Alive_ThreadNum*0.7 )){
            //当前闲线程占到了70% 
            //缩容到50%
            int DELNUM = ptr->Alive_ThreadNum - max(ptr->MIN_ThreadNum , ptr->Working_ThreadNum*2);
            ptr->EXIT_NUM = DELNUM;
            //cout << "debug: manger 缩容 " << DELNUM << "个线程" <<endl;
            for(int i = 1;i<=DELNUM ;i++){
                pthread_cond_signal(&ptr->cd_customer);
            }
        }
        //ptr->status();
        pthread_mutex_unlock(&ptr->lock);
        
    //     //cout << "debug: maneger give up lock" <<endl;
    //     //刷新时间
        usleep(ptr->manager_sleeptime);
    }
    

}

//没有任务时 阻塞挂在条件变量上
void* pthread_pool_t::thread_customer_work(void* arg){
    pthread_pool_t* ptr = (pthread_pool_t*)arg;
    task_t task;
    while(true){
        pthread_mutex_lock(&ptr->lock);
        
        if(ptr->taskqueue_nowsize == 0){
            pthread_cond_wait(&ptr->cd_customer , &ptr->lock);
            if(ptr->EXIT_NUM >0){
                ptr->EXIT_NUM--;
                ptr->Alive_ThreadNum--;
                ptr->Ready_ThreadNum--;
                pthread_mutex_unlock(&ptr->lock);
                pthread_exit(0);
            }
        }
        //cout << "debug: customer get lock" <<endl;
        if(ptr->IsOpen){
            //启动状态 就去使用
            //取出来一个任务
            task = ptr->taskqueue[ptr->taskqueue_tail];
            if(*task.business == nullptr){
                pthread_mutex_unlock(&ptr->lock);
                continue;
            }
            //debug;
            ptr->taskqueue[ptr->taskqueue_tail].business = nullptr;
            ptr->taskqueue_tail = (ptr->taskqueue_tail+1)%ptr->taskqueue_maxsize;
            ptr->taskqueue_nowsize--;
            if(ptr->taskqueue_nowsize == ptr->taskqueue_maxsize-1){
                pthread_cond_signal(&ptr->cd_producer);
            }
            //执行任务
            ptr->Working_ThreadNum++;
            ptr->Ready_ThreadNum--;
            //cout << "startwork 1" <<endl;
        }
        pthread_mutex_unlock(&ptr->lock);
        
        if(*task.business != nullptr){
            (*task.business)(task.arg);  
            pthread_mutex_lock(&ptr->lock);
            
            //cout << "finishwork 2" <<endl;
            ptr->Ready_ThreadNum++;
            ptr->Working_ThreadNum--;
            ptr->finishwork++;
            pthread_mutex_unlock(&ptr->lock);
            
           //cout << "debug: customer giveup lock" <<endl;
        }
    }
    
}

void pthread_pool_t::init(int thread_max , int thread_min , int queue_max){
    int err ;

    //任务队列
    taskqueue.resize(queue_max);
    taskqueue_head = 0;
    taskqueue_tail = 0;
    taskqueue_maxsize = queue_max;
    taskqueue_nowsize = 0;

    //锁 条件变量
    if(pthread_cond_init(&cd_customer, NULL) != 0 ){
        cerr << "条件变量的初始化失败" <<endl;
    }
    if(pthread_cond_init(&cd_producer, NULL) != 0){
        cerr << "条件变量的初始化失败" <<endl;
    }
    if(pthread_mutex_init(&lock , NULL) != 0){
        cerr << "锁的初始化失败"<<endl;
        exit(0);
    }

    //缩减码和间隔时间
    EXIT_NUM = 0;
    manager_sleeptime = 1000000;
    finishwork = 0;

    //初始化线程列表的大小
    MAX_ThreadNum = thread_max;
    MIN_ThreadNum = thread_min;
    IsOpen = false;
    //扩充线程数组
    threadarray.resize(MAX_ThreadNum);
    for(int i = 1;i<=MAX_ThreadNum;i++){
        threadarray[i-1]= 0;
    }
    for(int i = 1;i<=MIN_ThreadNum;i++){
        //创建最少量个线程
        err = pthread_create(&threadarray[i-1], NULL,&pthread_pool_t::thread_customer_work,(void*)this);    
        if(err != 0){
            switch(err){
                case EAGAIN:
                    cerr << "线程池初始化失败： 初始创建线程-系统资源不足" << endl;
                    break;
                case EINVAL:
                    cerr << "线程池初始化失败： 初始创建线程-传入参数无效" << endl;
                    break;
                case EPERM:
                    cerr << "线程池初始化失败： 初始创建线程-参数某些值非法" <<endl;
                    break;
                default:
                    cerr << "线程池初始化失败： 初始创建线程-未知错误" <<endl;
                    break;
            }
            exit(0);
        }
        pthread_detach(threadarray[i-1]);
    }
    
    //创建管理者线程
    err = pthread_create(&managertid, NULL,&pthread_pool_t::thread_manager_work,(void*)this);
    if(err != 0){
        switch(err){
            case EAGAIN:
                cerr << "线程池初始化失败： 管理者线程-系统资源不足" << endl;
                break;
            case EINVAL:
                cerr << "线程池初始化失败： 管理者线程-传入参数无效" << endl;
                break;
            case EPERM:
                cerr << "线程池初始化失败： 管理者线程-参数某些值非法" <<endl;
                break;
            default:
                cerr << "线程池初始化失败： 管理者线程-未知错误" <<endl;
                break;
        }
        exit(0);
    }
    pthread_detach(managertid);
    Alive_ThreadNum = MIN_ThreadNum;
    Working_ThreadNum = 0;
    Ready_ThreadNum = MIN_ThreadNum;


}
void pthread_pool_t::addwork(task_t task){
    //status();
    //如果任务满了 需要挂起在条件变量上
    //如果任务为空 要添加并且发送条件变量通知消费者
    pthread_mutex_lock(&lock);
    
    if(taskqueue_maxsize == taskqueue_nowsize){//满了 挂起
        pthread_cond_wait(&cd_producer,&lock);
    }
    //添加任务
    //cout << "debug: producer get lock" <<endl;
    taskqueue[taskqueue_head] = task;
    taskqueue_head = (taskqueue_head+1)%taskqueue_maxsize;
    taskqueue_nowsize++;
    //如果只有这一个任务唤醒消费者
    if(taskqueue_nowsize == 1){
        pthread_cond_signal(&cd_customer);
    }
    pthread_mutex_unlock(&lock);
    
    //cout << "debug: producer giveup lock" <<endl;
}

void pthread_pool_t::status(){
    cout <<"********************************"<<endl;
    cout << "finishwork        :" << finishwork        <<endl;
    cout << "manager_sleeptime :" << manager_sleeptime <<endl;
    cout << "EXIT_NUM          :" << EXIT_NUM          <<endl;
    cout << "MAX_ThreadNum     :" << MAX_ThreadNum     <<endl;
    cout << "MIN_ThreadNum     :" << MIN_ThreadNum     <<endl;
    cout << "Alive_ThreadNum   :" << Alive_ThreadNum   <<endl;
    cout << "Working_ThreadNum :" << Working_ThreadNum <<endl;
    cout << "Ready_ThreadNum   :" << Ready_ThreadNum   <<endl;
    cout << "IsOpen            :" << IsOpen            <<endl;
    cout << "managertid        :" << managertid        <<endl;
    cout << "taskqueue_head    :" << taskqueue_head    <<endl;
    cout << "taskqueue_tail    :" << taskqueue_tail    <<endl;
    cout << "taskqueue_maxsize :" << taskqueue_maxsize <<endl;
    cout << "taskqueue_nowsize :" << taskqueue_nowsize <<endl;
    cout <<"********************************"<<endl;
}

void pthread_pool_t::destroy(){
    //先清空信号量再关闭
    pthread_cond_broadcast(&cd_customer);
    pthread_cond_broadcast(&cd_producer);

    //锁 条件变量
    pthread_cond_destroy(&cd_customer);
    pthread_cond_destroy(&cd_producer);
    pthread_mutex_destroy(&lock);
    //销毁线程
    for(auto it:threadarray){
        if(it == 0) continue;
        if(pthread_kill(it, 0)){
            pthread_cancel(it);
        }
    }
    //管理者
    pthread_cancel(managertid);
}
void pthread_pool_t::open(){
    IsOpen = true;
}
void pthread_pool_t::Change_checks_frequency(int x){
    manager_sleeptime = x;
}