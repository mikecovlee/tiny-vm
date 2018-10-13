#pragma once
#include <cstdlib>
#include <cstdint>

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