#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <boost/asio.hpp>

#define BUF 8192

int OpenWrite(const char *pathname) {
    int file = open(pathname, O_CREAT|O_WRONLY|O_TRUNC, 0777);
    if (file == -1) {
        perror("Open for write failed");
        errno;
    }
    return file; 
}

int main() {
	ssize_t nwrite;
	int file = OpenWrite("/home/argoneon/Install/server.jpg");
	boost::asio::io_context service;

	while(true) {
		boost::asio::ip::udp::socket socket(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 12125));
		boost::asio::ip::udp::endpoint client;
		char recv[BUF];
		ssize_t nread[1] = {1};

		while(nread[0] > 0) {
			socket.receive_from(boost::asio::buffer(nread), client);
			socket.receive_from(boost::asio::buffer(recv, nread[0]), client);
			nwrite = write(file, recv, nread[0]);
			if (nwrite == -1) {
				perror("Write to file failed");
			}
		printf("lol\n");
		}
	}

	return 0;
}
