/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#pragma once

#include "Animal.h"
#include "SimpleSQL.h"
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <type_traits>
#include <functional>
#include <mutex>

class AnimalManager {
public:
	AnimalManager(
		std::string host,
		std::string user_name,
		std::string password,
		std::string db_name,
		int port
	);

	int add(std::shared_ptr<Animal> animal_ptr);

	void remove(int id);

	std::shared_ptr<Animal> get(int id);

	std::map<int, std::shared_ptr<Animal>> get_all() const;

	std::map<int, std::shared_ptr<Animal>> get_all_of_type(
		const std::string& type
	) const;

	void save(int id, std::shared_ptr<Animal> animal_ptr);

private:
	mutable SimpleSQL::Connector _db;
	mutable std::mutex _locker;
};

void to_json(nlohmann::json& j, std::shared_ptr<const Animal> animal_ptr);
