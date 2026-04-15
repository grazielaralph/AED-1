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
	void print() const;

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



//mostragem da materia 
void Course::print() const{	
	cout<< get_name()<<" - ";  
	cout<< get_code()<<" - ";
	cout<< get_courseLoad() << "\n";
}

//metodos gerais
/*void print (const Course& c){
	cout<< c.get_name()<<" - ";  
	cout<< c.get_code()<<" - ";
	cout<< c.get_courseLoad() << "\n";
}*/


//classe nó
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

//lista simplesmente encadeada
class SinglyLinkedList{
private:
	Node* first = nullptr; //prim
	Node* last = nullptr;
	int length; //ult
	void succ(Node*& p);
	Node* search(string name); //busca por chave
	bool del(Node* p);
	Node* predecessor(Node* r);
public:
	SinglyLinkedList(){
		first = new Node{}; 
		first -> next = nullptr;//nao precisa inicializar com o next nulo porque ja é feito no construtor padrão do node 
		last = first;
		length = 0;
	}
	void insert(Course c);
	void print();
	bool search(Course& c);
	bool del(Course& c);
	bool empty();
};

//metodo pra receber o nó do sucessor
void SinglyLinkedList::succ(Node*& p){
	p = p -> next;
}

//inserior novo item na lista
void SinglyLinkedList::insert (Course c){
	last->next = new Node{c, nullptr}; //pega o next do ultimo elemento e insere o nó do proximo elemento 
	//a setinha significa que estamos acessando tal elemento via ponteiro
	succ(last);
	length++;
}

//imprimir os elementos da lista
void SinglyLinkedList::print(){
	Node* p = first->next;
	while(p!=nullptr){
		p->get_course().print();
		succ(p);
	}
	cout<<"\n";
}

Node* SinglyLinkedList::search(string name){
	Node* p = first -> next;
	//p->get_course() pega o curso que está no endereço recebido pelo p. A partir disso, descobrimos o nome do curso neste nó
	while(p != nullptr && p->get_course().get_name()!=name){
		succ(p);
	}
	return p;
}
bool SinglyLinkedList::search(Course& c){
	string k = c.get_name(); //chave pra encontrar o nó
	Node* p = search(k); //procuro o nó na lista a partir da chave que eu peguei e recebo o ponteiro desse nó (ou nulo caso nao encontre)
	if(p!=nullptr){ //depois verifico se o ponteiro retornado é nulo ou nao
		c = p->get_course();
		return true;
	}
	return false;
}

Node* SinglyLinkedList::predecessor(Node* r){
	Node* p = first->next;
	//enquanto o p for diferente do r, a gente percorre a lista porque o endereço do nó é sempre do próximo
	while(p!=nullptr && p->next != r){
		succ(p);
	}
	return p;
}

bool SinglyLinkedList::del(Node* r){
	if(empty() || r==nullptr){
		return false;
	}
	Node* p = predecessor(r);
	if(p==nullptr){return false;}
	p->next = r->next;
	if(p->next == nullptr){
		last = p;
	}
	delete r;
	return true;
}

bool SinglyLinkedList::del(Course& c){
	Node* r = search(c.get_name());
	if(del(r)){
		length--;
		return true;
	}
	return false;
}

bool SinglyLinkedList::empty(){
	//a lista estará vazia se o endereço do nó apontar pra ele mesmo
	return length==0;
}

int main(){

	Course c1 {"Matematica Discreta", "ECPMM001", 60};
	Course c2 {"AED1", "ECPMM002", 90};
	Course c3 {"POO", "ECPMM003", 60};
	Course c4 {"Calculo 1", "ECPMM004", 90};

	SinglyLinkedList l{};

	l.insert(c1);
	l.insert(c2);
	l.insert(c3);
	l.insert(c4);

	l.print();

	cout<<"Testando a busca...\n";

	Course c{"Física 4", "", 0};

	if(l.search(c)){
		cout<<"Disciplina encontrada! \n";
		c.print();
	}else{
		cout<<"Disciplina nao encontrada! \n";
	}

	cout<<"Testando remocao\n";
	Course cc{"Matematica Discreta", "", 0};

	if(l.del(cc)){
		cout<<"Disciplina removida!\n";
	}else{
		cout<<"Disciplina nao removida!\n";
	}

	cout<<"\n";
	l.print();

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