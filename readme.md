# DebateOL 服务端

当前平台: ubuntu 22.04

当前架构: 微服务架构

rpc服务框架: thrift 0.19.0


客户端：

opencv - 4.8.0

QT 6.6.0

架构图：
![png](./png/微服务架构.jpg)

---

## 运行流程

QT客户端 -> 封装http ->（可能nginx）-> 网关 -> http转对应结构体 -> (配置写死或服务注册中心 找到内网对应ip 和 端口) -> 发送给对应服务处理

QT客户端 <- 封装http <-（可能nginx）<- 网关 <- 对应结构体转http <- (配置写死或服务注册中心 找到内网对应ip 和端口) <- 对应服务处理

1. 启动frp
2. 启动web
3. 启动微服务

---

## 内网穿透

基于frp实现 公网部署frps 内网部署frpc 进行内网穿透

## webserver

我们需要一个入口 把从网关接收到的http请求包转发到各个微服务 这个入口就是Webserver

他需要具备以下能力

1. 开放端口对接frp 接受网关信息
2. 根据路由选择对应的微服务
3. 解析http包 反序列化 请求体转发过去
4. 微服务处理过后把对应的包进行返回
5. 序列化返回应答

抽象出两个工具类 ： 1. Http解析 路由  2. json序列化反序列化工具
