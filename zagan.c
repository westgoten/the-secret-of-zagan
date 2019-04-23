#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define NUMBER_OF_CHAPTERS 3
#define MAX_NUMBER_OF_RINGS 3
#define MAX_RING_SIZE 5

typedef const char* Page;

typedef struct {
    const char *title;
    Page *pages;
    int numberOfPages;
    int isThereGameplayAfterIt;
} Chapter;

typedef struct {
    Chapter chapters[NUMBER_OF_CHAPTERS];
    int nextChapter;
} Story;

typedef struct {
    char* body;
    int size;
} Ring;

typedef struct {
    Ring rings[MAX_NUMBER_OF_RINGS];
    int top;
} Tower;

typedef struct {
    Tower leftTower;
    Tower middleTower;
    Tower rightTower;
} HanoiBoard;

enum GameMode {
    STORY,
    GAMEPLAY,
    ENDGAME
} gameMode;

void initializeStory(Story *story);

void introduction();

void storyMode(Story *story);

void gameplayMode();

void endgame();

void printChapterTitle(Chapter chapter);

int hasWonHanoiGame(HanoiBoard *board);

int moveRing(Tower *sourceTower, Tower *destTower);

void initializeHanoiBoard(HanoiBoard *board);

void printHanoiBoard(HanoiBoard *board);

void printStones();

void pushRingToTower(Tower *tower, Ring ring);

Ring popRingFromTower(Tower *tower);

Ring peekTower(Tower *tower, int position);

int isTowerEmpty(Tower *tower);

int isTowerFull(Tower *tower);

void initializeTower(Tower *tower);

void initializeRing(Ring *ring, int size);

int main() {
    setlocale(LC_ALL, "");

    Story story;
    int running = 1;
    gameMode = STORY;

    initializeStory(&story);
    introduction();
    while (running) {
        switch (gameMode) {
            case STORY:
                storyMode(&story);
                break;
            case GAMEPLAY:
                gameplayMode();
                break;
            case ENDGAME:
                endgame();
                running = 0;
                break;
            default:
                printf("\nAlgum erro inusitado surgiu\n");
                running = 0;
        }
    }

    return 0;
}

void initializeStory(Story *story) {
    story->nextChapter = 0;

    Chapter *chapter1 = &(story->chapters[0]);
    chapter1->title = "Prólogo";
    chapter1->isThereGameplayAfterIt = 0;
    chapter1->numberOfPages = 4;
    chapter1->pages = (Page*) malloc(chapter1->numberOfPages * sizeof(Page));
    chapter1->pages[0] = "A história se passa em Jormungand, lar de todos \
os reinos e seres. \n\nAntes de existirem civilizações na superfície do \
mundo, nasceu Zagan, conhecida como a Árvore Sagrada, que é a terceira \
árvore detentora de todo o saber e responsável por guiar os reis \
portadores do Olho de Aurelius, um artefato tão antigo quanto a própria \
Jormungand.";
    chapter1->pages[1] = "Cada Árvore Sagrada é capaz de guiar apenas um rei. Em seguida, ela \
morre e dá lugar a uma nova árvore, que gera um novo Olho de Aurelius \
e guiará o próximo rei. Até então, apenas 2 reinos foram guiados por \
uma Árvore Sagrada: Svartalfheim, a primeira das civilizações, e Naza, \
o reino dos humanos.";
    chapter1->pages[2] = "Há séculos, o reino vulcânico de Muspelheim \
tenta roubar o Olho de Aurelius dos humanos, mas nunca tiveram sucesso. \
Amon, o rei de Muspelheim, nunca foi capaz de falar com uma Árvore \
Sagrada por não possuir um Olho de Aurelius e tem inveja dos humanos \
por terem realizado tal feito.";
    chapter1->pages[3] = "Um dia, numa das mais fartas primaveras \
que a população de Naza já presenciou, uma repentina calamidade \
aconteceu: os solos e rios do reino tornaram-se estéreis. Após algumas \
semanas, descobriu-se que o Olho de Aurelius havia sido roubado. \
Apenas o rei e seus conselheiros mais leais sabiam da existência do \
artefato.";

    Chapter *chapter2 = &(story->chapters[1]);
    chapter2->title = "A jornada";
    chapter2->isThereGameplayAfterIt = 0;
    chapter2->numberOfPages = 4;
    chapter2->pages = (Page*) malloc(chapter2->numberOfPages * sizeof(Page));
    chapter2->pages[0] = "3 anos se passaram e Naza está sofrendo com uma grande escassez de alimentos, \
tendo conseguido sobreviver através do comércio e da importação de alimentos, \
mas a população tem diminuído consideravelmente ao longo desses anos.";
    chapter2->pages[1] = "Um sábio \
chamado Baldur, descobriu a existência de um antigo poder, e percebeu que \
encontrar esse poder era a chave para salvar Naza, seu reino natal. Depois de \
muitos estudos, ele descobriu que o poder que ele tanto buscava era Zagan, a \
Árvore Sagrada.";
    chapter2->pages[2] = "Após tentar descobrir como encontrar Zagan, cuja tentativa \
fracassou, o sábio encontrou uma mulher, chamada Frigg, que também buscava \
uma maneira de salvar Naza. Ele a contou tudo o que ele conhecia sobre a Árvore Sagrada e \
como isso poderia ser a salvação do reino.";
    chapter2->pages[3] = "Então, a mulher lhe contou sobre um \
livro que está localizado em Svartalfheim, o reino subterrâneo dos elfos \
negros, e que irá ajudá-lo a encontrar o que ele procura.";

    Chapter *chapter3 = &(story->chapters[2]);
    chapter3->title = "A caverna";
    chapter3->isThereGameplayAfterIt = 1;
    chapter3->numberOfPages = 3;
    chapter3->pages = (Page*) malloc(chapter3->numberOfPages * sizeof(Page));
    chapter3->pages[0] = "Em busca do reino informado, Baldur encontra uma caverna no Deserto Vermelho, \
à sudoeste de Naza, na qual ele entra e segue em frente até parar em seu \
primeiro obstáculo.";
    chapter3->pages[1] = "À sua frente está uma grande rocha, que bloqueia a \
passagem. Próximo a ela, há 3 pedras retangulares, similares a pequenas \
caixas, uma ao lado da outra. Não há nada sobre as duas últimas pedras, mas \
sobre a primeira há 3 discos de tamanhos diferentes, empilhados de modo que \
o maior disco está na base e o menor disco está no topo.";
    chapter3->pages[2] = "Ao se aproximar da grande rocha, Baldur percebe \
que há uma mensagem escrita nela: 'Um movimento de cada vez. Todos eles \
migrarão. Da primeira para a terceira. A ordem persiste'. Baldur decide mover \
os discos.";
}

