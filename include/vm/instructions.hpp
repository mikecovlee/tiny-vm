#pragma once
#include <vm/vm.hpp>

namespace vm {
	class push_i32 final:public instruction_base {
	public:
		virtual void vm_obj_destroy() const override
		{
			this->~push_i32();
		}
		virtual size_t get_args_byte_count() const
		{
			return 4;
		}
		virtual void execute(byte_t* data, instance_t* inst)
		{
			inst->push(data, 4);
		}
	};

	class add_i32 final:public instruction_base {
	public:
		virtual void vm_obj_destroy() const override
		{
			this->~add_i32();
		}
		virtual size_t get_args_byte_count() const
		{
			return 0;
		}
		virtual void execute(byte_t*, instance_t* inst)
		{
			std::int32_t* a=reinterpret_cast<std::int32_t*>(inst->top());
			inst->pop();
			std::int32_t* b=reinterpret_cast<std::int32_t*>(inst->top());
			inst->pop();
			*a=*b+*a;
			inst->push(reinterpret_cast<byte_t*>(a), 4);
		}
	};

	class sub_i32 final:public instruction_base {
	public:
		virtual void vm_obj_destroy() const override
		{
			this->~sub_i32();
		}
		virtual size_t get_args_byte_count() const
		{
			return 0;
		}
		virtual void execute(byte_t*, instance_t* inst)
		{
			std::int32_t* a=reinterpret_cast<std::int32_t*>(inst->top());
			inst->pop();
			std::int32_t* b=reinterpret_cast<std::int32_t*>(inst->top());
			inst->pop();
			*a=*b-*a;
			inst->push(reinterpret_cast<byte_t*>(a), 4);
		}
	};

	class interrupt final:public instruction_base {
	public:
		virtual void vm_obj_destroy() const override
		{
			this->~interrupt();
		}
		virtual size_t get_args_byte_count() const
		{
			return 1;
		}
		virtual void execute(byte_t* data, instance_t* inst)
		{
			switch(*data) {
			case 1:
				::printf("%d\n", *reinterpret_cast<std::int32_t*>(inst->top()));
				break;
			}
		}
	};
}