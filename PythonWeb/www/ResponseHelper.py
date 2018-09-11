# _*_ coding: UTF-8 _*_


#服务器的根目录，不允许访问该目录的父目录
_root_dir = "/home/dinghao/Documents/www"

def _getFileData(path):
    data = ''
    try:
        f = open(_root_dir+path,'r')
        data = f.read()
        f.close()
        data = 'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'+data
    except IOError as e:
        if e.errno==2:
            data = 'HTTP/1.1 404 NOT FOUND\r\nContentType: text/html\r\n\r\n<h1>404 NOT FOUND</h1>'
    return data

def getResponseData(request):
    return _getFileData(request['path'])
