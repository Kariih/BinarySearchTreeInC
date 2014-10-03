#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//Struct which is used in the pointer array to store different values.
struct indexArray {
  int value;
  int indexNow;
  int indexBefore;
}*pArray;

//buble sort algorithm
void bubble(struct indexArray *arr,int n)
{
  int i,j;
  struct indexArray temp;
  for(i=1;i<n;i++)
    {
      for(j=0;j<n-i;j++)
        {
          if(arr[j].value>arr[j+1].value)
            {
              temp=(arr[j]);
              (arr[j])=(arr[j+1]);
              (arr[j+1])=temp;
            }
        }
    }
}

//Binary search algorithm
struct indexArray binarySearch(struct indexArray *pArray, int lenght, int key)
{
    int low = 0;
    int high = lenght - 1;
    int currentIndex;
    struct indexArray index;

    while(low <= high)
    {
        currentIndex = (high + low) / 2;
        if(key == pArray[currentIndex].value){
            index.indexBefore = pArray[currentIndex].indexNow;
            index.indexNow = currentIndex;
            index.value = pArray[currentIndex].value;
            return index;
        }else if(key < pArray[currentIndex].value){
            high = currentIndex - 1;
        }else{
            low = currentIndex + 1;
        }
    }
    index.indexNow = -1;
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
void print(struct indexArray *pArray, int i)
{
    int key = -1, success = 0;

    key = getNumberInput(key, success);

    while(key != 0)
    {
        //starting binary search after input from the getNumberInput method.
        struct indexArray result = binarySearch(pArray, i, key);
        if(result.indexNow == -1)
        {
            printf("\nCan't find the index of that number\n");
        }
        else
        {
            printf("\n%d has index %d and had original index %d.",
                    result.value, result.indexNow, result.indexBefore);

            //A little "hack" to find matching numbers.
            //I know it's not "best practise". Sorrryyyyyyyy :)
            int j;
            for(j = -3; j < 7; j++)
            {
                if(result.value == pArray[result.indexNow + j].value
                    && pArray[result.indexNow + j].indexNow != result.indexBefore)
                {

                    printf("\nSame number also exist at index %d and had original index %d.",
                          result.indexNow + j, pArray[result.indexNow + j].indexNow);

                }

            }
        }
    key = getNumberInput(key, success);
    }
}
//Scan the choosen file
int scan()
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
    pArray = malloc(size*sizeof(int));
    FILE* f = fopen (filename, "r");
    if(f == NULL)
    {
        fprintf(stderr, "Unable to open file\n");
        exit(-1);
    }

    int i = 0, num = 0;
    while (fscanf(f, "%d", &num) == 1)
    {
        pArray[i].value = num;
        pArray[i].indexNow = i;
        i++;
        if(i > 200000){
            printf("file is too big, reload program \n");
            exit(-1);
        }
    }
    if(i < 2){
        printf("file is too short, reload program \n");
        exit(-1);
    }
    return i;
    fclose(f);
}
//main method
int main()
{
    int i = scan();
    bubble(pArray, i);
    print(pArray, i);
}
