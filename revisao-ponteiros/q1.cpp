/*Escreva uma função que imprime os elementos de um vetor de float a partir de um endereço inicial (ponteiro) até um endereço final;
 - A função recebe como parâmetros dois ponteiros para float (os endereços inicial e final) e deve utilizar notação de ponteiros não de vetores;
- Deve ser criada uma função main() para testar a função implementada com três vetores de tamanhos e conteúdos diferentes;
- A função main deve imprimir duas partes distintas de cada um dos três vetores, utilizando a função criada.*/

#include<iostream>

using namespace std; //namespace -> seria como um projeto em java 

const int TAM = 5;

void printArray(float *primeiro, float *ultimo);

int main(){
    float v1 [TAM] = {5.9, 7.8, 2.1, 345.89, 45.90};
    float v2 [7] = {4.58, 3.45, 2.87, 90.93, 70.35, 81.20, 65.87};
    float v3 [3] = {67.90, 82.37, 54.55};

    printArray (&v1[0], &v1[4]);
    printArray(&v2[0], &v2[4]);
    printArray(&v3[0], &v3[4]);

    return 0;
}

void printArray(float *primeiro, float *ultimo){
    cout << "-----------------------APRESENTANDO O VETOR:-----------------------" << "\n";
    //percorre o vetor atraves do endereço
    for(; primeiro<=ultimo; primeiro++){
        cout << *primeiro << "\n"; // com * -> acessa o valor no endereço; sem * -> imprime o endereço

    }
}

