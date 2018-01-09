#include<stdio.h>
#include<string.h>
#include"driver.h"

int main(){
	
	sortFileData();

	char message[1000];

	printf("\n\n\n\n\t\t\t\t");
                fgets(message,1000,stdin);

                filterUnSentimentalWords(message);

                printf("\n\n\n\n\t\t\t\tNon-Sentimental Words are:\n\n\n\n\n\t\t\t\t");
                printf("%d->",no_of_NonSentimentalWords);
                showNonSentimentalWords();

                printf("\n\n\n\n\t\t\t\tSentimental Words are:\n\n\n\t\t\t\t");
                printf("%d->",no_of_sentimentalWords);
                showSentimentalWords();


                if(no_of_sentimentalWords == 0) printf("\n\t\t\t\tNeurtal Sentence!!");
                else printf("\n\t\t\t%s\n",train_bayesSentimentPredictionClassifier().nameOfSentiment);
		
	return 0;




}
