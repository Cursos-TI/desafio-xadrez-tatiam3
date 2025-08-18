#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Versão bem básica de xadrez em C
// Apenas mostra o tabuleiro e permite mover peças sem validar regras

#define BOARD_SIZE 64

static inline int idx(int r, int c) { return r * 8 + c; }

void print_board(const char b[BOARD_SIZE]){
    printf("\n    a   b   c   d   e   f   g   h\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    for(int r=7;r>=0;--r){
        printf("%d |", r+1);
        for(int c=0;c<8;++c){
            char p=b[idx(r,c)];
            if(p==' ') p='.';
            printf(" %c |", p);
        }
        printf(" %d\n", r+1);
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    a   b   c   d   e   f   g   h\n\n");
}

int parse_square(const char *s){
    if(strlen(s)<2) return -1;
    char f=tolower(s[0]);
    char r=s[1];
    if(f<'a'||f>'h'||r<'1'||r>'8') return -1;
    int file=f-'a';
    int rank=r-'1';
    return idx(rank,file);
}

void starting_position(char b[BOARD_SIZE]){
    const char *start=
        "rnbqkbnr"
        "pppppppp"
        "        "
        "        "
        "        "
        "        "
        "PPPPPPPP"
        "RNBQKBNR";
    for(int i=0;i<BOARD_SIZE;i++) b[i]=start[i]==" "[0]? ' ' : start[i];
}

int main(){
    char b[BOARD_SIZE]; starting_position(b);
    char input[32];

    printf("Xadrez básico em C (sem regras, apenas mover)\n");
    print_board(b);

    while(1){
        printf("> Digite movimento (ex: e2e4) ou quit: ");
        if(!fgets(input,sizeof(input),stdin)) break;
        size_t n=strlen(input);
        while(n>0 && (input[n-1]=='\n' || input[n-1]=='\r')) input[--n]='\0';
        if(strcmp(input,"quit")==0) break;
        if(n<4){ printf("Comando inválido.\n"); continue; }
        int from=parse_square(input);
        int to=parse_square(input+2);
        if(from<0||to<0){ printf("Posição inválida.\n"); continue; }
        b[to]=b[from];
        b[from]=' ';
        print_board(b);
    }
    return 0;
}
