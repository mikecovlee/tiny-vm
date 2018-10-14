#pragma once
#include <vm/allocator.hpp>
#include <functional>
#include <stdexcept>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <utility>

namespace vm {
	class instance_base:public memory_handler {
	public:
		using memory_handler::memory_handler;
	};
	class instruction_base {
	public:
		instruction_base()=default;
		virtual ~instruction_base()=default;
		virtual size_t get_args_byte_count() const
		{
			return 0;
		}
		virtual void execute(byte_t*, instance_base*)=0;
	};
	class bytecode_interpreter final {

	};
}