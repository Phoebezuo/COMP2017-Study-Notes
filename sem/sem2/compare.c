#include <stdio.h>

// comapsre String to substring
int compare_string(char* haystack, char* needle){
    int haystack_len = 0;
    char* cur = haystack;
    while(*cur){
        haystack_len++;
        cur++;
    }

    int needle_len = 0;
    cur = needle;
    while(*cur){
        needle_len++;
        cur++;
    }

    // can not found it
    if(needle_len > haystack_len){
        return -1;
    }

    int result = 0;
    for(int i = 0; i <= (haystack_len - needle_len); i++){
        int match = 1;
        for(int j = 0; j < needle_len; j++){
            if(haystack[i + j] != needle[j]){
                match = 0; // 0 i ndicate false
            }
        }
        if(match == 1){ // 1 indicate true
            result = 1;
            break;
        }
    }
    return result;
}


int main(){
    printf("%s %s %d\n", "Woman", "man", compare_string("Woman", "man"));
    printf("%s %s %d\n", "Woman", "mannnnnn", compare_string("Woman", "mannnnnn"));
    printf("%s %s %d\n", "Woman", "mj", compare_string("Woman", "mj"));
    return 0;
}
