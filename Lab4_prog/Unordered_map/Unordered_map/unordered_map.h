#pragma once
#include <iostream>
#include <optional>

template <typename TKey, typename TValue>
struct node
{
	TKey key;
	TValue value;
};

template <typename TKey, typename TValue>
class Unordered_map {
	std::optional<node<TKey, TValue>> *table_;
	unsigned capacity_;
	unsigned count_;

public:
	Unordered_map();
	Unordered_map(unsigned capasity);
	~Unordered_map();
	unsigned hash(int key) const;
	TValue search(TKey key) const;
	void insert(TKey key_val, TValue el_value);
	void show() const;
	void Delete(TKey key);
};

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
unsigned Unordered_map<TKey, TValue>::hash(int const key) const
{
	return key % capacity_;
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::insert(TKey key_val, TValue el_value) {
	try
	{
		for (int i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt && key_val == table_[i]->key)
			{
				throw std::exception("An object with this key already exist!");
			}
		}
		unsigned position = hash((int)key_val);
		for (int i = position; i < capacity_; i++)
		{
			if (table_[i] == std::nullopt)
			{
				node<TKey, TValue> a;
				table_[i] = a;
				table_[i]->key = key_val;
				table_[i]->value = el_value;
				break;
			}
		}
		count_++;
		if (count_ * 3 >= capacity_)
		{
			capacity_ *= 2;
			std::optional<node<TKey, TValue>> *new_table = new std::optional<node<TKey, TValue>>[capacity_];
			for (int i = 0; i < capacity_ / 2; i++)
			{
				if (table_[i] != std::nullopt)
				{
					node<TKey, TValue> a;
					new_table[i] = a;
					new_table[i]->key = table_[i]->key;
					new_table[i]->value = table_[i]->value;
				}
			}
			delete[] table_;
			table_ = new_table;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

template <typename TKey, typename TValue>
void Unordered_map<TKey, TValue>::show() const
{
	for (int i = 0; i < capacity_; i++)
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
		for (int i = 0; i < capacity_; i++)
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
		for (int i = 0; i < capacity_; i++)
		{
			if (table_[i] != std::nullopt && table_[i]->key == key)
			{
				table_[i] = std::nullopt;
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