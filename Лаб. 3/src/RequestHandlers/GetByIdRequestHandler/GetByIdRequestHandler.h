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
	 * GetByIdRequestHandler returns animal by the given id.
	 */

	class GetByIdRequestHandler : public RequestHandlerBase {
	public:
		GetByIdRequestHandler(AnimalManager& animal_manager);

		HTTPHandler::Answer handle(HTTPHandler::Request request) override;
	};
};
