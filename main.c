#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <ctype.h>

struct indexArray {
  int value;
  int index;
};
struct index {
    int indexNow;
    int indexBefore;
};

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

struct index binarySearch(struct indexArray *arr, int lenght, int key)
{
  int low = 0;
  int high = lenght - 1;
  int currentIndex;
  struct index index;

  while(low <= high)
  {
    currentIndex = (high + low) / 2;
    if(key == arr[currentIndex].value){
        index.indexNow = currentIndex;
        index.indexBefore = arr[currentIndex].index;
        return index;
    }else if(key < arr[currentIndex].value){
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
  int key;
  printf("\nPut in an integer for search(type 0 for exit): ");
  scanf("%d", &key);
  while(!(isdigit(key))){
    printf("\nPut in an integer for search(type 0 for exit): ");
    scanf("%d", &key);
  }

  while(key != 0)
  {
    struct index result = binarySearch(pArray, i, key);
    if(result.indexNow == -1)
    {
      printf("\nCan't find the index of that number");
    }
    else
    {
      printf("\nThe number you searched has index %d and had original index %d",
        result.indexNow, result.indexBefore);
    }
    printf("\nPut in an integer for search (type 0 for exit): ");
    scanf("%d", &key);
  }
}

int main()
{
  char filename[255];
  printf("Write the name of the input file: ");
  scanf("%s", filename);
  FILE* f = fopen (filename, "r");

  if(f == NULL) {
    fprintf(stderr, "Unable to open file");
    exit(-1);
  }

  struct stat st;
  stat(filename, &st);
  int size = st.st_size;

  struct indexArray *pArray = malloc(size*sizeof(int));

  int i = 0, num = 0;
  while (fscanf(f, "%d", &num) == 1)
  {
    pArray[i].value = num;
    pArray[i].index = i;
    i++;
  }
  fclose(f);

  bubble(pArray, i);
  print(pArray, i);
  }
