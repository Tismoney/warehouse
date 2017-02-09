#include "hash.h"

int main()
{
	FILE* file1 = fopen("data1.txt", "r");
	FILE* file2 = fopen("data1.1.txt", "r");
	FILE* file3 = fopen("data2.txt", "r");
	char key[14] = "Никита";
	char ke[14] = "Даня";


		//Make hash and add data
	hash_ptr hash1 = hash_ctor();
	hash_add(hash1, file1);
	hash_dump(hash1);

		//Add some data
	hash_add(hash1, file2);
	hash_dump(hash1);

		//Find in hash
	int tmp = hash_find_key(hash1, key);
	if(tmp)
		printf("Hash have %s\n", key);
	else
		printf("Hash have no %s \n", key);

		//Dump hash with key
	hash_dump_key(hash1, ke);


		//Delete in hash
	hash_del_key(hash1, key);
	hash_dump(hash1);

		//Make a new hash and add it
	hash_ptr hash2 = hash_ctor();
	hash_add(hash2, file3);
	hash_dump(hash2);

		//Delete hash
	hash_dtor(hash1);
	hash_dtor(hash2);


	 	//We couldn`t work with hashes
	hash_add(hash2,file1);


	fclose(file1);
	fclose(file2);
	fclose(file3);
	return 0;
}