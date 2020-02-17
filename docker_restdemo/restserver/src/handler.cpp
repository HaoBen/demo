#include "handler.h"
#include <unistd.h>

typedef pair<utility::string_t, function<void(http_request)> > PathFuncPair;

handler::handler()
{
    
}
handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

    m_router.insert(PathFuncPair(U("/rest/ask"), std::bind(&handler::postForAsk, this, std::placeholders::_1)));
    m_router.insert(PathFuncPair(U("/rest/calc"), std::bind(&handler::postForCalc, this, std::placeholders::_1)));
}

handler::~handler()
{
    //dtor
}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{
    ucout <<  message.to_string() << endl;

    utility::string_t reqSrc;
    reqSrc.append(m_staticResourcePath);
    reqSrc.append(http::uri::decode(message.relative_uri().path()));
    if (reqSrc[reqSrc.length()-1] == '/')
    {
        reqSrc.append(U("index.html"));
    }
    
    concurrency::streams::fstream::open_istream(reqSrc, std::ios::in)
    .then([=](concurrency::streams::istream is)
    {
        message.reply(status_codes::OK, is,  U("text/html"))
		.then([](pplx::task<void> t)
		{
			try{
				t.get();
			}
			catch(...){
			}
	    });
    }).then([=](pplx::task<void>t)
	{
		try{
			t.get();
		}
		catch(...){
			message.reply(status_codes::InternalError,U("<h1>500 INTERNAL ERROR</h1>"), U("text/html"));
            ucout << "Failed to reply with file [" << reqSrc << "]!" << endl;
		}
	});
    return;
};

//
// A POST request
//
void handler::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;
    auto path = message.request_uri().to_string();

    auto it = m_router.find(path);
    if (it != m_router.end())
    {
        auto &func = it->second;
        func(message);
    }
    else
    {
        message.reply(status_codes::NotFound, "REQUESTED URI NOT EXISTS IN SERVER.");
    }
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
     ucout <<  message.to_string() << endl;

        string rep = U("WRITE YOUR OWN DELETE OPERATION");
      message.reply(status_codes::OK,rep);
    return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
    ucout <<  message.to_string() << endl;
     string rep = U("WRITE YOUR OWN PUT OPERATION");
     message.reply(status_codes::OK,rep);
    return;
};




//--------customed function for handler post request
void handler::postForAsk(http_request req)
{
    req.extract_json()
    .then([&req](json::value body) {
        auto oBody = body.as_object();
        utility::string_t mesAsk, asker;
        if (oBody["mesAsk"].is_null())
        {
            mesAsk = U("");
        }
        else
        {
            mesAsk = oBody["mesAsk"].as_string();
        }

        if (oBody["asker"].is_null())
        {
            asker = U("");
        }
        else
        {
            asker = oBody["asker"].as_string();
        }

        auto mes = utility::string_t("Hello,").append(asker).append(".Your question is [").append(mesAsk).append("].");
        return mes;
    }).then([&req](utility::string_t mes){
        json::value obj;
        obj["mesReply"] = json::value::string(mes);
        auto res = obj.serialize();
        ucout << res << endl;
        req.reply(status_codes::OK, res, U("application/json"));
    }).then([&req](pplx::task<void> t){
        try
        {
            t.wait();
        }
        catch(...)
        {
            req.reply(status_codes::InternalError, "PLEASE CHECK YOUR INPUT.");
        }
    });
}

void handler::postForCalc(http_request req)
{
    req.extract_json()
    .then([&req](json::value body) {
        auto oBody = body.as_object();
        double left = oBody["left"].as_double();
        double right = oBody["right"].as_double();
        int opCode = oBody["opCode"].as_integer(); // 1+,2-,3*,4/

        double calRes = 0;
        switch(opCode)
        {
        case 1:
            calRes = left+right;
            break;
        case 2:
            calRes = left-right;
            break;
        case 3:
            calRes = left*right;
             break;
        case 4:
            calRes = left/right;
            break;
        default:
            break;
        }
        return calRes;
    }).then([&req](int calRes){
        sleep(3);
        ucout << &req << endl;
        json::value res;
        res["res"] = json::value::number(calRes);
        res["message"] = json::value::string(U("OK"));
        ucout << res.serialize() << endl;
        req.reply(status_codes::OK, res.serialize(), U("application/json"));
    });
}