void introduction() {
    //system("tput reset"); // Linux only
    system("cls"); // Windows only
    printf("\n###############################################################\n");
    printf("#                                                             #\n");
    printf("#                                                             #\n");
    printf("#                     O SEGREDO DE ZAGAN                      #\n");
    printf("#                                                             #\n");
    printf("#                                                             #\n");
    printf("###############################################################\n");

    printf("\n\nPressione ENTER para jogar...");
    while (getchar() != '\n');
}

void storyMode(Story *story) {
    int pageNumber = 0;

    while (gameMode == STORY) {
        //system("tput reset"); // Linux only
        system("cls"); // Windows only
        Chapter currentChapter = story->chapters[story->nextChapter];
        printChapterTitle(currentChapter);

        if (pageNumber < currentChapter.numberOfPages) {
            printf("%s", currentChapter.pages[pageNumber]);
            printf("\n\nPressione ENTER para avançar...");
            while (getchar() != '\n');
            pageNumber++;
        }

        if (pageNumber >= currentChapter.numberOfPages) {
            pageNumber = 0;
            story->nextChapter++;

            if (currentChapter.isThereGameplayAfterIt) {
                gameMode = GAMEPLAY;
            } else if(story->nextChapter >= NUMBER_OF_CHAPTERS) {
                gameMode = ENDGAME;
            }
        }
    }
    printf("\n\n");
}

void gameplayMode() {
    HanoiBoard board;

    initializeHanoiBoard(&board);

    int running = 1;
    do {
        //system("tput reset"); // Linux only
        system("cls"); // Windows only
        printf("\n'Um movimento de cada vez. Todos eles \
migrarão. Da primeira para a terceira. A ordem persiste'\n\n");
        printHanoiBoard(&board);

        if (hasWonHanoiGame(&board)) {
            printf("\nBaldur: 'A caverna está tremendo!'\n");
            while (getchar() != '\n');
            printf("\nPressione ENTER para avançar...");
            while (getchar() != '\n');
            gameMode = ENDGAME;
            break;
        }

        printf("Retirar disco de qual pedra? ");
        int sourceStoneNumber;
        scanf("%d", &sourceStoneNumber);
        printf("Colocar disco em qual pedra? ");
        int destStoneNumber;
        scanf("%d", &destStoneNumber);

        Tower *sourceTower = NULL, *destTower = NULL;
        switch (sourceStoneNumber) {
            case 1:
                sourceTower = &board.leftTower;
                break;
            case 2:
                sourceTower = &board.middleTower;
                break;
            case 3:
                sourceTower = &board.rightTower;
                break;
            default:
                break;
        }

        switch (destStoneNumber) {
            case 1:
                destTower = &board.leftTower;
                break;
            case 2:
                destTower = &board.middleTower;
                break;
            case 3:
                destTower = &board.rightTower;
                break;
            default:
                break;
        }

        if (sourceTower == NULL || destTower == NULL) {
            printf("\nEssa pedra não existe.\n");
            while (getchar() != '\n');
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
        } else {
            if (!moveRing(sourceTower, destTower)) {
                printf("\nNão há discos para serem retirados.\n");
                while (getchar() != '\n');
                printf("\nPressione ENTER para continuar...");
                while (getchar() != '\n');
            }
        }
    } while(running);
}

