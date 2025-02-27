#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for getopt()

#define BYTES_PER_WORD 4
// #define DEBUG

/*
 * Cache structures
 */
int time = 0;

typedef struct
{
    int age;
    int valid;
    int modified; //더티 됐다, 되지 않았다~
    uint32_t tag;
} cline;

typedef struct
{
    cline *lines;
} cset;

typedef struct
{
    int s; // index bits
    int E; // way
    int b; // block offset bits
    cset *sets;
} cache;

int index_bit(int n){
    int cnt = 0;

    while(n) {
        cnt++;
        n = n >> 1;
    }

    return cnt-1;
}

/***************************************************************/
/*                                                             */
/* Procedure : build_cache                                     */
/*                                                             */
/* Purpose   : Initialize cache structure                      */
/*                                                             */
/* Parameters:                                                 */
/*     int S: The set of cache                                 */
/*     int E: The associativity way of cache                   */
/*     int b: The blocksize of cache                           */
/*                                                             */
/***************************************************************/


cache build_cache(cache *cache2, int E, int S, int b)
{	// 인덱스 비트로 캐시 블록 개수 알 수 있다.
	//index = index_bit(b);
	cache2->s= index_bit(S);
	cache2->E = E;
	cache2->b = index_bit(b);
	

	cache2->sets = malloc(sizeof(cset)*(S));
	for (int i = 0; i < S; i++)
	{

		cache2->sets[i].lines = (cline*)malloc(sizeof(cline)*(E));
		
		
	}

	/* Implement this function */
}

/***************************************************************/
/*                                                             */
/* Procedure : access_cache                                    */
/*                                                             */
/* Purpose   : Update cache stat and content                   */
/*                                                             */
/* Parameters:                                                 */
/*     cache *L: An accessed cache                             */
/*     int op: Read/Write operation                            */
/*     uint32_t addr: The address of memory access             */
/*     int *hit: The number of cache hit                       */
/*     int *miss: The number of cache miss                     */
/*     int *wb: The number of write-back                       */
/*                                                             */
/***************************************************************/
void access_cache(cache *L, int op, uint32_t addr, int *way, int *set,int *index,int *tag, int *readhit,int *writehit,int *readmiss,int *writemiss, int *writeback)
{
	
	// total read , total write, wirte-back, read hit, write hit, read miss, write miss

		for (int i = 0; i < (*way); i++) {

			if (op == 1) {

				if (L->sets[*index].lines[i].valid == 0) {
					(*readmiss)++;
					L->sets[*index].lines[i].valid = 1;
					L->sets[*index].lines[i].modified = 0;
					L->sets[*index].lines[i].tag = (*tag);
					L->sets[*index].lines[i].age = 0;
					break;
				}
				else if (L->sets[*index].lines[i].valid == 1 && L->sets[*index].lines[i].tag == (*tag)) {
					(*readhit)++;
					L->sets[*index].lines[i].age = 0;
					break;
				}

				else if (i == ((*way) - 1)) {
					if (L->sets[*index].lines[i].valid == 1 && L->sets[*index].lines[i].tag != (*tag)) {
						(*readmiss)++;
						int old_age = 0;
						old_age = L->sets[*index].lines[0].age;
						int max = 0;
						for (int k = 0; k < (*way); k++) {
							if (L->sets[*index].lines[k].age > old_age) {
								old_age = L->sets[*index].lines[k].age;
								max = k;
							}
						}

						if (L->sets[*index].lines[max].modified == 1) {
							(*writeback)++;
						}
						L->sets[*index].lines[max].tag = (*tag);
						L->sets[*index].lines[max].age = 0;
						L->sets[*index].lines[max].modified = 0;



					}
					break;
				}

				

			}

			if (op == 0) {

				if (L->sets[*index].lines[i].valid == 0) {
					(*writemiss)++;
					L->sets[*index].lines[i].valid = 1;
					L->sets[*index].lines[i].tag = (*tag);
					L->sets[*index].lines[i].age = 0;
					L->sets[*index].lines[i].modified = 1;
					break;
				}
				else if (L->sets[*index].lines[i].valid == 1 && L->sets[*index].lines[i].tag == (*tag)) {
					(*writehit)++;
					L->sets[*index].lines[i].age = 0;
					L->sets[*index].lines[i].tag = (*tag);
					L->sets[*index].lines[i].modified = 1;
					break;
				}

				else if (i == (*way) - 1) {
					if (L->sets[*index].lines[i].valid == 1 && L->sets[*index].lines[i].tag != (*tag)) {
						(*writemiss)++;
						int old_age = 0;
						old_age = L->sets[*index].lines[0].age;
						int max = 0;
						for (int b = 0; b < (*way); b++) {
							if (L->sets[*index].lines[b].age > old_age) {
								old_age = L->sets[*index].lines[b].age;
								max = b;
							}
						}

						if (L->sets[*index].lines[max].modified == 1) {
							(*writeback)++;
						}
						L->sets[*index].lines[max].tag = (*tag);
						L->sets[*index].lines[max].modified = 1;
						L->sets[*index].lines[max].age = 0;


					}
					break;

				}
			}

			

		}
		for (int a = 0; a < (*set); a++)
		{
			for (int j = 0; j < (*way); j++)
			{
				if (L->sets[a].lines[j].valid == 1)
				{
					(L->sets[a].lines[j].age)++;
				}
			}
		}

	
	

	/* Implement this function */
}

