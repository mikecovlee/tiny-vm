#include <cstdio>
int main(int argc, char** argv)
{
	/*
	TISC ASM:
	    push_i32 10
	    push_i32 20
	    add_i32
		loop: jmp_if $exit
	    int 1
	    push_i32 1
	    sub_i32
	    jmp $loop
		exit: int 1
	    eof
	C Code:
		int a=10;
		a=a+20;
		while(a>0)
		{
			printf("%d\n", a);
			a=a-1;
		}
		printf("%d\n", a);
	*/
	unsigned char buffer[] {
		5,10,0,0,0,
		5,20,0,0,0,
		7,
		3,8,0,0,0,0,0,0,0,
		1,1,
		5,1,0,0,0,
		9,
		2,3,0,0,0,0,0,0,0,
		1,1,
		255
	};
	FILE* f=fopen(argv[1], "w+");
	for(unsigned long i=0; i<sizeof(buffer); ++i)
		fprintf(f, "%c", buffer[i]);
	fclose(f);
	return 0;
}