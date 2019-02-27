#include "http.h"
#include "system.h"
#include "utils.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

/*----------------------------HttpRequest类----------start----------------------------------*/

/* 使用缓存的请求信息构造该类 */
HttpRequest::HttpRequest(string buf, Server *context) {
    /* 保存服务器上下文对象的指针 */
    this->serverContext = context;

    try {
        /* 解析请求方法 */
        string::size_type start = 0,end = 0;
        end = buf.find_first_of(" ",start);
        requestMethod.append(buf,start,end-start);
        /* 解析请求资源 */
        start = buf.find_first_not_of(" ",end);
        end = buf.find_first_of(" ",start);
        requestUrl.append(buf,start,end-start);
        /* 解析请求版本 */
        start = buf.find_first_not_of(" ",end);
        end = buf.find("\r\n",start);
        requestVersion.append(buf,start,end-start);
        /* 解析请求头 */
        start = buf.find_first_not_of("\r\n",end);
        end = buf.find("\r\n\r\n",start);
        vector<string> headers = Utils::splitString(buf.substr(start,end-start),"\r\n");
        for(vector<string>::iterator it = headers.begin(); it != headers.end(); ++it) {
            string::size_type s = 0,e = 0;
            string name,value;
            e = (*it).find_first_of(":",s);
            name.append((*it),s,e-s);
            s = (*it).find_first_not_of(": ",e);
            value.append((*it),s);
            requestHeaders.insert(pair<string,string>(name,value));
        }
        /* 解析请求正文 */
        start = buf.find_first_not_of("\r\n",end);
        if(start < buf.size()) {
            vector<string> params = Utils::splitString(buf.substr(start),"&");
            for(vector<string>::iterator it = params.begin(); it != params.end(); ++it) {
                vector<string> tmp = Utils::splitString((*it),"=");
                if(tmp.size() > 2) {
                    requestParams.insert(pair<string,string>(tmp[0],tmp[1]));
                }
            }
        }
    } catch(out_of_range err) {
        cout<<"Log: HTTP请求解析错误("<<err.what()<<")"<<endl;
    }
}

/*----------------------------HttpRequest类----------end------------------------------------*/

/*----------------------------HttpResponse类---------start----------------------------------*/

/* 初始化一个基本的HttpResponse对象 */
HttpResponse::HttpResponse() {
    responseVersion.append("HTTP/1.1");
    setResponseCode(200);

    string date = System::getSystemHandler()->getGMTime();
    date.append(" GMT");
    responseHeaders.insert(pair<string,string>("Date","2019.2.25"));
    responseHeaders.insert(pair<string,string>("Content-Type","text/html; charset=UTF-8"));
}

void HttpResponse::setResponseCode(unsigned short code)
{
    responseCode = code;
    switch (code) {
    case 200:
        responseStatus = "OK";
        break;
    case 400:
        responseStatus = "Bad Request";
        break;
    case 401:
        responseStatus = "Unauthorized";
        break;
    case 403:
        responseStatus = "Forbidden";
        break;
    case 404:
        responseStatus = "NOT FOUND";
        break;
    case 500:
        responseStatus = "Internal Server Error";
        break;
    case 501:
        responseStatus = "Unimplemented Service";
        break;
    default:
        break;
    }
}

void HttpResponse::setResponseBody(const string & body)
{
    responseBody.append(body);
    responseHeaders.insert(pair<string,string>("Content-Length",to_string(responseBody.size())));
}

void HttpResponse::setContentType(string type)
{
    responseHeaders.at("Content-Type") = type;
}

string HttpResponse::toString()
{
    stringstream ss;
    ss<<responseVersion<<" "<<responseCode<<" "<<responseStatus<<"\r\n";
    for (map<string,string>::iterator it = responseHeaders.begin(); it != responseHeaders.end(); ++it) {
        ss<<it->first<<": "<<it->second<<"\r\n";
    }
    ss<<"\r\n"<<responseBody;
    return ss.str();
}

/*----------------------------HttpResponse类---------end------------------------------------*/
