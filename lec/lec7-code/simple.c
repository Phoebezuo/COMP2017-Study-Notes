#include <stdio.h>

void special_function() {
    printf("%s executed!\n", __FUNCTION__);
}

int main() {
    printf("foreign program here\n");
    special_function();
    
	return 0;
}
