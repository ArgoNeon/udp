#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <boost/asio.hpp>

#define BUF 8192

int OpenRead(const char *pathname) {
    int file = open(pathname, O_RDONLY);
    if (file == -1) {
        perror("Open for read failed");
        errno;
    }
    return file;
}

int main() {
	char buf[BUF];
	int file = OpenRead("/home/argoneon/Pictures/client.jpg");
	ssize_t nread[1] = {1};
	boost::asio::io_context service;

	while(nread[0] > 0) {
	   	nread[0] = read(file, buf, BUF);
        	if (nread[0] == -1) {
	            perror("Read from file failed");
       		}

        	boost::asio::ip::udp::socket socket(service);
        	socket.open(boost::asio::ip::udp::v4());

		socket.send_to(boost::asio::buffer(nread), boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12125));
		socket.send_to(boost::asio::buffer(buf), boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12125));

		socket.close();
	}

	close(file);

        return 0;
}
