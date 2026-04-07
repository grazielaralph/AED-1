#include <iostream>
using namespace std;
//const int NIL = -1; 

class Task{
	//atributos sao privados e metodos publicos
private:
	string description;
	string datetime;
	bool done;
public:
	Task()=default;
	Task(string desc, string dt):
		description(desc),
		datetime(dt),
		done(false){}

	void markAsDone();
	void markAsNotDone();
	bool isDone(); //isDone() tambem é considerado um método get, porem com nome diferente rs
	
	//get -> metodo para acessar os atributos que estao privados 
	string get_description();
	string get_datetime();
};

//metodos da classe Task
string Task::get_description(){
		return description;
}

string Task::get_datetime(){
		return datetime;
}

bool Task::isDone(){
		return done;
}

void Task::markAsDone(){
		done = true;
	}

void Task::markAsNotDone(){
		done = false;
	}

template <typename T>
class List{
private: 
	T* itens;
	int length = 0;
	int max_length = 0;
	bool valid_position(int pos) const;
public:
	//construtores
	List()=default;

	List(int max_length_):max_length(max_length_){
		itens = new Task[max_length];
		length=0;
	}
	

	//destrutor pra matar minha listinha procrastinada
	~List(){
		delete[] itens;
		itens = nullptr;
	}

	//metodos
	T* get_item(int pos) const;
	void insert(T item);
	int get_length() const;
	bool del(int pos);
	bool empty();
};

template<typename T>
bool List<T>::valid_position(int pos) const{
	return pos>0 && pos<=length;
}

template <typename T>
T* List<T>::get_item(int pos) const{
	if(valid_position(pos)){
		return &itens[pos];
	}
	return nullptr;
}

template <typename T>
void List<T>::insert(T item){
	if(length < max_length){
		length++;
		itens[length] = item;
	}else{
		cout << "Lista cheia\n";
	}
}

template<typename T>
int List<T>::get_length() const{
	return length;
}

template <typename T>
bool List<T>::empty(){
	return length == 0;
}

template<typename T>
bool List<T>::del(int pos){
	if(!empty() && valid_position(pos)){
		for(int i=pos; i<=length-1; i++){
			itens[i] = itens[i+1];
		}
		length--;
		return true;
	}
	return false;
}


//metodos globais
void print(Task t){
	cout << t.get_description() << " - ";
	cout << t.get_datetime() << " - ";
	cout << (t.isDone()?"Feito":"Por fazer") << "\n";
	}


template <typename T>
void print (const List<T>& l){
	for (int i=1; i<=l.get_length(); i++){
		T* item_ptr = l.get_item(i);
		if(item_ptr != nullptr){
			print(*item_ptr);
		}else{
			cout<<"Erro no print. Posição nao encontrada\n";
		}

	}
}

Task* search_task_by_desk(string desc, const List<Task>& list){
	for(int i=1; i<list.get_length(); i++){ //percorre a lista
		Task* prt_task = list.get_item(i); 
		//pega o ponteiro da lista e verifica se bate com a descrição da pesquisa
		if(desc == prt_task->get_description()){
			return prt_task; //caso encontre a task desejada. Retorno o ponteiro
		}
	}
	return nullptr;
}

int main(){

	Task t1{"Comer um x-caboquinho", 
		   "20/03/2026 7:00"};
	Task t2{"Ir para a academia", 
		   "20/03/2026 9:00"};
	Task t3{"Comer lasanha",
		   "20/03/2026 12:00"};

	List<Task> minha_todolist{10}; //lista generica se tornando especifica para o tipo task

	minha_todolist.insert(t1);
	minha_todolist.insert(t2);
	minha_todolist.insert(t3);
	print(minha_todolist);

	std::cout << "\nRemovendo...\n";
	int pos = 3;
	if (minha_todolist.del(pos)) {
		cout << "Item removido com sucesso.\n";
	}	
	else {
		cout << "Remoção não efetuada.\n";
	}
	print(minha_todolist);
	pos = 1;
	if (minha_todolist.del(pos)) {
		cout << "Item removido com sucesso.\n";
	}	
	else {
		cout << "Remoção não efetuada.\n";
	}
	print(minha_todolist);



	return 0;

	/*Task t{"Comer x salada", "18/03/20206 20:00"};
	print(t);

	t.markAsDone();
	print(t);

	t.markAsNotDone();
	print(t);*/
}