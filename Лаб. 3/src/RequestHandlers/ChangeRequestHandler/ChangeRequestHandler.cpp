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
		Animal& animal = _animal_manager[id];

		if (json_body.count("name")) {
			animal.set_name(json_body.at("name").get<string>());
		}
		if (json_body.count("age")) {
			animal.set_age(json_body.at("age").get<size_t>());
		}
		if (json_body.count("price")) {
			animal.set_price(json_body.at("price").get<double>());
		}
		if (animal.get_type() == "dog") {
			if (json_body.count("breed")) {
				Dog& dog = dynamic_cast<Dog&>(animal);
				dog.set_breed(json_body.at("breed").get<string>());
			}
		}

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
