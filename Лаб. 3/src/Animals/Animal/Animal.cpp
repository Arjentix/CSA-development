/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 09.10.2019
*/

#include "Animal.h"

using namespace std;

using json = nlohmann::json;

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


void to_json(nlohmann::json& j, const Animal& a)
{
	j = a._to_json();
}

void from_json(const json& j, Animal& a)
{
	a.set_type(j.at("type").get<string>());
	a.set_name(j.at("name").get<string>());
	a.set_age(j.at("age").get<size_t>());
	a.set_price(j.at("price").get<double>());
}
