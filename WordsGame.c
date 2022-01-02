#include <stdio.h>
#include <signal.h>
#include <Windows.h> //Windows.h를 include한다. c언어와 c++의 경우.
#define max 200
typedef struct card{
    char w1[max];
    char w2[max];
}card;

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    char tstr[2], buf[max];

    FILE* fp = fopen("words.txt", "r");
    if(fp==NULL) {
        printf("Manque de fichier. Il faut \"words.txt\"\n");
        scanf(buf);
    }

    int count = 0;
    card t; //temporaire


    //printf("count1=%d\n",count);
    while(!feof(fp)){
        fgets(t.w1, max, fp);
        fgets(t.w2, max, fp);
        //printf("[%s] [%s]\n",t.w1,t.w2);
        fgets(tstr,2,fp);
        if(t.w1[0]=='\n')break; //마지막에 무의미한 엔터키가 있을 경우 그냥 중단.
        count++;
    }
    //printf("count2=%d\n",count);


    rewind(fp); //파일포인터를 썼으면 되감기 필수. ㅜㅜ

    card sc[count]; //단어들이 저장될 배열 sc (StudyCard)


    for(int i=0; i<count ; i++){
        fgets(buf, max, fp);
        if(buf[0]=='\n')break;
        strcpy(sc[i].w1, buf);
        fgets(sc[i].w2, max, fp);
        fgets(tstr,2,fp);

    }
/*
    printf("\ncheck\n");
    for(int i=0; i<count; i++){
        printf("1:%s2:%s\n",sc[i].w1, sc[i].w2);
    }
*/

    //카드섞기
    int idx1, idx2;
    for(int i=0; i<count; i++){
        idx1=rand()%count;
        do{
            idx2=rand()%count;
        }while (idx1==idx2);
        t=sc[idx1];
        sc[idx1]=sc[idx2];
        sc[idx2]=t;
    }
/*
    printf("\ncheck!\n");
    for(int i=0; i<count; i++){
        printf("1:%s2:%s\n",sc[i].w1, sc[i].w2);
    }
*/
    printf("-------------------------------------------\n");
    printf("|          W O R D S     G A M E           |\n");
    printf("-------------------------------------------\n");
    printf("--> Il y a %d questions \n",count);

    //study
    for(int i=0; i<count; i++){
        printf("\n\n-------n.%d---------------------------------\n",i+1);
        printf("  %s\n",sc[i].w1);
        scanf(buf);
        fflush(stdin);
        printf("  %s\n",sc[i].w2);
        printf("-------------------------------------------\n\n\n");
        if(i==count-1)printf("\nla fin  끝\n");
        fflush(stdin);
    }


    scanf(buf);
    fflush(stdin);
    fclose(fp);
    return 0;
}