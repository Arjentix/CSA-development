/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#include "Dog.h"

using namespace std;

Dog::Dog() : Animal() {}

Dog::Dog(
		const string& name,
		size_t age,
		double price,
		const string& breed
) : Animal("dog", name, age, price), _breed(breed) {}

string Dog::get_breed() const
{
	return _breed;
}

void Dog::set_breed(const string& breed)
{
	_breed = breed;
}

string Dog::voice() const
{
	return "Woof";
}

nlohmann::json Dog::_to_json() const
{
	nlohmann::json j;
	j = Animal::_to_json();
	j.push_back({"breed", get_breed()});

	return j;
}

void from_json(const nlohmann::json& j, Dog& dog)
{
	from_json(j, dynamic_cast<Animal&>(dog));
	dog.set_breed(j.at("breed").get<string>());
}
