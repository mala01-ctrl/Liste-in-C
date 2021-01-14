//Malavolti Lorenzo 1° anno tecnico scientifico
#include<stdio.h>
#include<stdlib.h>

//definizione di un nuovo tipo 
#define TRUE 1
#define FALSE 0
typedef unsigned short int Boolean;

struct Record {
	int value;
	int next;
};

struct List {
	int size;
	int first;
	int free;
	struct Record* buffer;
};

//Prototipo della funzione di inizializzazione della lista
Boolean init(struct List* list, int size);

//Prototipo della funzione di inserimento in testa alla lista di un valore
Boolean pre_insert(struct List* list, int value);

//Prototipo della funzione di visita della lista
void visit(struct List* list);

//Prototipo della funzione di inserimento di un valore in coda alla lista
Boolean suf_insert(struct List* list, int value);

//Prototipo della funzione di eliminazione di un elemento in testa alla lista
Boolean pre_delete(struct List* list, int* value);

//Prototipo della funzione di eliminazione di un elemento in coda alla lista 
Boolean suf_delete(struct List* list, int* value);

//Prototipo della funzione di ricerca di un elemento all'interno della lista
Boolean search_value(struct List* list, int value);

int main() {
	struct List list;
	const int size = 10;
	if (!init(&list, size)) {
		printf("Errore nell'allocazione della memoria!\n");
		return 1;
	}
	//Test della funzione pre_insert()
	if (!pre_insert(&list, 5))
		printf("Lista piena!\n");
	if (!pre_insert(&list, 4))
		printf("Lista piena!\n");
	if (!pre_insert(&list, 3))
		printf("Lista piena!\n");

	//Test della funzione suf_insert()
	if (!suf_insert(&list, 7))
		printf("Lista piena!\n");
	if (!suf_insert(&list, 9))
		printf("Lista piena!\n");
	visit(&list);

	//Test della funzione pre_delete()
	int deletedItem;
	if (!pre_delete(&list, &deletedItem))
		printf("Lista vuota!\n");
	else
		printf("Elemento eliminato: %d\n", deletedItem);
	if (!pre_delete(&list, &deletedItem))
		printf("Lista vuota!\n");
	else
		printf("Elemento eliminato: %d\n", deletedItem);

	//Test della funzione suf_delete()
	if (!suf_delete(&list, &deletedItem))
		printf("Lista vuota!\n");
	else
		printf("Elemento eliminato: %d\n", deletedItem);
	if (!suf_delete(&list, &deletedItem))
		printf("Lista vuota!\n");
	else
		printf("Elemento eliminato: %d\n", deletedItem);
	if (!suf_insert(&list, 8))
		printf("Lista piena!\n");

	//Test della funzione search_value()
	if (search_value(&list, 8))
		printf("Elemento presente all'interno della lista!\n");
	visit(&list);
	free(list.buffer);
    system("pause");
	return 0;
}

/**
* Funzione di inizializzazione della lista collegata con array ed indici. Questa funzione 
* riceve in ingresso il puntatore all'indirizzo della lista dichiarata nella funzione main
* e la dimensione di cui vogliamo che sia la lista.
* @param list puntatore all'indirizzo della lista della funzione main
* @param size valore della dimensione della lista
* @return TRUE se la lista è stata inizializzata, altrimenti FALSE.
*/
Boolean init(struct List* list, int size)
{
	list->buffer = (struct Record*)malloc(sizeof(struct Record) * size);
	if (list->buffer == NULL)
		return FALSE;
	list->first = size;
	list->free = 0;
	list->size = size;
	for (int i = 0; i < list->size; i++)
		list->buffer[i].next = i + 1;
	return TRUE;
}

/**
* Funzione di inserimento di un valore in testa alla lista. La funzione riceve nei parametri formali
* il puntatore all'indirizzo della lista dichiarata nella funzione main, e il valore da inserire.
* @param list puntatore all'indirizzo della lista della funzione main
* @param value valore da inserire in testa alla lista
* @return TRUE se l'elemento è stato inserito, altrimenti FALSE.
*/
Boolean pre_insert(struct List* list, int value)
{
	if (list->free == list->size)  //lista piena
		return FALSE;
	int moved = list->free;
	list->free = list->buffer[moved].next; //aggiornamento attributo free
	list->buffer[moved].value = value;   //inserimento del valore
	list->buffer[moved].next = list->first;
	list->first = moved;   //aggiornamento attributo first
	return TRUE;
}

