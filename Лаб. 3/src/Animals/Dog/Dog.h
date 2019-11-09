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

private:
	std::string _breed;

protected:
	nlohmann::json _to_json() const override;
};

void from_json(const nlohmann::json& j, Dog& dog);
