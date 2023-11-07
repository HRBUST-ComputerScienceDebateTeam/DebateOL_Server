# BUG

1. 大量请求下 会出现 `terminate called after throwing an instance of 'apache::thrift::transport::TTransportException' ` 报错 服务器崩掉

   定位问题：

   1. 问题发生在接收方
   2. 接收到的http请求是分离开来的
      ![bug1](../png/bug1.png)
      问题处理：
      问题产生原因： 未知
      问题解决方法： 接收方进行检验 如果接受的http请求 并不是一个完整的包 就进行等待 等待包变得完整 或者结束了流 才结束通讯
      解决效果：
      ![bug2](../png/bug2.png)
2. 客户端编码问题 中文
   转QString解决
3. 微服务导致web崩溃问题 - 异常处理
4. 客户端 网络发送失败的崩溃问题
5. 并发崩溃问题

   1. rpc内部定义了全局变量使用冲突
6. web - IP地址问题
