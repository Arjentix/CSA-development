/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 15.10.2019
 */

#include "Fox.h"

using namespace std;

Fox::Fox() : Animal() {}

Fox::Fox(const string& name, size_t age, double price)
	: Animal("fox", name, age, price) {}

string Fox::voice() const
{
	return "Fr";
}
