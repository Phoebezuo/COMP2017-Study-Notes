#include <stdio.h>
#include <string.h>
#define NAME_LENGTH (100)
#define MAN_NUM (10)

int main() {
    int i = 0;
    char first_names[MAN_NUM][NAME_LENGTH];
    char last_names[MAN_NUM][NAME_LENGTH];
    int runs[MAN_NUM];
    int count = 1; 
    while (i < MAN_NUM) {
        printf("Enter Name and Score for batter %d: ", i + 1);
        count = (scanf("%s %s %d", first_names[i], last_names[i], &runs[i]) == 3);
        i = i + count ;
    }
    for (int i = 0; i < MAN_NUM; i++) {
        if (runs[i] == 0) {
            printf("%c. %s: Duck\n", first_names[i][0], last_names[i]);
        } else {
            printf("%c. %s: %d\n", first_names[i][0], last_names[i], runs[i]);
        }
    }
    return 0;
}
