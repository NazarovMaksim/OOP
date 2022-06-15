#pragma once

#include <iostream>
#include <exception>
#include <type_traits>
#include <vector>
using namespace std;


template <typename T>
concept ObjectRequirements = requires(T object)
{
	//{(int)object } -> std::convertible_to<int>;
	requires std::is_default_constructible<T>::value;
	//requires is_class<T>::value;
	requires is_copy_constructible<T>::value;
};



template<ObjectRequirements T>
class ContainerInterface      //Основной интерфейс контейнера
{
public:
	virtual ~ContainerInterface() = default;

	virtual void push_back(T) = 0;
	virtual void erase(int) = 0;
	virtual void pop() = 0;
	virtual void insert(int, T) = 0;
	virtual T& at(size_t) = 0;
};

template<typename T> // Вспомогательный контейнер типа Stack с поддержкой извлечения выбранного элемента 
class CustomVector : public ContainerInterface< T>
{
	class Node
	{
	public:
		T data;
		Node* next;
		Node* pred;
		Node(T data_, Node* pred_ = nullptr, Node* next_ = nullptr) : data{ data_ }, pred{ pred_ }, next{ next_ } {}
		friend ostream& operator << (ostream& out, Node& object)
		{
			out << object.data;
			return out;
		}
	};

	Node* head;
	Node* tail;
	int size;

	template<class Iter>
	class NodeIterator
	{
		friend struct CustomVector::Node;
		friend class CustomVector;
	public:
		typedef Iter iterator_type;
		typedef std::input_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

		iterator_type* value;

	private:
		NodeIterator(Iter* p) : value{ p } { } //закрытый конструктор

	public:
		NodeIterator(const NodeIterator& it) : value{ it.value } {} // конструктор копирования 

		bool operator !=(NodeIterator const& other) const
		{
			return value != other.value;
		}
		bool operator ==(NodeIterator const& other) const
		{
			return value == other.value;
		}
		typename NodeIterator::reference operator*() const
		{
			return *value;
		}
		NodeIterator& operator++()
		{
			if (value)
			{
				value = value->next;
				return *this;
			}
		}
	};

	Node* search(T data)
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == data)
				return temp;
		}
		return nullptr;
	}
public:
	CustomVector()
	{
		head = nullptr;
		tail = nullptr;
	}

	~CustomVector()
	{
		Node* temp = head;
		while (head)
		{
			head = head->next;
			delete temp;
			temp = head;
		}

	}

	void push_back(T data) override
	{
		if (!head)
		{
			head = new Node(data);
			tail = head;
		}
		else
		{
			Node* new_element = new Node(data, tail);
			tail->next = new_element;
			tail = new_element;
		}
		size++;
	}


	void pop() override
	{
		if (!head)
			throw logic_error("Trying to remove from an empty container");
		else
		{
			if (head == tail)
			{
				delete tail;
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				Node* temp = head->next;
				temp->pred = nullptr;
				delete head;
				head = temp;
			}
			size--;
		}
	}

	void insert(int index, T data) override
	{
		if (index > size || index < 0)
			throw logic_error("Out of range");
		else
		{
			if (index == 0)
			{
				Node* temp = new Node(data);
				temp->next = head;
				if (head)
					head->pred = temp;
				else
					tail = temp;
				head = temp;
			}
			else if (index == size)
			{
				Node* temp = new Node(data);
				temp->pred = tail;
				tail->next = temp;
				tail = temp;
			}
			else
			{
				Node* temp = head;
				while (index != 0) {
					temp = temp->next;
					index--;
				}
				Node* new_node = new Node(data, temp->pred, temp);
				temp->pred->next = new_node;
				temp->pred = new_node;
			}
			size++;
		}
	}

	void erase(int index) override
	{
		if (index >= size || index < 0)
			throw logic_error("Out of range");
		else
		{
			if (index == 0)
			{
				Node* temp = head;
				head = head->next;
				delete temp;
				if (head == nullptr)
					tail = head;
				else
					head->pred = nullptr;
			}
			else if (index == size - 1)
			{
				Node* temp = tail;
				tail = tail->pred;
				delete temp;
				if (tail == nullptr)
					head = tail;
				else
					tail->next = nullptr;
			}
			else
			{
				Node* temp = head;
				while (index != 0) {
					temp = temp->next;
					index--;
				}
				temp->next->pred = temp->pred;
				temp->pred->next = temp->next;
				delete temp;
			}
			size--;
		}
	}

	T& at(size_t index) override
	{
		if (index >= size || index < 0)
			throw logic_error("Out of range");
		else
		{
			Node* temp = head;
			while (index != 0) {
				temp = temp->next;
				index--;
			}
			return temp->data;
		}
	}

	T& operator[](size_t index) { return at(index); }

	size_t get_size() { return size; }
	/// 
	/// Публичный интерфейс итератора
	/// 
	typedef NodeIterator<Node> iterator;
	typedef NodeIterator<const Node> const_iterator;
	iterator begin()
	{
		return head;
	}

	iterator end()
	{
		return nullptr;
	}

	const_iterator begin() const
	{
		return head;
	}

	const_iterator end() const
	{
		return nullptr;
	}
};


template<class InputIt, class UnaryPredicate>
constexpr vector<InputIt> custom_find_all(InputIt first, InputIt last, UnaryPredicate p)
{
	vector<InputIt> result;
	for (; first != last; ++first) {
		if (p(*first)) {
			result.push_back(first);
		}
	}
	return result;
}