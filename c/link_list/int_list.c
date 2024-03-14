#include "list.h"
#include <stdio.h>
#include "dlist.h"

void print_int(const void* data)
{
    printf("%d ", *(const int*)data);
}

int main(int argc, char** argv)
{
    List* list = (List*) malloc(sizeof(List));
    DList* dlist = (DList*) malloc(sizeof(DList));
    if(list == NULL)
    {
        return -1;
    }
    int a[] = {1, 2, 3, 4, 5, 6,7 ,8, 9, 10};
    list_init(list, NULL);
    dlist_init(dlist, NULL);
    for(int i = 0; i < 10; i++)
    {
        list_ins_next(list, list->tail, &a[i]);
        dlist_ins_next(dlist, dlist_tail(dlist), &a[i]);

    }
    print_list(list, print_int);
    print_dlist(dlist, print_int);
    void** data = (void**)malloc(sizeof(void*));
    list_rem_next(list, NULL, data);
    dlist_remove(dlist, dlist_head(dlist), data);

    printf("Delteting element : %d \n", *(int*)(*data));
    print_dlist(dlist, print_int);
    dlist_remove(dlist, dlist_tail(dlist), data);
    printf("Delteting element : %d \n", *(int*)(*data));
    print_dlist(dlist, print_int);


}