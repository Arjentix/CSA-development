/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 28.10.2019
 */

#include "GetByTypeRequestHandler.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

GetByTypeRequestHandler::GetByTypeRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer GetByTypeRequestHandler::handle(HTTPHandler::Request request) {
	string type = request.variables.at("type");
	json body(_animal_manager.get_all_of_type(type));

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
