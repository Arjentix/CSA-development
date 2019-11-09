/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#pragma once

#include "Animal.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <type_traits>
#include <functional>
#include <mutex>

class AnimalManager {
public:
	int add(std::shared_ptr<Animal> animal_ptr);
	void remove(int id);
	std::vector<std::shared_ptr<const Animal>> get_all() const;

	std::vector<std::shared_ptr<const Animal>> get_all_of_type(
		const std::string& type
	) const;

	Animal& operator[](int id);

private:
	std::unordered_map<int, std::shared_ptr<Animal>> _id_to_animal;
	int _last_id = 0;
	mutable std::mutex _locker;
};

void to_json(nlohmann::json& j, const std::shared_ptr<const Animal> animal_ptr);
