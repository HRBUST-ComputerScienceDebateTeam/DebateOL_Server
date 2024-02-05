tar_center = center.out

#路径
ServiceRegisty_path = ./
PKG_path = ../../pkg/
Thread_path = $(PKG_path)pool/
JsonMap_path = $(PKG_path)JsonChange/
time_wheel_path = $(PKG_path)time_wheel/

#特定文件
Thread_cpp = $(Thread_path)threadpool.cpp
ServiceRegisty_cpp = $(ServiceRegisty_path)ServiceRegistry.cpp
JsonMap_cpp = $(JsonMap_path)jsonchange.cpp
time_wheel_cpp = $(time_wheel_path)time_wheel.cpp


#依赖路径和选项
Lib = $(Simple_path) 
Lib2 = $(Thread_path)
Lib3 = $(JsonMap_path)
Lib5 = $(time_wheel_path) 
Flags = -lthrift -lpthread


#任务
Make_Center:$(Thread_cpp) $(ServiceRegisty_cpp)  $(JsonMap_cpp) $(time_wheel_cpp)
	g++ $^ -I$(Lib) -I$(Lib2)  -I$(Lib3) -I$(Lib5) -o $(tar_center) $(Flags)

clean: $(tar_server) $(tar_client) $(tar_sidecar) $(tar_center)
	-rm $^
