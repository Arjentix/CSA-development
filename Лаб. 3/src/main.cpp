/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#include "HTTPHandler.h"
#include "HTTPServer.h"
#include "AnimalManager.h"
#include "ClientHandler.h"
#include "AddNewRequestHandler.h"
#include "ChangeRequestHandler.h"
#include "PurchaseRequestHandler.h"
#include "ShowAllRequestHandler.h"
#include "GetByIdRequestHandler.h"
#include "GetByTypeRequestHandler.h"
#include "Logger.h"
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <future>
#include <thread>

using namespace std;

bool finish = false;

void signal_handler(int)
{
	finish = true;
}

int main(int argc, char** argv)
{
	// Daemon mode
	if (argc > 1 && strcmp(argv[1], "-d") == 0) {
		int fork_res = fork();
		if (fork_res == -1) {	// Error
			return -1;
		}
		if (fork_res > 0) {		// Parent
			return 0;
		}
		
		// Child 
		// Closing useless fds
		close(0);
		close(1);
		close(2);
	}

	try {
		logger.open("log/log.txt");
		logger << "Start" << endl;

		HTTPServer server;
		server.start_server(2525);
		server.turn_to_listen(5);

		AnimalManager animal_manager(
			"mysql", 
			"AnimalStoreAdmin",
			"secret",
			"AnimalStoreDb",
			3306
		);

		// Capturing SIGINT signal
		signal(SIGINT, signal_handler);

		// Adding handlers
		ClientHandler client_handler;
		client_handler.add_request_handler(
			{HTTPHandler::Method::POST, "/animals/new", {}},
			make_shared<RequestHandler::AddNewRequestHandler>(animal_manager)
		);
		client_handler.add_request_handler(
			{HTTPHandler::Method::POST, "/animals/change", {}},
			make_shared<RequestHandler::ChangeRequestHandler>(animal_manager)
		);
		client_handler.add_request_handler(
			{HTTPHandler::Method::POST, "/animals/purchase", {}},
			make_shared<RequestHandler::PurchaseRequestHandler>(animal_manager)
		);
		client_handler.add_request_handler(
			{HTTPHandler::Method::GET, "/animals/all", {}},
			make_shared<RequestHandler::ShowAllRequestHandler>(animal_manager)
		);
		client_handler.add_request_handler(
			{HTTPHandler::Method::GET, "/animals", {"id"}},
			make_shared<RequestHandler::GetByIdRequestHandler>(animal_manager)
		);
		client_handler.add_request_handler(
			{HTTPHandler::Method::GET, "/animals", {"type"}},
			make_shared<RequestHandler::GetByTypeRequestHandler>(animal_manager)
		);

		vector<future<void>> futures;
		while (!finish) {
			int client_sock = server.connect_client();
			logger << "Client connected on socket " << client_sock << endl;
			futures.push_back(async(
				&ClientHandler::handle_client, &client_handler, client_sock
			));
		}
	}
	catch (exception& ex) {
		logger << ex.what() << endl;
	}
	
	logger << "Shutting down" << endl;
	return 0;
}
