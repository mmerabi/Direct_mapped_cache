#include <stdio.h>
#include <stdlib.h>

//Michael Merabi Project #2
//Cache Memory in C

	int mainmemsize = 0;
	int cachesize = 0;
	int blocksize = 0;
	int linesize = 0;
	int numblines = 0;
	FILE *test;
	int *mainmem;
	
struct node {
	int tag;
	int *block;
}*cache=NULL;

typedef struct node n;

void startup(){ //the starting display
    printf( "\nProgram Written by Michael Merabi2 \n");
    printf( "Prog 2 - Cache Simulation \n");
    printf( "Class Meeting Time: 8:00 - 9:15 \n\n\n");
    printf( "Main Menu - Main Memory to Cache Memory Mapping \n");
    printf( "----------------------------- \n");
    printf( "1) Enter Configuration Parameters \n");
    printf( "2) Read from cache \n");
    printf( "3) Write to cache \n");
    printf( "4) Exit  \n");
}


int poweroftwo(int base){//helper method to decide if a number is base 2
	while ((base % 2) == 0 &&base > 1){
		base /=2;
	}
	return base;
}


void collisionreplace(int linenum, int tagnum, int memoryaddress){
	int baseaddress = 0;
	baseaddress = ((memoryaddress / blocksize)*blocksize);

	cache[linenum].tag = tagnum;

	int i;
	for (i = 0; 1 < blocksize; i++){
		cache[linenum].block[i] = (mainmem[baseaddress]+ i);
	}
	return;
}

void config(){
	fscanf(test, "%d", &mainmemsize);
	printf("\n Enter main memory size (words): ""%d",mainmemsize);

	fscanf(test, "%d", &cachesize);
	printf("\n Enter cache size (words): ""%d",cachesize);
	
	fscanf(test, "%d", &blocksize);
	printf("\n Enter block size (words/block): ""%d",blocksize);


	//Error Checks happen here
	if(!(poweroftwo(mainmemsize)==1)){
		printf("\n Error: Main memory is not a power of two \n");
		return;
	}
	if(!(poweroftwo(cachesize)==1)){
		printf("\n Error: cachesize is not a power of two \n");
		return;
	}
	if(!(poweroftwo(blocksize)==1)){
		printf("\n Error: blocksize is not a power of two \n");
		return;
	}
	if (blocksize > cachesize){
		printf("\n Error: Block size is larger than cache size\n");
		return;
	}
	if (!(cachesize%blocksize == 0)){
		printf("\n Error: Cache size is not a multiple of the block size\n");
		return;
	}
	printf("\n ***Data Accepted");

	//Malloc for space of Main memory and init
	numblines = (cachesize / blocksize);
	mainmem=(int*)malloc(mainmemsize * sizeof(int));
	
	//for every instance of main memory it will be = to mainmemsize - 1
	int i;
	for(i = 0; i < mainmemsize; i++){
		mainmem[i] = mainmemsize - 1;
	}

	//Space allocation for Cache
	cache = (n*)malloc(numblines * sizeof(n));
	int j;
	for (j = 0; j < numblines; j++){
		cache[j].block = (int*)malloc(blocksize * sizeof(int));
	}

	//Setting all pointers in cache to null
	int k;
	for (k = 0; k < numblines; k++){
		for (i = 0; i < blocksize; i++){
			cache[k].block[i] = NULL;
		}
	}

	int m;
	for (m = 0; m < numblines; m++){
		cache[m].tag = NULL;
	}
}

//method to write a value to cache memory based on input
void writecache(){
	int i = 0;
	int value = 0;
	int address = 0;
	int addressbuffer = 0;
	int tagbuffer = 0;
	int line = 0;
	int wordbuffer = 0;

	fscanf(test, "%d", &address);
	printf("\n Enter Main memory address to write to: ""%d",address);
	if(address > (mainmemsize - 1)){
		printf("\nError: Address value is bigger than main memory size");
		return;
	}

	fscanf(test, "%d", &value);
	printf("\n Enter the Values: ""%d", value);
	mainmem[address] = value;

	
	tagbuffer = (address / cachesize); //tag buffer to check cache to see if memory is stored
	line = ((address%cachesize) / blocksize); //line calculation
	addressbuffer = ((address / blocksize)*blocksize); //starting number for block
	wordbuffer = (address - addressbuffer); // word calculation

	if(cache[line].tag != tagbuffer){
        printf("\n***Write Miss, load block from memory");
        cache[line].tag = tagbuffer;
        int j;
        for(j =0; j < blocksize; j++){
            cache[line].block[j] = mainmem[addressbuffer+j];
        }
    }
    else {
        cache[line].block[wordbuffer] = value;
    }
}

void readcache(){
	int line;
	int wordbuffer;
	int address;
	int value;
	int	addressbuffer;
	int i = 0;
	int readmem = 0;
	int readline = 0;
	int readtag = 0;
	int tagbuffer = 0;

	fscanf(test, "%d",&address);
	printf("\nEnter the memory address to read from: ""%d",address);

	if(address > (mainmemsize - 1)){
		printf("\nError: Address value is bigger than main memory size");
		return;
	}

	readline = (readmem%cachesize) / blocksize;
	readtag = (readmem / cachesize);

	if(readtag == 0){
		for (i = 0; i < blocksize; i++){
			if (!(cache[0].block[i] == 0)) {

			}
		}
	}

	tagbuffer = (address / cachesize); //tag buffer to check cache to see if memory is stored
	line = ((address%cachesize) / blocksize); //line calculation
	addressbuffer = ((address / blocksize)*blocksize); //starting number for block
	wordbuffer = (address - addressbuffer); // word calculation

	if(cache[line].tag != tagbuffer){
        cache[line].tag = tagbuffer;
        int j;
        for(j =0; j < blocksize; j++){
            cache[line].block[j] = mainmem[addressbuffer+j];
        }
    }
    else {
       value = cache[line].block[wordbuffer];
    }
    printf("\n\n***Word %i of cache line %i with tag %i contains the Value %i\n\n", wordbuffer, line, tagbuffer, value);
    return;
}


int main(void){
	int input;
	test = fopen("prog2_test_data.txt", "r");

	while(input != 4){ // loop to ensure user can run unless program is exited
        fscanf(test, "%d", &input);
        
        if(input == 1){
            startup();
            printf("\n***Starting to Read Data from the input file: prog2_test_data.txt\n");
            config(); 
            printf("\n***All Input Parameters Accepted. Starting to Process Write/Read Requests\n");
            //take input of cache, mainmem and block sizes and then construct simulated cache
        }
        
        if (input == 2){ // read cache
        	startup();
        	readcache();
        }

        if(input == 3) { // write cache
        	startup();
        	writecache();
    	}
    	if (input == 4){
    		printf("\nMemory Freed Up - Program Terminated Normally\n");
    		return 0;

    	}
    }
 }
	