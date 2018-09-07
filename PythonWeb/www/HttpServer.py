#!/usr/bin/python
# _*_ coding: UTF-8 _*_

from BaseServer import BaseServer
import socket

class HttpServer(BaseServer):
    'Http服务器'

    def __init__(self, host, port):
        BaseServer.__init__(self, host, port)

    def sendfile(self,client,filename):
        f = open(filename,'r')
        data = f.read()
        f.close()
        client.sendall(data)

    def run(self):
        server_sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        server_sock.bind((self.host,self.port))
        server_sock.listen(1)
        print "HttpServer running at %s:%d" %(self.host,self.port)

        while 1:
            client,addr = server_sock.accept()
            print "Request From:%s------------------------" %("localhost")
            req = client.recv(1024)
            print req

            response = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
            client.sendall(response)
            self.sendfile(client,'./index.html')
            client.close()