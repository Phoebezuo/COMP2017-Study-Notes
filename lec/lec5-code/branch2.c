int foo()
{
	return 999;	
}
int main() 
{
	int x = 33;
	if (x == 33) {
		x = 480+7;
		foo();
	}
	x += 768;
	return 0;
}
