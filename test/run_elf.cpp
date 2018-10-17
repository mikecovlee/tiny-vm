#include <vm/instructions.hpp>
vm::instruction_set tisc;
int main(int argc, char** argv)
{
	tisc
	.add_instruction(2, vm::instruction_builder(vm::type_container<vm::push_i32>()))
	.add_instruction(4, vm::instruction_builder(vm::type_container<vm::add_i32>()))
	.add_instruction(6, vm::instruction_builder(vm::type_container<vm::sub_i32>()))
	.add_instruction(8, vm::instruction_builder(vm::type_container<vm::interrupt>()));
	vm::instance_t instance(256);
	vm::bytecode_interpreter interpreter(&vm::default_alloc, &tisc, &instance);
	interpreter.assemble_bytecode(argv[1]);
	interpreter.interpret();
	return 0;
}