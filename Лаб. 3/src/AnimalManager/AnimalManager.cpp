/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#include "AnimalManager.h"
#include <iostream>

using namespace std;

int AnimalManager::add(shared_ptr<Animal> animal_ptr)
{
	lock_guard guard(_locker);
	_id_to_animal[++_last_id] = animal_ptr;

	return _last_id;
}

void AnimalManager::remove(int id)
{
	lock_guard guard(_locker);
	_id_to_animal.at(id); // Throwing out_of_range if not exist
	_id_to_animal.erase(id);
}

vector<shared_ptr<const Animal>> AnimalManager::get_all() const
{
	lock_guard guard(_locker);
	vector<shared_ptr<const Animal>> animals;
	for (const auto& [id, animal] : _id_to_animal) {
		animals.push_back(animal);
	}

	return animals;
}

vector<shared_ptr<const Animal>> AnimalManager::get_all_of_type(
	const string& type
) const
{
	lock_guard guard(_locker);
	vector<shared_ptr<const Animal>> animals;
	for (const auto& [id, animal] : _id_to_animal) {
		if (animal->get_type() == type) {
			animals.push_back(animal);
		}
	}

	return animals;
}

Animal& AnimalManager::operator[](int id)
{
	lock_guard guard(_locker);
	return *(_id_to_animal.at(id));
}


void to_json(nlohmann::json& j, const std::shared_ptr<const Animal> animal_ptr)
{
	to_json(j, *animal_ptr);
}
