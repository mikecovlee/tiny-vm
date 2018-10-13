#pragma once
#include <functional>
#include <stdexcept>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <utility>

namespace vm
{
    namespace types
    {
        using i32=std::int32_t;
        using i64=std::int64_t;
    }
    using byte_t=unsigned char;
    using size_t=unsigned long;
    class allocator_base
    {
    public:
        allocator_base()=default;
        virtual ~allocator_base()=default;
        virtual byte_t* malloc(size_t)=0;
        virtual void free(byte_t*)=0;
    };
    namespace allocator
    {
        template<typename T, typename...ArgsT>void construct(byte_t* ptr, ArgsT&&...args)
        {
            ::new (reinterpret_cast<T*>(ptr)) T(std::forward<ArgsT>(args)...);
        }
        template<typename T>void destroy(byte_t* ptr)
        {
            reinterpret_cast<T*>(ptr)->~T();
        }
    }
    class default_allocator final:public allocator_base
    {
    public:
        virtual byte_t* malloc(size_t size) override
        {
            return reinterpret_cast<byte_t*>(::malloc(size));
        }
        virtual void free(byte_t* ptr) override
        {
            ::free(reinterpret_cast<void*>(ptr));
        }
    };
    enum class error_status
    {
        ready, warning, error, fatal
    };
    class exception_handler_base
    {
        allocator_base* m_alloc=new default_allocator;
    public:
        exception_handler_base()=default;
        explicit exception_handler_base(allocator_base* alloc):m_alloc(alloc) {}
        virtual ~exception_handler_base(){delete m_alloc;}
        /*
        Description: Exception Listener Type
        Return: The status of listener, return true means finished
        Argument:
        1) Standard Exception Object
        2) Exception Level: -1=Fatal Error 0=Information 1-10=Warning 11-20=Error
        */
        using listener_t=std::function<bool(std::exception*, int)>;
        /*
        Description: Add an exception listener
        Return: none
        Argument: Listener Object
        */
        virtual void add_listener(const listener_t&)=0;
        /*
        Description: Raise an exception
        Return: None
        Argument:
        1) Standard Exception Object
        2) Exception Level: -1=Fatal Error 0=Information 1-10=Warning 11-20=Error
        3) Allocator: Pass nullptr to use default allocator
        */
        virtual void raise(std::exception* e, int level=0, allocator_base* alloc=nullptr)=0;
        /*
        Description: Check status
        Return: Exception Handler's Status
        Argument: None
        */
        virtual error_status check_status() const=0;
    };
    class stack final {
	public:
		using byte=uint8_t;
		using size_t=uint64_t;
	private:
		// Stack Start
		void *ss = nullptr;
		// Stack Pointer
		byte *sp = nullptr;
		// Stack Limit
		byte *sl = nullptr;
	public:
		stack() = delete;

		stack(const stack &) = delete;

		stack(size_t size) : ss(::malloc(size))
		{
			sp = reinterpret_cast<byte *>(ss) + size;
			sl = sp;
		}

		~stack()
		{
			::free(ss);
		}

		inline bool empty() const
		{
			return sp == sl;
		}

		void *top()
		{
			if (sp == sl)
				throw std::runtime_error("Stack is empty.");
			return reinterpret_cast<void *>(sp + sizeof(size_t));
		}

		void *push(size_t size)
		{
			if (sp - reinterpret_cast<byte *>(ss) < size + sizeof(size_t))
				throw std::runtime_error("Stack overflow.");
			sp -= size + sizeof(size_t);
			*reinterpret_cast<size_t *>(sp) = size;
			return reinterpret_cast<void *>(sp + sizeof(size_t));
		}

		void pop()
		{
			if (sp == sl)
				throw std::runtime_error("Stack is empty.");
			sp += *reinterpret_cast<size_t *>(sp) + sizeof(size_t);
		}

		size_t size_of(void *ptr)
		{
			return *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(ptr) - sizeof(size_t));
		}
	};
    class instance_base;
    class instruction_base;
    class instance_base
    {
        allocator_base* m_alloc=new default_allocator;
    public:
        instance_base()=default;
        explicit instance_base(allocator_base* alloc):m_alloc(alloc) {}
        virtual ~instance_base(){delete m_alloc;}
    };
    class instruction_base
    {
    public:
        instruction_base()=default;
        virtual ~instruction_base()=default;
        virtual size_t get_args_byte_count() const
        {
            return 0;
        }
        virtual void execute(byte_t*, instance_base*)=0;
    };
    class bytecode_interpreter final
    {

    };
}