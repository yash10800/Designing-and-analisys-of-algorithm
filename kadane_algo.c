#include<stdio.h>

int max(int a,int b){
    if(a>b)
        return a;
    else
        return b;
}

void main(){
    int a[]={100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97};
    int arr[sizeof(a) / sizeof(a[0])-1];
    for (int i=1;i<sizeof(a) / sizeof(a[0]);i++){
        arr[i-1]=a[i]-a[i-1];
    }
    //int arr[]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    int max_current=arr[0];
    int max_global=arr[0];

    for(int i=0;i<sizeof(arr) / sizeof(arr[0]);i++){
        max_current=max(arr[i],max_current+arr[i]);
        if(max_current>max_global){
            max_global=max_current;
        }
    }
    printf("\n\n\n\n\t\t\t%d",max_global);
}
