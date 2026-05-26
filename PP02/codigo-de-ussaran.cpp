#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
    T item;
public:
    Node<T>* next;
    Node<T>* prev;
    Node(): next(nullptr),prev(nullptr) {}
    Node(T item): item(item), next(nullptr), prev(nullptr) {}
    T& get_item();
};

template<typename T>
T& Node<T>::get_item() { return item; }

//----------------------------------------------------------------------------------------------------------------------------
template<typename V, typename K>
class HashNode{
private:
	K key;
	V value;
public:
	HashNode(K key, V value): key(key), value(value){}
	K& getKey();
	V& getValue();
}

template<typename V>
V& HashNode<V>::getValue() {return value;}

template <typename K>
K& HashNode<K>::getKey(){return key;}



//----------------------------------------------------------------------------------------------------------------------------
template <typename T>
class HashTable{
private:
	

public:


}

int main(){

	return 0;
}