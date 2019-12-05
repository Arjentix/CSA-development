/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#include "Dog.h"
#include <iostream>

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
	cout << "Dog::_to_json" << endl;
	nlohmann::json j;
	j = Animal::_to_json();
	j.push_back({"breed", get_breed()});

	return j;
}

void Dog::_from_json(const nlohmann::json& j)
{
	Animal::_from_json(j);
	set_breed(j.at("breed").get<string>());
}

void Dog::add_breed_to_db(SimpleSQL::Connector& db, int id) const
{
	cout << "Dog::add_breed_to_db" << endl;
	db.query(
		"UPDATE dog "
		"SET Breed = '" + get_breed() + "' " +
		"WHERE Id = " +  to_string(id) + ";"
	);
}

void Dog::to_db(SimpleSQL::Connector& db) const
{
	cout << "Dog::to_db" << endl;
	Animal::to_db(db);

	int last_id = atoi(db.query(
		"SELECT AnimalId FROM Id_Animal WHERE Id = LAST_INSERT_ID();")->get_row()[0]
	);
	add_breed_to_db(db, last_id);
}

void Dog::to_db(SimpleSQL::Connector& db, int id) const
{
	Animal::to_db(db, id);
	add_breed_to_db(db, id);
}

void Dog::_from_row(SimpleSQL::Row row)
{
	cout << "Dog::_from_row" << endl;
	Animal::_from_row(row);
	cout << "row[5] = " << row[5] << endl;
	set_breed(row[5]);
}
