/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#pragma once

#include "RequestHandlerBase.h"

namespace RequestHandler {

	/**
	 * AddNewRequestHandler adds new animal in the list.
	 * 
	 * Request should contains body with json text with fields required by
	 * to_json() function of animal type class (or of Animal parent class if
	 * to_json() wasn't overrided in subclass). Otherwise a error will be sent
	 * to the client.
	 * 
	 * Returns answer with new id of added element in "id" field.
	 */

	class AddNewRequestHandler : public RequestHandlerBase {
	public:
		AddNewRequestHandler(AnimalManager& animal_manager);

		HTTPHandler::Answer handle(HTTPHandler::Request request) override;
	};

};
