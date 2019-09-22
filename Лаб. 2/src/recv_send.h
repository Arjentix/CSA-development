/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 04.09.2019
*/

#include <string>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

const size_t BUF_SIZE = 1024;

void Send(int client_sockfd, stringstream &os) {
	char buffer[BUF_SIZE];
	strncpy(buffer, os.str().c_str(), BUF_SIZE);
	os.str("");

	send(client_sockfd, buffer, BUF_SIZE, 0);
}

string Recv(int client_sockfd) {
	char buffer[BUF_SIZE];
	int res;

	res = recv(client_sockfd, buffer, BUF_SIZE, 0);
	if (res == -1) {
		throw runtime_error("Error in reading socket");
	}

	return buffer;
}
