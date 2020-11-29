#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef unsigned short int Boolean;

struct List
{
    int *buffer; //Array dei valori della lista
    int head;    //testa
    int tail;    //coda
    int size;    //dimensione
};

/*Prototipo della funzione di inizializzazione della lista.*/
Boolean init(struct List *list, int size);

/*Prototipo della funzione di inserimento in testa*/
Boolean pre_insert(struct List *list, int value);

/*Prototipo della funzione di visita*/
void visit(struct List *list);

/*Prototipo della funzione di inserimento in coda*/
Boolean suff_insert(struct List *list, int value);

/*Prototipo della funzione di cancellazione in testa*/
Boolean pre_delete(struct List *list, int *value);

/*Prototipo della funzione di cancellazione in coda */
Boolean suff_delete(struct List *list, int *value);

/*Prototipo della funzione di ricerca*/
Boolean search_element(struct List *list, int value);

/*Prototipo della funzione di cancellazione di un elemento presente nella lista*/
Boolean delete_element(struct List *list, int value);

int main()
{
    struct List list;
    const int size = 9;
    const int value = 3;
    const char error[] = {'E', 'r', 'r', 'o', 'r', 'e', '!', '\0'};
    if (init(&list, size) == FALSE)
    {
        printf("Errore di allocazione della memoria!\n");
        return 1;
    }
    printf("Dimensione della lista: %d\n", list.size);

    /*Test dell'inseriemnto in testa*/
    if (!pre_insert(&list, value))
        printf("%s\n", error);
    if (!pre_insert(&list, 7))
        printf("%s\n", error);
    printf("Stampa dei valori della lista: \n");
    visit(&list);

    /*Test inserimento in coda*/
    if (!suff_insert(&list, 9))
        printf("%s\n", error);
    printf("Stampa dei valori della lista: \n");
    visit(&list);

    /*Test cancellazione in testa*/
    int deleteElement;
    if (!pre_delete(&list, &deleteElement))
        printf("%s\n", error);
    printf("Stampa dei valori della lista: \n");
    visit(&list);

    /*Test cancellazione in testa*/
    if (!pre_insert(&list, 7))
        printf("%s\n", error);
    if (!suff_delete(&list, &deleteElement))
        printf("%s\n", error);
    printf("Stampa dei valori della lista: \n");
    visit(&list);
    printf("Elemento eliminato: %d\n", deleteElement);

    /*Test ricerca di un elemento in testa*/
    if (search_element(&list, 7))
        printf("Elemeto trovato!\n");
    else
        printf("Elemento inesistente o lista vuota!\n");
    /*Test eliminazione di un elemento da ricercare */
    if (delete_element(&list, 3))
        printf("Elemento eliminato!\n");
    else
        printf("Elemento inesistente o lista vuota!\n");
    printf("Stampa dei valori della lista: \n");
    visit(&list);
    free(list.buffer);
    return 0;
}

/**
 * Funzione che inizializza una nuova lista. Alloca memoria all'attributo buffer della
 * list con la funzione malloc. Setta la dimensione della lista all'attributo size e 
 * imposta il valore 0 alla testa e alla coda della lista.
 * @param list puntatore all'indirizzo della lista della funzione main
 * @param size dimensione della lista da inizializzare
 * @return TRUE se la lista è stata inizializzata, altrimenti FALSE.
 */
Boolean init(struct List *list, int size)
{
    list->buffer = (int *)malloc(sizeof(int) * size);
    if (list->buffer == NULL)
        return FALSE;
    list->size = size;
    list->head = 0;
    list->tail = 0;
    return TRUE;
}

/**
 * Funzione che inserisce un nuovo elemento in testa alla lista.
 * @param list Puntatore di tipo struct List all'indirizzo della lista nel main.
 * @param value Valore da inserire nella lista 
 * @return TRUE se il valore è stato inserito, FALSE altrimenti (lista piena).
 */
