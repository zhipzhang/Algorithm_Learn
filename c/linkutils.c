#include "link_list/list.h"
#include <stdio.h>
#include <time.h>

void print_int(const void* data)
{
    printf("%d ", *(const int*)data);
}

void InverseList1(List* list)
{
    if(list_size(list) <= 1 )
    {
        return;
    }
    // 必须知道尾节点
    ListElmt* element = list_tail(list);
    void** data  = (void**)malloc(sizeof(void *));
    while(list_head(list) != element)
    {
        list_rem_next(list, NULL, data);
        list_ins_next(list, element, *data);
    }

}
void InverseList2(List* list)
{
    ListElmt* current = list_head(list);
    ListElmt* prev = NULL;
    ListElmt* next = NULL;
    printf("Before Inverse: \n");
    print_list(list, print_int);
    list->head = list->tail;
    list->tail = current;
    printf("After Inverse \n");
        while (current != NULL) {
        next = current->next; // 保存下一个节点
        current->next = prev; // 反转当前节点的指针
        prev = current; // 移动prev到当前节点
        current = next; // 移动current到下一个节点
    }
    print_list(list, print_int);
    return;
}

// 合并有序链表
List* Merge_Two_List(List* list1, List* list2, int (*compare)(const void* data1, const void* data2))
{
    printf("Before Merge: \n");
    print_list(list1, print_int);
    print_list(list2, print_int);
    List* ans = (List*) malloc(sizeof(List));
    list_init(ans, NULL);
    if(list_size(list1) == 0)
    {
        return list2;
    }
    if(list_size(list2) == 0)
    {
        return list1;
    }
    ListElmt* cur;
    ListElmt* l1_elem = list_head(list1);
    ListElmt* l2_elem = list_head(list2);
    while(l1_elem != NULL && l2_elem != NULL)
    {
        if(*(int*)list_data(l1_elem) < *(int*)list_data(l2_elem))
        {
            list_ins_next(ans, list_tail(ans), list_data(l1_elem));
            l1_elem = list_next(l1_elem);
        }
        else {
            list_ins_next(ans, list_tail(ans), list_data(l2_elem));
            l2_elem = list_next(l2_elem);
        }
    }
    while(l1_elem != NULL)
    {
        list_ins_next(ans, list_tail(ans), list_data(l1_elem));
    }
    while(l2_elem != NULL)
    {
        list_ins_next(ans, list_tail(ans), list_data(l2_elem));
        l2_elem = list_next(l2_elem);
    }
    printf("After merge !\n");
    print_list(ans, print_int);
    return ans;
}

int list_delete_finaln(List* list, int n)
{
    printf("Delteing %d last element\n", n);
    ListElmt* fast = list_head(list);
    ListElmt* slow = list_head(list);
    for(int i = 0; i < n ; i++)
    {
        fast = list_next(fast);
        if(fast == NULL)
        {
            printf("Failed delteing \n");
            return -1;
        }
    }
    while(fast->next != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    void** data = (void**)malloc(sizeof(void*));
    list_rem_next(list, slow, data);
    return 0;
}
int main(int argc, char** argv)
{
    clock_t start, end;
    double cpu_time_used;

    List* list1 = (List*) malloc(sizeof(List));
    List* list2 = (List*) malloc(sizeof(List));
    if(list1 == NULL)
    {
        return -1;
    }
    int *a = (int*) malloc(sizeof(int) * 10000);
    for(int i = 0; i < 15; i++)
    {
        a[i] = i;
    }
    list_init(list1, NULL);
    list_init(list2, NULL);
    for(int i = 0; i < 15; i++)
    {
        if(i%2)
            list_ins_next(list1, list1->tail, &a[i]);
        else
            list_ins_next(list2, list2->tail, &a[i]);
    }
    //start = clock();
    InverseList2(list1);
    InverseList2(list1);
    List* merge_list = Merge_Two_List(list1, list2);
    list_delete_finaln(merge_list, 2);
    print_list(merge_list, print_int);
    list_delete_finaln(merge_list, 100);
    print_list(merge_list, print_int);
}