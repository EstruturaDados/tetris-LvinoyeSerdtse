#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_PILHA 3

// estrutura 'Peca'
typedef struct {
char tipo;
int id;
}Peca;

// estrutura de dados 'Fila' que comporta um array do tipo 'Peca' (a estrutura supracitada)
typedef struct {
Peca conjunto[MAX];
int inicio;
int fim;
int total;
}Fila;

typedef struct {
Peca reservas[MAX_PILHA];
int topo;
}Pilha;


// 1 - PROTOTIPOS DE FUNCAO
void mainMenu(Fila *f, Pilha *r);

// 1.1 - funcoes de fila
void inicializarFila(Fila *f);
void inserir(Fila *f, Peca pp);
void remover(Fila *f, Peca *p);
void exibirFila(Fila *f);
void gerarPeca(Peca *p, int idGerado);

// 1.2 - funcoes de pilha
int pilhaCheia(Pilha *r);
int pilhaVazia(Pilha *r);
void inicializarPilha(Pilha *r);
void exibirPilha(Pilha *r);
void peek(Pilha *r, Peca *escolhida);
void pop(Pilha *r, Peca *removida);
void push(Pilha *r, Peca inserida);
// 1.3 - funcoes "in-game" da pilha
void reservarPeca(Fila *fila, Pilha *pilha);
Peca usarReserva(Pilha *p);


// funcao principal, onde o programa de fato roda
int main(){
    srand(time(NULL));

    Fila minhaFila;
    Pilha duracell;

    inicializarFila(&minhaFila);
    inicializarPilha(&duracell);

    mainMenu(&minhaFila, &duracell);

return 0;
}


void mainMenu(Fila *f, Pilha *r) {
    printf("TETRIS (inserir aquela musiquinha legal)\n");
    printf("=============================\n");
    int opcao;
    Peca pecaTemporaria;
    char entrada;
    static int contadorId = 0;

    do {

    printf("Opções:\n");
    printf("[1] - JOGAR PEÇA\n");
    printf("[2] - INSERIR NOVA PEÇA\n");
    printf("[3] - RESERVAR PEÇA\n");
    printf("[4] - USAR PEÇA RESERVA\n");
    printf("[5] - PECAS DISPONIVEIS\n");
    printf("[0] - SAIR DO JOGO\n\n\n");
    printf("OPCAO: ");
    scanf("%d", &opcao);
    printf("\n\n");
    switch (opcao) {
        
        //"[1] - JOGAR PEÇA"
        case 1: 
            do {
            // validando escolha do jogador
            char escolha;
            exibirFila(f);
            printf("Jogar peca? (S/N)\n");
            scanf(" %c", &escolha);

            // se sim, vamos jogar a peca
            if (escolha == 'S' || escolha == 's') {
                printf("\nJogando a primeira peca...\n");
                remover(f, &pecaTemporaria);
                exibirFila(f);
                break;
            }

            // se nao, cancelar a operacao que o usuario cogitou fazer quando selecionou a opcao [1]
            else if (escolha == 'N' || escolha == 'n') {
                printf("Ok! Peca nao sera jogada.\n");
                break;
            }

            // se n digitou N(n) ou S(s), vai repetir a pergunta dps de dizer que a escolha eh invalida 
            else { 
                printf("[!] - Escolha invalida\n");
            }

        } while (1);
        break;
    
        case 2:
        printf("Pegando nova peca...\n");
        // gera a peca em uma variavel temporaria de peca;
        gerarPeca(&pecaTemporaria, contadorId);

        // insere essa variavel pecaTemporaria na fila 
        inserir(f, pecaTemporaria);
        
        // autoexplicativo, mas cumpre a exigencia de exibir a fila a cada interacao do usuario.
        exibirFila(f);

        // incrementa o contador de id, pra sempre que criar uma peca nova ele incrementar o id global que gerencia os ids das pecas.
        contadorId++;
        break;

        case 3:
            printf("\nReservando peça...");
            if(pilhaCheia(r)){
                printf("\n[!] - Pilha cheia!");
                break;
            }

            do {
            // validando escolha do jogador
            char escolha;
            exibirFila(f);
            exibirPilha(r);

            printf("Reservar a primeira peça? (S/N)\n");
            scanf(" %c", &escolha);

            // se sim, vamos jogar a peca
            if (escolha == 'S' || escolha == 's') {
                printf("\nReservando a peça...\n");
                reservarPeca(f, r);
                exibirFila(f);
                printf("\n");
                exibirPilha(r);
                break;
            }

            // se nao, cancelar a operacao que o usuario cogitou fazer quando selecionou a opcao [1]
            else if (escolha == 'N' || escolha == 'n') {
                printf("Ok! A peça nao sera reservada.\n");
                break;
            }

            // se n digitou N(n) ou S(s), vai repetir a pergunta dps de dizer que a escolha eh invalida 
            else { 
                printf("[!] - Escolha invalida\n");
            }

        } while (1);
        break;
    
    
        case 4:
            printf("\nUsando a reserva de peças...");
            if (pilhaVazia(r)){
                printf("\n[!] - Pilha vazia!");
                break;
            }

            do {
            // validando escolha do jogador
            char escolha;
            Peca pecaDaVez;
            peek(r, &pecaDaVez);

            exibirFila(f);
            exibirPilha(r);
            

            printf("\nA peça jogada será: %c [ID: %d]", pecaDaVez.tipo, pecaDaVez.id);

            printf("\nDeseja usar a peça reserva? (S/N)\n");
            scanf(" %c", &escolha);

            // se sim, vamos jogar a peca
            if (escolha == 'S' || escolha == 's') {
                printf("\nJogando a peça da reserva...");
                Peca removida;
                pop(r, &removida);

                exibirFila(f);
                printf("\n");
                exibirPilha(r);
                break;
            }

            // se nao, cancelar a operacao que o usuario cogitou fazer quando selecionou a opcao [1]
            else if (escolha == 'N' || escolha == 'n') {
                printf("\nOk! A peça nao sera reservada.");
                break;
            }

            // se n digitou N(n) ou S(s), vai repetir a pergunta dps de dizer que a escolha eh invalida 
            else { 
                printf("\n[!] - Escolha invalida\n");
            }

        } while (1);
        break;



            

        case 5:
        // literalmente isso mesmo. exibe as pecas que o usuario tem a disposicao
        printf("\nPeças atuais: ");
        exibirFila(f);
        exibirPilha(r);
        break;
    } 
} while (opcao != 0);
// enquanto o usuario n apertar pra quitar, o menu estara em loop
}


