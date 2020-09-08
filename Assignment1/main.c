#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
* Tries to read the file into the array.
* Each line has one value.
*
* Returns the number of lines read or -1 in case of file open error.
*/
int read_array_from_file(const char *filepath, int *arr, int array_length) {
    FILE *file;
    int i;
    if ((file = fopen(filepath, "r")) == NULL) return -1;
    for (i = 0; i < array_length; i++) {
        if (fscanf(file, "%d", &arr[i]) == EOF)
            break;
    }
    return i;
}

/**
* Generates a number of random lower case letters.
* The letters will be stored in the given array.
*/
void generate_letters(int number, char *destination) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int i;
    unsigned int rand_seed;
    printf("Enter seed number < 1000:\n");
    scanf("%d", &rand_seed); // initialise the PRNG
    getchar();

    srandom(rand_seed);
    // Half of the letters should be vowels
    for (i = 0; i < number / 2; i++, destination++) *destination = vowels[random() % 5];
    for (; i < number; i++, destination++) *destination = random() % 26 + 'a';
}

int main() {
  //Declare Variables
  char string[7][7], a, c; //2D array for storing strings
  int i = 0, z = 0, again = 1, count[26] = {0}, y, test = 1;
  int genNum = 7;
  int counter = 0;
  char destination[7];
  char temp_array[7];
  const char *filepath = "letter_values.txt";
  int arr[26], array_length = 26;
  int points[7], total_points, word_points=0, total_letters = 0;
  int x = 0, m;

    read_array_from_file(filepath, arr, array_length);

    //check if file with letter values is empty,
    if (arr[0] < 0) {
        printf("file is empty 🙁  ");
    } else {
        generate_letters(genNum, destination);

        //letters available to user with the corresponding amount.
        for (i = 0; i < strlen(destination); i++) {
            //printf("%c",destination[i]);
            temp_array[i] = destination[i];
            //printf("%c",destination[i]);
            count[destination[i] - 'a']++;
        }
        printf("\n════════════════════════════════");
        printf("\nYour letters (and their count) are:\n");
        for (i = 0; i < 26; i++) {
            if (count[i] > 0) {
                printf("%c --> %d\n", i + 'a', count[i]);
            }
        }
        printf("\n════════════════════════════════\n");

        //just to check if points are read in properly
        // for(i=0;i<26;i++){
        //   printf("%d\n",arr[i]);
        // }

        while (again) {
            //Read the string from user
            z++;
            word_points = 0;
            printf("Input word: ");
            scanf("%s", string[z]);

            //convert all userinput to lowercase
            for (i = 0; string[z][i] != '\0'; i++) {
                if (string[z][i] >= 'A' && string[z][i] <= 'Z') {
                    string[z][i] = string[z][i] + 32;

                }
            }

            /**calculate points for each word,
            *the total points,
            *and the total letters used.
            */
            while (test == 1) {

                for (int i = 0; i < 7; i++) {
                    //printf("%c",destination[i]);
                    //printf("%c", string[z][x]);
                    if (string[z][x] == temp_array[i]) {
                        temp_array[i] = destination[i - 21];
                        x = x + 1;
                        break;
                    }
                        //once the counter equals string length, we know that the letter matches the pool
                    else if ((int) (strlen(string[z])) == x) {
                        
                        for (i = 0; i < strlen(string[z]); i++) {
                          word_points=word_points+arr[string[z][i] - 97];
                          //word_points+=word_points;
                            //word_points += point;
                            //printf("%d",string[z][i]);
                            
                            //po+=word_points;
                            //printf("%d",points);
                            //printf("%d",po);
                            total_points += arr[string[z][i] - 97];
                            total_letters += 1;
                        }

                        points[z] =word_points;

                        printf("You used: %s. Worth %d, Total points %d", string[z], points[z], total_points);
                        test = -1;
                        x = 0;
                        break;
                    }
                        //if the letter is not found and i is at position 6, no points added for the word
                    else if (i == 6) {

                        printf("Sorry, but you need to use letters from the pool. letter \" %c \" is missing.",
                               string[z][x]);
                        test = 0;
                        break;
                    }
                }
            }

            printf("\nTry again? (y/n): ");
            scanf("%s", &a);
            if (a == 'n' || a == 'N') {
                again = 0;
            } else if (a == 'y' || a == 'Y') {

                for (i = 0; i < strlen(destination); i++) {
                    //add characters back to the temporary array
                    temp_array[i] = destination[i];
                }
                test = 1;
            } else {
                printf("hmm, please type only n or y\n");
                for (i = 0; i < strlen(destination); i++) {
                    //add characters back to the temporary array
                    temp_array[i] = destination[i];
                }
                test = 1;
            }
        }

        y = z + 1;
        printf("\n════════════════════════════════");
        printf("\nYou provided the following words: \n");

        for (z = 1; z < y; z++) {
            //Print the string at current index
            printf("%s --> %d\n", string[z], points[z]);
        }

        printf("Total score: %d", total_points);
        printf("\nTotal letters used: %d:", total_letters);
        printf("\n════════════════════════════════\n");

        //Return to the system
        return 0;
    }
}
