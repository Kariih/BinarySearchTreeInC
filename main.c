#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

struct indexArray {
  int value;
  int indexNow;
  int indexBefore;
}*pArray;

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
void print(struct indexArray *pArray, int i)
{
    int key = -1;

    printf("\nPut in an integer for search (type 0 for exit): ");
    scanf("%d", &key);

    while(key != 0)
    {
        struct indexArray result = binarySearch(pArray, i, key);
            if(result.indexNow == -1)
            {
                printf("\nCan't find the index of that number\n");
            }
            else
            {
                    printf("\n%d has index %d and had original index %d.",
                    result.value, result.indexNow, result.indexBefore);
                  for(int j = -3; j < 7; j++)
                  {
                      if(result.value == pArray[result.indexNow + j].value && pArray[result.indexNow + j].indexNow != result.indexBefore)
                      {

                              printf("\n%d also exist at %d and had original index %d.",
                              pArray[result.indexNow + j].value, result.indexNow + j, pArray[result.indexNow + j].indexNow);

                      }

                  }
            }
            printf("\nPut in an integer for search (type 0 for exit): ");
            scanf("%d", &key);
    }
}

int scan()
{
    char filename[255];
    printf("Write the name of the input file: ");
    scanf("%s", filename);
    struct stat st;
    stat(filename, &st);
    while( access( filename, F_OK ) == -1 )
    {
        printf("File didn't exist, try again: ");
        scanf("%s", filename);
    }
    int size = st.st_size;
    pArray = malloc(size*sizeof(int));
    FILE* f = fopen (filename, "r");
    if(f == NULL)
    {
        fprintf(stderr, "Unable to open file");
        exit(-1);
    }

    int i = 0, num = 0;
    while (fscanf(f, "%d", &num) == 1)
    {
        if (num < '0' || num > '9')
        {
            printf("File need to contain only integers. Reload program");
            exit(-1);
        }
        pArray[i].value = num;
        pArray[i].indexNow = i;
        i++;
    }
    return i;
    fclose(f);
}
int main()
{
    int i = scan();
    bubble(pArray, i);
    print(pArray, i);
}
