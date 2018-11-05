// Design and implement a lexical analyser for given lang using C
// and lex analyser should ignore redundant implemenation of space, tab and newline

#include <stdio.h>
#include <string.h>

#define MAX_WORD 10000

enum tokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    DELIMITER
};

char* getTypeName(int type) {
    switch(type) {
        case KEYWORD:
            return "Keyword";
        case IDENTIFIER:
            return "Identifier";
        case OPERATOR:
            return "Operator";
        case DELIMITER:
            return "Delimiter";
    }
}

struct token {
    int type;
    char name[100];
};

// Function that takes array list of words and return number of words read
// Aguments the file to read from and the array of words
int getWords(FILE *fp, char words[MAX_WORD][100]) {
    FILE *fo = fopen("output.txt", "w");
    int num = 0;
    while(fscanf(fp, "%s", words[num++]) == 1) {
        fprintf(fo, "%s", words[num-1]);

        if(words[num - 1][ strlen(words[num - 1])-1 ] == ';') {
            words[num - 1][ strlen(words[num - 1])-1 ] = '\0';
            strcpy(words[num++], ";");
        }

    }
    return num - 1; // Last word is just a newline
}

const int NUM_KEYWORDS = 10;
const char keywords[10][100] = {
    "#include",
        "if",
        "else",
        "while",
        "const",
        "for",
        "void",
        "int",
        "double",
        "char"
};

const int NUM_OPERATORS = 5;
const char operators[10][100] = {
    "+",
        "-",
        "*",
        "=",
        "/",
};

const int NUM_DELIMITER = 5;
const char delimiter[10][100] = {
    ";",
        "{",
        "}",
        "[",
        "]",
};

int getToken(char word[]) {

    for(int i = 0; i < NUM_KEYWORDS; ++i) {
        if(strcmp(keywords[i], word) == 0) {
            return KEYWORD;
        } else if(strcmp(operators[i], word) == 0) {
            return OPERATOR;
        } else if(strcmp(delimiter[i], word) == 0) {
            return DELIMITER;
        }

    }
    return IDENTIFIER;

}

int main(int argc, char* argv[]) {

    if(argc < 2) {
        return 1;
    }
    char* filename = argv[1];

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("===== FILE ===== \n\n");
    // Print file
    char c = fgetc(fp);
    while (c != EOF) {
        printf ("%c", c);
        c = fgetc(fp);
    }
    printf("\n===== FILE ===== \n\n");
    // Reset file pointer to start
    rewind(fp);

    char words[MAX_WORD][100];
    int word_num = 0;
    struct token tokens[100];

    word_num = getWords(fp, words);

    for(int i = 0; i < word_num; ++i) {
        strcpy(tokens[i].name, words[i]);
        tokens[i].type = getToken(words[i]);
    }

    for(int i = 0; i < word_num; ++i) {
        printf("%s - %s\n", getTypeName(tokens[i].type), tokens[i].name);
    }


    fclose(fp);

    return 0;
}
