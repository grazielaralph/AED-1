#include <iostream>
using namespace std;

class Course{
private:
	string name;
	string code;
	int courseLoad;
public:
	//construct
	Course()=default;
	Course(string name_,
	string code_,
	int courseLoad_):
	name(name_),
	code(code_),
	courseLoad(courseLoad_){}

	//get 
	string get_name() const;  
	string get_code()const;
	int get_courseLoad() const;
};

//metodos da classe
string Course::get_name() const {
	return name;
}

string Course::get_code() const {
	return code;
}

int Course::get_courseLoad() const {
	return courseLoad;
}

//metodos gerais
void print (const Course& c){
	cout<< c.get_name()<<"-";  
	cout<< c.get_code()<<"-";
	cout<< c.get_courseLoad() << "\n";
}

class Node{
private:
	Course course;
public:
	Node* next;
	Node(): next(nullptr){}
	Node(Course course, Node* next): course(course), next(next){}

};

int main(){
	Course c1 {"Matemática Discreta", "ECPMM001", 60};
	Course c2 {"AED1", "ECPMM002", 90};
	Course c3 {"POO", "ECPMM003", 60};
	Course c4 {"Cálculo 1", "ECPMM004", 90};

	Node n1{c1,nullptr};
	Node n2{c2, nullptr};
	Node n3{c3, nullptr};
	Node n4{c4, nullptr};
	Node* ptr_node;
	ptr_node = &n1;
	ptr_node -> n1.next = &n2;

	return 0;
}