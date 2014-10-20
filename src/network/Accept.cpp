
#include "Accept.h"


static bool Accept::mainLoop(int sock_listen_fd) {
	struct sockaddr_in sin;
	socklen_t len = sizeof(struct sockaddr_in);
	while (true) {
		int sock_conn_fd = accept(sock_listen_fd, (struct sockaddr *)&sin, &len);
		if (sock_conn_fd > 0) {
			
		} else {

		} 
	}

}

