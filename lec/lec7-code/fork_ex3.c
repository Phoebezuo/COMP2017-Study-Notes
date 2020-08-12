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
		foo(owner, 0);
		foo(owner, 1);
		foo(owner, 1);
		foo(owner, 0);
    	printf("%s done\n", owner);
	} else {
		printf("I am the parent: %d\n", getpid());
		foo(owner, 0);
		foo(owner, 0);
		foo(owner, 0);
		foo(owner, 1);
		foo(owner, 1);
		foo(owner, 1);
		foo(owner, 1);
		foo(owner, 1);
    	printf("%s done\n", owner);
	}

	return 0; // terminate program
}
