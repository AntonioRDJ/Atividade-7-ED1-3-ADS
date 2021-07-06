#include <iostream>
#include <locale.h>
using namespace std;
#define MAX 99999999

struct No {
	float dado;
	struct No *prox;
};

struct Fila
{
	No *ini;
	No *fim;
};

Fila* init()
{
	Fila *f = new Fila;
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

int isEmpty(Fila *f) {
	return (f->ini == NULL);
}

void enqueue(Fila *f, float v) {
	No *no = new No;
	no->dado = v;
	no->prox = NULL;
	if (isEmpty(f)) {
		f->ini = no;
	}
	else {
		f->fim->prox = no;
	}
	f->fim = no;
}

float dequeue(Fila *f) {
	float ret;
	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		No *no = f->ini;
		ret = no->dado;
		f->ini = no->prox;
		if (f->ini == NULL) {
			f->fim = NULL;
		}
		free(no);
	}
	return ret;
}

int count(Fila *f) {
	int qtde = 0;
	No *no;
	no = f->ini;
	while (no != NULL) {
		qtde++;
		no = no->prox;
	}
	return qtde;
}

void freeFila(Fila *f) {
	No *no = f->ini;
	while (no != NULL) {
		No *temp = no->prox;
		free(no);
		no = temp;
	}
	free(f);
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	bool sair = false;
	int cont = 0;
	int option = 0;

	Fila *senhasGeradas = new Fila();
	senhasGeradas = init();
	
	Fila *senhasAtendidas = new Fila();
	senhasAtendidas = init();

	while(!sair) {	
		cout << "0. Sair." << endl;
		cout << "1. Gerar senha." << endl;
		cout << "2. Realizar atendimento." << endl;
		cin >> option;
	
		switch(option)
		{
			case 0:
				if(isEmpty(senhasGeradas)) {
					sair = true;
					freeFila(senhasGeradas);
					freeFila(senhasAtendidas);
				} else{
					cout << "Não é possível encerrar pois a fila não está vazia." << endl;
				} 
				break;
			case 1:
				cont++;
				enqueue(senhasGeradas, cont);
				cout << "Senha Registrada com sucesso!." << endl;
				cout << endl;
				break;
			case 2:
				if(isEmpty(senhasGeradas)) {
					cout << "Fila vazia" << endl;
				} else {
					cout << "Senha Número: " << (senhasGeradas->ini->dado) << " atendida com sucesso!." << endl;
					cout << endl;
					enqueue(senhasAtendidas, senhasGeradas->ini->dado);
					dequeue(senhasGeradas);
					cout << "Quantidade de senhas aguardando atendimento: " << count(senhasGeradas) << endl;
				}
				break;
			default:
				cout << "Digite uma opção valida." << endl;
				break;
		}
	}
	
	return 0;
}

/*
Implementar um sistema simples de atendimento com a oferta de 3 opções através de um seletor:

0. Sair
1. Gerar senha
2. Realizar atendimento
A opção 1 deverá incrementar o controle de senhas, gerando e enfileirando a senha gerada na fila "senhasGeradas"

A opção 2 deverá consumir a senha "da vez", exibindo-a na tela e enfileirando-a na fila "senhasAtendidas".

Sempre que o seletor for exibido, informar a quantidade de senhas ainda aguardando atendimento.

O programa só poderá ser encerrado quando a fila "senhasGeradas" estiver vazia. Ao encerrar, informar a quantidade de senhas atendidas.
*/
