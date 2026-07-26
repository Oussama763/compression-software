#include <stdio.h>
#include<stdlib.h>
//#include <stdint.h>
#include <inttypes.h>


#define WINDOW 32768 // 32KB
#define LOOKAHEAD 258


typedef struct{
    int is_reference;
    uint8_t caracter;
    int distance;
    int length;
} LZ77Token;




int compress_LZ77(uint8_t *to_compress, int length_bytes, LZ77Token *tokens){ //you need to add arguments for this fundtion (check claude's suggestion)
    //int w_cursor_index = 0;
    uint8_t *window_cursor = to_compress;
    int la_cursor_index = 2;    //lookahead cursor index, how many caracters have we compressed

    LZ77Token first_token;
    LZ77Token second_token;

    first_token.is_reference = 0;
    first_token.caracter = *to_compress;
    first_token.distance = 0;
    first_token.length = 1;

    second_token.is_reference = 0;
    second_token.caracter = *(to_compress + 1);
    second_token.distance = 0;
    second_token.length = 1;

    *tokens = first_token;
    *(tokens + 1) = second_token;

    int token_count = 2;

    //to_compress = to_compress + la_cursor_index;

    while (la_cursor_index < length_bytes){
        int memo_index = 0; //this variable memorizes where we left off in the previous match so that we don't start over from the beginning
        int i = 0;
        int max_match = 0;
        int distance = 0;

        (*(tokens + la_cursor_index)).is_reference = 0; 
        (*(tokens + la_cursor_index)).caracter = *(to_compress + la_cursor_index);
        //(*(tokens + la_cursor_index)).distance = 0;
        //(*(tokens + la_cursor_index)).length = 1;

        while(memo_index < ((WINDOW < la_cursor_index) ? WINDOW : la_cursor_index)){
            int match_cursor = 0;
            while(*(to_compress + match_cursor) == *(window_cursor + match_cursor + memo_index) && match_cursor + la_cursor_index < length_bytes){
                match_cursor++;
                i++;
            }

            memo_index = i;  // I guess I can just use the "memo_index = match_max" I don't need "i" but that's okay 

            if(match_cursor > max_match){
                max_match = match_cursor;
                distance = la_cursor_index - (memo_index - max_match) - 1;
                /*
                I don't want to think too much about why did I substruct 1 at the end, instead I just
                took a simple example to make it right, since everything is linear here an example
                is enough to make any "translation"(linear transformation with scaling factor 1) right.
                Example:
                0 1 2 3 4 5 6 7 3 4 5 2
                          ^     ^       
                la_cursor_index = 8
                max_match = 3
                memo_index = 5
                */
            }
        }
        if(max_match > 1){
            (*(tokens + la_cursor_index)).is_reference = 1; 
            //(*(tokens + la_cursor_index)).caracter = *(to_compress + la_cursor_index);
            (*(tokens + la_cursor_index)).distance = distance;
            (*(tokens + la_cursor_index)).length = max_match;

            la_cursor_index += max_match;
        }
        la_cursor_index += 1;
        token_count++;      
    }                    
    return token_count;  
}    

int succerssor(int n){
    return n + 1;
}


int main(){
    /*LZ77Token token_list[3];
    for(int i = 0; i < 3; i++){
        scanf("%d", &token_list[i].is_reference);
        scanf("%hhu", &token_list[i].caracter);
        scanf("%d", &token_list[i].distance);
        scanf("%d", &token_list[i].length);
    }
    char mot[3];

    for(int i = 0; i < 3; i++){
        if(token_list[i].is_reference == 0){
            mot[i] = (char)(token_list[i].caracter);
        }
        else{
            
        }
    }
    printf("%s", mot);
    printf("%p", mot);*/
    int i = 5;
    printf("%d", succerssor(i));
    return 0;
}

// is there a difference between code1 and code2  

code1(){
    int x = 4;
    int *X = &x;
    int X_prime = X;
    int *Y = X_prime;
}

code2(){
    int x = 4;
    int *X = &x;
    int *Y = X;
}