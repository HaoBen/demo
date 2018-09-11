# _*_ coding: UTF-8 _*_

import re

def getRequestMap(req):
    requestMap = {}
    paramStrs = re.split(r'(\r\n)+',req)

    tmp = re.match(r'^(\w+)\s+([/\w\.]+)\s+(HTTP/\d\.\d)',paramStrs[0])
    requestMap['method'] = tmp.group(1)
    requestMap['path'] = tmp.group(2)
    requestMap['version'] = tmp.group(3)
    requestMap['content'] = paramStrs[-1]

    paramStrs = paramStrs[1:-1]
    for paramStr in paramStrs:
        tmp = re.match(r'^[\w\-]+',paramStr)
        if tmp:
            paramValue = re.match(r'[\w\-]+:\s*(.*)',paramStr).group(1)
            requestMap[tmp.group()] = paramValue
    return requestMap


