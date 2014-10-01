#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble(int *arr,int n)
{
int i,j;
int temp;
for(i=1;i<n;i++)
 {
  for(j=0;j<n-i;j++)
   {
    if(*(arr+j)>*(arr+j+1))
     {
      temp=*(arr+j);
      *(arr+j)=*(arr+j+1);
      *(arr+j+1)=temp;
     }
   }
 }
}

int binarySearch(int *arr, int lenght, int key)
{
  int low = 0;
  int high = lenght - 1;
  int currentIndex;

  while(low <= high)
  {
    currentIndex = (high + low) / 2;
    if(key == arr[currentIndex])
        return currentIndex;
    else if(key < arr[currentIndex])
      high = currentIndex - 1;
    else
      low = currentIndex + 1;
  }
  return -1;
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

  int *array = malloc(10000*sizeof(int));
  int *arrySort = malloc(10000*sizeof(int));

  int i = 0, num = 0;
  while (fscanf(f, "%d", &num) == 1)
  {
    array[i++] = num;
  }
  fclose(f);

  memcpy(arrySort, array, i*sizeof(int));
  bubble(arrySort, i);
  int key;
  printf("Put in an integer for search: ");
  scanf("%d", &key);

  while(key != 0)
  {
    int result = binarySearch(arrySort, i, key);
    if(result == -1)
      printf("Can't find the index of that number");
    else
      printf("The number you searched has index %d", result);
    printf("Put in an integer for search (type 0 for exit): ");
    scanf("%d", &key);
  }

}
