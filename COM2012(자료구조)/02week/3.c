#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char word[30];
    int length;
    bool palindrome=true;

    printf("문자열 입력 : ");
    scanf("%s", word);

    length=strlen(word);

    for (int i=0; i<length/2; i++){
        if (word[i]!=word[length-i-1]){
            palindrome=false;
            break;
        }
    }
    printf("%d\n", palindrome);
}