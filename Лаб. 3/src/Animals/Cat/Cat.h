/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#pragma once

#include "Animal.h"

class Cat : public Animal {
public:
	Cat();
	Cat(const std::string& name, size_t age, double price);

	std::string voice() const override;
};
