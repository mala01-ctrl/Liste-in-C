/*Malavolti Lorenzo */
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef unsigned short int Boolean; //definizione di un nuovo tipo

/*Rappresentazione record della lista*/
struct Record
{
    int value; //Valore di un record
    int next;  //Prossima posizione libera
};

/*Rappresentazione della lista collegata con array ed indici*/
struct List
{
    struct Record *buffer; //Array di record
    int size;              //dimensione della lista
    int first;             //Primo elemento della lista
    int free;              //Prossimo elemento libero
};

/*Prototipo della funzione di inizializzazione della lista.*/
Boolean init(struct List *list, int size);

/*Prototipo della funzione di stampa dei valori contenuti nella lista*/
void visit(struct List *list);

/*Prototipo della funzione di inserimento in testa alla lista*/
Boolean pre_insert(struct List *list, int value);

/*Prototipo della funzione di cancellazione di un elemento in testa alla lista*/
Boolean pre_delete(struct List *list, int *value);

/*Prototipo della funzione di ricerca di un elemento della lista*/
Boolean search(struct List *list, int target);

/*Prototipo della funzione di inserimento in coda alla lista*/
Boolean suf_insert(struct List *list, int value);

/**
 * Funzione main principale del programma.
 * @return 0 se non ci sono errori nella funzione, altrimenti 1
 */
int main()
{
    struct List list;
    const int size = 5;
    const char errorMessage[] = {'E', 'r', 'r', 'o', 'r', 'e', '\0'};

    /*Test della inizializzazione della lista*/
    if (!init(&list, size))
    {
        printf("Errore di allocazione della memoria!\n");
        return 1;
    }

    /*Test della funzione pre_insert()*/
    if (!pre_insert(&list, 7))
        printf("%s\n", errorMessage);
    if (!pre_insert(&list, 6))
        printf("%s\n", errorMessage);
    if (!pre_insert(&list, 5))
        printf("%s\n", errorMessage);

    /*Test della funzione pre_delete()*/
    int deleteElement;
    if (!pre_delete(&list, &deleteElement))
        printf("%s\n", errorMessage);

    /*Test della funzione search()*/
    if (search(&list, 7))
        printf("Elemento trovato\n");
    else
        printf("Elemento inesistente o lista vuota!\n");

    /*Test della funzione suf_insert()*/
    if (!suf_insert(&list, 4))
        printf("%s\n", errorMessage);

    /*Test della funzione di stampa della lista*/
    visit(&list);

    free(list.buffer);
    return 0;
}

/**
 * Funzione che inizializza una nuova lista allocando memoria nel campo buffer. 
 * Imposta il primo elemento alla dimensione della lista.
 * @param list puntatore all'indirizzo della lista creata nella funzione main()
 * @param size dimensione della lista desiderata
 * @return TRUE se la lista è stata inizializzata, altrimenti FALSE (fallimento della malloc).
 */
Boolean init(struct List *list, int size)
{
    list->buffer = (struct Record *)malloc(sizeof(struct Record) * size);
    if (list->buffer == NULL)
        return FALSE;
    list->size = size;
    list->first = size;
    list->free = 0;
    for (int i = 0; i < size; i++)
        list->buffer[i].next = i + 1;
}

/**
 * Funzione che stampa i valori presenti nella lista.
 * @param list puntatore all'indirizzo della lista creata nella funzione main()
 */
void visit(struct List *list)
{
    if (list->size == list->first) //Lista vuota
        return;
    int pos = list->first;
    while (pos != list->size) //cicla i valori fino alla posizione dell'elemento libero
    {
        printf("%d ", list->buffer[pos].value);
        pos = list->buffer[pos].next; //prossimo elemento della lista
    }
}

/**
 * Funzione che inserisce un elemento in testa alla lista. Al primo inserimento 
 * l'attributo first assumerà il valore di size, mentre free assumera valore 1.
 * Successivamente first assumerà il valore di free memorizzato nella variabile 
 * temporanea moved, free invece assume sempre il valore del campo next di buffer.
 * L'algoritmo consiste quindi nell'assegnare l'indice dell'elemento successivo da inserire
 * e modificare il campo first quando si inserisce in testa.
 * @param list puntatore contenente l'indirizzo della lista del main
 * @param value valore da inserire in testa alla lista 
 * @return TRUE se il valore è stato inserito, altrimenti FALSE (list piena).
 */
Boolean pre_insert(struct List *list, int value)
{
    if (list->size == list->free) //lista piena
        return FALSE;
    int moved = list->free;
    list->free = list->buffer[list->free].next;
    list->buffer[moved].value = value;
    list->buffer[moved].next = list->first;
    list->first = moved;
    return TRUE;
}

/**
 * Funzione di cancellazione in testa di un elemento della lista. L'algoritmo,
 * tramite gli indici first e free scollega l'elemento in testa dalla lista. 
 * L'indice first assumerà il valore del elemento successivo da eliminare, mentre free 
 * prende il valore di first.
 * @param list puntatore all'indirizzo della lista del main
 * @param value puntatore all'indirizzo dell'elemento eliminato dall lista
 * @return TRUE se l'elemento è stato eliminato, altrimenti FALSE (lista vuota).
 */
Boolean pre_delete(struct List *list, int *value)
{
    if (list->size == list->first) //Lista vuota
        return FALSE;
    *value = list->buffer[list->first].value;
    int moved = list->first;
    list->first = list->buffer[list->first].next;
    list->buffer[moved].next = list->free;
    list->free = moved;
    return TRUE;
}

/**
 * Funzione di ricerca di un'elemento della lista. La funzione scorre gli elementi
 * della lista tramite la variabile temporanea pos in modo tale da non perdere il
 * riferimento alla testa della lista.
 * @param list puntatore all'indirizzo della lista della funzione main
 * @param target elemento da ricercare all'interno della lista
 * @return TRUE se l'elemento è stato trovato, altrimenti false se la lista è vuota
 * o se l'elemento non è presente nella lista. 
 */
Boolean search(struct List *list, int target)
{
    if (list->size == list->first) //lista vuota
        return FALSE;
    int pos = list->first;
    while (pos != list->size)
    {
        if (list->buffer[pos].value == target)
            return TRUE;
        pos = list->buffer[pos].next;
    }
    return FALSE;
}

/**
 * Funzione che inserisce in coda un nuovo elemento nella lista. Utilizza un 
 * puntatore, il quale si riferisce all'attributo next o first. L'elemento in coda 
 * assume come valore di next il valore di size per indicare che il prossimo elemento 
 * non esiste.
 * @param list puntatore all'indirizzo della lista nella funzione main()
 * @param value elemento da inserire in coda della lista
 * @return TRUE se l'elemento è stato inserito, altrimenti FALSE (lista piena).
 */
Boolean suf_insert(struct List *list, int value)
{
    if (list->size == list->free) //lista piena
        return FALSE;
    int moved = list->free;                //copia dell'indice degli elementi liberi
    list->free = list->buffer[moved].next; //aggiornamento degli indici liberi a quello successivo

    int *position_ptr = &list->first;   //puntatore all'indice dell'elemento in testa alla lista
    while (*position_ptr != list->size) //scorrimento degli elementi fino alla coda.+
        position_ptr = &(list->buffer[*position_ptr].next);
    *position_ptr = moved;                 //Aggiornamento del campo next della coda ad indice elementi liberi
    list->buffer[moved].value = value;     //Inserimento del nuovo elemento nella nuova coda
    list->buffer[moved].next = list->size; //aggiornamento del'indice next a size.
    return TRUE;
}
