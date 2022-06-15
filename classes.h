#pragma once
#include <ctime>
#include <string>
using namespace std;

class Buyer
{
	string name;
	int balance;
public:
	Buyer(string name_, int balance_) : name{ name_ }, balance{balance_} {}  // констуктор
	Buyer() : name{ "Not difined" }, balance{0} {} // констуктор по умлочанию
	Buyer(const Buyer& ref_Point) // конструктор копирования
	{
		name = ref_Point.name;
		balance = ref_Point.balance;
	}
	int get_balance() { return balance; }
	string get_name() { return name; }
	void balance_decrement(int dec) { balance -= dec; }
	friend ostream& operator << (ostream& out, Buyer& object)
	{
		out << "Buyer name: " << object.name << " Balance: " << object.balance << "$";
		return out;
	}
};

class Provider
{
	string company_name;
	int provider_id;

public:
	static int id_increment;
	static bool initialize;
	Provider(string company_name_, int provider_id_ = id_increment) : company_name{ company_name_ }, provider_id{ id_increment }
	{
		if (!initialize)
			throw logic_error("Need to initialize class ID first");
		id_increment++;
	}
	Provider() : company_name{ "Not difined" }, provider_id{ id_increment }
	{
		if (!initialize)
			throw logic_error("Need to initialize class ID first");
		id_increment++;
	}
	Provider(const Provider& ref_Point) // конструктор копирования
	{
		company_name = ref_Point.company_name;
		provider_id = ref_Point.provider_id;
	}
	int get_id() { return provider_id; }
	static void set_id_increment(int id)
	{
		id_increment = id;
		initialize = true;
	}
	friend ostream& operator << (ostream& out, Provider& object)
	{
		out << "Company name: " << object.company_name << "  ID: " << object.provider_id;
		return out;
	}
};

class Product
{
	string name;
	string discription;
	int amount;
	int provider_id;
	int price;
	std::time_t time_of_registration;
public:
	Product(string name_, string discription_, int price_,int amount_, int provider_id_) :
		name{ name_ }, discription{ discription_ }, amount{ amount_ }, price{price_},
		time_of_registration{ std::time(nullptr)}, provider_id{ provider_id_ } {}
	Product() :
		name{ "" }, discription{ "" }, amount{ 0 }, time_of_registration{ std::time(nullptr) }, provider_id{0}, price{ 0 }{}
	Product(const Product& ref_Point) // конструктор копирования
	{
		name = ref_Point.name;
		discription = ref_Point.discription;
		amount = ref_Point.amount;
		time_of_registration = ref_Point.time_of_registration;
		provider_id = ref_Point.provider_id;
		price = ref_Point.price;
	}
	friend ostream& operator << (ostream& out, Product& object)
	{
		out <<"Product name: " << object.name << " Provider ID: " << object.provider_id << " | Discription: " << object.discription 
		<< " Price: " << object.price << " | Amount: " << object.amount << " | Registration time: " << asctime(localtime(&object.time_of_registration));
		return out;
	}
	void amount_decrement(int dec)
	{
		if (dec <= amount)
			amount -= dec;
		else
			throw logic_error("Out of amount range");
	}
	int get_id() { return provider_id; }
	string get_name() { return name; }
	int get_price() { return price; }
};

