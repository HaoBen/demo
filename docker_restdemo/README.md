# 这是一个制作docker镜像演示demo
>通过这个demo可以加深你对docker镜像的了解

## 1. 目录结构
```
.
├── build.sh                            #控制镜像制作过程的shell脚本
├── diff                                #diff会直接被拷贝为镜像的根目录
├── Dockerfile                          #docker的构建系统需要使用的脚本
├── README.md                           
└── restserver                          #基于cpprestsdk开发的rest服务器
    ├── include
    │   ├── handler.h
    │   └── stdafx.h
    ├── main.cpp
    ├── Makefile
    └── src
        └── handler.cpp
```

## 2. 使用方式
>为了保证docker镜像不那么臃肿，这里采用的是在宿主机编译，然后拷贝可执行文件到镜像中的方式

>请确认你的机器上已经安装了docker和libcpprest-dev

1. 执行`./build.sh`，正常情况下会成功，使用`docker images`会看到刚才制作的名为restdemo的镜像
2. 基于restdemo启动一个容器，`docker run -p 8081:8080 restdemo`。`-p 8081:8080`表示建立宿主机8081端口和容器端口8080的映射。
3. 测试一下，用`curl -H "Content-Type:application/json" -X POST --data '{"mesAsk":"Hello","asker":"dinghao188"}' http://127.0.0.1/rest/ask`，大概会看到下面的类似输出。关于这个REST服务的功能结构，[请看这里](restserver/README.md)。
