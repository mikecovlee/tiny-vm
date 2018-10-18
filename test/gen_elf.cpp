#include <cstdio>
void write_int(unsigned char* buff, int v)
{
	*reinterpret_cast<int*>(buff)=v;
}
int main(int argc, char** argv)
{
	/*
	TISC ASM:
	    push_i32 10000
	    push_i32 100
	    mul_i32
		loop: jmp_if $exit
	    push_i32 1
	    sub_i32
	    jmp $loop
	    exit: eof
	C Code:
		int a=100;
		a=a*100;
		while(a>0)
			a=a-1;
	*/
	unsigned char buffer[] {
		0x5,0,0,0,0,
		0x5,0,0,0,0,
		0xb,
		0x1,1,
		0x3,8,0,0,0,0,0,0,0,
		0x5,1,0,0,0,
		0x9,
		0x2,4,0,0,0,0,0,0,0,
		255
	};
	write_int(buffer+1, 10000);
	write_int(buffer+6, 100);
	FILE* f=fopen(argv[1], "w+");
	for(unsigned long i=0; i<sizeof(buffer); ++i)
		fprintf(f, "%c", buffer[i]);
	fclose(f);
	return 0;
}