/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#include "AddNewRequestHandler.h"
#include "Cat.h"
#include "Dog.h"
#include "Fox.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

AddNewRequestHandler::AddNewRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer AddNewRequestHandler::handle(HTTPHandler::Request request) {
	auto json_body = json::parse(request.body);
	string type = json_body.at("type").get<string>();
	shared_ptr<Animal> animal_ptr;

	if (type == "cat") {
		animal_ptr = make_shared<Cat>(json_body.get<Cat>());
	}
	else if (type == "dog") {
		animal_ptr = make_shared<Dog>(json_body.get<Dog>());
	}
	else if (type == "fox") {
		animal_ptr = make_shared<Fox>(json_body.get<Fox>());
	}

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
