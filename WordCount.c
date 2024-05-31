#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>  
#include <string.h>  
  
int is_word_separator(char c) {  
    return isspace(c) || c == ',';  
}  
  
int main(int argc, char *argv[]) {  
    if (argc != 3) {  
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);  
        return 1;  
    }  
  
    char *filename = argv[2];  
    FILE *file = fopen(filename, "r");  
    if (!file) {  
        perror("Error opening file");  
        return 1;  
    }  
  
    long char_count = 0;  
    int word_count = 0;  
    int in_word = 0;  
  
    char ch;  
    while ((ch = fgetc(file)) != EOF) {  
        char_count++;  
  
        if (is_word_separator(ch)) {  
            if (in_word) {  
                in_word = 0;  
                word_count++;  
            }  
        } else {  
            in_word = 1;  
        }  
    }  
  
    if (in_word) { // 如果文件末尾是单词的一部分，则也算作一个单词  
        word_count++;  
    }  
  
    fclose(file);  
  
    if (strcmp(argv[1], "-c") == 0) {  
        printf("%ld\n", char_count);  
    } else if (strcmp(argv[1], "-w") == 0) {  
        printf("%d\n", word_count);  
    } else {  
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);  
        return 1;  
    }  
  
    return 0;  
}