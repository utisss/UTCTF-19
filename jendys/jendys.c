#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPTIONS 5
unsigned long id;
char *options[] = {"Four for Four", "Nuggies", "Frosty", "Peppercorn Mushroom Melt", "Dave's Single"};

struct item {
    char item_name[24];
    struct item *next;
};

struct order {
    struct item *first;
    struct item *last;
    char *name;
    int num_items;
};

void print_menu() {
    printf("Welcome to Jendy's, How may we take your order?\n");
    printf("1. Add Name to Order\n");
    printf("2. Add Item to Order\n");
    printf("3. Remove Item from Order\n");
    printf("4. View order\n");
    printf("5. Checkout\n");
    printf(">");
}

void add_name(struct order *order) {
    printf("What is your name?\n");
    order->name = malloc(32);
    fgets(order->name, 32, stdin);
}

void add_item(struct order* order) {
    printf("Which item would you like to order from Jendy's?\n");
    for(int i = 0; i < NUM_OPTIONS; ++i) {
        printf("%d. %s\n", i, options[i]);
    }
    int choice;
    scanf("%d%*c", &choice);
    if(choice < 0 || choice >= NUM_OPTIONS) {
        printf("Not a valid option!\n");
        return;
    }
    struct item *item = malloc(sizeof(struct item));
    strncpy(item->item_name, options[choice], strlen(options[choice]));
    struct item *iter = order->first;
    ++order->num_items;
    if(iter == NULL) {
        order->first = item;
        order->last = item;
        return;
    }
    order->last->next = item;
    order->last = item;
}

void remove_item(struct order *order) {
    printf("Please enter the number of the item from your order that you wish to remove\n");
    int index;
    scanf("%d%*c", &index);
    if(index < 0) return;
    struct item *iter = order->first;
    struct item *prev = NULL;
    if(index == 0 && iter != NULL && index == 0) {
        free(iter);
        order->first = NULL;
        order->last = NULL;
        --order->num_items;
        return;
    }


    int curr = 0;
    while(iter != NULL && curr != index) {
        prev = iter;
        iter = iter->next; 
        ++curr;
    }

    if(iter != NULL && curr == index) {
        if(index == order->num_items - 1) {
            free(order->last);
            order->last = prev;
        } else {
            prev->next = iter->next;
            free(iter);
        }
        --order->num_items;
    }
}

void view_order(struct order *order) {
    if(order->name != NULL) {
        char buff[40];
        snprintf(buff, 40, "Name: %s\n", order->name);
        printf("%s", buff);
    }
    struct item *iter = order->first;
    for(int i = 0; i < order->num_items; ++i) {
        printf("Item #%d: ", i);
        printf(iter->item_name);
        printf("\n");
        iter = iter->next;
    }
}

void checkout() {
    printf("Thank you for for ordering at Jendy's!\n");
}

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    struct order *order = malloc(sizeof(struct order));
    while(1) {
        print_menu();
        int choice;
        scanf("%d%*c", &choice);
        switch(choice) {
            case 1:
                add_name(order);
                break;
            case 2:
                add_item(order);
                break;
            case 3:
                remove_item(order);
                break;
            case 4:
                view_order(order);
                break;
            case 5:
                checkout(order);
                return 0;
            default:
                printf("Not a valid choice!\n");
        }
    }

}
