/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 27.10.2019
 */

#pragma once

#include "RequestHandlerBase.h"

namespace RequestHandler {

	/**
	 * ChangeRequestHandler changes animal by the given id.
	 * 
	 * Request should contains body with json text with id of existing animal
	 * and fields required by to_json() function of animal type class
	 * (or of Animal parent class if to_json() wasn't overrided in subclass).
	 * Otherwise a error will be sent to the client.
	 *
	 * Returns answer with new id of added element in "id" field.
	 */

	class ChangeRequestHandler : public RequestHandlerBase {
	public:
		ChangeRequestHandler(AnimalManager& animal_manager);

		HTTPHandler::Answer handle(HTTPHandler::Request request) override;
	};
};
