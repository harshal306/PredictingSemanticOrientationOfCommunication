#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


/*
    structure to store the prediction of the respective sentiment efficiently.
*/

struct predictionProb{

    char nameOfSentiment[100];
    float predictionForSentence;

};


/*
    SentimentalWords contains sentimental words enter in a phrase by user.
    accordingly are the nonSentimentalWords

*/
char sentimentalWords[1000][1000];
char nonSentimentalWords[1000][1000];
int no_of_sentimentalWords;
int no_of_NonSentimentalWords;
char angryFile[] = "angry_sentiment/Train_Data/sentence.txt";
char sadFile[] = "sad_sentiment/Train_Data/sentence.txt";
char happyFile[] = "happy_sentiment/Train_Data/sentence.txt";
char vulgarFile[] = "vulgar_sentiment/Train_Data/sentence.txt";
struct predictionProb prediction[5];

/*
    return maximum of five float value;
*/

struct predictionProb maxAmongPrediction(struct predictionProb* value){

    struct predictionProb temp;
    int i=0,j=0;

    for(;i<5;i++){

        for(j=i+1;j<5;j++){

            if(value[i].predictionForSentence < value[j].predictionForSentence){

              stringcpy(temp.nameOfSentiment, value[i].nameOfSentiment);
              temp.predictionForSentence = value[i].predictionForSentence;
              stringcpy(value[i].nameOfSentiment, value[j].nameOfSentiment);
              value[i].predictionForSentence = value[j].predictionForSentence;
              stringcpy(value[j].nameOfSentiment, temp.nameOfSentiment);
              value[j].predictionForSentence = temp.predictionForSentence;
            }
        }
    }

    return value[0];
}

/*
    printing the Non Sentimenatal Words.
*/
void showNonSentimentalWords(){

    int i=0;
    for(;i<no_of_NonSentimentalWords;i++){
        printf(" %s;",nonSentimentalWords[i]);
    }
}

/*
    printing the Sentimental Words.
*/
void showSentimentalWords(){

    int i=0;
    for(;i<no_of_sentimentalWords;i++){
        printf(" %s;",sentimentalWords[i]);
    }
}

/*
    function to convert a string into lower case.
*/
char* toLower(char *data){

    int i=0;
    for(;i<strlen(data);i++){
        data[i] = (data[i]<92 && data[i]>64) ? data[i]+32:data[i];
    }
    return data;
}

/*
	AVL Tree node
*/

struct Node
{
    char key[100][100];
    struct Node *left;
    struct Node *right;
    int height;
};

/*
	This function gets the height of any node in AVL Tree.
*/

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

/*
	This function finds the maximun between 2 number.
*/

int max(int a, int b)
{
    return (a>b)?a:b;
}

/*
	Creating a new node for insertion.
*/

