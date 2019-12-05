/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#pragma once

#include "Animal.h"

class Dog : public Animal {
public:
	Dog();
	Dog(
		const std::string& name,
		size_t age,
		double price,
		const std::string& breed
	);

	std::string get_breed() const;
	void set_breed(const std::string& breed);

	std::string voice() const override;

	void to_db(SimpleSQL::Connector& db) const override;
	void to_db(SimpleSQL::Connector& db, int id) const override;

private:
	std::string _breed;
	void add_breed_to_db(SimpleSQL::Connector& db, int id) const;

protected:
	nlohmann::json _to_json() const override;
	void _from_json(const nlohmann::json& j) override;

	void _from_row(SimpleSQL::Row row) override;
};
