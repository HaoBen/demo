#!/usr/bin/python
# _*_ coding: UTF-8 _*_

from HttpServer import HttpServer

if __name__=='__main__':
    server = HttpServer("127.0.0.1",8888)
    server.run()