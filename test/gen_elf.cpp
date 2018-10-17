#include <cstdio>
int main(int argc, char** argv)
{
    /*
        push_i32 12
        push_i32 24
        add_i32
        int 1
        push_i32 48
        sub_i32
        int 1
        eof
    */
    unsigned char buffer[]{2,12,0,0,0,2,24,0,0,0,4,8,1,2,48,0,0,0,6,8,1,255};
    FILE* f=fopen(argv[1], "w+");
    for(unsigned long i=0;i<sizeof(buffer);++i)
        fprintf(f, "%c", buffer[i]);
    fclose(f);
    return 0;
}