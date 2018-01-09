/*
	By- Harshal Mittal
	Date: 28th August 2017
*/

#include<stdio.h>
#include<string.h>
#include"driver.h"

int initializeSystem();

int main(){

    sortFileData();

	char message[1000];
    int choice,exit=0;

    do{

        choice = initializeSystem();

        switch(choice){

            case 1: {

                test_EfficiencyOfClassifier();
                break;

            }

            case 2: {

                printf("\n\n\n\n\t\t\t\t");
                //scanf("%s",message);
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

                break;

            }

            case 0:{

                printf("\n\t\t\t\tThank You for using this classifier!!\n");
                exit = 1;
                break;
            }

            default:{

                printf("\n\t\t\t\tInvalid Input!! Please Enter either 1, 2 or 0");
            }
        }
    }while(choice != 0);

	return 0;
}

int initializeSystem(){

    int choice;
    printf("\n\n\n\n\t\t\t\tA. Press 1 to test for the efficiency of classifier!!\n\t\t\t\tB. Press 2 to Evaluate the Classifier!!\n\t\t\t\tC. Press 0 to exit!!\n\n\n\t\t\t\t");
    scanf("%d",&choice);
    return choice;
}
