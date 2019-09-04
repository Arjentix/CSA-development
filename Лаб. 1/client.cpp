/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 04.09.2019
*/

#include "recv_send.h"

#include <iostream>
#include <stdexcept>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const int COUNT = 10;

int main() {
	int port = 1500;
	const string ip("127.0.0.1");

	// Setting socket
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		throw runtime_error("Error establishing socket");
	}

	// Setting server address
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

	int res = connect(sock_fd,
					  (struct sockaddr *)&server_addr,
					  sizeof(server_addr));
	if ( res == 0) {
        cout << "Connection to the server "
			 << inet_ntoa(server_addr.sin_addr)
			 << " with port number: " << port << endl;
		cout << Recv(sock_fd);

		stringstream os;
		for (int i = 0; i < COUNT; i++) {
			os << "Hello";
			cout << "Client: " << os.str() << endl;
			Send(sock_fd, os);

			string answer = Recv(sock_fd);
			cout << "Server: " << answer << endl;
		}

		os << "End";
		Send(sock_fd, os);
	}

	close(sock_fd);
}
