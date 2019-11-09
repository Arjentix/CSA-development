/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
*/

#include "RequestHandlerBase.h"

using namespace RequestHandler;

RequestHandlerBase::RequestHandlerBase(AnimalManager& animal_manager)
	: _animal_manager(animal_manager) {}

RequestHandlerBase::~RequestHandlerBase() {}
