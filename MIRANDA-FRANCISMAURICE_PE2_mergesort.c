/*
Francis Maurice B. Miranda || BSCS 1B
Programming Exercise 2 - Merge Sort MODIFIED
    A modified version of the merge sort program given in Lecture 1.a but instead it sorts the array in descending order. The program will ask the user to
    input the size of the array which would then be followed by the elements of the array (separated with spaces). The program will then use the merge sort
    algorithm to sort the elements of the array from the highest number to the lowest. This sorted list is then outputted.
*/

#include <stdio.h>
#include <math.h>

//prototype declaration for the functions needed
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

//main function
int main() { 
    int a[30],n,i;
    printf("Enter no. of elements:"); //prompt for array size
    scanf("%d",&n);
    printf("Enter array elements:"); //prompt for the elements

    //for loop that takes the inputs
    for(i = 0; i < n; i++)
        scanf("%d",&a[i]);

    mergesort(a, 0, n-1); //function calls mergesort

    //outputs the sorted array
    printf("\nSorted array is :");
    for(i = 0; i < n; i++)
        printf("%d ",a[i]);

  return 0;
}

//function for splitting the array into sub-arrays and merging them after sorting
void mergesort(int a[],int i,int j){
    int mid;
    if(i<j){
        mid=(i+j)/2; //gets middle index
        mergesort(a,i,(i+j)/2); //recursion for the left half
        mergesort(a,((i+j)/2)+1,j); //recursion for the right half
        merge(a,i,mid,mid+1,j); //merging of two sorted sub-arrays
    }
}

//function for merging the sorted sub-arrays
void merge(int a[],int i1,int j1,int i2,int j2){
    int temp[50]; //array used for merging
    int i,j,k;
    i=i1; //beginning of the first list
    j=i2; //beginning of the second list
    k=0;

    while(i<=j1 && j<=j2){ //loop that merges the two sub-arrays in descending order
        if(a[i]>a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];

    }

    //loops for cases that the sub-arrays are uneven
    while(i<=j1) //loop that copies the remaining elements of the first list
        temp[k++]=a[i++];

    while(j<=j2) //loop that copies the remaining elements of the second list
        temp[k++]=a[j++];

    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];

}