/*************************************************************************************************************************
* Source code to play with bit patters.
* APIs implemented : check_bit_pattern(),fill_pattern(),init_zero(),my_free()
* Author		   : Sumanth Bhat
* Date  		   : 8 September 2015 
* Contact Details  : sumanthbhatt@gmail.com
* Institution	   : International Institute of Information Technology, Bangalore
*************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define HEAP_SIZE 2000

#define PATTERN_SIZE 5

const int bit_pattern[PATTERN_SIZE] = {1,1,0,1,1};

char StaticMemory[HEAP_SIZE];

char *check_bit_pattern (char * start_addr);
//This function checks whether the binary bit pattern given is found in the
//memory from the start address and returns the address where the pattern
//check has failed.

void fill_pattern (char * start_addr, char* end_addr);
//This function fills the binary bit pattern mentioned in the static array
//starting from the start address till the end address.

void init_zero (char * start_addr, char* end_addr);
//This function from the starting address to the end address fills the memory
//with zeros.

void hexdump(void);
void get_bits(int* split_bits,char byte);

int 
main(int argc, char const *argv[])
{
	char *start_addr,*end_addr;
	int i;
	start_addr = StaticMemory;
	end_addr = StaticMemory + 300;
	init_zero(start_addr,end_addr);
	fill_pattern (start_addr,end_addr);
	printf("End of pattern = %ld\n",(long)check_bit_pattern(start_addr+i));
	
	
	//hexdump();
	return 0;
}

char* 
check_bit_pattern (char * start_addr)
{
	int count,initial_offset,split_bits[16],flag=0;
	char byte1,byte2;
	char *Address;

	//Routine error checking
	if(start_addr < StaticMemory || start_addr > StaticMemory + HEAP_SIZE)
		return NULL;

	Address = start_addr;

	byte1 = *Address;
	byte2 = *(Address+1);
	
	get_bits(split_bits,byte1);
	get_bits(split_bits + 8,byte2);
	for (count = 0; 16 > count; ++count)
	{
		if(split_bits[count] == bit_pattern[0])
			if(split_bits[count+1] == bit_pattern[1])
				if(split_bits[count+2] == bit_pattern[2])
					if(split_bits[count+3] == bit_pattern[3])
						if(split_bits[count+4] == bit_pattern[4])
							break;
	}
	initial_offset = (PATTERN_SIZE-count)%PATTERN_SIZE;
	
	if(count==8)
		return start_addr;
	
	while(Address <= (StaticMemory + HEAP_SIZE))
	{		
		byte1 = *Address;
			
		get_bits(split_bits,byte1);
		
		for (count = 0; 8 > count; ++count)
		{
			if (split_bits[count] != bit_pattern[(initial_offset+count)%PATTERN_SIZE])
				{
					flag = 1;
					break;
				}
			}
		initial_offset = (initial_offset + 8) % PATTERN_SIZE;
		if(flag)
			break;
		Address++;
	}
	return Address;
}

void 
fill_pattern (char * start_addr, char* end_addr)
{
	int initial_offset = 0,count;
	char *Address,byte;
	
	//Routine error checking
	if(start_addr < StaticMemory || start_addr > StaticMemory + HEAP_SIZE || start_addr>end_addr)
		printf("Error in start address\n");
	if(end_addr < StaticMemory || end_addr > StaticMemory + HEAP_SIZE)
		printf("Error in start address\n");

	Address = start_addr;
	while(Address <= end_addr)
	{	
		byte = 0;
		for(count=0;count<8;count++)	
		{
			byte = byte << 1;
			byte |= bit_pattern[(initial_offset+count)%PATTERN_SIZE];
		}
		initial_offset = (initial_offset + 8) % PATTERN_SIZE;
		*Address = byte;
		Address++;
	}

}

void 
init_zero (char * start_addr, char* end_addr)
{
	if(end_addr > start_addr)
		memset(start_addr,0,(long)end_addr - (long)start_addr);
	else
		printf("Error in argument order...\n");
}

void
hexdump(void)
{
	int *a;
	int rowCount,columnCount;
	a = (int*)StaticMemory;
	printf("\n***************************************************************************");
	printf("\nBeginning Hex Dump\n");
	printf("Address\t1\t2\t3\t4\t5\t6\t7\t8\n");
	for(rowCount = 0 ; rowCount < HEAP_SIZE/(sizeof(int)*8) ; rowCount++)
	{
		printf("%ld\t",(long)a + (sizeof(int)*8*rowCount));
		for(columnCount=0;columnCount<8;columnCount++)
		{
			printf("%d\t",*(a + 8*rowCount + columnCount));
		}
		printf("\n");
	}
	printf("***************************************************************************\n");
}

void 
get_bits(int* split_bits,char byte)
{
	int i;
	for (i = 0; i < 8; ++i)
	{
		split_bits[i] = (byte & (1<<(7-i)))>>(7-i);
	}
}