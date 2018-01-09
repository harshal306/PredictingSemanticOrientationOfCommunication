
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void functionToOpenFile(){

    int i=0,s = 0;
    char data[10][10];
    FILE *corpus;

    corpus = fopen("test.txt","r");

    do{
        fscanf(corpus,"%s",data[i++]);

    }while(feof(corpus));

    for(s=0;s<i;s++){

        printf("%s",data[s]);
    }
}