// CORPO DAS FUNCOES QUE INTEGRAM O MENU!! 

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inserir(Fila *f, Peca pp){
    if(f->total == MAX) {
        printf("\n[!] - Fila cheia\n");
        return;
    }
    f->conjunto[f->fim] = pp;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Peca *p){
    if(f->total == 0){
        printf("\n[!] - Fila vazia\n");
        return;
    }
    *p = f->conjunto[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

}

void exibirFila(Fila *f){

    printf("\nExibindo fila...\n");

    if (f->total == 0){
    printf("\n[!] - Fila vazia\n");
    return;
    }

    printf("\nFila:");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
    printf("\nPEÇA: %c (ID: %d)", f->conjunto[idx].tipo, f->conjunto[idx].id);        
    }
    printf("\n==============");
}

void gerarPeca(Peca* p, int idGerado) {
    char tipos [] = {'I', 'O', 'T', 'L'};
    p->tipo = tipos[rand() % 4];
    p->id = idGerado;
}

void reservarPeca(Fila *fila, Pilha *pilha){
    if (fila->total > 0 && !pilhaCheia(pilha) ) {
        Peca removidaDaFila;
        remover(fila, &removidaDaFila);
        push(pilha, removidaDaFila);
    }
    else {
        printf("\n[!] - Operacao Impossivel!\n");
    return;
    }
}

Peca usarReserva(Pilha *p) {
        Peca pecaReserva;
        pop(p, &pecaReserva);
        return pecaReserva;
}


// implementacao da pilha
void inicializarPilha(Pilha *p){
    p->topo = -1;
}

int pilhaCheia(Pilha *p){
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p){
    return p->topo == -1;
}

void pop(Pilha *p, Peca *removida){
    if (pilhaVazia(p)) {
        printf("\n[!] - A pilha está vazia.\n");
        return;
    }
    
    *removida = p->reservas[p->topo];
    p->topo--;
}

void push(Pilha *p, Peca inserida){
    if (pilhaCheia(p)) {
        printf("[!] - A pilha está cheia.\n");
        return;
    }

    p->topo++;
    p->reservas[p->topo] = inserida;
}

void peek(Pilha *p, Peca *escolhida){
    if(pilhaVazia(p)) {
        printf("[!] - Pilha vazia!\n");
        return;
    }
    
    *escolhida = p->reservas[p->topo];
}

void exibirPilha(Pilha *p){

    printf("\nExibindo reserva...\n");
    if(pilhaVazia(p)){
        printf("[!] - Pilha vazia!\n");
        return;
    }
    printf("\nReserva:");

    for (int i = p->topo; i>=0; i--){
        printf("\nPEÇA: %c (ID: %d)", p->reservas[i].tipo, p->reservas[i].id);        
    }
    printf("\n==============");
}

