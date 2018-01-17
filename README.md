# client-server-socket

这个项目开源了基本的socket网络通讯实现方法，有需要的朋友可以直接使用。
目前实现了如下的需求：

1 . 使用linux c++，实现一个client和server，要求对功能做一些简单的封装，设计成几个简单的类，使用Makefile进行依赖管理；

2 . client使用连接池技术管理与服务器的通信，主线程间隔1s从连接池中取到一个连接，发送到server端，请求的格式为json，其中只有一个key为id；

3 . server使用epoll+多线程进行设计，工作线程取到client的请求后，响应一段protobuf格式的内容，形如：value:xxx，其中，xxx的值为id+1；

4 . client读到响应后，将响应的内容反序列化，并打印到日志文件，日志格式自定义（日志库可以使用开源的，如果没用过的话，可以网上了解）；

5 . client和server相关的配置通过配置文件进行设计，配置文件可以是纯文本形式，也可以是json格式。

# 运行结果演示
![client-server-socket](assets/result)

