#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
#define MAX_CHAIN_LENGTH 10
struct HashType
{
	struct RecordType chain[MAX_CHAIN_LENGTH]; 
    int chainLength; 
};

// Compute the hash function
int hash(int x)
{
	 return x % MAX_CHAIN_LENGTH;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i, j;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].chainLength > 0)
        {
            printf("Index %d -> ", i);
            for (j = 0; j < pHashArray[i].chainLength; ++j)
            {
                printf("%d %c %d", pHashArray[i].chain[j].id, pHashArray[i].chain[j].name, pHashArray[i].chain[j].order);
                if (j < pHashArray[i].chainLength - 1)
                    printf(" -> ");
            }
            printf("\n");
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	int i;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	// Initialize hash table
    const int HASH_SIZE = 10; // Choose an appropriate size for your hash table
    struct HashType hashTable[10];

    // Initialize hash table
	for (i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i].chainLength = 0;
    }

    // Insert records into hash table
    for (i = 0; i < recordSz; i++)
    {
        int index = hash(pRecords[i].id);
        if (hashTable[index].chainLength < MAX_CHAIN_LENGTH)
        {
            struct RecordType *recordPtr = &(hashTable[index].chain[hashTable[index].chainLength]);
            *recordPtr = pRecords[i];
            hashTable[index].chainLength++;
        }
    }

    // Display records in hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    // Free dynamically allocated memory
    free(pRecords);

    return 0;
}