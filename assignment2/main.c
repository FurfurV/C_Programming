#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**quiz night assignment by Viktoria Cseke
*
*/

int main(void) {
    FILE *infile;
    FILE *outfile;

    char **question = NULL;
    char **answer = NULL;
    char **shuffle = NULL;

    char line[250];
    char q[60];
    char myFile[100] = "";
    char userAnswer[80] = "";

    int counter = 0;
    int count = 0;
    int llen;
    int llen2;
    int j;
    int ch;
    int points = 0;

    printf("Welcome to Quiz night!\n");
    printf("Enter file name:");
    scanf("%s", myFile);

//if file not found, print error
    if ((infile = fopen(myFile, "r")) == NULL) {
        printf("File not found 😕\n");
        exit(1);
    }
//get questions and answers into the arrays.
    while ((ch = fgetc(infile)) != EOF) {
        q[count] = 0;

        if (ch == '?') {
            llen2 = count;
            //allocate memory for questions
            question = realloc(question, (counter) * sizeof(char *)+1);

            question[counter] = calloc(sizeof(char*), llen2);

            strcpy(question[counter], q);

            while ((fgets(line, llen2, infile)) != NULL) {

                //get rid of the space at front and end
                sscanf(line, "%s", line);

                // Allocate memory for pointer to line 
                answer = realloc(answer, (counter) * sizeof(char *)+1);
                shuffle = realloc(shuffle, (counter) * sizeof(char *)+1);

                // And allocate memory for that line itself!
                llen = strlen(line);
                answer[counter] = calloc(sizeof(char), llen);
                shuffle[counter] = calloc(sizeof(char), sizeof(answer));

                // Copy the line just read into that memory
                strcpy(answer[counter], line);
                strcpy(shuffle[counter], answer[counter]);

                // printf("%d characters in line %d \n",llen,counter);
                counter++;
                break;
            }
            count = 0;

        } else {
            q[count] = ch;
            count++;
        }
    }

//------------------creating an array in the range of the questions count, and randomizing the numbers-----------
// printf("%lu",sizeof(counter));
    int *indexing = malloc(counter * sizeof(int));
    
      if (indexing == NULL) {
        fprintf(stderr, "malloc failed\n");
        return -1;
      }

    int x;
    int h=0;

    srand(time(NULL));//to make it really random each time
    while(h<counter){
      int r=rand()%counter+1;
      r=r-1;

    for (x = 0; x < h; x++)
    {
      if(indexing[x]==r){
          break;
      }
    }
      if(x==h){
          indexing[h++]=r;
          // printf("%d-------r\n",r);
        }
    }

    //---------------check if the file was read in properly.----------------
    //   for (j = 0; j <= counter - 1; j++) {

    //       //check corresponding questions
    //       printf("%s?\n",question[j]);

    //       //prints the answers
    //       printf("%s\n", answer[j]);

    //       //check answer lengths
    //       printf("%lu\n\n", strlen(answer[j]));
    // }


//total number of questions.
    printf("\nTotal number of questions: %d\n", counter);

    char difficulty;
    char wrong[30];

//----------------------------menu-----------------
    printf("══════════════════════════════════════\n");
    printf("\nDifficulty levels available:\n");
    printf("\t1. No clue given.\n");
    printf("\t2. Dashes shown for the letters.\n");
    printf("\t3. First and last character is shown.\n");
    printf("\t4. Two random letters are shown.\n");
    printf("\t5. Scrabbled letters are shown.\n");
    printf("\t6. Random difficulty.\n");
    printf("═══════════════════════════════════════\n");
    printf("Enter choice: \n");

    scanf(" %c", &difficulty); //get difficulty from the user

    if (difficulty == '6') { //if user enters 6, get a random difficulty from 1 to 5
        srand(time(NULL)); //avoid uniformity
        
        int num = (rand() % (5 - 1 + 1)) + 1;

        printf("Your random difficulty is: %d ", num);
        difficulty = num + '0'; //change int num into char
    }

    points = 0; 
    switch (difficulty) {
//-----------------------1. No clue given-----------------
        case '1' :
            for (int v = 0; v < counter; v++) { //loop through the array
                int c = v;
                c += 1;
                
                printf("---------------------------------");
                printf("\n%s?\n", question[indexing[v]]);
                printf("?\n"); //no clue, only a question mark

                printf("\n>> ");

                scanf("%s", userAnswer);

                if (strcasecmp(answer[indexing[v]], userAnswer) == 0) //compare answers, not case sensitive
                {
                    printf("\nYes! Well done!");
                    wrong[indexing[v]]=-9; //placeholder in the array
                    points += 1; //add point for correct answer
                    
                    // printf("%d\n",wrong[v]);
                }else{
                  wrong[indexing[v]]+=indexing[v]; //store the number of wrong answer
                }
                // printf("%d\n",wrong[v]);
                printf("%d/%d\n", points, c);
            }
            printf("\ntotal points: %d", points);
            break;

//---------------2. Dashes shown for the letters-----------------
        case '2':

            for (int v = 0; v < counter; v++) { //loop through the array
                int c = v;
                c += 1;
                printf("\n%s?\n", question[indexing[v]]);
                int length = 0;
                length = strlen(answer[indexing[v]]);

                for (j = 0; j < length; j++) {
                    putchar('-'); //draw the wanted pattern
                    putchar(' ');
                }

                printf("\n>> ");
                scanf("%s", userAnswer);

                if (strcasecmp(answer[indexing[v]], userAnswer) == 0)//compare answers, not case sensitive
                {
                    printf("\nYes! Well done!");
                    wrong[indexing[v]]=-9;
                    points += 1; //add point for correct answer
                }else{
                  wrong[indexing[v]]+=indexing[v];  //store the number of wrong answer
                }
                printf("%d/%d\n", points, c);
            }
            printf("\ntotal points: %d\n", points);
            break;
//---------------3. First and last character is shown-----------------
        case '3':

            for (int v = 0; v < counter; v++) { //loop through the array
                int c = v;
                c += 1;
                printf("\n%s?\n", question[indexing[v]]);
                int length;
                length = strlen(answer[indexing[v]]);


                for (j = 0; j < length; j++) {
                    if (j == 0) {
                        printf("%c ", answer[indexing[v]][0]); //print first char
                    } else if (j == length - 1) {
                        printf("%c ", answer[indexing[v]][length - 1]); //print last char
                    } else {
                        putchar('-'); //fill rest with the pattern
                        putchar(' ');
                    }
                }
                printf("\n>> ");
                scanf("%s", userAnswer);

                if (strcasecmp(answer[indexing[v]], userAnswer) == 0) //compare answers, not case sensitive
                {
                    printf("\nYes! Well done!\n");
                    wrong[indexing[v]]=-9;
                    points += 1; //add point for correct answer
                }else{
                  wrong[indexing[v]]+=indexing[v];  //store the number of wrong answer
                }
                printf("%d/%d\n", points, c);
            }
            printf("\ntotal points: %d\n", points);
            break;
//---------------4. Two random letters are shown-----------------
        case '4':

            for (int v = 0; v < counter; v++) { //loop through the array
                int c = v;
                c += 1;
                printf("\n%s?\n", question[indexing[v]]);
                int length;
                length = strlen(answer[indexing[v]]);

                // int lower=0;
                int upper = strlen(answer[indexing[v]]);

                srand(time(NULL)); //to avoid uniformity of answer
                int r = rand() % upper;
                int p = rand() % upper;

                while (r == p) { //if somehow both at same position, generate a new one
                    r = rand() % upper;
                    // printf("%d\n", r);
                    if (r != p) {
                        break;
                    }
                }
                int k;

                for (j = 0; j < length; j++) {
                    if (j == r) {
                        printf("%c ", answer[indexing[v]][r]); //put letters at its position
                    } else if (j == p) {
                        printf("%c ", answer[indexing[v]][p]);
                    } else {
                        putchar('-');  //fill rest with the pattern
                        putchar(' ');
                    }
                }

                printf("\n>> ");
                scanf("%s", userAnswer);

                if (strcasecmp(answer[indexing[v]], userAnswer) == 0) //compare answers, not case sensitive
                {
                    printf("\nYes! Well done!\n");
                    wrong[indexing[v]]=-9;
                    points += 1; //add point for correct answer
                }else{
                  wrong[indexing[v]]+=indexing[v];  //store the number of wrong answer
                }
                printf("%d/%d\n", points, c);
            }
            printf("\ntotal points: %d\n", points);
            break;
//---------------5. Scrabbled letters are shown-----------------
        case '5':

            for (int v = 0; v < counter; v++) { //loop through the array
                int c = v;
                c += 1;
                printf("\n%s?\n", question[indexing[v]]);
                int length;
                length = strlen(answer[indexing[v]]);

                srand(time(NULL)); //to avoid uniformity of

                int i;
                int m;
                for (i = 0; i < length; i++) {

                    m = rand() % length;

                    char temp = shuffle[indexing[v]][m];
                    shuffle[indexing[v]][m] = shuffle[indexing[v]][i];

                    shuffle[indexing[v]][i] = temp;
                    // printf(" %c",shuffle[v][i]);
                }
                for (i = 0; i < length; i++) {
                    printf("%c ", shuffle[indexing[v]][i]);
                }

                printf("\n>> ");
                scanf("%s", userAnswer);

                if (strcasecmp(answer[indexing[v]], userAnswer) == 0) //compare answers, not case sensitive
                {
                    printf("\nYes! Well done!\n");
                    wrong[indexing[v]]=-9;
                    points += 1; //add point for correct answer
                }else{
                  wrong[indexing[v]]+=indexing[v];  //store the number of wrong answer
                }
                printf("%d/%d\n", points, c);
            }
            printf("\ntotal points: %d\n", points);
            break;

        default:
            printf("hmm, thats not right, try again.\n");
    }
//---------------- Write to file-----------
    outfile = fopen("quiz_history.txt", "a"); //append to file

    fprintf(outfile, "Name of the quiz file: %s\n", myFile);
    fprintf(outfile, "Number of questions answered correctly: %d\n", points);
    fprintf(outfile, "Total number of questions: %d\n", counter);
    fprintf(outfile, "Difficulty level: %c\n", difficulty);

// -------------only to check if they are correct
    // printf("here\n");
    // printf("%s\n",myFile);
    // printf("%d\n",points);
    // printf("%d\n",counter);
    // printf("%c\n",difficulty);
    printf("\n═══════════════════════════════════════\n");
    printf("\nWant to check correct answers for questions that you got wrong? y/n\n");
    char ans;
    scanf(" %c", &ans);
    if(ans=='y'){
      for(int i=0;i<counter;i++){
        if(wrong[i]!= -9){
          printf("\n%s?\n",question[i]);
          printf("%s\n", answer[i]);
        }
      }
    }
    printf("\n(∗ ･‿･)ﾉ゛\t Thanks, bye!");
    
    free(question); //free the memory
    free(answer);
    free(indexing);

    exit(2);
    return 0;
}
