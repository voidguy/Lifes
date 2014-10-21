
#include "Server.h"
#include <iostream>
#include <thread>

Server::Server() {
}

Server::Version Server::getVersion() {
	return this->version;
}


bool Server::initNetworkListen() {
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(listen_fd, F_SETFL, O_NONBLOCK);
    //printf("server listening, fd[%d]\n", listen_fd);
    //EventSet(event_queue + MAX_EVENTS, listenFd, AcceptConn, &g_Events[MAX_EVENTS]);

    // add listen socket
    //EventAdd(epoll_fd, EPOLLIN, &g_Events[MAX_EVENTS]);
    struct epoll_event epv;
    epv.events = EPOLLIN | EPOLLET; 

    struct Event *ev = &event_poll[event_pos++];
    ev->fd = listen_fd;
    ev->call_back = accept_connect;
    epv.data.ptr = ev;
    //epoll_fd epoll_op sock_fd epoll_event
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &epv) < 0) {
        printf("EPOLL_CTL_ADD failed, fd[%d]\n", listen_fd);
        return -1;
    } else {
        printf("EPOLL_CTL_ADD succ, fd[%d]\n", listen_fd);
    }

    // bind & listen
    struct sockaddr_in sin = {0};
    //memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr *)&sin, sizeof(sin));
    listen(listen_fd, 5);

    return listen_fd;

}

bool Server::init() {
    std::cout << "init..." << std::endl;

	std::thread accept_thread();




	//Version ver = this->getVersion();
	//std::cout << "version:" << ver.version << " major:" << ver.v.major_version << " minor:" << ver.v.minor_version << std::endl;
    return true;
}

bool Server::start() {
    std::cout << "start..." << std::endl;
    return true;
}

