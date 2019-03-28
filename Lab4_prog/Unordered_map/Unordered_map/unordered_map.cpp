#include "unordered_map.h"

template <typename T1, typename T2>
unordered_map<T1, T2>::unordered_map(T1 key, T2 value)
{
	this->key = key;
	this->value = value;
	this->next = nullptr;
}

template <typename T1, typename T2>
T1 unordered_map<T1, T2>::getKey()
{
	return key;
}

template <typename T1, typename T2>
T2 unordered_map<T1, T2>::getValue() {
	return value;
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::setValue(T2 value) {
	this->value = value;
}

template <typename T1, typename T2>
unordered_map<T1, T2>* unordered_map<T1, T2>::getNext() {
	return next;
}

template <typename T1, typename T2>
void unordered_map<T1, T2>::setNext(unordered_map<T1, T2> *next) {
	this->next = next;
}