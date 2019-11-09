/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 27.10.2019
 */

#include "GetByIdRequestHandler.h"
#include "Cat.h"
#include "Dog.h"
#include "Fox.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

GetByIdRequestHandler::GetByIdRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer GetByIdRequestHandler::handle(HTTPHandler::Request request) {
	try {
		int id = atoi(request.variables.at("id").c_str());
		json body = _animal_manager[id];

		string str_body = body.dump(4);
		return {
			200, "OK",
			{
				{"Content-Type", "application/json"},
				{"Content-Length", to_string(str_body.size())},
				{"Connection", "close"}
			},
			str_body
		};
	}
	catch (out_of_range& ex) {
		return {
			400, "Bad Request",
			{
				{"Content-Length", "0"},
				{"Connection", "close"}
			},
			""
		};
	}
}
