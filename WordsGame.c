#include <stdio.h>
#include <signal.h>
#include <Windows.h>
#include <time.h>

#define max 200
typedef struct card{
    char w1[max];
    char w2[max];
}card;

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    char tstr[2], buf[max];
    int n=1;

    char fichier[100];
    while(n) {
        printf("Mettez le nom de fichier, par exemple, si le fichier s'appelle \"words.txt\", mettez juste \"words\".\n ▷  ");
        scanf("%s", &fichier);
        fflush(stdin);
        strcat(fichier, ".txt");

        FILE *fp = fopen(fichier, "r");
        if (fp == NULL) {
            printf("Manque de fichier. Il faut mettre le logiciel et le fichier dans le même dossier.\n"
                   "Et quand vous entrez le nom du fichier il faut respecter les majuscules et les minuscules.\n");
            scanf(buf);
        }

        int count = 0;
        card t; //temporaire, buffer



        while (!feof(fp)) {
            fgets(t.w1, max, fp);
            fgets(t.w2, max, fp);
            //printf("[%s] [%s]\n",t.w1,t.w2);
            fgets(tstr, 2, fp);
            if (t.w1[0] == '\n')break; //마지막에 무의미한 엔터키가 있을 경우 그냥 중단.
            count++;
        }


        rewind(fp); //파일포인터를 썼으면 되감기 필수. ㅜㅜ

        card sc[count]; //단어들이 저장될 배열 sc (StudyCard)


        for (int i = 0; i < count; i++) {
            fgets(buf, max, fp);
            if (buf[0] == '\n')break;
            strcpy(sc[i].w1, buf);
            fgets(sc[i].w2, max, fp);
            fgets(tstr, 2, fp);

        }
/*
    printf("\ncheck\n");
    for(int i=0; i<count; i++){
        printf("1:%s2:%s\n",sc[i].w1, sc[i].w2);
    }
*/

        // shuffle the cards
        srand(time(NULL));
        int idx1, idx2;
        for (int i = 0; i < count; i++) {
            idx1 = rand() % count;
            do {
                idx2 = rand() % count;
            } while (idx1 == idx2);
            t = sc[idx1];
            sc[idx1] = sc[idx2];
            sc[idx2] = t;
        }
/*
    printf("\ncheck!\n");
    for(int i=0; i<count; i++){
        printf("1:%s2:%s\n",sc[i].w1, sc[i].w2);
    }
*/
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("\n-------------------------------------------\n");
        printf("|          W O R D S     G A M E           |\n");
        printf("-------------------------------------------\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf(" Il y a %d questions.\n", count);


        //study
        for (int i = 0; i < count; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            printf("\n\n-------n.%d---------------------------------\n", i + 1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("▷  %s\n   ", sc[i].w1);
            scanf(buf);
            fflush(stdin);
            printf("▶  %s\n", sc[i].w2);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            printf("-------------------------------------------\n\n\n");
            if (i == count - 1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                printf("\nla fin  끝\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }

        }


        scanf(buf);
        fflush(stdin);
        fclose(fp);
        printf("Si vous voulez continuer, entrer n'importe quel caractère sauf 0. Si Vous voulez finir, entrer \"0\"\n" );
        printf("▷ ");
        scanf("%d",&n);
        fflush(stdin);
    }
    return 0;
}
