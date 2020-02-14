#!/bin/sh
WORKDIR=$PWD

#创建根目录结构
mkdir -p diff/lib
mkdir -p diff/lib64
mkdir -p diff/bin

#编译restserver
cd restserver && make && cd $WORKDIR

#拷贝文件到diff目录
cp restserver/restserver diff/bin/
cp /lib64/ld-linux-x86-64.so.2 diff/lib64/
for item in `ldd diff/bin/restserver | awk '{print $3}'`
do
	cp $item diff/lib
done
chmod u+x diff/lib/*

#构建镜像
docker build -t restdemo .
