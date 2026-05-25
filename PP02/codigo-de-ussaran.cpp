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
	

}

//----------------------------------------------------------------------------------------------------------------------------
<typename T>
class HashTable{
private:
	T

public:


}

int main(){

	return 0;
}