/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#pragma once

#include "Animal.h"

class Fox : public Animal {
public:
	Fox();
	Fox(
		const std::string& name,
		size_t age,
		double price
	);

	std::string voice() const override;
};
