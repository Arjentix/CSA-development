/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
*/

#pragma once

#include "HTTPHandler.h"
#include "AnimalManager.h"

namespace RequestHandler {

	class RequestHandlerBase {
	public:
		RequestHandlerBase(AnimalManager& animal_manager);
		virtual ~RequestHandlerBase();

		virtual HTTPHandler::Answer handle(HTTPHandler::Request request) = 0;

	protected:
		AnimalManager& _animal_manager;
	};

};
