
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//POSIX.1
#include <time.h>
#include <sys/socket.h>
#include <sys/epoll.h>


//c runtime
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define MAX_EVENTS 500

int epoll_fd;

struct Event {
	int fd;
	void *arg;
    char buff[1536];
    int len;
	int (*call_back) (void *arg);
} event_poll[102400];
int event_pos = 0;

//struct epoll_event event_queue[MAX_EVENTS+1];
/*
void RecvData(int fd, int events, void *arg);
void SendData(int fd, int events, void *arg);
*/


// receive data
int recv_data(void *arg) {
    struct Event *pev = (struct Event*)arg;
    int fd = pev->fd;

    // receive data
    int len = recv(fd, pev->buff + pev->len, sizeof(pev->buff) - pev->len - 1, 0);
    //EventDel(g_epollFd, ev);
    if(len > 0) {
        pev->len += len;
        pev->buff[pev->len] = 0;
        printf("fd[%d]: %s\n", fd, pev->buff);
        // change to send event
        //EventSet(ev, fd, SendData, ev);
        //EventAdd(g_epollFd, EPOLLOUT, ev);
    } else if(len == 0) {
        close(pev->fd);
        printf("fd[%d] pos[%d], closed gracefully.\n", fd, 0);
    } else {
        close(pev->fd);
        printf("recv fd[%d] errno[%d]: %s\n", fd, errno, strerror(errno));
    }

    return 0;
}

/*
// send data
void SendData(int fd, int events, void *arg)
{
struct myevent_s *ev = (struct myevent_s*)arg;
int len;
// send data
len = send(fd, ev->buff + ev->s_offset, ev->len - ev->s_offset, 0);
if(len > 0)
{
printf("send[fd=%d], [%d<->%d]%s\n", fd, len, ev->len, ev->buff);
ev->s_offset += len;
if(ev->s_offset == ev->len)
{
// change to receive event
EventDel(g_epollFd, ev);
EventSet(ev, fd, RecvData, ev);
EventAdd(g_epollFd, EPOLLIN, ev);
}
}
else
{
close(ev->fd);
EventDel(g_epollFd, ev);
printf("send[fd=%d] error[%d]\n", fd, errno);
}
}
*/

// accept new connections from clients
int accept_connect(void *arg) {
    struct Event *pev = (struct Event *)arg;
    int fd = pev->fd;

    struct sockaddr_in sin;
    socklen_t len = sizeof(struct sockaddr_in);
    // accept
    int i = 0;
    int nfd = accept(fd, (struct sockaddr*)&sin, &len);
    if (nfd == -1) {
        printf("accept failed, errno[%d]: %s\n", errno, strerror(errno));
        return -1;
    }
    /*
       for(i = 0; i < MAX_EVENTS; i++) {
       if(g_Events[i].status == 0) {
       break;
       }
       }

       if(i == MAX_EVENTS) {
       printf("%s:max connection limit[%d].", __func__, MAX_EVENTS);
       return -1;
       }
       */

    // set nonblocking
    int ret = fcntl(nfd, F_SETFL, O_NONBLOCK);
    if (ret < 0) {
        printf("fcntl nonblocking failed, %d\n", ret);
        return -1;
    }

    // add a read event for receive data
    //EventSet(&g_Events[i], nfd, RecvData, &g_Events[i]);
    //EventAdd(g_epollFd, EPOLLIN, &g_Events[i]);

    struct epoll_event epv;
    epv.events = EPOLLIN | EPOLLET; 
    struct Event *ev = &event_poll[event_pos++];
    ev->fd = nfd;
    ev->call_back = recv_data;
    ev->len = 0;
    epv.data.ptr = ev;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, nfd, &epv);

    printf("new conn[%s:%d], fd[%d] time[%d] pos[%d]\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), nfd, 0, 0);

    return 0;
}

int init_listen_socket(uint16_t port) {
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

int main(int argc, char **argv) {
    uint16_t port = 12345;
    if(argc > 1){
        port = atoi(argv[1]);
    }

    // create epoll
    epoll_fd = epoll_create(MAX_EVENTS);
    if(epoll_fd <= 0) {
        printf("create epoll failed.%d\n", epoll_fd);
    }

    // create & bind listen socket, and add to epoll, set non-blocking
    int listen_fd = init_listen_socket(port);

    // event loop
    struct epoll_event wait_event_list[MAX_EVENTS];
    printf("server running, port[%d]\n", port);

    int checkPos = 0;
    while(1) {
        // a simple timeout check here, every time 100, better to use a mini-heap, and add timer event
        /*
           long now = time(NULL);
           for(int i = 0; i < 100; i++, checkPos++) // doesn't check listen fd   
           {
           if(checkPos == MAX_EVENTS) {
           checkPos = 0;
           }
           if(g_Events[checkPos].status != 1) {
           continue;
           }
           long duration = now - g_Events[checkPos].last_active;
           if(duration >= 60) // 60s timeout {
           close(g_Events[checkPos].fd);
           printf("[fd=%d] timeout[%d--%d].\n", g_Events[checkPos].fd, g_Events[checkPos].last_active, now);
           EventDel(g_epollFd, &g_Events[checkPos]);
           }
           */

        // wait for events to happen
        int fds = epoll_wait(epoll_fd, wait_event_list, MAX_EVENTS, 1000);
        if(fds < 0) {
            printf("epoll_wait error!\n");
            break;
        }

        //printf("epoll_wait return, event_num[%d]\n", fds);

        struct epoll_event *event_ptr = wait_event_list;
        while(event_ptr < wait_event_list + fds) {  
            //myevent_s *ev = (struct myevent_s*) events[i].data.ptr;
            /*
               if((events[i].events & EPOLLIN)&&(ev->events & EPOLLIN)) // read event
               {
               ev->call_back(ev->fd, events[i].events, ev->arg);
               }
               if((events[i].events&EPOLLOUT)&&(ev->events&EPOLLOUT)) // write event
               {
               ev->call_back(ev->fd, events[i].events, ev->arg);
               }
               */
            printf("got a event, events[%d]\n", event_ptr->events);

            struct Event *ev = event_ptr->data.ptr;
            //int (*call_back)(int, void*) = int (*(event_ptr->data.ptr))(int, void*);
            ev->call_back(ev);


            printf("event call back done!\n");
            //call_back(event_ptr->);
            ++event_ptr;
        }
    }


    // free resource
    return 0;
    }

