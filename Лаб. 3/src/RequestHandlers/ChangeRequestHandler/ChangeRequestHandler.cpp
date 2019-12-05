/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 27.10.2019
 */

#include "ChangeRequestHandler.h"
#include "Dog.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

ChangeRequestHandler::ChangeRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer ChangeRequestHandler::handle(HTTPHandler::Request request) {
	try {
		auto json_body = json::parse(request.body);
		int id = json_body.at("id").get<int>();
		shared_ptr<Animal> animal_ptr = _animal_manager.get(id);

		if (json_body.count("name")) {
			animal_ptr->set_name(json_body.at("name").get<string>());
		}
		if (json_body.count("age")) {
			animal_ptr->set_age(json_body.at("age").get<size_t>());
		}
		if (json_body.count("price")) {
			animal_ptr->set_price(json_body.at("price").get<double>());
		}
		if (animal_ptr->get_type() == "dog") {
			if (json_body.count("breed")) {
				shared_ptr<Dog> dog_ptr = dynamic_pointer_cast<Dog>(animal_ptr);
				dog_ptr->set_breed(json_body.at("breed").get<string>());
			}
		}

		_animal_manager.save(id, animal_ptr);

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
