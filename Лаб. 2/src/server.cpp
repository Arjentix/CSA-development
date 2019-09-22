/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 04.09.2019
*/

#include "recv_send.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
	// Setting socket
	int server_sockfd;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd < 0) {
		throw runtime_error("Errror establishing socket");
	}

	// Setting address
	int port = 1500;
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(port);

	// Binding
	int res = bind(server_sockfd,
				   (sockaddr*)&server_address,
				   sizeof(server_address));
	if (res != 0) {
		throw std::runtime_error("Can't bind the socket");
	}

	// Listening
	listen(server_sockfd, 5);

	// Accepting
	int client_sockfd;
	sockaddr_in client_address;
	unsigned int length = sizeof(client_address);

	client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address,
						&length);
	if (client_sockfd != -1) {
		cout << "Connected with client " << inet_ntoa(client_address.sin_addr)
			 << endl;

		stringstream answer;
		answer << "Connected to the server" << endl;
		Send(client_sockfd, answer);

		string req;
		while ((req = Recv(client_sockfd)) != "End") {
			answer << "Echo: " << req;
			cout << "answer is = " << answer.str() << endl;
			Send(client_sockfd, answer);
		}
	}

	cout << "Server finished" << endl;
	close(client_sockfd);
	close(server_sockfd);
}
