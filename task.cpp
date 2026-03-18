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
	ToDoList()=default;
	ToDoList(int max_length_):max_length(max_length_){
		itens = new Task[max_length];
		length=0;
	}
	

	//destrutor pra matar minha listinha procrastinada
	~ToDoList(int max_length_):max_length(max_length_){
		delete[] itens;
		itens = nullptr;
	}
	Task get_task(int pos);
	void insert(Task t);
	int get_length();
};

//metodos da ToDoList
Task* ToDoList::get_task(int pos){
	if(pos>=0 && pos>max_length){
		return itens[pos];
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

int get_length(){
	return length;
}





//metodos globais
void print(Task t){
		std::cout << t.get_description() << "\n";
		std::cout << t.get_datetime()<< "\n";
		if(t.isDone()){
			cout<<"Tarefa realizada\n";
		}else{
			cout<<"Tarefa nao realizada\n";
		}
	}


void print (ToDoList l){
	for (int i=0; i<l.get_length(); i++){
		Task* task_ptr = l.get_task(i);
		if(task_ptr != nullptr){
			print(*task_ptr);
		}else{
			cout<<"Erro no print. Posição nao encontrada";
		}

	}
}

int main(){

	ToDoList minhaLista{10};

	Task t1{"Comer x salada", "18/03/20206 20:00"};
	Task t2{"Nadar no mar da tristeza", "20/03/20206 07:00"};



	return 0;

	/*Task t{"Comer x salada", "18/03/20206 20:00"};
	print(t);

	t.markAsDone();
	print(t);

	t.markAsNotDone();
	print(t);*/
}