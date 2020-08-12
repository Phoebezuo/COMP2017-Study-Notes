#include <stdio.h>
#include <string.h>

int substring(const char* haystack, const char* needle) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);

    int result = 0;
    int index;
    for(int i = 0; i <= (haystack_len - needle_len); i++){
       int match = 1;
       for(int j = 0; j < needle_len; j++){
           if(haystack[i + j] != needle[j]){
               match = 0; // 0 i ndicate false
           } else {
               index = i;
           }
       }
       if(match == 1){ // 1 indicate true
           return index;
       }
    }
    return -1;
}

int main() {
    printf("%d\n", substring("racecar", "car")); //4
    printf("%d\n", substring("telephone", "one")); //6
    printf("%d\n", substring("monkey", "cat")); //-1

    return 0;
}
