/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 14.10.2019
*/

#include "Cat.h"

using namespace std;

Cat::Cat() : Animal() {}

Cat::Cat(const string& name, size_t age, double price)
	: Animal("cat", name, age, price) {}

string Cat::voice() const
{
	return "Meow";
}
