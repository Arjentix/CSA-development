/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 27.10.2019
 */

#include "ShowAllRequestHandler.h"
#include "Cat.h"
#include "Dog.h"
#include "Fox.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

ShowAllRequestHandler::ShowAllRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer ShowAllRequestHandler::handle(HTTPHandler::Request request) {
	json body = json::object();
	map<int, shared_ptr<Animal>> id_to_animals = _animal_manager.get_all();
	for (const auto& [id, animal] : id_to_animals) {
			body.push_back({to_string(id), *animal});
	}

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
