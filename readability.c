#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int coleman_liau_func(int word_count, int char_count, int sent_count);
int get_word_count(string text);
int get_sent_count(string text);
bool is_punc(char c);
int get_letter_count(string text);
void print_result(int index);

int main(void)
{
    //Prompt user for the text
    string text = get_string("Text: ");
    //Run the algorithm's to get the stat's from the teext
    int word_count = get_word_count(text);
    int letter_count = get_letter_count(text);
    int sent_count = get_sent_count(text);
    //Calculate the Coleman-liau index
    int index = coleman_liau_func(word_count, letter_count, sent_count);
    //Print the result based on what the description in the program asks for
    print_result(index);
}
/*
    Function that does the computation of the Coleman-Liau Index
*/
int coleman_liau_func(int word_count, int letter_count, int sent_count)
{
    float letter_per_hundred_words = (float)(letter_count) / word_count * 100;
    float sent_per_hundred_words = (float)(sent_count) / word_count * 100;

    int coleman_liau_index = 0.0588 * letter_per_hundred_words - 0.296 * sent_per_hundred_words - 15.8;
    //Need 2 version's of the index that way you can use them to round up
    float index = 0.0588 * letter_per_hundred_words - 0.296 * sent_per_hundred_words - 15.8;
    //Runs a check to see if the index needs to be rounded up
    if (index - (float) coleman_liau_index >= 0.5)
    {
        coleman_liau_index++;
    }
    return coleman_liau_index;
}
/*
    Function that gets the number of words in the text
*/
int get_word_count(string text)
{
    int count = 0;
    //Run a for loop through all of the text and count when there is a space
    //this will give us an accurate count of the words
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    //Add 1 to the count for the last word in the string that did not get counted
    count++;
    return count;
}
/*
    Function that gets the number of sentences in the text
*/
int get_sent_count(string text)
{
    int count = 0;
    //For loop that runs through the string and counts the punctuation marks
    //in the string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (is_punc(text[i]))
        {
            count++;
        }
    }
    return count;
}

/*
     Helper Function that checks for puncuation that ends a sentence
*/
bool is_punc(char c)
{
    return c == '.' || c == '?' || c == '!';
}

/*
    Function that gets the number of letters in the text
*/
int get_letter_count(string text)
{
    int count = 0;
    //For loop that checks if each char is part of the alphabet
    //increments count if so
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

/*
    Prints the final output telling the user the grade level
    of the text
*/
void print_result(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}