#include <iostream>
using namespace std;

template <typename T>
class QueueNavigator{};

template <typename T>
class Queue{
private: 
    int length=0;
public:
	void enqueue(T item);
	void dequeue();
	const T& front();
	bool empty();
	int size();
	QueueNavigator getStackNavigator();
    };


 int main(){
 	
 return 0;
 }