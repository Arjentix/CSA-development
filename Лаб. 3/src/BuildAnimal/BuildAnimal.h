/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 26.11.2019
 */

#include "Cat.h"
#include "Dog.h"
#include "Fox.h"
#include <memory>
#include <string>
#include "nlohmann/json.hpp"

std::shared_ptr<Animal> build_animal(const std::string& type);

std::shared_ptr<Animal> build_animal(
	const std::string& type,
	const nlohmann::json& j
);
