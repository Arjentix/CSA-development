/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
*/

#include "ClientHandler.h"
#include "HTTPServer.h"
#include "Logger.h"
#include "nlohmann/detail/exceptions.hpp"
#include <string>

using namespace std;


void ClientHandler::add_request_handler(
	RequestParams request_params,
	std::shared_ptr<RequestHandler::RequestHandlerBase> handler_ptr
)
{
	_request_handlers.insert({request_params, handler_ptr});
	_available_methods.insert(request_params.method);
}

void ClientHandler::handle_client(int client_sock) const
{
	HTTPHandler::Answer http_answer = {	// Default answer
		400, "Bad Request",
		{
			{"Content-Length", "0"},
			{"Connection", "close"}
		},
		""
	};

	string request_str;
	try {
		// Parsing request
		auto request = HTTPServer::get_request(client_sock);
		logger << "Getted request: \n" + request.str() << endl;

		vector<string> vars;
		for (const auto& [var, value] : request.variables) {
			vars.push_back(var);
		}
		RequestParams params = {
			request.method,
			request.uri,
			vars
		};
		// If there is a handler for this HTTP request
		if (_request_handlers.count(params)) {
			// Handling request and getting answer
			http_answer = _request_handlers.at(params)
							->handle(request);
		}
		// If there is a handler for given HTTP method but not for given URI
		else if (_available_methods.count(request.method)) {
			http_answer = {
				404, "Not Found",
				{
					{"Content-Length", "0"},
					{"Connection", "close"}
				},
				""
			};
		}
		else {
			http_answer = {
				405, "Method Not Allowed",
				{
					{"Content-Length", "0"},
					{"Connection", "close"}
				},
				""
			};
		}
	}
	catch (invalid_argument& ex) {
		// http_answer is already set to "Bad Request"
		logger << "Error: invalid_argument: " << ex.what() << endl;
	}
	catch(nlohmann::detail::exception& ex) {
		// http_answer is already set to "Bad Request"
		logger << "Error: nlohmann::detail::exception: " << ex.what() << endl;
	}
	catch (HTTPServer::ServerException& ex) {
		logger << ex.what() << endl;
		HTTPServer::close_con(client_sock);
		return;
	}
	catch (exception& ex) {
		logger << "Error: exception: id = " << typeid(ex).name()
			   <<  ", what = " << ex.what() << endl;
		http_answer = {
			500, "Internal Server Error",
			{
				{"Content-Length", "0"},
				{"Connection", "close"}
			},
			""
		};
	}

	// Sending answer
	logger << "Answer:\n" << http_answer.str() << endl;
	HTTPServer::send_answer(client_sock, http_answer);

	logger << "Closing connection with client on socket " << client_sock << endl;
	HTTPServer::close_con(client_sock);
}


bool ClientHandler::RequestParams::operator==(const RequestParams& other) const
{
	return (
		make_tuple(method, url, vars) == 
		make_tuple(other.method, other.url, other.vars)
	);
}


size_t ClientHandler::RequestParamsHash::operator()(
	const RequestParams& params
) const
{
	size_t h = hash<int>()(static_cast<int>(params.method)) ^ hash<string>()(params.url);
	for (const auto& var : params.vars) {
		h ^= hash<string>()(var);
	}

	return h;
}
