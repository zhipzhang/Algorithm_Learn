#include "dlist.h"
#include "stdio.h"



void dlist_init(DList *list, void (*destroy)(void **))
{
    list->size = 0;
    list->head = 0;
    list->tail = 0;
    list->destroy = destroy;
}

void dlist_destroy(DList *list)
{
    void ** data;
    while(dlist_remove(list, dlist_head(list), data) == 0)
    {
        if(list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    return;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    DListElmt* old_element;
    if(dlist_size(list) == 0) 
    {
        return -1;
    }
    if(element == NULL)
    {
        return -1;
    }
    else {
        old_element = element;
        *data = old_element->data;
        if(dlist_is_head(element))
        {
            list->head = element->next;
            list->head->prev = NULL;
            if(dlist_size(list) == 1)
            {
                list->tail = NULL;
            }
        }
        else if( dlist_is_tail(element))
        {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        else {
            element->prev->next = element->next;
            element->next->prev = element->prev;
        }
    }
    free(old_element);
    list->size --;
    return 0;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt* new_element;
    if(element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }
    new_element = (DListElmt*) malloc(sizeof(DListElmt));
    if(new_element == NULL)
    {
        return -1;
    }
    new_element->data = (void* )data;
    if(dlist_size(list) == 0)
    {
        list->head = list->tail = new_element;
        new_element->prev  = new_element->next = NULL;
    }
    else{
        if(element->next == NULL)
        {
            element->next = new_element;
            new_element->prev = element;
            new_element->next = NULL;
            list->tail = new_element;
        }
        else {
            element->next->prev = new_element;
            new_element->next = element->next;
            element->next = new_element;   
            new_element->prev = element;
        }
    }
    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt* new_element;
    if(element == NULL && dlist_size(list) != 0)
    {
        return -1;
    }
    new_element = (DListElmt*) malloc(sizeof(DListElmt));
    if(new_element == NULL)
    {
        return -1;
    }
    new_element->data = (void*) data;
    if(dlist_size(list) == 0)
    {
        list->head = list->tail = new_element;
        new_element->next = new_element->prev = NULL;
    }
    else {
        if(dlist_is_head(element))
        {
            list->head = new_element;
            list->head->next = element;
            list->head->prev = NULL;

            element->prev = new_element;
        }
        else {
            element->prev->next = new_element;
            new_element->prev = element->prev;
            new_element->next = element;
            element->prev = new_element;
        }
    }
    list->size++;
    return 0;
}

void print_dlist(DList *list, void (*print)(const void *))
{
    void* data;
    DListElmt * elem;
    for(elem = list->head; elem != NULL; elem = elem->next)
    {
        data = elem->data;
        print(data);
        if(!dlist_is_tail(elem))
            printf("<->");
        else
            printf("\n");

    }
}