Boolean pre_insert(struct List *list, int value)
{
    if (list->head == (list->tail + 1) % list->size) //lista piena
        return FALSE;
    list->head = (list->head - 1 + list->size) % list->size;
    list->buffer[list->head] = value;
    return TRUE;
}

/**
 * Funzione che stampa i valori presenti nella lista.
 * @param list lista di cui si vuole stampare i valori
 */
void visit(struct List *list)
{
    int pos = list->head; // variabile utilizzata per non modificare la testa della lista.
    while (pos != list->tail)
    {
        printf("%d ", list->buffer[pos]);
        pos = (pos + 1) % list->size;
    }
    printf("\n");
}

/**
 * Funzione che inserisce un valore in coda alla lista. 
 * @param list lista in cui si vuole inserire il valore 
 * @param value valore che si vuole inserire nella lista
 * @return TRUE se l'elemento è stato inserito, altrimenti FALSE (lista piena).
 */
Boolean suff_insert(struct List *list, int value)
{
    if (list->head == (list->tail + 1) % list->size) //lista piena
        return FALSE;
    list->buffer[list->tail] = value;
    list->tail = (list->tail + 1) % list->size;
    return TRUE;
}

/**
 * Funzione che elimina un elemento in testa alla lista.
 * @param list puntatore all'indirizzo della lista di cui si vuole eliminare l'elemento
 * @param value valore eliminato dalla lista
 * @return TRUE se l'elemento è stato eliminato, altrimenti FALSE (lista vuota)
 */
Boolean pre_delete(struct List *list, int *value)
{
    if (list->head == list->tail) //lista vuota
        return FALSE;
    *value = list->buffer[list->head];
    list->head = (list->head + 1) % list->size;
    return TRUE;
}

/**
 * Funzione che elimina un elemento in coda alla lista.
 * @param list puntatore all'indirizzo della lista di cui si vuole eliminare l'elemento
 * @param value valore eliminato dalla lista
 * @return TRUE se l'elemento è stato eliminato, altrimenti FALSE (lista vuota)
 */
Boolean suff_delete(struct List *list, int *value)
{
    if (list->head == list->tail) //lista vuota
        return FALSE;
    list->tail = (list->tail - 1 + list->size) % list->size;
    *value = list->buffer[list->tail];
    return TRUE;
}

/**
 * Funzione che ricerca un elemento all'interno della lista.
 * @param list puntatore all'indirizzo della lista di cui si vuole eliminare l'elemento
 * @param value valore da ricercare nella lista
 * @return TRUE se l'elemento è stato trovato, altrimenti FALSE.
 */
Boolean search_element(struct List *list, int value)
{
    if (list->head == list->tail) //lista vuota
        return FALSE;
    int pos = list->head;
    while (pos != list->tail)
    {
        if (list->buffer[pos] == value)
            return TRUE;
        pos = (pos + 1) % list->size;
    }
    return FALSE;
}

/**
 * Funzione che ricerca un elemento all'interno della lista e successivamente lo elimina
 * @param list puntatore all'indirizzo della lista di cui si vuole eliminare l'elemento
 * @param value valore da eliminare nella lista
 * @return TRUE se l'elemento è stato eliminato, altrimenti FALSE.
 */
Boolean delete_element(struct List *list, int value)
{
    if (list->head == list->tail) //lista vuota
        return FALSE;
    int pos = list->head;
    int count;
    while (pos != list->tail)
    {
        if (list->buffer[pos] == value)
            count = pos; //posizione dell'elemento da eliminare
        pos = (pos + 1) % list->size;
    }
    if (pos >= 0 && pos < 9)
    {
        for (count = pos; count < list->tail; count = (count + 1) % list->size)
            list->buffer[count] = list->buffer[(count + 1) % list->size];
        list->tail = (list->tail - 1 + list->size) % list->size;
        return TRUE;
    }
    return FALSE;
}
