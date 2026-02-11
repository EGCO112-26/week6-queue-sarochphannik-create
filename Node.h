//
//  linkedlist.h
//  LinkedList_simple
//
//  Created by Mingmanas Sivaraksa on 5/2/2566 BE.
//
#ifndef Node_h
#define Node_h
#include <string.h>

typedef struct node{
    struct node* next;
    int order_number;
    int price;
    char menu[50];
}order;

typedef struct{
    order *head, *tail;
    int size;
}Queue;

typedef order* OrderPtr;

void enqueue(Queue* q, int order_num, const char* menu_item, int price){
    OrderPtr new_order = (OrderPtr) malloc(sizeof(order));
    if(new_order){
        new_order->order_number = order_num;
        new_order->price = price;
        strcpy(new_order->menu, menu_item);
        new_order->next = NULL;
        
        if(q->size == 0){
            q->head = new_order;
        }
        else{
            q->tail->next = new_order;
        }
        q->tail = new_order;
        q->size++;
    }
}

order dequeue(Queue* q){
    order empty_order = {NULL, 0, 0, ""};
    
    if(q->size > 0){
        OrderPtr temp = q->head;
        order result = *temp;
        q->head = temp->next;
        q->size--;
        if(q->size == 0) q->tail = NULL;
        free(temp);
        return result;
    }
    return empty_order;
}

void clearQueue(Queue* q){
    while(q->size > 0){
        dequeue(q);
    }
}

#endif
