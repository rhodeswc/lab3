#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

/*
*
* @author Wesley Rhodes
* @date 9-11-2014
*
*/

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

/*
* Initializes the arrayList struct to its default values.
*
* @param primitiveType type is the type of element being inserted 
*
* @return returns a pointer to the arrayList struct
*/
arrayList * initialize(primitiveType type)
{
	arrayList *a;
	a = (arrayList *) malloc(sizeof(arrayList));
	
	(*a).array = (arrayList *) malloc(getSize(type)*4);
	(*a).elementSize = getSize(type);
	(*a).arraySize = 4;
	(*a).numElements = 0;
	(*a).type = type;
	return a;
}

/*
* Gets the size of the type 
*
* @param primitiveType type is the type of element being inserted 
*
* @return returns the size of the type
*/
static int getSize(primitiveType type)
{
	if (type == charType) {
		return sizeof(char);
	}
	else if (type == shortType) {
		return sizeof(short);
	}
	else if (type == intType) {
		return sizeof(int);

	}
   return 0;
}

/*
* Adds an element to the array
*
* @param arrayList * arylstP is a pointer to the arrayList struct
* @param void * element is a void pointer to the element being added 
*/
void addElement(arrayList * arylstP, void * element)
{
	char* p = (char*)element;
	

	if (arylstP->numElements == arylstP->arraySize)
	{
		void * newArray = malloc((*arylstP).elementSize * (*arylstP).arraySize * 2); //allocates a block of mem for newArray; //creates new array
		int i; 
		for (i = 0; i < arylstP->numElements * arylstP->elementSize; i++)
		{
			((char *)newArray)[i] = ((char*)arylstP->array)[i]; //copies the data to new array
		}
		free (arylstP->array); 
	
		arylstP->array = newArray; // points newArray to array
		arylstP->arraySize *= 2; //changes the arraySize
				
	}
	
	int j;
	
	for(j = 0; j < arylstP->elementSize; j++)
	{
		((char*)arylstP->array)[arylstP->elementSize * arylstP->numElements + j] = p[j]; //stores the element in its spot
	}
	
	arylstP->numElements += 1; //increments the num of elements
    return;
}

/*
* Removes an element from the array at the given index
*
* @param arrayList * arylstP is the pointer to the arrayList struct
* @param int index is the index at which the element is being removed
*/
void removeElement(arrayList * arylstP, int index)
{
	int i;
	
	for(i = index; i < (arylstP->numElements)-1; i++)
	{
		if(arylstP->type == charType)
		{
			
			((char *)arylstP->array)[i] = ((char*)arylstP->array)[i+1];
		}
		else if(arylstP->type == shortType)
		{
			
			((short *)arylstP->array)[i] = ((short*)arylstP->array)[i+1];
		}
		else if(arylstP->type == intType)
		{
			
			((int *)arylstP->array)[i] = ((int*)arylstP->array)[i+1];
		}
		
	}
	arylstP->numElements -= 1;
    return;
}
      
/*
* Prints the data stored in the array
*
* @param arrayList * arylstP is the pointer to the arrayList struct 
*/
void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
	   if (arylstP->type == charType) {
		   
		   printf("%02x ", (0xff & ((char*)arylstP->array)[i]));
		   
	   }
	   else if (arylstP->type == shortType) {
		   
		   printf("%04x ", (0xffff & ((short*)arylstP->array)[i]));
	   }
	   else if (arylstP->type == intType) {
		  
		   printf("%08x ", (0xffffffff & ((int*)arylstP->array)[i]));
	   }
   }
   printf("\n");
}

