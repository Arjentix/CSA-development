/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#pragma once

#include <string>
#include "nlohmann/json.hpp"

class Animal {
public:
	Animal();
	Animal(
		const std::string& type,
		const std::string& name,
		size_t age,
		double _price
	);
	virtual ~Animal();

	// Getters
	std::string get_type() const;
	std::string get_name() const;
	size_t get_age() const;
	double get_price() const;

	// Setters
	void set_type(const std::string& type);
	void set_name(const std::string& name);
	void set_age(size_t age);
	void set_price(double price);

	virtual std::string voice() const = 0;

	friend void to_json(nlohmann::json& j, const Animal& a);

private:
	std::string	_type;
	std::string _name;
	size_t		_age;
	double		_price;

protected:
	virtual nlohmann::json _to_json() const;
};

/**
 * to_json() - json serialization function.
 * The fields that will be writen are the same as fields required by from_json()
 * function.
 */
void to_json(nlohmann::json& j, const Animal& a);

/**
 * from_json() - json deserialization funstion.
 * Requires the next fields:
 * 		type: string
 * 		name: string
 * 		age: positive int
 * 		price: double
 */
void from_json(const nlohmann::json& j, Animal& a);
