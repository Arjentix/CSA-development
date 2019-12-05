/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#include "AnimalManager.h"
#include "BuildAnimal.h"
#include "Logger.h"
#include <array>
#include <iostream>
#include <unistd.h>

using namespace std;

const size_t attempts_num = 50;

pair<int, string> get_local_id_and_type(SimpleSQL::Connector& db, int id);

AnimalManager::AnimalManager(
	string host,
	string user_name,
	string password,
	string db_name,
	int port
)
{
	for (int i = 0; i < attempts_num; ++i) {
		logger << "Trying to connect to the db: attempt #" << i + 1 << endl;
		_db.connect(host, user_name, password, db_name, port);
		if (_db.is_connected()) {
			break;
		}

		sleep(1);
	}
	if (!_db.is_connected()) {
		logger << "Connection failed after " << attempts_num << " attempts."
			   << endl;
		throw runtime_error("Failed to connect to the db");
	}
	logger << "Successfully conneted to the db" << endl;
}

int AnimalManager::add(shared_ptr<Animal> animal_ptr)
{
	lock_guard guard(_locker);

	cout << "AnimalManager:: Adding animal of type: " << animal_ptr->get_type() << endl;
	animal_ptr->to_db(_db);

	int last_id = atoi(
		_db.query("SELECT LAST_INSERT_ID() AS id;")->get_row()[0]
	);
	return last_id;
}

void AnimalManager::remove(int id)
{
	lock_guard guard(_locker);


	auto res = get_local_id_and_type(_db, id);

	_db.query("DELETE FROM " + res.second + " WHERE Id = " + to_string(res.first) + ";");
	_db.query("DELETE FROM Id_Animal WHERE Id = " + to_string(id) + ";");
}

shared_ptr<Animal> AnimalManager::get(int id)
{
	lock_guard guard(_locker);

	// Getting info from main table
	cout << "AnimalManager:: selecting from main table" << endl;
	SimpleSQL::Row row = _db.query(
		"SELECT AnimalId, Type FROM Id_Animal WHERE Id = " + to_string(id) + ";"
	)->get_row();
	if (row == nullptr) {
		return nullptr;
	}

	int animal_id = atoi(row[0]);
	string type = row[1];

	// Getting directly animal
	cout << "AnimalManager:: selecting directly" << endl;
	row = _db.query(
		"SELECT * FROM " + type + " WHERE Id = " + to_string(animal_id) + ";"
	)->get_row();
	if (row == nullptr) {
		return nullptr;
	}

	shared_ptr<Animal> animal_ptr = build_animal(type);
	from_row(row, *animal_ptr);
	return animal_ptr;
}

map<int, shared_ptr<Animal>> AnimalManager::get_all() const
{
	lock_guard guard(_locker);
	map<int, shared_ptr<Animal>> animals;

	cout << "AnimalManager::get_all:: Before for" << endl;
	for (const string& type : array<string, 3>{"cat", "dog", "fox"}) {
		cout << "AnimalManager::get_all::for:: type = " << type << endl;
		auto animals_of_type = get_all_of_type(type);
		animals.merge(move(animals_of_type));
	}
	cout << "AnimalManager::get_all:: After for" << endl;

	return animals;
}

map<int, shared_ptr<Animal>> AnimalManager::get_all_of_type(
	const string& type
) const
{
	map<int, shared_ptr<Animal>> id_to_animal;

	auto query_res = _db.query("SELECT * FROM " + type + ";");

	// Saving result cause one more db query is needed
	map<int, shared_ptr<Animal>> local_id_to_animal;
	SimpleSQL::Row row;
	while ((row = query_res->get_row()) != nullptr) {
		shared_ptr<Animal> animal_ptr = build_animal(type);
		from_row(row, *animal_ptr);

		int local_id = atoi(row[0]);
		local_id_to_animal[local_id] = animal_ptr;
	}

	for (const auto& [local_id, animal_ptr] : local_id_to_animal) {
		// Getting real id
		query_res = _db.query(
			"SELECT Id FROM Id_Animal WHERE AnimalId = " 
			+ to_string(local_id) + " AND Type = '" + type + "';"
		);
		int real_id = atoi(query_res->get_row()[0]);
		cout << "get_all_of_type:: real_id = " << real_id << endl;

		id_to_animal[real_id] = animal_ptr;
	}

	return id_to_animal;
}

void AnimalManager::save(int id, shared_ptr<Animal> animal_ptr)
{
	lock_guard guard(_locker);

	auto res = get_local_id_and_type(_db, id);
	animal_ptr->to_db(_db, res.first);
}


void to_json(nlohmann::json& j, std::shared_ptr<const Animal> animal_ptr)
{
	to_json(j, *animal_ptr);
}

pair<int, string> get_local_id_and_type(SimpleSQL::Connector& db, int id)
{
	SimpleSQL::Row row = db.query(
		"SELECT AnimalId, Type FROM Id_Animal WHERE Id = " + to_string(id) + ";"
	)->get_row();
	if (row == nullptr) {
		throw out_of_range("");
	}
	return {atoi(row[0]), row[1]};
}
