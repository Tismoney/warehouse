#include "hash.h"

unsigned int SIZE = 262144;
unsigned int LEN = 164;

#define CHECKNULL(ptr) if(ptr == NULL) return -1;
 

//-----------------------------------------------------------------//
//-----------------------Hach key function-------------------------//
//-----------------------------------------------------------------//

unsigned int hash_FAQ6(KEY key)
{
	unsigned int hash = 0;

	for(; *key; key++)
	{
		hash += (unsigned char)(*key);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash % SIZE;
}

//-----------------------------------------------------------------//
//--------------------Begin&End with hash-table--------------------//
//-----------------------------------------------------------------//

hash_ptr hash_ctor()
{
	return (hash_ptr)malloc(sizeof(hash_table) * SIZE);
}

int hash_dtor(hash_ptr pointer)
{
	for(int i = 0; i < SIZE; i++)
	{
		if(pointer[i].is_full == 1)
		{
			free(pointer[i].value);
			free(pointer[i].key);
		}

	}
	free(pointer);
	pointer = NULL;
}

//-----------------------------------------------------------------//
//---------------------Function of hash-table----------------------//
//-----------------------------------------------------------------//

int hash_add(hash_ptr pointer, FILE* file)
{
	CHECKNULL(pointer)

	char* str = (char*) malloc(sizeof(char)*LEN);
	char* tmp = (char*) malloc(sizeof(char)*LEN);
	unsigned int hash;
	unsigned int hash_check;
	unsigned int k = 1;
	char* key;
	char* val;
		//Divider
	char ch[2] = ":";
	char dv[2] = "\n";

	while(fgets(str, 164, file) != NULL)
	{
		key = strtok(str, ch);
		val = str + strlen(key) + 1;
		val = strtok(val, dv);
		hash = hash_FAQ6(key);

		while(pointer[hash].is_full)
		{
			if((hash + k) < SIZE)
				hash += k;
			else
				hash = 0;

				//If return to the top
			if(hash == hash_check)
			{
				free(str);
				free(tmp);
				return -1;
			}
		}

		pointer[hash].key = (KEY)malloc(sizeof(char)*32);
		pointer[hash].value = (VAL)malloc(sizeof(char)*128);
		pointer[hash].is_full = 1;

		strcpy(pointer[hash].key, key);
		strcpy(pointer[hash].value, val);

	}

	free(str);
	free(tmp);

	return 0;
}


int hash_find_key(hash_ptr pointer, KEY key)
{
	CHECKNULL(pointer)

	unsigned int hash;
	unsigned int hash_check;
	unsigned int k = 1;

	hash = hash_FAQ6(key);
	hash_check = hash;


	while(pointer[hash].is_full)
	{
		if(strcmp(pointer[hash].key, key) == 0)
			return 1;

		if((hash + k) < SIZE)
			hash += k;
		else
			hash = 0;

			//If return to the top
		if(hash == hash_check)
			return 0;
	}

	return 0;
}


int hash_del_key(hash_ptr pointer, KEY key)
{
	CHECKNULL(pointer)

	unsigned int hash;
	unsigned int hash_check;
	unsigned int k = 1;
	unsigned int chek = 0;

	hash = hash_FAQ6(key);
	hash_check = hash;


	while(pointer[hash].is_full)
	{
		if(strcmp(pointer[hash].key, key) == 0)
		{
			free(pointer[hash].value);
			free(pointer[hash].key);
			pointer[hash].is_full = 0;
			chek++;
		}
		
		if((hash + k) < SIZE)
			hash += k;
		else
			hash = 0;

			//If return to the top
		if(hash == hash_check)
			return 0;

	}

	if(k > 0)
		return 1;
	else
		return 0;
}


int hash_dump(hash_ptr pointer)
{
	CHECKNULL(pointer)
	unsigned int num = 0;

	printf("Hash-table:\n");
	for(int i = 0; i < SIZE; i++)
	{
		if(pointer[i].is_full)
		{
			printf("[%d] [%d] [key : %s] [val : %s] \n", i, hash_FAQ6(pointer[i].key), pointer[i].key, pointer[i].value);
			num++;
		}
	}
	printf("\n");
	return num;
}


int hash_dump_key(hash_ptr pointer, KEY key)
{
	CHECKNULL(pointer)

	unsigned int hash;
	unsigned int hash_check;
	unsigned int k = 1;
	unsigned int num = 0;

	hash = hash_FAQ6(key);
	hash_check = hash;

	printf("Hash-table-key:\n");
	while(pointer[hash].is_full)
	{
		if(strcmp(pointer[hash].key, key) == 0)
		{
			printf("[%d] [key : %s] [val : %s] \n", hash, pointer[hash].key, pointer[hash].value);
			num++;
		}

		if((hash + k) < SIZE)
			hash += k;
		else
			hash = 0;

			//If return to the top
		if(hash == hash_check)
		{
			printf("Hash is full of anoter elements.\n");
			return 0;
		}
			
	}

	if(num > 0)
		return num;
	else
	{
		printf("I`m so sory, but there aren`t element with this key.\n");
		return 0;
	}
}