/**
* Funzione che stampa tutti gli elementi presenti nella lista. La funzione riceve tra 
* i parametri formali il puntatore all'indirizzo della lista per motivi di efficienza. 
* In quanto nello stack sarà copiato solamento il puntatore e non tutta la lista.
* @param list puntatore all'indirizzo della lista dichiarata nella funzione main
*/
void visit(struct List* list)
{
	int pos = list->first;
	while (pos != list->size) {
		printf("%d ", list->buffer[pos].value);
		pos = list->buffer[pos].next;
	}
	printf("\n");
}

/**
* Funzione che inserisce un valore in coda alla lista. Tra i parametri formali della 
* funzione viene passato il puntatore all'indirizzo della lista dichiarata nella funzione 
* main e il valore da inserire.
* @param list puntatore all'indirizzo della lista
* @param value valore da inserire in coda alla lista
* @return TRUE se l'elemento è stato inserito, altrimenti FALSE
*/
Boolean suf_insert(struct List* list, int value)
{
	if (list->free == list->size)  //lista piena
		return FALSE;
	int moved = list->free;
	list->free = list->buffer[moved].next;
	int* position = &(list->first);
	while (*position != list->size)
		position = &(list->buffer[*position].next);
	list->buffer[moved].value = value;
	list->buffer[moved].next = list->size;
	*position = moved;
	return TRUE;
}

/**
* Funzione che elimina un elemento presente in testa alla lista. Riceve in ingresso 
* il puntatore all'indirizzo della lista dichiarata nel main e un puntatore all'indirizzo 
* della variabile dichiarata nel main che rappresenta l'elemento eliminato.
* @param list puntatore all'indirizzo della lista 
* @param value puntatore all'indirizzo della variabile rappresentante l'elemento eliminato
* @return TRUE se l'elemento è stato eliminato, altrimenti FALSE
*/
Boolean pre_delete(struct List* list, int* value)
{
	if (list->first == list->size) //lista vuota
		return FALSE;
	int moved = list->first;
	*value = list->buffer[list->first].value;
	list->first = list->buffer[list->first].next;
	list->buffer[moved].next = list->free;
	list->free = moved;
	return TRUE;
}

/**
* Funzione che elimina un elemnto in coda alla lista. Restituisce tra i parametri formali 
* l'elemento eliminato e come valore di ritorno un valore booleano che indica se l'elemento è
* stato eliminato.
* @param list puntatore all'indirizzo della lista 
* @param value puntatore all'indirizzo della variabile dichiarata nella funzione main
* @return TRUE se l'elemento è stato eliminato, altrimenti FALSE.
*/
Boolean suf_delete(struct List* list, int* value)
{
	if (list->first == list->size) //lista vuota
		return FALSE;
	int* position = &(list->buffer[list->first].next);
	while (list->buffer[*position].next != list->size)
		position = &(list->buffer[*position].next);
	*value = list->buffer[*position].value;
	list->buffer[*position].next = list->free;
	list->free = *position;
	*position = list->size;
	return TRUE;
}

/**
* Funzione che ricerca un elemento all'interno della lista. Viene passato
* tra i parametri formali il puntatore all'indirizzo della lista per motivi 
* di efficienza tra i parametri copiati nello stack. Il valore di ritorno della
* funzione è booleano
* @param list puntatore all'indirizzo della lista
* @param value valore da ricercare all'interno della lista
* @return TRUE se l'elemento è stato trovato, altrimenti FALSE.
*/
Boolean search_value(struct List* list, int value)
{
	if (list->first == list->size)
		return FALSE;
	int pos = list->first;
	while (pos != list->size) {
		if (list->buffer[pos].value == value)
			return TRUE;
		else
			pos = list->buffer[pos].next;
	}
	return FALSE;
}
