#include <iostream>
#include <iomanip>
const int NIL=-1;

class ContaCorrente{
public:
	//atributos
	std:: string nome_cliente;
	int num_ag;
	int num_cc;
	float saldo;

	//construtores pra instanciar 
	ContaCorrente() = default;

	ContaCorrente(std:: string nome_cliente_, int num_ag_, int num_cc_, float saldo_){
		nome_cliente = nome_cliente_;
		num_ag = num_ag_;
		num_cc = num_cc_;
		saldo = saldo_;
	}

	//metodos
	void print();
	void deposita (float valor_deposito);
	float saque (float valor_saque);
};

void ContaCorrente::print(){
	std::cout<<"\nNome: "<<nome_cliente;
	std::cout<<"\nAg: "<<num_ag;
	std::cout<<"\nConta: "<<num_cc;
	std::cout<<"\nSaldo: R$"<< std::fixed << std::setprecision(2) << saldo<<"\n";
}

void ContaCorrente::deposita(float valor_deposito){
	if(valor_deposito>0.0f){
		saldo = saldo + valor_deposito;	
	}
	
}

float ContaCorrente::saque(float valor_saque){
	if(saldo - valor_saque >= 0.0f){
		saldo = saldo - valor_saque;
		return valor_saque;	
	}else{
		return NIL;
	}
	
}

void transferencia (ContaCorrente& cc_origem, ContaCorrente& cc_destino, float valor_transf){
	float valor_sacado = cc_origem.saque(valor_transf);
	if (valor_sacado==NIL){
		std::cout<<"\nTransferencia invalida. Saldo insuficiente!\n";
	}else{
		cc_destino.deposita(valor_sacado);
		std::cout<<"\nTransferencia realizada com sucesso!\n";
	}	
}

int main(){
	ContaCorrente cc0 {"Bernardo Alencar", 9823, 556668332, 100.00};
	ContaCorrente cc1 {"Gabriela Silva", 1234, 000000001, 50000.00};

	cc0.print();
	cc1.print();

	std::cout<<"\n---------------DEPOSITO---------------";
	cc0.deposita(5000.00f);
	cc0.print();

	std::cout<<"\n---------------SAQUE---------------";
	if(cc0.saque(2000.0f)==-1){
		std::cout<<"\nSaque invalido. Saldo insuficiente!\n";
	}else{
		cc0.print();
	}

	std::cout<<"\n---------------TRANSFERENCIA---------------";
	float valor_transf = 0.25f;
	transferencia(cc1, cc0, valor_transf);
	cc0.print();
	cc1.print();

	return 0;
	
}