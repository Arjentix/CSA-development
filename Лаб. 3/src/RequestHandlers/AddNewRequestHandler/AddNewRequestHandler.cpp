/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#include "AddNewRequestHandler.h"
#include "BuildAnimal.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

AddNewRequestHandler::AddNewRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer AddNewRequestHandler::handle(HTTPHandler::Request request) {
	auto json_body = json::parse(request.body);
	string type = json_body.at("type").get<string>();

	shared_ptr<Animal> animal_ptr = build_animal(type, json_body);

	int id = _animal_manager.add(animal_ptr);
	json json_answer = {{"id", id}};
	string str_body = json_answer.dump(4);

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