struct Node* newNode(char *key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    stringcpy(node->key,key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

/*
	If the AVL Tree got Imbalance then
	these both function "RightRotate" and "LeftRotate" helps in achieving the
	level of balancing
*/

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

/*
	This function returns the balancing factor of any Node in
	AVL Tree.
*/

int getBalance(struct Node *N)
{

    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/*
	This function is inserting the file data to the AVL Tree for Oranizing the
	searching technique.
*/

struct Node* insert(struct Node* node, char *key)
{
    if (node == NULL)
        return(newNode(key));

    if (stringcmp(key,node->key)<0)
        node->left  = insert(node->left, key);
    else if (stringcmp(key,node->key)>0)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

 	// left case
    if (balance > 1 && stringcmp(key,node->left->key)<0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && stringcmp(key,node->right->key)>0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && stringcmp(key,node->left->key)>0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && stringcmp(key,node->right->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*
	This function is used for traversing the AVL in INORDER.
*/

void InOrder(struct Node *root)
{
    if(root != NULL)
    {
    	InOrder(root->left);
    	printf("\n\t\t\t\t");
        printf("%s", &root->key);
        InOrder(root->right);
    }
}

/*
	This function search the element in AVL Tree.
*/

int searchData(struct Node* node,char* data){

	if(node == NULL){
		//printf(" leaf.");
		return 0;
	}
	else if(stringcmp(node->key,data)==0){
		//printf(" Searched.");
		return 1;
	}
	else if(stringcmp(node->key,data)<0){
		//printf(" Searching right,");
		searchData(node->right,data);
	}
	else if(stringcmp(node->key,data)>0){
		//printf(" Searching Left,");
		searchData(node->left,data);
	}
	else return 0;
}


/*
	String comparison function:

	* This function return -1 if first string'letter's ascii value is smaller than
		second one.
	* This function return 1 if first string'letter's ascii value is greater than
		second one.
	* otherwise 0


*/

int stringcmp(char* strone, char* strtwo){

	int i = 0;
   while (strone[i] == strtwo[i] && strone[i] != '\0')
      i++;
   if (strone[i] > strtwo[i])
      return 1;
   else if (strone[i] < strtwo[i])
      return -1;
   else
      return 0;

}

/*
	String Copying function:

	* This function Copies second sting into first one.
*/

void stringcpy(char *strone, char *strtwo){

	int i = 0;
   while (strtwo[i] != '\0') {
      strone[i] = strtwo[i];
      i++;
   }

   strone[i] = '\0';

   return;
}

/*
	File data Sorting function:

	This function actually sort the data collected from the large corpus
	so that it can be easily organised.
*/

void sortFileData(){

	FILE *p;
   char data[1000][1000],temp[1000][1000];
   int data_size,inpt=0,i,j,c,root_node;
   p = fopen("Trash_Keywords/Trash.txt", "r");
   //fprintf(p,"%s %d", e.name, e.age);
   do
   {
      fscanf(p,"%s", data[inpt++]);
      //printf("%s\n", data);
   }
   while( !feof(p) );
   data_size = inpt-1;
   inpt = data_size;
   fclose(p);

   for (i = 1; i < data_size+1; i++)
    {
        c = i;
        do
        {
            root_node = (c - 1) / 2;
            if (stringcmp(data[root_node],data[c])<0)
            {
                stringcpy(*temp, data[root_node]);
                stringcpy(data[root_node], data[c]);
                stringcpy(data[c], *temp);
            }
            c = root_node;
        } while (c != 0);
    }

    for (j = data_size; j >= 0; j--)
    {
        stringcpy(temp, data[0]);
        stringcpy(data[0], data[j]);
        stringcpy(data[j], temp);
        root_node = 0;
        do
        {
            c = 2 * root_node + 1;
            if (stringcmp(data[c],data[c+1])<0 && c < j-1)
                c++;
            if (stringcmp(data[root_node],data[c])<0 && c<j)
            {
                stringcpy(temp, data[root_node]);
                stringcpy(data[root_node], data[c]);
                stringcpy(data[c], temp);
            }
            root_node = c;
        } while (c < j);
    }
    printf("\n\n\n\t\t\t\t\t");

    FILE *q;
    q = fopen("Trash_Keywords/Trash.txt", "w");
    for (i = 0; i < data_size+1; i++){

	   if(i == data_size){
	   	fprintf(q,"%s", data[i]);
	   }
	   else
	   fprintf(q,"%s\n", data[i]);

    }
    fclose(q);
    printf("!!File data succesfully Sorted and Copied back to the database!!");

	return;
}

/*
	Organizing File Data function:

	This function actually organize the data into AVL Tree and
	efficiently finds the required element in O(nlogn) time complexity.
*/

int organizeFileData_SearchElement(char *element){

  FILE *p;
  char data[1000][1000];
  struct Node *root = NULL;

  p = fopen("Trash_Keywords/Trash.txt", "r");

  do
   {
      fscanf(p,"%s", &data);
      //printf("%s\n", data);
      root = insert(root, data);
      //printf("done");
   }
   while( !feof(p) );

 	fclose(p);
 	//printf("Ok");
  //printf("\n\n\n\t\t\t\t\t\tInorder traversal of the constructed AVL"
         //" tree is \n\n\n\n\t\t\t\t");
  //InOrder(root);

  //printf("\n\n\n\n\t\t\t\t");

  if(searchData(root,element) == 1){
  	//printf("Ok!!");

	  return 1;
  }
  else return 0;

}

/*
	This function helps in splitting up the sentances into words
	and filtering the sentimental and non sentimental words.
*/

void filterUnSentimentalWords(char *message){

    char split[1000][1000];
    int i,j,wordsCount,p=0;

    j=0; wordsCount=0;
    for(i=0;i<(strlen(message));i++)
    {
        if(message[i]==' '||message[i]=='\0' || message[i] == '\n')
        {
            split[wordsCount++][j]='\0';
            j=0;
        }

		else if((message[i] == ',') || (message[i] == ':') || (message[i] == '@') || (message[i] == '.') || (message[i] == '>')|| (message[i] == '<')
                || (message[i] == '=') || (message[i] == '-')|| (message[i] == ';') || (message[i] == '?') || (message[i] == '!') )
        {
            if ((i+1)==strlen(message)){
                split[wordsCount][j] = '\0';
            }
            else if(message[i+1]!=' '){
                continue;
            }
            else{

                split[wordsCount][j++]='\0';
            }
		}

        else if((message[i] == '"')|| (message[i] == '\'') )

            continue;

        else
        {
            split[wordsCount][j++]=message[i];
        }
    }
    split[wordsCount][j] = '\0';

    j = 0;

	for(i=0;i<wordsCount;i++){

		if(organizeFileData_SearchElement(toLower(split[i])) == 1){

            strcpy(nonSentimentalWords[p++],split[i]);
		}
		else{

			strcpy(sentimentalWords[j++],split[i]);
		}

	}
	no_of_NonSentimentalWords = p;
	no_of_sentimentalWords = j;
	return ;
}

/*
    function that accepts the 2 argument
    1. word
    2. a sentence.

    and returns the frequency of the word in that particular sentence.
*/

int frequencyOfSentimentInSentence(char *word, char *message){

    char split[1000][1000],temp[1000][1000];
    int i,j,wordsCount,c,previous,frequency;

    j=0; wordsCount=0;
    for(i=0;i<(strlen(message));i++)
    {
        if(message[i]==' '||message[i]=='\0' || message[i] == '\n')
        {
            split[wordsCount++][j]='\0';
            j=0;
        }

		else if((message[i] == ',') || (message[i] == ':') || (message[i] == '@') || (message[i] == '.') || (message[i] == '>')|| (message[i] == '<')
                || (message[i] == '=') || (message[i] == '-')|| (message[i] == ';') || (message[i] == '?') || (message[i] == '!') )
        {
            if ((i+1)==strlen(message) || (i+1)>strlen(message)){
                split[wordsCount][j] = '\0';
            }
            else if(message[i+1]!=' '){
                continue;
            }
            else{

                split[wordsCount][j++]='\0';
            }
		}
//
        else if((message[i] == '"')|| (message[i] == '\'') || (message[i] == '(' || (message[i] == ')')) )

            continue;

        else
        {
            split[wordsCount][j++]=message[i];
        }
    }
    split[wordsCount][j] = '\0';

    for(i=0;i<=wordsCount;i++){

        strcpy(split[i],toLower(split[i]));
    }

    for (i = 1; i < wordsCount; i++)
    {
        c = i;
        do
        {
            previous = (c - 1) / 2;
            if (stringcmp(split[previous],split[c])<0)
            {
                stringcpy(*temp, split[previous]);
                stringcpy(split[previous], split[c]);
                stringcpy(split[c], *temp);
            }
            c = previous;
        } while (c != 0);
    }

    for (j = wordsCount; j >= 0; j--)
    {
        stringcpy(temp, split[0]);
        stringcpy(split[0], split[j]);
        stringcpy(split[j], temp);
        previous = 0;
        do
        {
            c = 2 * previous + 1;
            if (stringcmp(split[c],split[c+1])<0 && c < j-1)
                c++;
            if (stringcmp(split[previous],split[c])<0 && c<j)
            {
                stringcpy(temp, split[previous]);
                stringcpy(split[previous], split[c]);
                stringcpy(split[c], temp);
            }
            previous = c;
        } while (c < j);
    }
//
    frequency = 0;
    j = wordsCount;

    for(i=0;i<=wordsCount;i++){

        if (strcmp(toLower(word),split[i])==0){
            j= i;
            frequency++;
        }
        else if(i>j){

            break;
        }
        else continue;

    }

    return frequency;
}

/*
    this function helps in finding the frequency of filtered sentiment in a database file.
*/

int frequencyOfSentimentInCorpus(char *sentiment, char *fileName){

    FILE *corpus;
    unsigned int frequency = 0,i;
    char sentence[2000][1000];
//
    corpus = fopen(fileName,"r");
    if(corpus == NULL){
        printf("File could not open!!");
    }

    i = 0;

    while(fgets(sentence[i++],sizeof(sentence),corpus)){

        //printf("%s",sentence[i-1]);
        frequency += frequencyOfSentimentInSentence(toLower(sentiment),sentence[i-1]);
    }
//
 	fclose(corpus);

    return frequency;
}

/*
    this function returns the size of corpus
*/

int sizeOfCorpus(char *fileName){

    FILE *corpus;
    corpus = fopen(fileName,"r");
    unsigned int corpusSize=0;
    char data[1000];

    while(fgets(data,1000,corpus)){

        corpusSize++;
    }

    fclose(corpus);

    return corpusSize;
}


/*
    Creating Structure for storing data of sentiment efficiently.
*/

struct dataForSentiment{

    char nameOfSentiment[100];
    int frequencyInAngry;
    int frequencyInSad;
    int frequencyInLove;
    int frequencyInVulgar;
    int frequencyInHappy;
};


/*
    Training The classifier to learn the Sentiments
*/

struct predictionProb train_bayesSentimentPredictionClassifier(){

    float probOfAngry,probOfSad,probOfHappy,probOfVulgar,probOfLove;
    struct dataForSentiment sentiment[no_of_sentimentalWords];
    int i=0,totalCorpusSize,totalAngryFreq=0,totalSadFreq=0,totalLoveFreq=0,totalVulgarFreq=0,totalHappyFreq=0;

    for(;i<no_of_sentimentalWords;i++){

        stringcpy(sentiment[i].nameOfSentiment,sentimentalWords[i]);
        sentiment[i].frequencyInAngry = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,angryFile);
        sentiment[i].frequencyInSad = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,sadFile);
        sentiment[i].frequencyInHappy = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,happyFile);
        sentiment[i].frequencyInVulgar = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,vulgarFile);
    }

    printf("\n\n\t\t\t-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t|  Sentiment\t|\tFreqInAngry (out of %d)\t|\tFreqInSad (out of %d)\t|\tFreqInHappy (out of %d)\t|\tFreqInVulagr      |\n",sizeOfCorpus(angryFile),sizeOfCorpus(sadFile),sizeOfCorpus(happyFile),sizeOfCorpus(vulgarFile));
    printf("\t\t\t---------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for(i=0;i<no_of_sentimentalWords;i++){

        printf("\t\t\t|  %s       \t|\t            %d            \t|\t     %d            \t|\t      %d            \t|\t     %d             |\n",sentiment[i].nameOfSentiment,sentiment[i].frequencyInAngry,sentiment[i].frequencyInSad,sentiment[i].frequencyInHappy,sentiment[i].frequencyInVulgar);

    }

    printf("\t\t\t---------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    totalCorpusSize = sizeOfCorpus(angryFile) + sizeOfCorpus(sadFile) + sizeOfCorpus(happyFile) + sizeOfCorpus(vulgarFile);

    for(i=0;i<no_of_sentimentalWords;i++){

        totalAngryFreq += sentiment[i].frequencyInAngry;
        totalSadFreq += sentiment[i].frequencyInSad;
        totalHappyFreq += sentiment[i].frequencyInHappy;
        totalVulgarFreq += sentiment[i].frequencyInVulgar;
        //Love and vulgar
    }

    probOfAngry = ((float)totalAngryFreq/(float)sizeOfCorpus(angryFile))*(((float)sizeOfCorpus(angryFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfSad = ((float)totalSadFreq/(float)sizeOfCorpus(sadFile))*(((float)sizeOfCorpus(sadFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfHappy = ((float)totalHappyFreq/(float)sizeOfCorpus(happyFile))*(((float)sizeOfCorpus(happyFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfVulgar = ((float)totalVulgarFreq/(float)sizeOfCorpus(vulgarFile))*(((float)sizeOfCorpus(vulgarFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/ (float)totalCorpusSize);


    printf("\n\t\t\tProbability for this sentence to be Angry is: %.4f",probOfAngry);
    printf("\n\t\t\tProbability for this sentence to be Sad is: %.4f",probOfSad);
    printf("\n\t\t\tProbability for this sentence to be Happy is: %.4f",probOfHappy);
    printf("\n\t\t\tProbability for this sentence to be Non-Decent is: %.4f\n",probOfVulgar);

    stringcpy(prediction[0].nameOfSentiment, "Angry Mood!!");
    prediction[0].predictionForSentence = probOfAngry;
    stringcpy(prediction[1].nameOfSentiment, "Sad Mood!!");
    prediction[1].predictionForSentence = probOfSad;
    stringcpy(prediction[2].nameOfSentiment, "Happy Mood!!");
    prediction[2].predictionForSentence = probOfHappy;
    stringcpy(prediction[3].nameOfSentiment, "Love Mood!!");
    prediction[3].predictionForSentence = 0;
    stringcpy(prediction[4].nameOfSentiment, "Non-Decent!!");
    prediction[4].predictionForSentence = probOfVulgar;

    return maxAmongPrediction(prediction);
}

struct predictionProb evaluate_bayesSentimentPredictionClassifier(){

    float probOfAngry,probOfSad,probOfHappy,probOfVulgar,probOfLove;
    struct dataForSentiment sentiment[no_of_sentimentalWords];
    int i=0,totalCorpusSize,totalAngryFreq=0,totalSadFreq=0,totalLoveFreq=0,totalVulgarFreq=0,totalHappyFreq=0;

    for(;i<no_of_sentimentalWords;i++){

        stringcpy(sentiment[i].nameOfSentiment,sentimentalWords[i]);
        sentiment[i].frequencyInAngry = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,angryFile);
        sentiment[i].frequencyInSad = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,sadFile);
        sentiment[i].frequencyInHappy = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,happyFile);
        sentiment[i].frequencyInVulgar = frequencyOfSentimentInCorpus(sentiment[i].nameOfSentiment,vulgarFile);
    }

    totalCorpusSize = sizeOfCorpus(angryFile) + sizeOfCorpus(sadFile) + sizeOfCorpus(happyFile) + sizeOfCorpus(vulgarFile);

    for(i=0;i<no_of_sentimentalWords;i++){

        totalAngryFreq += sentiment[i].frequencyInAngry;
        totalSadFreq += sentiment[i].frequencyInSad;
        totalHappyFreq += sentiment[i].frequencyInHappy;
        totalVulgarFreq += sentiment[i].frequencyInVulgar;
    }

    probOfAngry = ((float)totalAngryFreq/(float)sizeOfCorpus(angryFile))*(((float)sizeOfCorpus(angryFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfSad = ((float)totalSadFreq/(float)sizeOfCorpus(sadFile))*(((float)sizeOfCorpus(sadFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfHappy = ((float)totalHappyFreq/(float)sizeOfCorpus(happyFile))*(((float)sizeOfCorpus(happyFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/(float)totalCorpusSize);

    probOfVulgar = ((float)totalVulgarFreq/(float)sizeOfCorpus(vulgarFile))*(((float)sizeOfCorpus(vulgarFile)/(float)totalCorpusSize))/

                                ((float) (totalAngryFreq + totalSadFreq + totalHappyFreq + totalVulgarFreq)/ (float)totalCorpusSize);


    stringcpy(prediction[0].nameOfSentiment, "Angry Mood!!");
    prediction[0].predictionForSentence = probOfAngry;
    stringcpy(prediction[1].nameOfSentiment, "Sad Mood!!");
    prediction[1].predictionForSentence = probOfSad;
    stringcpy(prediction[2].nameOfSentiment, "Happy Mood!!");
    prediction[2].predictionForSentence = probOfHappy;
    stringcpy(prediction[3].nameOfSentiment, "Love Mood!!");
    prediction[3].predictionForSentence = 0;
    stringcpy(prediction[4].nameOfSentiment, "Non-Decent!!");
    prediction[4].predictionForSentence = probOfVulgar;

    return maxAmongPrediction(prediction);
}

void test_EfficiencyOfClassifier(){

    int countOfCorrectPrediction=0,no_of_prediction=0,i=0;
    char sentence[2000][1000];
    float efficiency;
    FILE *corpus;

    corpus = fopen("angry_sentiment/Test_Data/sentence.txt","r");
    if(corpus==NULL){
        printf("File not Found!!");
    }

    while(fgets(sentence[i++],sizeof(sentence),corpus)){

        no_of_prediction++;
        filterUnSentimentalWords(sentence[i-1]);
        if(no_of_sentimentalWords == 0) printf("\n\t\t\t\tNeurtal Sentence!!");
        else {

            if(strcmp("Angry Mood!!",evaluate_bayesSentimentPredictionClassifier().nameOfSentiment) == 0){

                printf("#");
                countOfCorrectPrediction++;
            }
        }

    }

    //printf("\n%.f\n", (float)( (float)countOfCorrectPrediction / (float)no_of_prediction)*100);
    fclose(corpus);

    corpus = fopen("happy_sentiment/Test_Data/sentence.txt","r");
    if(corpus==NULL){
        printf("File not Found!!");
    }

    while(fgets(sentence[i++],sizeof(sentence),corpus)){

        no_of_prediction++;
        filterUnSentimentalWords(sentence[i-1]);
        if(no_of_sentimentalWords == 0) printf("\n\t\t\t\tNeurtal Sentence!!");
        else {

            if(strcmp("Happy Mood!!",evaluate_bayesSentimentPredictionClassifier().nameOfSentiment) == 0){

                printf("$");
                countOfCorrectPrediction++;
            }
        }

    }

    //printf("\n%.f\n", (float)( (float)countOfCorrectPrediction / (float)no_of_prediction)*100);
    fclose(corpus);

    corpus = fopen("sad_sentiment/Test_Data/sentence.txt","r");
    if(corpus==NULL){
        printf("File not Found!!");
    }

    while(fgets(sentence[i++],sizeof(sentence),corpus)){

        no_of_prediction++;
        filterUnSentimentalWords(sentence[i-1]);
        if(no_of_sentimentalWords == 0) printf("\n\t\t\t\tNeurtal Sentence!!");
        else {

            if(strcmp("Sad Mood!!",evaluate_bayesSentimentPredictionClassifier().nameOfSentiment) == 0){

                printf("@");
                countOfCorrectPrediction++;
            }
        }

    }

    //printf("\n%.f\n",(float)( (float)countOfCorrectPrediction / (float)no_of_prediction)*100);
    fclose(corpus);

    corpus = fopen("vulgar_sentiment/Test_Data/sentence.txt","r");
    if(corpus==NULL){
        printf("File not Found!!");
    }

    while(fgets(sentence[i++],sizeof(sentence),corpus)){

        no_of_prediction++;
        filterUnSentimentalWords(sentence[i-1]);
        if(no_of_sentimentalWords == 0) printf("\n\t\t\t\tNeurtal Sentence!!");
        else {

            if(strcmp("Non-Decent!!",evaluate_bayesSentimentPredictionClassifier().nameOfSentiment) == 0){

                printf("*");
                countOfCorrectPrediction++;
            }
        }

    }

    efficiency = ((float)countOfCorrectPrediction / (float)no_of_prediction);
    printf("\n\t\t\t\t%.4f(%)\n", efficiency*100);
    fclose(corpus);

    return ;

}


