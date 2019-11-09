/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 28.10.2019
 */

#pragma once

#include "RequestHandlerBase.h"

namespace RequestHandler {

	/**
	 * GetByTypeRequestHandler returns all animals with given type.
	 */

	class GetByTypeRequestHandler : public RequestHandlerBase {
	public:
		GetByTypeRequestHandler(AnimalManager& animal_manager);

		HTTPHandler::Answer handle(HTTPHandler::Request request) override;
	};
};
