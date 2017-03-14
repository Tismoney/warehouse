#ifndef HASH_H
#define HASH_H
//-----------------------------------------------------------------//
//----------------------Header of hash-table-----------------------//
//-----------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//-----------------------------------------------------------------//
//---------------------------Hash-table----------------------------//
//-----------------------------------------------------------------//
	//Key for string is string... 
typedef char* VAL;
typedef char* KEY;
typedef unsigned int bool;


typedef struct hash_table 
{
	KEY key;
	VAL value;
	bool is_full;
}hash_table;

typedef struct hash_table *hash_ptr;
//-----------------------------------------------------------------//
//-----------------------Hach key function-------------------------//
//-----------------------------------------------------------------//

	//Calculete a hash of key
unsigned int hash_FAQ6(KEY key);

//-----------------------------------------------------------------//
//--------------------Begin&End with hash-table--------------------//
//-----------------------------------------------------------------//
	//Constructor of hash-table
hash_ptr hash_ctor();
		//Make a hash table with size = size and begin pointer = pointer


	//Destructor of hash-table
void hash_dtor(hash_ptr pointer);
		//Delete a hash table: delete all values and free all memory


//-----------------------------------------------------------------//
//---------------------Function of hash-table----------------------//
//-----------------------------------------------------------------//
	//Add a value in hash-table
int hash_add(hash_ptr pointer, FILE* file);
		//0 - added, -1 - error


	//Search in hash-table value of key
int hash_find_key(hash_ptr pointer, KEY key);
		//1 - yes, 0 - no, -1 - error

	//Delete in hash-table all value of key
int hash_del_key(hash_ptr pointer, KEY key);
		//1 - yes, 0 - no, -1 - error

	//Print all hash-table
int hash_dump(hash_ptr pointer);

	//Print all element hash-table with key
int hash_dump_key(hash_ptr pointer, KEY key);

#endif