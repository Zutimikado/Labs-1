#pragma once

template <typename T1, typename T2>
class unordered_map {
private:
	T1 key;
	T2 value;
	unordered_map<T1, T2> *next;
public:
	unordered_map<T1, T2>(T1, T2);
	T1 getKey();
	T2 getValue();
	void setValue(T2);
	unordered_map<T1, T2>* getNext();
	void setNext(unordered_map<T1, T2>*);
};