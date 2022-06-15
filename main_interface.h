#pragma once
#include "classes.h"
#include "Header.h"

class StorageMainInterface // Паттерн Фасад   // Пример интерфейса сущности типа СКЛАД
{
public:
    // Функция-член для доступа к единственному экземпляру (паттерн Синглтон)
    static StorageMainInterface* getInstance() {
        static StorageMainInterface instance;
        return &instance;
    }
private:
    CustomVector<Buyer*> buyers_list;
    CustomVector<Provider*> providers_list;
    CustomVector<Product*> products_list;
    StorageMainInterface() {} // закрытый конструктор
public:
    inline void add_new_buyer(string name, int balance)  // добавление нового покупателя 
    {
        Buyer* new_customer{ new Buyer(name, balance) };
        buyers_list.push_back(new_customer);
    }
    inline void add_new_provider(string name)   // добавление нового поставщика
    {
        Provider* new_customer{ new Provider(name) };
        providers_list.push_back(new_customer);
    }
    inline void add_new_product(string name, string discription, int price, int amount, int product_provider) // добавление нового продукта
    {
        Product* new_customer{ new Product(name, discription, price, amount, product_provider)};
        products_list.push_back(new_customer);
    }
    inline void show_list_of_buyers()  /// методы, выводящие в консоль информацию о сущностях (через range for)
    {
        for (auto buyer : buyers_list)
            cout << *buyer.data << endl;
    }
    inline void show_list_of_providers()
    {
        for (auto provider : providers_list)
            cout << *provider.data << endl;
    }
    inline void show_list_of_products()
    {
        for (auto products : products_list)
            cout << *products.data << endl;
    }

    void show_all_products_with_current_provider(int id)   // пример поиска с кастомной фунцией типа STD::find
    {                                                   // поиск всех продуктов с соответствующим id
        auto search_all_with_id = [&id](auto item) {return (item.data->get_id() == id) ? true : false; };
        auto answers = custom_find_all(products_list.begin(), products_list.end(), search_all_with_id);
        for (auto item : answers)
            cout << *item.value->data << endl;
    }


};