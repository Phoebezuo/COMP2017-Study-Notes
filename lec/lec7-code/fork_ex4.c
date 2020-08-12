void foo(char *str, char increment) {
    static int x = 0;
   
    if (increment) {
        x++;
        printf("%s incrementing x: %d\n", str, x);
    }
    else {
        printf("%s reporting x: %d\n", str, x);
    }
}

int main() {
    foo("prefork", 1);
    foo("prefork", 1);
    foo("prefork", 0);
    
	int result = fork();
	char *owner = "parent";
	if (result == 0){
		owner = "child";
		printf("I am the child: %d\n", getpid());
        int i = 0;
        while (i < 1000) { 
    		foo(owner, rand()%2); // 1 in 2 chance increment
            i++;
        }
	} else {
		printf("I am the parent: %d\n", getpid());
        int i = 0;
        while (i < 1000) { 
    		foo(owner, rand()%100==0); // 1 in 100 chance increment
            i++;
        }
	}

    usleep(1000);
    foo(owner, 0);
   	printf("%s done\n", owner);
    
	return 0; // terminate program
}
