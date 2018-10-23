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
    printf( "Class Meeting Time: 8:00 - 9:15 \n");
    printf( "1) Comp 222 - Fall 2018 \n");
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
	printf("\n Enter main memory size (words): ");
	fscanf(test, "%d", mainmemsize);

	printf("\n Enter cache size (words): ");
	fscanf(test, "%d", cachesize);

	printf("\n Enter block size (words/block): ");
	fscanf(test, "%d", blocksize);


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
			cache[j].block[i] = NULL;
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
	int addresssub = 0;
	int tagbuffer = 0;
	int line = 0;
	int wordbuffer = 0;

	printf("\n Enter Main memory address to write to: ");
	fscanf(test, "%d", &address);
	if(address > (mainmemsize - 1)){
		printf("\nError: Address value is bigger than main memory size");
		return;
	}

	printf("\n Enter the Values: ");
	fscanf(test, "%d", value);
	mainmem[address] = value;

	
	tagbuffer = (address / cachesize); //tag buffer to check cache to see if memory is stored
	line = ((address%cachesize) / blocksize); //line calculation
	addressbuffer = ((address / blocksize)*blocksize); //starting number for block
	wordbuffer = (address - addressbuffer); // word calculation

}

int main(void){
	int input;
	test = fopen("prog2_test_data.txt", "r");

	while(input != 4){ // loop to ensure user can run unless program is exited
        scanf(test, "%d", &input);
        
        if(input == 1){
            startup();
            config(); 
            //take input of cache, mainmem and block sizes and then construct simulated cache
        }
        
        if (input == 2){ // calculate answers
            startup();
        }

        if(input == 3) { //
        startup();
    	}

    }

 }
	