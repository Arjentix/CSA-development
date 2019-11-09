#include "AnimalManager.h"
#include "Cat.h"
#include <iostream>
#include <memory>

using namespace std;

class Banana {

};

int main()
{
	AnimalManager animal_manager;
	auto v_id = animal_manager.add(make_shared<Cat>("Vasya", 1, 5.25));
	animal_manager.add(make_shared<Cat>("Murzik", 2, 3.75));
	animal_manager.add(make_shared<Cat>("Barsik", 5, 2));

	cout << "Getting by id: name = " << animal_manager[v_id].get_name() << endl;

	cout << "Getting all:" << endl;
	for (const auto& animal_ptr : animal_manager.get_all()) {
		cout << "name: " << animal_ptr->get_name()
			 << ", voice: " << animal_ptr->voice() << endl;
	}

	cout << "Cats:" << endl;
	for (const auto& animal_ptr : animal_manager.get_all_of_type<Cat>()) {
		cout << "name: " << animal_ptr->get_name() << ", voice: " << animal_ptr->voice() << endl;
	}

	try {
		cout << "Bananas:" << endl;
		for (const auto& animal_ptr : animal_manager.get_all_of_type<Banana>()) {
			cout << "name: " << animal_ptr->get_name() << ", voice: " << animal_ptr->voice() << endl;
		}
	}
	catch(invalid_argument) {
		cout << "Banana isn't animal" << endl;
	}

	animal_manager[v_id].set_name("Boris");
	cout << "Cats:" << endl;
	for (const auto& animal_ptr : animal_manager.get_all_of_type<Cat>()) {
		cout << "name: " << animal_ptr->get_name() << ", voice: " << animal_ptr->voice() << endl;
	}

	return 0;
}
