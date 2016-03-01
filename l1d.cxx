#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>

const size_t memsize = 1024*1024*20;
const size_t n_accesses = 1024*1024*10;
const size_t bigprime = 982451653;

int main(int argc, char **argv) {
    typedef unsigned int TT;
    TT *random_memory = (TT *)malloc(sizeof(TT) * memsize);

    srand(2);
    for(size_t ii = 0; ii < memsize; ++ii)
        random_memory[ii] = rand() % (ii+1); // THIS TRICK LETS YOU AVOID %

    size_t first = 4;
    size_t stride = 1;
    size_t increment = 1000;
    size_t biggest = 1024*1024*10;
    int result = 0;
    for(size_t working_set_size = first;
        working_set_size < biggest;
        working_set_size *= 1.3) {
        assert(working_set_size < memsize);

        clock_t begin = clock();

        size_t  address = 0;
        for(size_t ii = 0; ii < n_accesses; ++ii) {
            address = working_set_size - random_memory[address];
            result += random_memory[address];
        }

        clock_t end = clock();

        printf("%lu %f %d\n", sizeof(TT)*working_set_size, (end-begin)*1.0/CLOCKS_PER_SEC, result);
        fflush(stdout);
    }

    free(random_memory);
    return 0;
}
