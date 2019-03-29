#pragma once
#include <iostream>

template <typename T1, typename T2>
struct Node
{
	T1 key;
	T2 value;
	Node<T1, T2> *next, *prev;
};

template <typename T1, typename T2>
class Unordered_map {
private:
	Node<T1, T2> *head, *tail;
public:
	Unordered_map<T1, T2>()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	void AddNode(T1 key, T2 value)
	{
		Node<T1, T2> *temp = new Node<T1, T2>;
		temp->next = nullptr;
		temp->key = key;
		temp->value = value;

		if (head != nullptr)
		{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		else
		{
			temp->prev = nullptr;
			head = tail = temp;
		}
	}

	T1 FindKey(T2 value)
	{
		Node<T1, T2> *temp = new Node<T1, T2>;
		temp = head;

		try
		{
			while (temp != nullptr)
			{
				if (temp->value == value)
				{
					return temp->key;
				}
				temp = temp->next;
			}

			throw std::exception("There is no key with this value!");
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	T2 FindValue(T1 key)
	{
		Node<T1, T2> *temp = new Node<T1, T2>;
		temp = head;

		try
		{
			while (temp != nullptr)
			{
				if (temp->key == key)
				{
					return temp->value;
				}
				temp = temp->next;
			}

			throw std::exception("There is no key with this value!");
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void DeleteNode(T1 key)
	{
		Node<T1, T2> *temp = new Node<T1, T2>;
		temp = head;

		while (temp->key != key)
		{
			temp = temp->next;
		}

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}

	void Show()
	{
		Node<T1, T2> *temp = new Node<T1, T2>;
		temp = head;

		while (temp != nullptr)
		{
			std::cout << temp->key << ": " << temp->value << std::endl;
			temp = temp->next;
		}
	}
};