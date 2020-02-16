#ifndef HANDLER_H
#define HANDLER_H
#include <iostream>
#include <map>
#include <functional>
#include "stdafx.h"
//#include "../dbms/include/Dbms.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class handler
{
    public:
        handler();
        handler(utility::string_t url);
        virtual ~handler();

        pplx::task<void>open(){return m_listener.open();}
        pplx::task<void>close(){return m_listener.close();}

    protected:
        void postForAsk(http_request req);
        void postForCalc(http_request req);

    private:
        void handle_get(http_request message);
        void handle_put(http_request message);
        void handle_post(http_request message);
        void handle_delete(http_request message);
        void handle_error(pplx::task<void>& t);

    public:


    protected:
        map<utility::string_t, function<void(http_request)> > m_router;

    private:
        http_listener m_listener;

        utility::string_t m_staticResourcePath = "/www";
};

#endif // HANDLER_H


