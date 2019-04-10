#pragma once
#include <iostream>
#include <optional>
#include <filesystem>

template <typename TKey, typename TValue>
struct node
{
	TKey key;
	TValue value;
	node<TKey, TValue>() = default;
	node<TKey, TValue>& operator= (std::optional<node<TKey, TValue>>& a);
};

template <typename TKey, typename TValue>
node<TKey, TValue>& node<TKey, TValue>::operator= (std::optional<node<TKey, TValue>>& a)
{
	this->key = a->key;
	this->value = a->value;
	return *this;
}

template <typename TKey, typename TValue>
class Unordered_map {
	std::optional<node<TKey, TValue>>* table_;
	unsigned capacity_;
	unsigned count_;

public:
	class iterator;
	Unordered_map();
	Unordered_map(unsigned capasity);
	~Unordered_map();
	unsigned hash(TKey key) const;
	TValue search(TKey key) const;
	void insert(TKey key_val, TValue el_value);
	void show() const;
	void Delete(TKey key);
	TKey& operator[] (unsigned position) const;
	unsigned count() const;
	unsigned size() const;
	bool empty() const;
	void clear();
	iterator begin();
	iterator end();
	void test();

	friend class iterator;

	class iterator
	{
		std::optional<node<TKey, TValue>>* current_;
	public:
		iterator(std::optional<node<TKey, TValue>>* first);
		std::optional<node<TKey, TValue>>& operator+ (int n);
		std::optional<node<TKey, TValue>>& operator- (int n);
		std::optional<node<TKey, TValue>>& operator++ (int);
		std::optional<node<TKey, TValue>>& operator-- (int);
		bool operator!= (const iterator& it);
		bool operator== (const iterator& it);
		std::optional<node<TKey, TValue>>& operator* ();
	};
};

template <typename TKey, typename TValue>
Unordered_map<TKey, TValue>::iterator::iterator (std::optional<node<TKey, TValue>>* first)
{
	current_ = first;
}

template <typename TKey, typename TValue>
std::optional<node<TKey, TValue>>& Unordered_map<TKey, TValue>::iterator::operator+ (int n)
{
	while (n > 0)
	{
		current_ += 1;
		if (*current_ != std::nullopt)
		{
			n--;
		}
	}
	return *current_;
}

template <typename TKey, typename TValue>
std::optional<node<TKey, TValue>>& Unordered_map<TKey, TValue>::iterator::operator- (int n)
{
	while (n > 0)
	{
		current_ -= 1;
		if (*current_ != std::nullopt)
		{
			n--;
		}
	}
	return *current_;
}

template <typename TKey, typename TValue>
std::optional<node<TKey, TValue>>& Unordered_map<TKey, TValue>::iterator::operator++ (int)
{
	while (true)
	{
		if (*(current_ + 1) != std::nullopt)
		{
			return *current_++;
		}
		current_ += 1;
	}
}

template <typename TKey, typename TValue>
std::optional<node<TKey, TValue>>& Unordered_map<TKey, TValue>::iterator::operator-- (int)
{
	while (true)
	{
		if (*(current_ - 1) != std::nullopt)
		{
			return *current_--;
		}
		current_ -= 1;
	}
}

template <typename TKey, typename TValue>
bool Unordered_map<TKey, TValue>::iterator::operator!=(const iterator& it)
{
	return current_ != it.current_;
}

template <typename TKey, typename TValue>
bool Unordered_map<TKey, TValue>::iterator::operator==(const iterator& it)
{
	return this.current_ == it.current_;
}


template <typename TKey, typename TValue>
std::optional<node<TKey, TValue>>& Unordered_map<TKey, TValue>::iterator::operator* ()
{
	return *current_;
}

