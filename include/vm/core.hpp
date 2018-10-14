#pragma once
#include <cstdint>

namespace vm {
	namespace types {
		using i32=int32_t;
		using i64=int64_t;
	}
	using byte_t=uint8_t;
	using size_t=uint32_t;
	class instance_base;
	class instruction_base;
}