#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
//Kari Helene Bekkelund
//Struct which is used in the pointer array to store different values.
struct indexArray {
  int value;
  int indexCurrent;
  int indexOriginal;
}*pIndexArray;

//buble sort algorithm
void bubbleSort(struct indexArray *pIndexArray,int count)
{
  int i,j;
  struct indexArray temp;
  for(i=1;i<count;i++)
    {
      for(j=0;j<count-i;j++)
        {
          if(pIndexArray[j].value>pIndexArray[j+1].value)
            {
              temp=(pIndexArray[j]);
              (pIndexArray[j])=(pIndexArray[j+1]);
              (pIndexArray[j+1])=temp;
            }
        }
    }
}

//Binary search algorithm
struct indexArray binarySearch(struct indexArray *pIndexArray, int lenght, int key)
{
    int low = 0;
    int high = lenght - 1;
    int currentIndex;
    struct indexArray index;

    while(low <= high)
    {
        currentIndex = (high + low) / 2;
        if(key == pIndexArray[currentIndex].value){
            index.indexOriginal = pIndexArray[currentIndex].indexCurrent;
            index.indexCurrent = currentIndex;
            index.value = pIndexArray[currentIndex].value;
            return index;
        }else if(key < pIndexArray[currentIndex].value){
            high = currentIndex - 1;
        }else{
            low = currentIndex + 1;
        }
    }
    index.indexCurrent = -1;
    return index;
}
//Handle input of number for search.
int getNumberInput(int key, int success)
{
  char buffer[255];
  memset(buffer, 0, sizeof(buffer));
  do {
      printf("\nPut in an integer for search (type 0 for exit): ");
      if(strlen(fgets(buffer, sizeof(buffer), stdin)) > 1) {
          success = sscanf(buffer, "%d", &key);
          return key;
      }
  } while(!success);
  return 0;
}
//print the result of the binary search.
void printResultFromSearch(struct indexArray *pIndexArray, int count)
{
    int key = -1, success = 0;

    key = getNumberInput(key, success);

    while(key != 0)
    {
        //starting binary search after input from the getNumberInput method.
        struct indexArray result = binarySearch(pIndexArray, count, key);
        if(result.indexCurrent == -1)
        {
            printf("\nCan't find the index of that number\n");
        }
        else
        {
            printf("\n%d has index %d and had original index %d.",
                    result.value, result.indexCurrent, result.indexOriginal);

            //A little "hack" to find matching numbers.
            //I know it's not "best practise". Sorrryyyyyyyy :)
            int j;
            if(result.indexCurrent < 1)
            {
                for(j = 0; j < 5; j++)
                {
                    if(result.value == pIndexArray[result.indexCurrent + j].value
                        && pIndexArray[result.indexCurrent + j].indexCurrent != result.indexOriginal)
                    {
                        printf("\nSame number also exist at index %d and had original index %d.",
                              result.indexCurrent + j, pIndexArray[result.indexCurrent + j].indexCurrent);
                    }
                  }
              }
              else
              {
                for(j = -2; j < 5; j++)
                {
                    if(result.value == pIndexArray[result.indexCurrent + j].value
                        && pIndexArray[result.indexCurrent + j].indexCurrent != result.indexOriginal)
                    {
                        printf("\nSame number also exist at index %d and had original index %d.",
                              result.indexCurrent + j, pIndexArray[result.indexCurrent + j].indexCurrent);
                    }
                  }
              }
        }
    key = getNumberInput(key, success);
    }
}
//Scan the choosen file
int scanIntToArray()
{
    char filename[255];
    memset(filename, 0, sizeof(filename));

    //give access to the choosen file
    int success = 0;
    while(strlen(filename) == 0 || success == 0) {
        printf("Write the name of the input file: ");
        int inputLength = strlen(fgets(filename, sizeof(filename), stdin));
        filename[--inputLength] = 0;

        if(access(filename, F_OK) == 0) {
            success = 1;
        } else if(inputLength > 0) {
            fprintf(stderr, "Unable to open file: %s\n", filename);
        }
    }

    struct stat st;
    stat(filename, &st);


    //set the size of the struct array and start reading input.
    int size = st.st_size;
    pIndexArray = malloc(size*sizeof(int));
    FILE* f = fopen (filename, "r");
    if(f == NULL)
    {
        fprintf(stderr, "Unable to open file\n");
        exit(-1);
    }

    int count = 1, numberFromFile = 0;
    while (fscanf(f, "%d", &numberFromFile) == 1)
    {
        pIndexArray[count].value = numberFromFile;
        pIndexArray[count].indexCurrent = count;
        count++;
        if(count > 200000){
            printf("file is too big, reload program \n");
            exit(-1);
        }
    }
    if(count < 2){
        printf("file is too short, reload program \n");
        exit(-1);
    }
    return count;
    fclose(f);
}
//main method
int main()
{
    int n = scanIntToArray();
    bubbleSort(pIndexArray, n);
    printResultFromSearch(pIndexArray, n);
}
