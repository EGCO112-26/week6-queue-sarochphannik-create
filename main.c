#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

#define MAX_MENU 10

typedef struct {
    char name[50];
    int price;
} MenuItem;

MenuItem menu[MAX_MENU];
int menu_count = 0;

void displayMenu(){
    printf("\n====== MENU ======\n");
    for(int i = 0; i < menu_count; i++){
        printf("%d. %s - %d Bath\n", i+1, menu[i].name, menu[i].price);
    }
    printf("==================\n");
}

int findMenuPrice(const char* name){
    for(int i = 0; i < menu_count; i++){
        if(strcmp(menu[i].name, name) == 0){
            return menu[i].price;
        }
    }
    return -1;
}

void interactiveMode(Queue* q){
    int choice, order_num = 1;
    char menu_name[50];
    int cash;
    
    while(1){
        printf("\n1. Add Order\n2. Process Order (Dequeue)\n3. Show Queue\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        if(choice == 1){
            displayMenu();
            printf("Enter menu name: ");
            fgets(menu_name, sizeof(menu_name), stdin);
            menu_name[strcspn(menu_name, "\n")] = 0;
            
            int price = findMenuPrice(menu_name);
            if(price > 0){
                enqueue(q, order_num, menu_name, price);
                printf("My order is %d\n", order_num);
                order_num++;
            }
            else{
                printf("Menu not found!\n");
            }
        }
        else if(choice == 2){
            if(q->size > 0){
                order current = dequeue(q);
                printf("My order is %d\n", current.price);
                printf("Customer no: %d\n", current.order_number);
                printf("%s\n", current.menu);
                printf("You have to pay %d\n", current.price);
                printf(":Cash:");
                scanf("%d", &cash);
                
                if(cash >= current.price){
                    int change = cash - current.price;
                    printf("Cash:%d\n", cash);
                    printf("Thank you\n");
                    printf("Change is:%d\n", change);
                }
                else{
                    printf("Not enough cash!\n");
                }
            }
            else{
                printf("Empty queue\n");
            }
        }
        else if(choice == 3){
            printf("\nQueue size: %d\n", q->size);
            if(q->size > 0){
                order* current = q->head;
                printf("Orders in queue:\n");
                int count = 1;
                while(current != NULL){
                    printf("%d. Order #%d - %s (%d Bath)\n", count, current->order_number, current->menu, current->price);
                    current = current->next;
                    count++;
                }
            }
        }
        else if(choice == 4){
            printf("\n====== CLOSING STORE ======\n");
            printf("There are %d ppl left in the queue\n", q->size);
            clearQueue(q);
            printf("Queue cleared\n");
            break;
        }
    }
}

void initMenu(){
    strcpy(menu[0].name, "Ramen");
    menu[0].price = 200;
    strcpy(menu[1].name, "Fried Chicken");
    menu[1].price = 100;
    strcpy(menu[2].name, "Pad Thai");
    menu[2].price = 150;
    strcpy(menu[3].name, "Tom Yum Soup");
    menu[3].price = 120;
    menu_count = 4;
}

int main(int argc, char **argv){
    Queue q = {NULL, NULL, 0};
    initMenu();
    
    // If arguments provided, process them
    if(argc > 1){
        int order_num = 1;
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "process") == 0 || strcmp(argv[i], "x") == 0){
                if(q.size > 0){
                    order current = dequeue(&q);
                    printf("My order is %d\n", current.price);
                    printf("Customer no: %d\n", current.order_number);
                    printf("%s\n", current.menu);
                    printf("You have to pay %d\n", current.price);
                    
                    // Take next argument as cash if exists
                    if(i + 1 < argc && atoi(argv[i+1]) > 0){
                        i++;
                        int cash = atoi(argv[i]);
                        printf(":Cash:%d\n", cash);
                        printf("Cash:%d\n", cash);
                        if(cash >= current.price){
                            int change = cash - current.price;
                            printf("Thank you\n");
                            printf("Change is:%d\n", change);
                        }
                    }
                }
                else{
                    printf("Empty queue\n");
                }
            }
            else{
                // Try to add as menu name
                int price = findMenuPrice(argv[i]);
                if(price > 0){
                    enqueue(&q, order_num, argv[i], price);
                    printf("My order is %d\n", order_num);
                    order_num++;
                }
            }
        }
        
        // Show remaining queue at end
        if(q.size > 0){
            printf("\nThere are %d ppl left in the queue\n", q.size);
            clearQueue(&q);
        }
    }
    else{
        // Interactive mode
        interactiveMode(&q);
    }
    
    return 0;
}
