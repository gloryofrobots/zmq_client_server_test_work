#include "Server.h"
#include "UUIDBoost.h"



namespace dmsg 
{
    namespace dserver 
    {         
        /////////////////////////////////////////////////////
        Server::Server()
            : m_isRun(false)
        {
            m_uuid = new UUIDBoost();
        }
        /////////////////////////////////////////////////////
        Server::~Server()
        {
            delete m_uuid;
        }
        /////////////////////////////////////////////////////
        bool Server::init(TUInt port)
        {
            return this->_onInit(port);
        }
        /////////////////////////////////////////////////////
        bool Server::run(TUInt port)
        {
            if (m_isRun == true)
            {
                return false;
            }
            
            if (this->init(port) == false)
            {
                return false;
            }
            
            while (true)
            {
                bool isSuccess = update();
                if(isSuccess == false)
                {
                    return false;
                }
            }
        }
        /////////////////////////////////////////////////////
        bool Server::update()
        {
            return this->_onUpdate();
        }
        /////////////////////////////////////////////////////
        TRawConstString Server::getUUIDString()
        {
            return m_uuid->toCharArray();
        }
        /////////////////////////////////////////////////////
        void Server::getNewMessage()
        {
            
        }
        /////////////////////////////////////////////////////
    }
    
     /*
    // construct fro${CMAKE_CURRENT_BINARY_DIR}/m a file
    std::ifstream file("test.json");
    json::value v1 = json::parse(file);
    std::cout << json::pretty_print(v1, json::ESCAPE_UNICODE) << std::endl;
    std::cout << "----------" << std::endl;
    
    // construct programatically
    json::object obj1;
    obj1.insert("test1", "hello world")
    .insert("test2", 10)
    .insert("test3", json::object().insert("x", json::null()))
    .insert("test4", json::array().append(1).append(2).append(3).append(4));
    
    std::cout << json::pretty_print(obj1) << std::endl;
    std::cout << "----------" << std::endl;
    
    // construct from string
    json::value v = json::parse("{\"test3\" : {\"x\" : 123.456},\"test4\" : [1,2,3,{\"z\":12345}],\"test1\" : \"hello world\",\"test2\" : \"BLAH\\uD840\\uDC8ABLAH\"}");
    std::cout << json::pretty_print(v) << std::endl;
    std::cout << "----------" << std::endl;
    
    // get a specific value
    json::value z = v["test4"][3]["z"];
    std::cout << json::to_number(z) << std::endl;
    
    std::cout << json::serialize(v, json::ESCAPE_UNICODE) << std::endl;
    */
}
