#include "Header.h"
#include "classes.h"
#include "main_interface.h"

int Provider::id_increment;
bool Provider::initialize;

int main()
{

	//auto answers = custom_find_all(test.begin(), test.end(), [](auto number) {return (number.data % 2 == 0) ? true : false; });
	//for (auto item : answers)
	//	cout << *item << endl;

	Provider::set_id_increment(1);


	cout << "Buyers:" << endl;
	StorageMainInterface::getInstance()->add_new_buyer("Add", 134);
	StorageMainInterface::getInstance()->add_new_buyer("Nick", 200);
	StorageMainInterface::getInstance()->add_new_buyer("Joe", 10000);
	StorageMainInterface::getInstance()->show_list_of_buyers();
	/////////////////////////////////
	cout << "Providers:" << endl;
	StorageMainInterface::getInstance()->add_new_provider("Media-Tec");
	StorageMainInterface::getInstance()->add_new_provider("Science-Lab");
	StorageMainInterface::getInstance()->show_list_of_providers();

	////////////////////////////////
	cout << "Products:" << endl;
	StorageMainInterface::getInstance()->add_new_product("TestProd1", "TestDiscription1", 100, 12, 1);
	StorageMainInterface::getInstance()->add_new_product("TestProd2", "TestDiscription2", 1000, 15, 1);
	StorageMainInterface::getInstance()->add_new_product("TestProd1", "TestDiscription1", 120, 10, 2);
	StorageMainInterface::getInstance()->show_list_of_products();
	StorageMainInterface::getInstance()->show_all_products_with_current_provider(1);
}

