//Mingzhe Ou
//mi.ou@northeastern.edu

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    int index = 0;

    for(int i = 0; i < n; i++){
        int count = 1;
        while(i < n - 1 && arr[i] == arr[i + 1]){
            count++;
            i++;
        }

        res[index++] = arr[i];

        if(count > 1){
            int count_len = snprintf(res + index, n - index, "%d", count);
            index += count_len;
        }
    }
    res[index] = '\0';
    
    return index;
    
}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("length of the compressed string:%d\n",r);
    printf("compressed string: %s\n", res);
    return 0;
}
