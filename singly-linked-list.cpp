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
template<typename T>
class Node{
private:
	T item;
public:
	Node<T>* next; //ponteiro pro proximo elemento da lista
	Node(): next(nullptr){} //construtor padrão
	Node(T item): item(item), next(nullptr){} //construtor instanciando o item e o ponteiro
	T& get_item();

};

template <typename T>
T& Node<T>::get_item(){
	return item;
}

template<typename T>
class ListNavigator;


//lista simplesmente encadeada
template<typename T>
class SinglyLinkedList{
private:
	Node<T>* first = nullptr; //prim
	Node<T>* last = nullptr; //ult
	int length=0; 
	void succ(Node<T>*& p);
public:
	SinglyLinkedList(){
		first = new Node<T>{}; 
		first -> next = nullptr;//nao precisa inicializar com o next nulo porque ja é feito no construtor padrão do node 
		last = first;
		length = 0;
	}
	bool empty();
	bool valid_pos(int pos) const;
	void insert(T item);
	ListNavigator<T> get_ListNavigator() const;
};

//metodo pra receber o nó do sucessor
template<typename T>
void SinglyLinkedList<T>::succ(Node<T>*& p){
	p = p -> next;
}

//inserior novo item na lista
template<typename T>
void SinglyLinkedList<T>::insert (T item){
	last->next = new Node{item}; //pega o next do ultimo elemento e insere o nó do proximo elemento 
	//a setinha significa que estamos acessando tal elemento via ponteiro
	succ(last);
	length++;
}

template<typename T>
ListNavigator<T> SinglyLinkedList<T>::get_ListNavigator() const{
	return ListNavigator<T>{first->next}; //cria o ponteiro navigator e ja retorna diretamente. 
	//logo nao é necessario alocar um espaco da memoria task neste momento
}

template<typename T>
bool SinglyLinkedList<T>::empty(){
	//a lista estará vazia se o endereço do nó apontar pra ele mesmo
	return length==0;
}

//classe do Navigator
template<typename T>
class ListNavigator{
private:
	Node<T>* current; //ponteiro que irá apontar pro item da vez
public:
	ListNavigator(Node<T>* start): current(start){}
	bool end();//verifica se está no final da fila
	bool next();
	bool getCurrentItem(T&); //pega o item corrente
};

template<typename T>
bool ListNavigator<T>::end(){
	return current == nullptr;
}

template <typename T>
bool ListNavigator<T>::next(){
	current = current->next; //o ponteiro do navigator recebe o endereço do proximo nó
}

template <typename T>
bool ListNavigator<T>::getCurrentItem(T& item){
	if(current == nullptr){
		return false;
	}
	item = current->get_item(); //pega o item cujo endereço está armazenado no ponteiro "navegante"
	return true;
}


//print se torna uma função e deixa de ser um metodo. 
//Para cada lista, seria necessario criar uma função diferente?
template <typename T>
void print(const SinglyLinkedList<T>& list){
	ListNavigator<T> nav = list.get_ListNavigator();
	Course course;
	while(!nav.end()){
		nav.getCurrentItem(course);
		course.print();
		nav.next();
	}
}

//pesquisa pelo codigo do curso 
optional<Course> search_by_code(const string course_code, const SinglyLinkedList<Course>& list){
	ListNavigator<Course> nav = list.get_ListNavigator();
	Course course; //cria um objeto do tipo curso pra comparar um elemento por vez
	while(!nav.end()){
		if(course_code == course.get_code()){
			return course;
		}
		nav.next();
	}
	return nullopt; //falha da busca
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