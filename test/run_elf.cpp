#include <vm/instructions.hpp>
vm::instruction_set tisc;
int main(int argc, char** argv)
{
	tisc
	.add_instruction(1, vm::instruction_builder(vm::type_container<vm::interrupt>()))
	.add_instruction(2, vm::instruction_builder(vm::type_container<vm::jump>()))
	.add_instruction(3, vm::instruction_builder(vm::type_container<vm::jump_if>()))
	.add_instruction(4, vm::instruction_builder(vm::type_container<vm::pop>()))
	.add_instruction(5, vm::instruction_builder(vm::type_container<vm::push_i32>()))
	.add_instruction(7, vm::instruction_builder(vm::type_container<vm::add_i32>()))
	.add_instruction(9, vm::instruction_builder(vm::type_container<vm::sub_i32>()));
	vm::instance_t instance(256);
	vm::bytecode_interpreter interpreter(&vm::default_alloc, &tisc, &instance);
	interpreter.assemble_bytecode(argv[1]);
	interpreter.interpret();
	return 0;
}