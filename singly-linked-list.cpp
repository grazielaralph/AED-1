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
	cout<< c.get_name()<<" - ";  
	cout<< c.get_code()<<" - ";
	cout<< c.get_courseLoad() << "\n";
}

class Node{
private:
	Course course;
public:
	Node* next;
	Node(): next(nullptr){}
	Node(Course course, Node* next): course(course), next(next){}
	const Course& get_course();

};

const Course& Node::get_course(){
	return course;
}

class SinglyLinkedList{
private:
	Node* first = nullptr; //prim
	Node* last = nullptr;
	int length; //ult
	void succ(Node*& p);
public:
	SinglyLinkedList(){
		first = new Node{}; 
		first -> next = nullptr;//nao precisa inicializar com o next nulo porque ja é feito no construtor padrão do node 
		last = first;
		length = 0;
	}
	void insert(Course c);

};

void SinglyLinkedList::succ(Node*& p){
	p = p -> next;
}

void SinglyLinkedList::insert (Course c){
	last->next = new Node{c, nullptr}; //pega o next do ultimo elemento e insere o nó do proximo elemento 
	//a setinha significa que estamos acessando tal elemento via ponteiro
	succ(last);
}


int main(){

	Course c1 {"Matematica Discreta", "ECPMM001", 60};
	Course c2 {"AED1", "ECPMM002", 90};
	Course c3 {"POO", "ECPMM003", 60};
	Course c4 {"Cálculo 1", "ECPMM004", 90};

	SinglyLinkedList l{};

	l.insert(c1);
	l.insert(c2);
	l.insert(c3);
	l.insert(c4);


	return 0;
}
//forma braçal 
/*int main(){
	Course c1 {"Matematica Discreta", "ECPMM001", 60};
	Course c2 {"AED1", "ECPMM002", 90};
	Course c3 {"POO", "ECPMM003", 60};
	Course c4 {"Cálculo 1", "ECPMM004", 90};

	Node n1{c1,nullptr};
	Node n2{c2, nullptr};
	Node n3{c3, nullptr};
	Node n4{c4, nullptr};
	Node* ptr_node;
	ptr_node = &n1;
	print(ptr_node->get_course());
	ptr_node->next = &n2;
	print(ptr_node->next->get_course());

	return 0;
}*/