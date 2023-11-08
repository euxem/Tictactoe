#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "tictactoe.h"

void init_tab(POINT tab[3][3]){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            tab[i][j] = NOTHING;
        }
    }
    return;
}
void print_who_win(POINT team){
    if (team == CROSS){
        printf("\x1b[1mCross (\e[0;34mX\033[0m\x1b[1m) Win !\x1b[0m\n");
    }else{
        printf("\x1b[1mCercle (\e[0;31mO\033[0m\x1b[1m) Win !\x1b[0m\n");
    }
}

POINT verif_ligne(POINT tab[3][3]){
    for (int i=0; i<3; i++){
        if (tab[i][0] != NOTHING && tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]){
            print_who_win(tab[i][0]);
            return tab[i][0];
        }
    }
    return NOTHING;
}

POINT verif_colone(POINT tab[3][3]){
    for (int i=0; i<3; i++){
        if (tab[0][i] != NOTHING && tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]){
            print_who_win(tab[0][i]);
            return tab[0][i];
        }
    }
    return NOTHING;
}

POINT verif_diag(POINT tab[3][3]){
    if (tab[0][0] != NOTHING && tab[0][0] == tab[1][1] && tab[2][2] == tab[1][1]){
        print_who_win(tab[0][0]);
        return tab[0][0];
    }
    if (tab[0][2] != NOTHING && tab[0][2] == tab[1][1] && tab[2][0] == tab[1][1]){
        print_who_win(tab[0][2]);
        return tab[0][2];
    }
    return NOTHING;
}

POINT win_condition(POINT tab[3][3]){
    POINT var_win;
    var_win = verif_ligne(tab);
    if ( var_win != NOTHING){
        return var_win;
    }
    var_win = verif_colone(tab);
    if ( var_win != NOTHING ){
        return var_win;
    }
    var_win = verif_diag(tab);
    if ( var_win != NOTHING ){
        return var_win;
    }
    return NOTHING;
}