void endgame() {
    //system("tput reset"); // Linux only
    system("cls"); // Windows only
    printf("\nUm grande estrondo ressoou no pequeno espaço e uma nuvem de \
poeira cobriu o local. Incapaz de enxergar nessa situação, Baldur tenta, \
inutilmente, afastar a poeira. Após alguns momentos, a poeira finalmente \
se assenta. Baldur abre os olhos e percebe que a rocha, que antes bloqueava \
a passagem, havia desaparecido, liberando o caminho. Baldur segue em direção \
à entrada.\n");

    printf("\nPressione ENTER para avançar...");
    while (getchar() != '\n');

    printf("\nCONTINUA\n\n");
}

void printChapterTitle(Chapter chapter) {
    const char* title = chapter.title;
    int i, titleLength = strlen(title);

    printf("\n");
    for (i = 0; i < titleLength; i++) printf("-");

    printf("\n%s\n", title);

    for (i = 0; i < titleLength; i++) printf("-");
    printf("\n\n");
}

int hasWonHanoiGame(HanoiBoard *board) {
    if (isTowerFull(&board->rightTower)) {
        int i;
        Ring ringBelow = peekTower(&board->rightTower, 0);
        for (i = 1; i < MAX_NUMBER_OF_RINGS; i++) {
            Ring currentRing = peekTower(&board->rightTower, i);
            if (ringBelow.size < currentRing.size) return 0;
            ringBelow = currentRing;
        }
        return 1;
    }
    return 0;
}

int moveRing(Tower *sourceTower, Tower *destTower) {
    if (isTowerEmpty(sourceTower) || isTowerFull(destTower)) return 0;

    Ring ring = popRingFromTower(sourceTower);
    pushRingToTower(destTower, ring);
    return 1;
}

void initializeHanoiBoard(HanoiBoard *board) {
    Ring rings[MAX_NUMBER_OF_RINGS];

    int i, ringSize = MAX_RING_SIZE;
    for (i = 0; i < MAX_NUMBER_OF_RINGS; i++) {
        initializeRing(&rings[i], ringSize);
        ringSize -= 2;
    }

    initializeTower(&board->leftTower);
    initializeTower(&board->middleTower);
    initializeTower(&board->rightTower);

    for (i = 0; i < MAX_NUMBER_OF_RINGS; i++) {
        pushRingToTower(&board->leftTower, rings[i]);
    }
}

void printHanoiBoard(HanoiBoard *board) {

    int i;
    for (i = MAX_NUMBER_OF_RINGS; i >= 0; i--) {
        Ring leftTowerRing, middleTowerRing, rightTowerRing;

        initializeRing(&leftTowerRing, 0);
        initializeRing(&middleTowerRing, 0);
        initializeRing(&rightTowerRing, 0);

        if (board->leftTower.top >= i) leftTowerRing = peekTower(&board->leftTower, i);
        if (board->middleTower.top >= i) middleTowerRing = peekTower(&board->middleTower, i);
        if (board->rightTower.top >= i) rightTowerRing = peekTower(&board->rightTower, i);

        printf(" %*s%*s    %*s%*s    %*s%*s\n",
        (int) (ceil((MAX_RING_SIZE - leftTowerRing.size)/2.0)) + leftTowerRing.size, leftTowerRing.body,
        (MAX_RING_SIZE - leftTowerRing.size)/2, "",
        (int) (ceil((MAX_RING_SIZE - middleTowerRing.size)/2.0)) + middleTowerRing.size, middleTowerRing.body,
        (MAX_RING_SIZE - middleTowerRing.size)/2, "",
        (int) (ceil((MAX_RING_SIZE - rightTowerRing.size)/2.0)) + rightTowerRing.size, rightTowerRing.body,
        (MAX_RING_SIZE - rightTowerRing.size)/2, "");
    }
    printStones();
}

void printStones() {
    printf(" -----    -----    -----\n");
    printf("|  1  |  |  2  |  |  3  |\n");
    printf(" -----    -----    -----\n\n");
}

void pushRingToTower(Tower *tower, Ring ring) {
    assert(!isTowerFull(tower));

    tower->top++;
    tower->rings[tower->top] = ring;
}

Ring popRingFromTower(Tower *tower) {
    assert(!isTowerEmpty(tower));

    Ring topRing = tower->rings[tower->top];
    tower->top--;
    return topRing;
}

Ring peekTower(Tower *tower, int position) {
    assert(!isTowerEmpty(tower) && position <= tower->top);

    return tower->rings[position];
}

int isTowerEmpty(Tower *tower) {
    return (tower->top == -1);
}

int isTowerFull(Tower *tower) {
    return (tower->top+1 == MAX_NUMBER_OF_RINGS);
}

void initializeTower(Tower *tower) {
    tower->top = -1;
}

void initializeRing(Ring *ring, int size) {
    assert(size >= 0);

    ring->size = size;
    ring->body = (char*) calloc(size+1, sizeof(char));
    memset(ring->body, '*', size);
}
