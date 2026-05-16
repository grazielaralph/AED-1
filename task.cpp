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


class ToDoList{
private: 
	Task* itens;
	int length = 0;
	int max_length = 0;
public:
	//construtores
	ToDoList()=default;

	ToDoList(int max_length_):max_length(max_length_){
		itens = new Task[max_length];
		length=0;
	}
	

	//destrutor pra matar minha listinha procrastinada
	~ToDoList(){
		delete[] itens;
		itens = nullptr;
	}

	//metodos
	Task* get_task(int pos);
	void insert(Task t);
	int get_length();
};

//metodos da ToDoList
Task* ToDoList::get_task(int pos){
	if(pos>0 && pos<max_length){
		return &itens[pos];
	}
	return nullptr;
}

void ToDoList::insert(Task t){
	if(length < max_length){
		length++;
		itens[length] = t;
	}else{
		cout << "Lista cheia\n";
	}
}

int ToDoList::get_length(){
	return length;
}


//metodos globais
void print(Task t){
	cout << t.get_description() << " - ";
	cout << t.get_datetime() << " - ";
	cout << (t.isDone()?"Feito":"Por fazer") << "\n";
	}


void print (ToDoList l){
	for (int i=1; i<=l.get_length(); i++){
		Task* task_ptr = l.get_task(i);
		if(task_ptr != nullptr){
			print(*task_ptr);
		}else{
			cout<<"Erro no print. Posição nao encontrada\n";
		}

	}
}

int main(){

	Task t1{"Comer um x-caboquinho", 
		   "20/03/2026 7:00"};
	Task t2{"Ir para a academia", 
		   "20/03/2026 9:00"};
	Task t3{"Comer lasanha",
		   "20/03/2026 12:00"};

	ToDoList minha_todolist{10};

	minha_todolist.insert(t1);
	minha_todolist.insert(t2);
	minha_todolist.insert(t3);
	print(minha_todolist);



	return 0;

	/*Task t{"Comer x salada", "18/03/20206 20:00"};
	print(t);

	t.markAsDone();
	print(t);

	t.markAsNotDone();
	print(t);*/
}