void print_plateau(POINT tab[3][3], int point[2]){
    printf("_______\n");
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            printf("|");
            if (point[0] == i && point[1] == j){
                printf(".");
            }else if (tab[i][j] == CROSS){
                printf("\e[0;34mX\033[0m");
            }else if (tab[i][j] == ROUND){
                printf("\e[0;31mO\033[0m");
            }else{
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("‾‾‾‾‾‾‾\n");
    return;
}

void premiere_case_libre(POINT tab[3][3],int point[2]){
    for (int i=0; i<3;i++){
        for (int j=0; j<3; j++){
            if (tab[i][j] == NOTHING){
                point[0]=i;
                point[1]=j;
                return;
            }
        }
    }
}

int ligne_test_droite(POINT tab[3][3],int point[2],int num){
    for (int i=0; i<3; i++){
        if (tab[num][i] == NOTHING){
            point[0]=num;
            point[1]=i;
            return 1;
        }
    }
    return 0;
}

int ligne_test_gauche(POINT tab[3][3],int point[2],int num){
    for (int i=2; i>=0; i--){
        if (tab[num][i] == NOTHING){
            point[0]=num;
            point[1]=i;
            return 1;
        }
    }
    return 0;
}

int ligne_test(POINT tab[3][3],int point[2],int num, int temp_pos){
    if (temp_pos == 2){
        return ligne_test_gauche(tab,point,num);
    }
    return ligne_test_droite(tab,point,num);
}

POINT play(POINT tab[3][3], POINT turn){
    if (turn == ROUND){
        printf("\x1b[1mCercle turn :\x1b[0m\n");
    }else{
        printf("\x1b[1mCross turn :\x1b[0m\n");
    }
    printf("Choose a case :\n");

    struct termios orig_termios, new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);

    int point[2];
    int temp_pos;
    premiere_case_libre(tab,point);
    temp_pos = point[1];
    char c;

    while (1) {
        print_plateau(tab, point);
        c = getchar();
        if (c == 27) {
            if (getchar() == 91) {
                switch (getchar()) {
                    case 65: // touche haut
                        if (point[0] == 2){
                            if (tab[1][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 1;
                            }else if (ligne_test(tab,point,1,temp_pos)){
                            }else if (tab[0][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 0;
                            }else if (ligne_test(tab,point,0,temp_pos)){
                            }
                        }else if (point[0] == 1){
                            if (tab[0][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 0;
                            }else if (ligne_test(tab,point,0,temp_pos)){
                            }
                        }
                        break;
                    case 66: // touche bas
                        if (point[0] == 0){
                            if (tab[1][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 1;
                            }else if (ligne_test(tab,point,1,temp_pos)){
                            }else if (tab[2][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 2;
                            }else if (ligne_test(tab,point,2,temp_pos)){
                            }
                        }else if (point[0] == 1){
                            if (tab[2][temp_pos] == NOTHING){
                                point[1] = temp_pos;
                                point[0] = 2;
                            }else if (ligne_test(tab,point,2,temp_pos)){
                            }
                        }
                        break;
                    case 67:
                        if (point[1] == 0){
                            if (tab[point[0]][1] == NOTHING){
                                point[1]=1;
                            }else if (tab[point[0]][2] == NOTHING){
                                point[1]=2;
                            }
                        }else if (point[1] == 1){
                            if (tab[point[0]][2] == NOTHING){
                                point[1]=2;
                            }
                        }
                        temp_pos = point[1];
                        break;
                    case 68:
                        if (point[1] == 2){
                            if (tab[point[0]][1] == NOTHING){
                                point[1]=1;
                            }else if (tab[point[0]][0] == NOTHING){
                                point[1]=0;
                            }
                        }else if (point[1] == 1){
                            if (tab[point[0]][0] == NOTHING){
                                point[1]=0;
                            }
                        }
                        temp_pos = point[1];
                        break;
                }
            }
        } else if (c == '\n') {
            tab[point[0]][point[1]]=turn;
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
            return (turn+1)%2;
        } else if (c == 4) {  // 4 correspond à Ctrl+D (EOF)
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
            exit(0);
        }
        printf("\x1b[5A");
    }
}

POINT start_menu(){
    struct termios orig_termios, new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);

    printf("\x1b[1mThe Tic-Tac-Toe Game !\n\x1b[0m");
    printf("Who play first ?\n");
    printf("● Cross\n○ Cercle\n");
    char c;
    POINT choice=CROSS;
    while (1)
    {
        c = getchar();
        if (c == 27) {
            if (getchar() == 91) {
                switch (getchar())
                {
                case 65:
                    if (choice == ROUND){
                        printf("\x1b[2A");
                        printf("● Cross\n○ Cercle\n");
                        choice = CROSS;
                    }
                    break;
                case 66:
                    if (choice == CROSS){
                        printf("\x1b[2A");
                        printf("○ Cross\n● Cercle\n");
                        choice = ROUND;
                    }
                default:
                    break;
                }
            }
        }else if (c == '\n'){
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
            printf("\x1b[4A");
            printf("                        \n                  \n                  \n                  \n");
            printf("\x1b[4A");
            return choice;
        }else if (c == 4){ // 4 correspond à Ctrl+D (EOF)
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
            exit(0);
        }
    }    
}

int main(){
    POINT games_tab[3][3];
    POINT start_turn = start_menu();
    int finish = 1;
    char number_play;
    number_play = 0;
    init_tab(games_tab);
    while (finish && number_play < 9){
        start_turn = play(games_tab, start_turn);
        printf("\x1b[7A");
        printf("                  \n");
        printf("\x1b[1A");
        finish = (win_condition(games_tab) == NOTHING);
        number_play++;
    }
    if (finish) {
        printf("\x1b[1mNobody Win !\x1b[0m\n");
    }
    printf("                \n");
    printf("\x1b[1A");
    int tab[2]={-1, -1};
    print_plateau(games_tab,tab);
    return 0;
}
