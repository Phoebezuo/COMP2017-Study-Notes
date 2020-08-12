#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_LEN (100)

struct customer {
    char name[ARR_LEN];
    int age;
    char thing[ARR_LEN];
};

int main() {
    puts("Welcome to ShopaMocha,");
    puts("Could you please tell me your name, age and what you looking for?");

    struct customer customer_list[ARR_LEN];
    int count = 0;
    char buffer[ARR_LEN];

    while (scanf("%s", buffer) != EOF) {
        strcpy(customer_list[count].name, buffer);
        scanf("%d", &customer_list[count].age);
        scanf("%s", customer_list[count].thing);
        printf("Hrmm, I think you should talk to a ShopaMocha assistant to find \"%s\" Have a good day!\n", customer_list[count].thing);

        count++;

        puts("Welcome to ShopaMocha,");
        puts("Could you please tell me your name, age and what you looking for?");
    }

    for (int i = 0; i < count; i++) {
        printf("Customer: %d, Name: %s, Age: %d, Looking for: %s\n", i, customer_list[i].name, customer_list[i].age, customer_list[i].thing);
    }

    return 0;
}
