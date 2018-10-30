#include <vm/instructions.hpp>
#include <cstdio>
void write_int(vm::byte_t* buff, std::int32_t v)
{
	*reinterpret_cast<std::int32_t*>(buff)=v;
	vm::to_vm_endian(buff, sizeof(std::int32_t));
}
int main(int argc, char** argv)
{
	/*
	TISC ASM:
	    push_i32 10000
	    push_i32 1000
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
	vm::byte_t buffer[] {
		0x5,0,0,0,0,
		0x5,0,0,0,0,
		0xb,
		0x1,1,
		0x3,0,0,0,0,0,0,0,8,
		0x5,0,0,0,1,
		0x9,
		0x2,0,0,0,0,0,0,0,4,
		0x1,1,
		255
	};
	write_int(buffer+1, 10000);
	write_int(buffer+6, 1000);
	FILE* f=fopen(argv[1], "w+");
	for(vm::size_t i=0; i<sizeof(buffer); ++i)
		fprintf(f, "%c", buffer[i]);
	fclose(f);
	return 0;
}