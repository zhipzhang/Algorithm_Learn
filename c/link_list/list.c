#include "list.h"
#include "stdio.h"


// 使用函数指针来初始化destroy函数
void list_init(List *list, void (*destroy)(void *))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    return;
}
void list_destroy(List *list)
{
    void *data;
    while(list_size(list) > 0)
    {
        if(list_rem_next(list, NULL, (void **)&data) && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;
    if((new_element = (ListElmt*) malloc(sizeof(ListElmt))) == NULL)
    {
        return -1;
    }
    new_element->data = (void*)data;
    if(element == NULL)
    {
        if(list_size(list) == 0)
        {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    }
    else {
        if(element->next == NULL) // element is the tail element
        {
            list->tail = new_element;
        }
            new_element->next = element->next;
            element->next = new_element;
    }
    list->size++;
    return 0;
}


int list_rem_next(List *list, ListElmt *element, void **data)
{
    if(list_size(list) == 0)
    {
        return -1;
    }
    ListElmt *old_element;
    if(element == NULL)
    {
        *data = list->head->data; 
        old_element = list->head;
        list->head = list->head->next;
        if(list_size(list) == 1)
        {
            list->tail = NULL;
        }
    }
    else {
        if(element->next == NULL)
        {
            return -1;
        }
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;
        if(element->next == NULL)
        {
            list->tail = element;
        }

    }
    free(old_element);
    list->size--;
    return 0;
}

void print_list(List *list, void (*print)(const void* data))
{
    void* data;
    ListElmt * elem;
    for(elem = list->head; elem != NULL; elem = elem->next)
    {
        data = elem->data;
        print(data);
        if(!list_is_tail(elem))
            printf("->");
        else
            printf("\n");
    }
}