#include "chtbl.h"
#include <string.h>
#include <stdio.h>

typedef struct StringIntMap{
    char* key;
    int value;
} StringIntMap;

int string_hash(const void *key) {
    const char *ptr = ((const StringIntMap*)key)->key;
    unsigned int val = 0;

    while (*ptr != '\0') {
        unsigned int tmp;
        val = (val << 4) + (*ptr);

        if (tmp = (val & 0xf0000000)) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val;
}

int string_match(const void *key1, const void *key2) {
    return strcmp(((const StringIntMap *)key1)->key, ((const StringIntMap *)key2)->key) == 0;
}

void destroy_map(void *data) {
    free(((StringIntMap *)data)->key);
    free(data);
}

int main(int argc, char** argv)
{
    CHTbl htbl;
    int buckets = 10;
    if((chtbl_init(&htbl, buckets, string_hash, string_match, destroy_map)) != 0 )
    {
        printf("init error");
    }

    StringIntMap* data = (StringIntMap*)malloc(sizeof(StringIntMap));
    data->key = strdup("hello");
    data->value = 100;
    chtbl_insert(&htbl, data);
    printf("The size of chtbl %d \n", chtbl_size(&htbl));

    StringIntMap* data2 = (StringIntMap*)malloc(sizeof(StringIntMap));
    data2->key = strdup("hello");

    chtbl_lookup(&htbl, (void**)&data2);
    printf("The value of helllo is %d \n", data2->value);
}