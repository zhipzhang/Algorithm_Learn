#include <stdlib.h>
#include <string.h>

#include "chtbl.h"



int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *), int (*match)(const void *, const void *), void (*destroy)(void *))
{
    int  i;
    if((htbl->table = (List*)malloc(buckets * sizeof(List))) == NULL)
    {
        return -1;
    }
    htbl->buckets = buckets;
    for(i = 0; i < buckets; i++)
    {
        list_init(&htbl->table[i], destroy);
    }
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;
    return 0;
}

void chtbl_destroy(CHTbl *htbl)
{
    int i;
    for(int i = 0; i < htbl->size; i++)
    {
        list_destroy(&htbl->table[i]);
    }
    free(htbl->table);
    return;
}

int chtbl_insert(CHTbl* htbl, const void* data)
{
    void *temp;
    int  bucket, retval;
    temp = (void*) data;
    if( chtbl_lookup(htbl, &temp) == 0)
    {
        return 1;
    }

    bucket = htbl->h(data) % htbl->buckets;
    if((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
    {
        htbl->size++;
    }
    return retval;
}

int chtbl_remove(CHTbl *htbl, void **data)
{
    ListElmt   *element, *prev;
    int bucket;

    prev = NULL;                                    // 作为哨兵的作用，使其可以很好的对于list_head也同样成立 
    bucket = htbl->h(data) % htbl->buckets;
    for(element = list_head(&htbl->table[bucket]); element!= NULL; element = list_next(element))
    {
        if(htbl->match(list_data(element), *data) == 0)
        {
            if(list_rem_next(&htbl->table[bucket], prev, data) == 0)
            {
                htbl->size --;
                return 0;
            }
            else {
                return -1;
            }

        }
        prev = element;
    }
    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data)
{
    ListElmt* elem;
    int bucket;

    bucket = htbl->h(*data) % htbl->buckets;
    for( elem = list_head(&htbl->table[bucket]); elem != NULL; elem = list_next(elem))
    {
        if( htbl->match(list_data(elem), *data))
        {
            *data = list_data(elem);
            return 0;
        }
    }
    return -1;
}