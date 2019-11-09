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
	 * PurchaseRequestHandler delete animal by the given id.
	 *
	 * Returns answer with empty body.
	 */

	class PurchaseRequestHandler : public RequestHandlerBase {
	public:
		PurchaseRequestHandler(AnimalManager& animal_manager);

		HTTPHandler::Answer handle(HTTPHandler::Request request) override;
	};
};
