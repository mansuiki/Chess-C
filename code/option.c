#include "option.h"
int askForPlayerSide()
{
    int n;
    while(1) {
        printf("흰색과 검은색중 플레이할 편을 골라주십시오 [W/B] : ");
        scanf(" %c",&n);
        if (n == 'W' || n=='w')
        {
            printf("흰색으로 플레이합니다\n");
            return 0;
        }
        else if (n == 'B' || n=='b')
        {
            printf("검은색으로 플레이합니다\n");
            return 1;
        }
        else
            printf("잘못 선택하셨습니다. 다시 선택해주시기 바랍니다.\n");
    }
}
int askForDepthOfAI()
{
    int depth;
    printf("\nAI의 난이도를 설정합니다 (1,2,3 단계) : ");
    scanf("%d",&depth);
    printf("AI %d 단계로 설정되었습니다.\n",depth);
}
int setChessGameMode()
{
    int n;
    while(1) {
        printf("\n게임 모드를 설정합니다.\n");
        printf("1. 1Player\n");
        printf("2. 2Player\n");
        scanf("%d", &n);
        if (n == 1) {
            printf("1Player 로 플레이 합니다. AI와 대결합니다\n");
            return 0;
        }
        else if (n == 2) {
            printf("2Player 로 플레이 합니다.\n");
            return 1;
        }
        else
            printf("잘못 선택하셨습니다. 다시 선택해주시기 바랍니다.\n");
    }
}