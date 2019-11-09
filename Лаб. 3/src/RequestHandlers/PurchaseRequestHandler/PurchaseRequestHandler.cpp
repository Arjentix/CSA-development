/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 27.10.2019
 */

#include "PurchaseRequestHandler.h"
#include <string>

using namespace RequestHandler;
using namespace std;
using json = nlohmann::json;

PurchaseRequestHandler::PurchaseRequestHandler(AnimalManager& animal_manager)
	: RequestHandlerBase(animal_manager) {}

HTTPHandler::Answer PurchaseRequestHandler::handle(HTTPHandler::Request request) {
	try {
		auto json_body = json::parse(request.body);
		int id = json_body.at("id").get<int>();

		_animal_manager.remove(id);

		return {
			200, "OK",
			{
				{"Content-Type", "application/json"},
				{"Content-Length", "0"},
				{"Connection", "close"}
			},
			""
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
