#!/usr/bin/python
# _*_ coding: UTF-8 _*_

from BaseServer import BaseServer
import RequestParser
import ResponseHelper

import socket
import threading
import re

class HttpServer(BaseServer):
    'Http服务器'

    def __init__(self, host, port):
        '''
        初始化服务器相关的配置
        :param host: Http服务器监听的ip
        :param port: Http服务器监听的端口
        '''
        BaseServer.__init__(self, host, port)

    def __handler(self,client_sock):
        '''
        处理客户端请求，每到来一个用户请求都会生成一个新的线程处理请求
        :param client_sock: 将要处理的请求客户端socketobject
        '''
        req = client_sock.recv(1024)
        requestMap = RequestParser.getRequestMap(req)
        response = ResponseHelper.getResponseData(requestMap)
        client_sock.sendall(response)

        client_sock.close()

    def run(self):
        '''
        服务器运行入口
        '''
        server_sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        server_sock.bind((self.host,self.port))
        server_sock.listen(1)
        print "HttpServer is running at %s:%d" %(self.host,self.port)

        while 1:
            client_sock,addr = server_sock.accept()
            print("Request From: "+str(addr))
            t = threading.Thread(target=self.__handler, args=(client_sock,))
            t.start()
