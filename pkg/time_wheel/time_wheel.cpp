#include "./time_wheel.h"



Time_Wheel::WORK::WORK(int index , int time, void* workfn, void * arg){
    this->index = index;
    this->workfn = workfn;
    this->arg = arg;
    set_time(time);
}
Time_Wheel::WORK::~WORK(){
    if(arg){
        delete arg;
    }
}

void Time_Wheel::WORK::set_time(int time){
    auto timetuple = time_decode(time);
    this->time_hour = get<0>(timetuple);
    this->time_min = get<1>(timetuple);
    this->time_sec = get<2>(timetuple);
}

tuple<int ,int ,int> Time_Wheel::time_decode(int in){
    int sec = in%60;
    in/=60;
    int min = in%60;
    in/=60;
    int hour = in%24;
    in/=24;

    return {hour , min , sec};
}

int Time_Wheel::time_encode(tuple<int ,int ,int> in){
    int hour = get<0>(in);
    int min = get<1>(in);
    int sec = get<2>(in);
    return hour*24*60 + min * 60 + sec;
}

Time_Wheel::Time_Wheel(){
    this->now_sec = 0;
    this->now_min = 0;
    this->now_hour = 0;
    return;
}

Time_Wheel::~Time_Wheel(){
    for(auto it = work_mp.begin();it!=work_mp.end();it++ ){
        delete it->second;
    }
    work_mp.clear();
}

void Time_Wheel::time_go(){
    //向下计时一秒
    //同时高层的任务会降落到低层
    //检查有没有任务 如果有执行任务
    if((++this->now_sec) == 60){
        this->now_sec = 0;
        if((++this->now_min) == 60){
            this->now_min = 0;
            if((++this->now_hour) == 24){
                this->now_hour = 0;
            }
        }
    }

    //判断新的点上有没有任务
    if(!wheel_hour[now_hour].empty()){
        //任务向下转移
        for(auto it : wheel_hour[now_hour]){
            //转移向对应任务的min
            wheel_min[it->time_min].push_back(it);
        }
    }
    if(!wheel_min[now_min].empty()){
        //任务向下转移
        for(auto it : wheel_hour[now_min]){
            //转移向对应任务的min
            wheel_min[it->time_sec].push_back(it);
        }
    }
    if(!wheel_sec[now_sec].empty()){
        //工作
        for(auto it : wheel_hour[now_sec]){
            do_work(it->index);
            //mp清除
            work_mp.erase(it->index);
        }
        //节点回收
        wheel_sec[now_sec].clear();
    }


}

void Time_Wheel::add_work(int index , int time , void * workfn , void * arg){
    //添加任务
    int basetime = time_encode({now_hour , now_min , now_sec});
    int aimtime = gen_wheel_time(basetime, time);

    //挂载任务节点
    work_mp[index] = new WORK(index , aimtime , workfn , arg);
    auto timetuple = time_decode(aimtime);
    if(get<0>(timetuple) != now_hour){
        wheel_hour[get<0>(timetuple)].push_back(work_mp[index]);
        return;
    }
    if(get<1>(timetuple) != now_min){
        wheel_min[get<1>(timetuple)].push_back(work_mp[index]);
        return;
    }
    if(get<2>(timetuple) != now_sec){
        wheel_sec[get<2>(timetuple)].push_back(work_mp[index]);
        return;
    }
    
}

void Time_Wheel::change_work(int index , int timeoff){
    //修改任务时间
    //int下表记录的信息 - timeoff为时间偏移量
    //添加任务
    WORK * aimwork = work_mp[index];
    int basetime = time_encode({aimwork->time_hour , aimwork->time_min, aimwork->time_sec});
    int aimtime = gen_wheel_time(time_encode({aimwork->time_hour , aimwork->time_min , aimwork->time_sec}), timeoff);

    //遍历删除 TODO 优化
    for(auto it =  wheel_hour[aimwork->time_hour].begin() ; it!= wheel_hour[aimwork->time_hour].end();it++){
        if((*it)->index == index){
            wheel_hour[aimwork->time_hour].erase(it);
            break;
        }
    }
    for(auto it =  wheel_min[aimwork->time_min].begin() ; it!= wheel_min[aimwork->time_min].end();it++){
        if((*it)->index == index){
            wheel_min[aimwork->time_min].erase(it);
            break;
        }
    }
    for(auto it =  wheel_sec[aimwork->time_sec].begin() ; it!= wheel_sec[aimwork->time_sec].end();it++){
        if((*it)->index == index){
            wheel_sec[aimwork->time_sec].erase(it);
            break;
        }
    }

    //挂载任务节点
    aimwork->set_time(aimtime);

    auto timetuple = time_decode(aimtime);
    if(get<0>(timetuple) != now_hour){
        wheel_hour[get<0>(timetuple)].push_back(work_mp[index]);
        return;
    }
    if(get<1>(timetuple) != now_min){
        wheel_min[get<1>(timetuple)].push_back(work_mp[index]);
        return;
    }
    if(get<2>(timetuple) != now_sec){
        wheel_sec[get<2>(timetuple)].push_back(work_mp[index]);
        return;
    }

}

void Time_Wheel::del_work(int index){
    //删除任务
    WORK* aimwork = work_mp[index];
    //链表遍历删除 TODO 优化
    for(auto it =  wheel_hour[aimwork->time_hour].begin() ; it!= wheel_hour[aimwork->time_hour].end();it++){
        if((*it)->index == index){
            wheel_hour[aimwork->time_hour].erase(it);
            break;
        }
    }
    for(auto it =  wheel_min[aimwork->time_min].begin() ; it!= wheel_min[aimwork->time_min].end();it++){
        if((*it)->index == index){
            wheel_min[aimwork->time_min].erase(it);
            break;
        }
    }
    for(auto it =  wheel_sec[aimwork->time_sec].begin() ; it!= wheel_sec[aimwork->time_sec].end();it++){
        if((*it)->index == index){
            wheel_sec[aimwork->time_sec].erase(it);
            break;
        }
    }
    //释放资源
    work_mp.erase(index);
}

//给出相隔时间 指定轮上时间
int Time_Wheel::gen_wheel_time(int basetime , int offtime){
    tuple<int ,int ,int> toff = time_decode(offtime);
    tuple<int ,int ,int> tbase = time_decode(basetime);
    int new_hour = get<0>(tbase) + get<0>(toff);
    int new_min = get<1>(tbase) + get<1>(toff);
    int new_sec = get<2>(tbase) + get<2>(toff);

    int add = 0;
    add = new_sec/60;
    new_sec%=60;

    add = (new_min + add ) /60;
    new_min%=60;

    new_hour = (new_hour+add )%24;
    return time_encode({new_hour , new_min ,new_sec});
}
//给出现在时间轮的时间戳 
int Time_Wheel::NowWheeltime(){
    return time_encode({now_hour , now_min , now_sec});
}