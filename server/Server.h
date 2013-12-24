#ifndef SERVER_H
#define SERVER_H

class Server {
    public:
        Server();
        virtual ~Server();
        bool init();
        
    protected:
        bool _init();
        
};

#endif
