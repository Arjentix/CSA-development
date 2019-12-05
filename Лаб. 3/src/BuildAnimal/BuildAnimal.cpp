/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 26.11.2019
 */

#include "BuildAnimal.h"

using namespace std;

std::shared_ptr<Animal> build_animal(const std::string& type)
{
	if (type == "cat") {
		return make_shared<Cat>();
	}
	if (type == "dog") {
		return make_shared<Dog>();
	}
	if (type == "fox") {
		return make_shared<Fox>();
	}

	return make_shared<Cat>();
}

std::shared_ptr<Animal> build_animal(
	const std::string& type,
	const nlohmann::json& j
)
{
	if (type == "cat") {
		return make_shared<Cat>(j.get<Cat>());
	}
	if (type == "dog") {
		return make_shared<Dog>(j.get<Dog>());
	}
	if (type == "fox") {
		return make_shared<Fox>(j.get<Fox>());
	}

	return make_shared<Cat>(j.get<Cat>());
}