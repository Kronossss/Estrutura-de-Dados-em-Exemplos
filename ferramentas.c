#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ferramentas.h"

/*
Implementa a busca numa lista linear de alocação sequencial
do tipo TAluno. Nesta função se trabalha com uma lista 
definida como um array de forma estática. 
Entrada:
- lista: Uma lista sequencial estática na forma de uma referência 
	um array de tipo tAluno. Nesta implementação se assume que a chave
    procurada foi copiada no final da lista;
- tam: Tamanho da lista, ou seja os índices dos elementos da lista
	vão de 0 até tam-1. A chave procurada deve ter sido copiada para
    o elemento de índice tam, que não pertence à lista; 
- chave: Número de matrícula do aluno que está sendo procurado. 
	Para evitar ambiguidades, supõe-se que todas as chaves são
	distintas;
saída:
- A função retorna o índice da lista que possui a chave procurada.
	Caso a chave não pertença a nenhum dos elementos da lista a 
	função retorna tam;
*/

int buscaLisAluno(TAluno lista[], int tam, int chave)
{
	int i = 0;
	while (lista[i].numMatricula != chave){
		i++;
	}
	return i;
}

int buscaLisAlunoOrd(TAluno lista[], int tam, int chave)
{	
	int min = 0, max = tam, i;
	while (min != max)	{
		i = (max + min) / 2;
		if (lista[i].numMatricula < chave)
			min = ++i;
		else
			if (lista[i].numMatricula > chave)
				max = i;
			else			
				return i;
	}
	return i;
}

/*
Implementa a inclusão numa lista linear de alocação sequencial
do tipo TAluno. Nesta função se trabalha com uma lista 
definida como um array de forma estática. Os elementos da lista
não podem repetir o mesmo atributi chave. 
Entrada:
- aluno: Variável de tipo TAluno com as informações do elemnto
    que se deseja incluir na lista;
- lista: Uma lista sequencial estática na forma de uma referência 
	um array de tipo tAluno. O array permite aloca um elementro a 
    mais do que a capacidade da lista para permitir um algorítmo de
    busca mais eficiente; 
- tam: Tamanho da lista, ou seja os índices dos elementos da lista
	vão de 0 até tam-1; 
saída:
- A função retorna o verdadeiro caso o aluno seja incluído na lista
    e falso caso contrário. Nesta implementação o aluno não sera 
    incluído na lista se já tiver um elemento na lista com o mesmo
    atributo chave
*/
int incLisAluno(TAluno aluno, TListAlunos lista[], int *tam)
{   
    lista->lista[lista->tam].numMatricula = aluno.numMatricula;
	if (buscaAluno(lista,aluno.numMatricula) == *tam){
        strcpy(lista->lista[lista->tam].nome, aluno.nome);
	    strcpy(lista->lista[lista->tam].email, aluno.email);
        *tam += 1;
        return TRUE;
	}
    return FALSE;
}

void trocaAluno(TAluno *alunoA, TAluno *alunoB){
	TAluno troca;
	troca.numMatricula = alunoA->numMatricula;
	strcpy(troca.nome, alunoA->nome);
	strcpy(troca.email, alunoA->email);

	alunoA->numMatricula = alunoB->numMatricula;
	strcpy(alunoA->nome, alunoB->nome);
	strcpy(alunoA->email, alunoB->email);

	alunoB->numMatricula = troca.numMatricula;
	strcpy(alunoB->nome, troca.nome);
	strcpy(alunoB->email, troca.email);
}

int incLisAlunoOrd(TAluno aluno, TListAlunos lista[], int *tam)
{   
	int pos = buscaAluno(lista,aluno.numMatricula);
	if(lista->lista[pos].numMatricula != aluno.numMatricula){
		for(int i = *tam; i > pos; i--){
			lista->lista[i].numMatricula = lista->lista[i-1].numMatricula;
			strcpy(lista->lista[i].nome,lista->lista[i-1].nome);
			strcpy(lista->lista[i].email,lista->lista[i-1].email);
		}
		lista->lista[pos].numMatricula = aluno.numMatricula;
		strcpy(lista->lista[pos].nome,aluno.nome);
		strcpy(lista->lista[pos].email,aluno.email);
        *tam += 1;
        return TRUE;
	}
    return FALSE;
}

int remLisAluno(TAluno aluno, TListAlunos lista[], int *tam){
    int pos = 0;
    lista->lista[lista->tam].numMatricula = aluno.numMatricula;
	if ((pos = buscaAluno(lista,aluno.numMatricula)) != *tam){
        for(int i=pos-1;i<*tam-1;i++){
            lista->lista[i].numMatricula = lista->lista[i+1].numMatricula;
            strcpy(lista->lista[i].nome, lista->lista[i+1].nome);
	        strcpy(lista->lista[i].email, lista->lista[i+1].email);
        }
        *tam -= 1;
        return TRUE;
	}
    return FALSE;
}

int remLisAlunoOrd(TAluno aluno, TListAlunos lista[], int *tam){
	int pos = buscaAluno(lista,aluno.numMatricula);
	if(lista->lista[pos].numMatricula == aluno.numMatricula){
	    *tam -= 1;
		for(int i =pos; i < *tam; i++){
			lista->lista[i].numMatricula=lista->lista[i+1].numMatricula;
			strcpy(lista->lista[i].nome,lista->lista[i+1].nome);
			strcpy(lista->lista[i].email,lista->lista[i+1].email);
		}
        return TRUE;
	}
    return FALSE;
}

void printLisAluno(TAluno lista[], int tam)
{
	printf("[ \n ");
	for (int i = 0; i < tam; i++)
	{
		printf("%d, ", lista[i].numMatricula);
		printf("%s, ", lista[i].nome);
		printf("%s;\n ", lista[i].email);
	}
	printf(" ]\n");
}

void iniListAlunos(TListAlunos *list, int cap, int eOrd){
	if (eOrd)
		list->lista = (TAluno *)malloc((cap) * sizeof(TAluno));
	else
		list->lista = (TAluno *)malloc((cap + 1) * sizeof(TAluno));
	list->cap = cap;
	list->tam = 0;
	list->eOrd = eOrd;
}

int buscaAluno(TListAlunos *lista, int chave){
	if (lista->eOrd == TRUE)
		return buscaLisAlunoOrd(lista->lista, lista->tam, chave);
	else{
		lista->lista[lista->tam].numMatricula = chave;
		return buscaLisAluno(lista->lista, lista->tam, chave);
	}
}

int incAluno(TAluno aluno, TListAlunos *lista){
	if(lista->eOrd == TRUE)
		if(incLisAlunoOrd(aluno,lista,&lista->tam) == TRUE)
			return TRUE;
		else	
			return FALSE;
	else{
		lista->lista[lista->tam].numMatricula = lista->lista[lista->tam].numMatricula;
		if(incLisAluno(aluno,lista,&lista->tam)==TRUE)
			return TRUE;
		else	
			return FALSE;
	}
}

int remAluno(TAluno aluno, TListAlunos *lista){
		if(lista->eOrd == TRUE)
		if(remLisAlunoOrd(aluno,lista,&lista->tam) == TRUE)
			return TRUE;
		else	
			return FALSE;
	else{
		lista->lista[lista->tam].numMatricula = lista->lista[lista->tam].numMatricula;
		if(remLisAluno(aluno,lista,&lista->tam)==TRUE)
			return TRUE;
		else	
			return FALSE;
	}
}