template <typename TKey, typename TValue>
typename Unordered_map<TKey, TValue>::iterator Unordered_map<TKey, TValue>::begin()
{
	try
	{
		if (this->empty())
		{
			throw std::exception("Container is empty!");
		}
		for (auto i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt)
			{
				return table_ + i;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
typename Unordered_map<TKey, TValue>::iterator Unordered_map<TKey, TValue>::end()
{
	try
	{
		if (this->empty())
		{
			throw std::exception("Container is empty!");
		}
		for (int i = capacity_; i >= 0; i--)
		{
			if (table_[i] != std::nullopt)
			{
				return table_ + i;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
Unordered_map<TKey, TValue>::Unordered_map()
{
	count_ = 0;
	capacity_ = 10;
	table_ = new std::optional<node<TKey, TValue>> [capacity_];
}

template <typename TKey, typename TValue>
Unordered_map<TKey, TValue>::Unordered_map(unsigned const capasity)
{
	count_ = 0;
	capacity_ = capasity;
	table_ = new std::optional<node<TKey, TValue>> [capacity_];
}

template <typename TKey, typename TValue>
Unordered_map<TKey, TValue>::~Unordered_map<TKey, TValue>()
{
	count_ = 0;
	delete[] table_;
}

template <typename TKey, typename TValue>
unsigned Unordered_map<TKey, TValue>::hash(TKey key) const
{
	auto const const_hash = 0.618033;
	return capacity_ * fmod(int(key) * const_hash, 1);
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::insert(TKey key_val, TValue el_value) {
	try
	{
		for (auto i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt && key_val == table_[i]->key)
			{
				throw std::exception("An object with this key already exist!");
			}
		}
		unsigned const position = hash(static_cast<int>(key_val));
		if (count_ * 2 >= capacity_)
		{
			capacity_ *= 2;
			auto*new_table = new std::optional<node<TKey, TValue>>[capacity_];
			for (auto i = 0; i < capacity_ / 2; i++)
			{
				if (table_[i] != std::nullopt)
				{
					node<TKey, TValue> a{};
					new_table[i] = a;
					new_table[i]->key = table_[i]->key;
					new_table[i]->value = table_[i]->value;
				}
			}
			delete[] table_;
			table_ = new_table;
		}
		if (position >= capacity_)
		{
			capacity_ = position + 1;
			auto*new_table = new std::optional<node<TKey, TValue>>[capacity_];
			for (auto i = 0; i < capacity_ / 2; i++)
			{
				if (table_[i] != std::nullopt)
				{
					node<TKey, TValue> a{};
					new_table[i] = a;
					new_table[i]->key = table_[i]->key;
					new_table[i]->value = table_[i]->value;
				}
			}
			delete[] table_;
			table_ = new_table;
		}
		for (int i = position; i < capacity_; i++)
		{
			if (table_[i] == std::nullopt)
			{
				node<TKey, TValue> a{};
				table_[i] = a;
				table_[i]->key = key_val;
				table_[i]->value = el_value;
				break;
			}
		}
		count_++;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::show() const
{
	for (auto i = 0; i < capacity_; i++)
	{
		if (table_[i] != std::nullopt)
		{
			std::cout << table_[i]->key << ": " << table_[i]->value << std::endl;
		}
	}
}

template <typename TKey, typename TValue>
TValue Unordered_map<TKey, TValue>::search(TKey key) const
{
	try
	{
		for (auto i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt && table_[i]->key == key)
			{
				return table_[i]->value;
			}
		}
		throw std::exception("No object with this key was found!");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::Delete(TKey key)
{
	try
	{
		for (auto i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt && table_[i]->key == key)
			{
				table_[i] = std::nullopt;
				count_--;
				return;
			}
		}
		throw std::exception("No object with this key was found!");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
TKey& Unordered_map<TKey, TValue>::operator[](unsigned position) const
{
	try
	{
		if (table_[position] != std::nullopt)
		{
			return table_[position]->key;
		}
		throw std::exception("No object with this position was found!");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
unsigned Unordered_map<TKey, TValue>::count() const
{
	return count_;
}

template <typename TKey, typename TValue>
unsigned Unordered_map<TKey, TValue>::size() const
{
	return capacity_;
}

template <typename TKey, typename TValue>
bool Unordered_map<TKey, TValue>::empty() const
{
	for (auto i = 0; i < capacity_; i++)
	{
		if (table_[i] != std::nullopt)
		{
			return false;
		}
	}
	return true;
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::clear()
{
	count_ = 0;
	for (auto i = 0; i < capacity_; i++)
	{
		table_[i] = std::nullopt;
	}
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::test()
{
	this->insert(14, "Nikita");
	this->insert(2481, "Anna");
	this->insert(35, "Andrei");
	this->insert(124, "Tanya");
	this->insert(52, "Masha");
	this->insert(642, "Nastya");

	this->show();
	std::cout << std::endl;

	this->Delete(52);

	for (auto it = this->begin(); it != this->end(); it++)
	{
		node<TKey, TValue> a{};
		a = *it;
		std::cout << a.key << ": " << a.value << std::endl;
	}
	std::cout << std::endl;

	if (this->empty())
	{
		std::cout << "Container is empty!" << std::endl;
	}
	else
	{
		std::cout << "Container isn't empty! Count = " << this->count() << ". Size = " << this->size() << std::endl;
	}
	std::cout << std::endl;

	this->clear();

	if (this->empty())
	{
		std::cout << "Container is empty!" << std::endl;
	}
	else
	{
		std::cout << "Container isn't empty! Count = " << this->count() << ". Size = " << this->size() << std::endl;
	}
	std::cout << std::endl;

	this->insert(89, "Petya");
	this->insert(775, "Vasya");
	this->insert(2000, "Sasha");
	this->insert(1991, "Kolya");
	this->insert(2323, "Masha");
	this->insert(688, "Nastya");
	this->insert(17, "Nikita");
	this->insert(2600, "Anna");
	this->insert(3000, "Andrei");
	this->insert(41, "Tanya");
	this->insert(1392, "Volodya");
	this->insert(72, "Seva");
	this->insert(124, "Denis");
	this->insert(100, "Vlad");
	this->insert(9999, "Egor");
	this->insert(12114, "Stas");
	this->insert(70, "Dasha");
	this->insert(3872, "Arina");
	this->insert(16, "Violetta");
	this->insert(248781, "Lesha");
	this->insert(352, "Aleksey");
	this->insert(12489, "Ilya");
	this->insert(2, "Anastasia");
	this->insert(567, "Igor");
	this->insert(14, "Maya");
	this->insert(2481, "Kostya");
	this->insert(35, "Misha");
	this->insert(124, "Somar");
	this->insert(52, "Maksim");
	this->insert(642, "Vladislav");

	this->show();
	std::cout << std::endl;

	if (this->empty())
	{
		std::cout << "Container is empty!" << std::endl;
	}
	else
	{
		std::cout << "Container isn't empty! Count = " << this->count() << ". Size = " << this->size() << std::endl;
	}
	std::cout << std::endl;

	std::cout << this->search(124) << std::endl;
	std::cout << std::endl;
}
