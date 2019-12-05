/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 09.10.2019
*/

#include "Animal.h"
#include <iostream>

using namespace std;

using json = nlohmann::json;

void Animal::update_main_table(SimpleSQL::Connector& db) const
{
	cout << "Updating main table" << endl;
	int last_id = atoi(db.query("SELECT LAST_INSERT_ID() AS id;")->get_row()[0]);
	db.query("INSERT INTO Id_Animal(Type, AnimalId) VALUES ("
		+ string("'") + get_type() + "',"
		+ to_string(last_id)
		+ ");"
	);
}


Animal::Animal() : _type(""), _name(""), _age(0), _price(0) {}

Animal::Animal(const string& type ,const string& name, size_t age, double price)
	: _type(type), _name(name), _age(age), _price(price) {}

Animal::~Animal() {}

string Animal::get_type() const
{
	return _type;
}

string Animal::get_name() const
{
	return _name;
}

size_t Animal::get_age() const
{
	return _age;
}

double Animal::get_price() const
{
	return _price;
}


void Animal::set_type(const string& type)
{
	_type = type;
}

void Animal::set_name(const string& name)
{
	_name = name;
}

void Animal::set_age(size_t age)
{
	_age = age;
}

void Animal::set_price(double price)
{
	_price = price;
}

nlohmann::json Animal::_to_json() const
{
	return {
		{"type", get_type()},
		{"name", get_name()},
		{"age", get_age()},
		{"price", get_price()}
	};
}

void Animal::_from_json(const nlohmann::json& j)
{
	set_type(j.at("type").get<string>());
	set_name(j.at("name").get<string>());
	set_age(j.at("age").get<size_t>());
	set_price(j.at("price").get<double>());
}

void Animal::to_db(SimpleSQL::Connector& db) const
{
	cout << "Inserting into " << get_type() << endl;
	db.query("INSERT INTO " + get_type() + " (Type, Name, Age, Price) VALUES ("
		+ "'" + get_type() + "', "
		+ "'" + get_name() + "', "
		+ to_string(get_age()) + ", "
		+ to_string(get_price())
		+ ");"
	);

	update_main_table(db);
}

void Animal::to_db(SimpleSQL::Connector& db, int id) const
{
	db.query("UPDATE " + get_type() + " SET "
		+ "Type = '" + get_type() + "', "
		+ "Name = '" + get_name() + "', "
		+ "Age = " + to_string(get_age()) + ", "
		+ "Price = " + to_string(get_price()) + " "
		+ "WHERE Id = " + to_string(id) + ";"
	);
}

void Animal::_from_row(SimpleSQL::Row row)
{
	cout << "row[0] = " << row[0] << endl
		 << "row[1] = " << row[1] << endl
		 << "row[2] = " << row[2] << endl
		 << "row[3] = " << row[3] << endl
		 << "row[4] = " << row[4] << endl;

	// row[0] - id
	set_type(row[1]);
	set_name(row[2]);
	set_age(atoi(row[3]));
	set_price(atof(row[4]));
}


void to_json(nlohmann::json& j, const Animal& a)
{
	j = a._to_json();
}

void from_json(const json& j, Animal& a)
{
	a._from_json(j);
}

void from_row(SimpleSQL::Row row, Animal& a)
{
	a._from_row(row);
}
