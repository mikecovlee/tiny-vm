#pragma once
#include <vm/core.hpp>
#include <cstdlib>

namespace vm {
	class allocator_base {
	public:
		allocator_base()=default;
		virtual ~allocator_base()=default;
		virtual byte_t* malloc(size_t)=0;
		virtual void free(byte_t*)=0;
	};
	class default_allocator final:public allocator_base {
	public:
		virtual byte_t* malloc(size_t size) override
		{
			return reinterpret_cast<byte_t*>(::malloc(size));
		}
		virtual void free(byte_t* ptr) override
		{
			::free(reinterpret_cast<void*>(ptr));
		}
	} default_alloc;
	class memory_handler {
	protected:
		allocator_base* m_alloc=&default_alloc;
	public:
		memory_handler()=default;
		explicit memory_handler(allocator_base* alloc):m_alloc(alloc) {}
		virtual ~memory_handler()=default;
		template<typename T, typename...ArgsT>static void construct(byte_t* ptr, ArgsT&&...args)
		{
			::new (reinterpret_cast<T*>(ptr)) T(std::forward<ArgsT>(args)...);
		}
		template<typename T>static void destroy(byte_t* ptr)
		{
			reinterpret_cast<T*>(ptr)->~T();
		}
		template<typename T, typename...ArgsT>static T* alloc_new(allocator_base* alloc, ArgsT&&...args)
		{
			byte_t* ptr=alloc->malloc(sizeof(T));
			::new (reinterpret_cast<T*>(ptr)) T(std::forward<ArgsT>(args)...);
			return reinterpret_cast<T*>(ptr);
		}
		template<typename T>static void alloc_delete(allocator_base* alloc, T* ptr)
		{
			reinterpret_cast<T*>(ptr)->~T();
			alloc->free(reinterpret_cast<byte_t*>(ptr));
		}
	};
	template<typename T, typename...ArgsT>T* vm_new(ArgsT&&...args)
	{
		return memory_handler::alloc_new(&default_alloc, std::forward<ArgsT>(args)...);
	}
	template<typename T>void vm_delete(T* ptr)
	{
		memory_handler::alloc_delete(&default_alloc, ptr);
	}
}