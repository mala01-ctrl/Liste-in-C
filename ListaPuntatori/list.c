//Malavolti Lorenzo 1° anno tecnico scientifico
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
typedef unsigned short int Boolean;

struct List {
	int value;
	struct List* next_ptr;
};

/*Prototipo della funzione di inizializzazione della lista*/
void init(struct List** list);

/*Prototipo della funzione di inserimento in testa alla lista di un valore intero*/
Boolean pre_insert(struct List** list, int value);

/*Prototipo della funzione di stampa della lista*/
void visit(struct List* list);

/*Prototipo della funzione di cancellazione di un elemento in testa alla lista*/
Boolean pre_delete(struct List** list, int* value);

/*Prototipo della funzione di inserimento in coda alla lista*/
Boolean suf_insert(struct List** list, int value);

/*Prototipo della funzione di cancellazione in coda alla lista di un elemento*/
Boolean suf_delete(struct List** list, int* value);

/*Protoipo della funzione di ricerca di un valore nella lista*/
Boolean search(struct List* list, int target);

int main() {
	struct List* list;
	//test della funzione init()
	init(&list);

	//Test della funzione pre_insert()
	if (!pre_insert(&list, 5))
		printf("Errore di allocazione della memoria!\n");
	if (!pre_insert(&list, 4))
		printf("Errore di allocazione della memoria!\n");
	if (!pre_insert(&list, 3))
		printf("Errore di allocazione della memoria!\n");
	
	//Test della funzione visit()
	visit(list);

	//Test della funzione pre_delete()
	int deletedItem;
	if (pre_delete(&list, &deletedItem))
		printf("Elemento eliminato in testa: %d\n", deletedItem);
	visit(list);

	//Test della funzione suf_insert()
	if (!suf_insert(&list, 7))
		printf("Errore di allocazione della memoria\n");
	if (!suf_insert(&list, 8))
		printf("Errore di allocazione della memoria\n");
	visit(list);

	//Test della funzione suf_delete()
	if (suf_delete(&list, &deletedItem))
		printf("Elemento eliminato: %d\n", deletedItem);
	visit(list);

	//Test della funzione search()
    printf("Ricerca del valore 7\n");
	if (search(list, 7))
		printf("Elemento trovato nella lista!\n");
	visit(list);
    system("pause");
	return 0;
}

/**
* Funzione di inizializzazione della lista. Inizializza la lista 
* a NULL.
* @param list doppio puntatore contenente l'indirizzo del puntatore dichiarato nel
* main che dichiara la lista
*/
void init(struct List** list)
{
	*list = NULL;
}

/**
* Funzione che inserisce un elemento in testa alla lista. Tra i parametri formali 
* della funzione vengono passati il doppio puntatore all'indirizzo della lista dichiarata 
* nel main, e il valore da inserire nella lista.
* @param list doppio puntatore contenente l'indirizzo del puntatore dichiarato nel
* main che dichiara la lista
* @param value valore da inserire in testa alla lista
* @return TRUE se l'elemento è stato inserito, altrimenti FALSE.
*/
Boolean pre_insert(struct List** list, int value)
{
	struct List* tmp = (struct List*)malloc(sizeof(struct List));
	if (tmp == NULL)
		return FALSE;
	tmp->value = value;
	tmp->next_ptr = *list;
	*list = tmp;
	return TRUE;
}

/**
* Funzione che stampa tutti i valori della lista.
* @param list puntatore all'indirizzo della lista dichiarata nel main
*/
void visit(struct List* list)
{
	while (list != NULL) {
		printf("%d ", list->value);
		list = list->next_ptr;
	}
	printf("\n");
}

/**
* Funzione che elimina un elemento in testa alla lista. Tra i parametri formali 
* della funzione vengono passati in ingresso il doppio puntatore contenente l'indirizzo
* della lista, e un puntatore alla variabile che rappresenta il dato eliminato.
* @param list list doppio puntatore contenente l'indirizzo del puntatore dichiarato nel
* main che dichiara la lista
* @param value puntatore all'indirizzo della variabile dichiarata nella funzione main()
* @return TRUE se l'elemento è stato eliminato, altrimenti FALSE
*/
Boolean pre_delete(struct List** list, int* value)
{
	if (*list == NULL)
		return FALSE;
	struct List* tmp = *list;
	*list = (*list)->next_ptr;
	*value = tmp->value;
	free(tmp);
	return TRUE;
}

/**
* Funzione che inserisce un valore in coda alla lista. Prende in ingresso 
* il doppio puntatore alla lista dichiarata nel main e il valore da inserire in 
* coda alla lista.
* @param list list doppio puntatore contenente l'indirizzo del puntatore dichiarato nel
* main che dichiara la lista
* @param value valore da inserire in coda alla lista
* @return TRUE se l'elemento è stato inserito, altrimenti FALSE
*/
Boolean suf_insert(struct List** list, int value)
{
	struct List** head_ptr = list;
	while ((*list)->next_ptr != NULL)
		list = &((*list)->next_ptr);
	struct List* tmp = (struct List*)malloc(sizeof(struct List));
	if (tmp == NULL)
		return FALSE;
	tmp->value = value;
	tmp->next_ptr = NULL;
	(*list)->next_ptr = tmp;
	return TRUE;
}

/**
* Funzione che elimina un elemento in coda alla lista. Riceve in ingresso
* tra i parametri formali il doppio puntatore alla lista e il puntatore all'elemnto
* che verrà eliminato.
* @param list list doppio puntatore contenente l'indirizzo del puntatore dichiarato nel
* main che dichiara la lista
* @param value puntatore al valore eliminato della lista
* @return TRUE se l'elemento è stato eliminato, altrimenti FALSE
*/
Boolean suf_delete(struct List** list, int* value)
{
	if (*list == NULL)
		return FALSE;
	while ((*list)->next_ptr != NULL)
		list = &((*list)->next_ptr);
	pre_delete(list, value);
	return TRUE;
}

/**
* Funzione che ricerca un elemento della lista. Riceve in ingresso
* il puntatore alla lista e il valore da ricercare.
* @param list puntatore alla lista dichiarata nella funzione main()
* @param target valore da ricercare nella lista
* @return TRUE se l'elemento è stato eliminato, altrimenti FALSE
*/
Boolean search(struct List* list, int target)
{
	if (list == NULL)
		return FALSE;
	while (list != NULL) {
		if (list->value == target)
			return TRUE;
		else
			list = list->next_ptr;
	}
	return FALSE;
}
