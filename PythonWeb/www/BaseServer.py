#!/usr/bin/python
# _*_ coding: UTF-8 _*_

class BaseServer:
    '服务器基类，可以派生出HTTP，FTP等服务器'
    host = ''   #绑定的ip
    port = 0    #监听的端口

    def __init__(self, host, port):
        self.host = host
        self.port = port