/***************************************************************/
/*                                                             */
/* Procedure : cdump                                           */
/*                                                             */
/* Purpose   : Dump cache configuration                        */
/*                                                             */
/***************************************************************/
void cdump(int capacity, int assoc, int blocksize)
{

    printf("Cache Configuration:\n");
    printf("-------------------------------------\n");
    printf("Capacity: %dB\n", capacity);
    printf("Associativity: %dway\n", assoc);
    printf("Block Size: %dB\n", blocksize);
    printf("\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : sdump                                           */
/*                                                             */
/* Purpose   : Dump cache stat		                           */
/*                                                             */
/***************************************************************/
void sdump(int total_reads, int total_writes, int write_backs,
           int reads_hits, int write_hits, int reads_misses, int write_misses)
{
    printf("Cache Stat:\n");
    printf("-------------------------------------\n");
    printf("Total reads: %d\n", total_reads);
    printf("Total writes: %d\n", total_writes);
    printf("Write-backs: %d\n", write_backs);
    printf("Read hits: %d\n", reads_hits);
    printf("Write hits: %d\n", write_hits);
    printf("Read misses: %d\n", reads_misses);
    printf("Write misses: %d\n", write_misses);
    printf("\n");
}


/***************************************************************/
/*                                                             */
/* Procedure : xdump                                           */
/*                                                             */
/* Purpose   : Dump current cache state                        */
/*                                                             */
/* Cache Design                                                */
/*                                                             */
/*      cache[set][assoc][word per block]                      */
/*                                                             */
/*                                                             */
/*       ----------------------------------------              */
/*       I        I  way0  I  way1  I  way2  I                 */
/*       ----------------------------------------              */
/*       I        I  word0 I  word0 I  word0 I                 */
/*       I  set0  I  word1 I  word1 I  work1 I                 */
/*       I        I  word2 I  word2 I  word2 I                 */
/*       I        I  word3 I  word3 I  word3 I                 */
/*       ----------------------------------------              */
/*       I        I  word0 I  word0 I  word0 I                 */
/*       I  set1  I  word1 I  word1 I  work1 I                 */
/*       I        I  word2 I  word2 I  word2 I                 */
/*       I        I  word3 I  word3 I  word3 I                 */
/*       ----------------------------------------              */
/*                                                             */
/*                                                             */
/***************************************************************/
void xdump(cache* L)
{
    int i, j, k = 0;
    int b = L->b, s = L->s;
    int way = L->E, set = 1 << s;

    uint32_t line;

    printf("Cache Content:\n");
    printf("-------------------------------------\n");

    for(i = 0; i < way; i++) {
        if(i == 0) {
            printf("    ");
        }
        printf("      WAY[%d]", i);
    }
    printf("\n");

    for(i = 0; i < set; i++) {
        printf("SET[%d]:   ", i);

        for(j = 0; j < way; j++) {
            if(k != 0 && j == 0) {
                printf("          ");
            }
            if(L->sets[i].lines[j].valid) {
                line = L->sets[i].lines[j].tag << (s + b);
                line = line | (i << b);
            }
            else {
                line = 0;
            }
            printf("0x%08x  ", line);
        }
        printf("\n");
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
	int capacity = 1024;
	int way = 8;
	int blocksize = 8;
	int set;

	// Cache
	cache simCache;

	// Counts
	int read = 0, write = 0, writeback = 0;
	int readhit = 0, writehit = 0;
	int readmiss = 0, writemiss = 0;

	// Input option
	int opt = 0;
	char* token;
	int xflag = 0;

	// Parse file
	char *trace_name = (char*)malloc(32);
	FILE *fp;
	char line[16];
	char *op;
	uint32_t addr;

	/* You can define any variables that you want */

	trace_name = argv[argc - 1];
	if (argc < 3) {
		printf("Usage: %s -c cap:assoc:block_size [-x] input_trace \n", argv[0]);
		exit(1);
	}

	while ((opt = getopt(argc, argv, "c:x")) != -1) {
		switch (opt) {
		case 'c':
			token = strtok(optarg, ":");
			capacity = atoi(token);
			token = strtok(NULL, ":");
			way = atoi(token);
			token = strtok(NULL, ":");
			blocksize = atoi(token);
			break;

		case 'x':
			xflag = 1;
			break;

		default:
			printf("Usage: %s -c cap:assoc:block_size [-x] input_trace \n", argv[0]);
			exit(1);

		}
	}

	// Allocate
	set = capacity / way / blocksize;
	

	/* TODO: Define a cache based on the struct declaration */
	// simCache = build_cache();
	build_cache(&simCache, way,set,blocksize);
	// Simulate
	fp = fopen(trace_name, "r"); // read trace file
	if (fp == NULL) {
		printf("\nInvalid trace file: %s\n", trace_name);
		return 1;
	}

	cdump(capacity, way, blocksize);

	/* TODO: Build an access function to load and store data from the file */
	while (fgets(line, sizeof(line), fp) != NULL) {
		op = strtok(line, " ");
		addr = strtoull(strtok(NULL, ","), NULL, 16);

		int index_bit_ = 1;

		for (int i = 32-index_bit(blocksize)-index_bit(set); i < 32-index_bit(blocksize); i++) {
			index_bit_ = index_bit_ * 2;


		}
		index_bit_ = index_bit_ - 1;
		

		int hi_index = 0;

		hi_index = (addr >> index_bit(blocksize))&index_bit_;

		int tag_bit_ = 1;
		for (int j = 0; j < 32 - (index_bit(set) + index_bit(blocksize)); j++) {
			tag_bit_ = tag_bit_ * 2;
		}
		tag_bit_ = tag_bit_ - 1;
		
		int hi_tag = 0;
		hi_tag = (addr >> (index_bit(set) + index_bit(blocksize)))&tag_bit_;

		

		if (strcmp(op, "R")==0) {
			read++;
			access_cache(&simCache, 1, addr, &way, &set, &hi_index, &hi_tag, &readhit, &writehit, &readmiss, &writemiss, &writeback);
		}
		
		else if (strcmp(op, "W")==0) {
			write++;
			access_cache(&simCache, 0, addr, &way, &set, &hi_index, &hi_tag, &readhit, &writehit, &readmiss, &writemiss, &writeback);

		}

#ifdef DEBUG
		// You can use #define DEBUG above for seeing traces of the file.
		fprintf(stderr, "op: %s\n", op);
		fprintf(stderr, "addr: %x\n", addr);
#endif
		// ...
		// access_cache()
		// ...
	}

	// test example
	sdump(read, write, writeback, readhit, writehit, readmiss, writemiss);
	if (xflag) {
		xdump(&simCache);
	}

	return 0;

}