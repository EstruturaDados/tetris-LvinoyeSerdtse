#include <stdio.h>
#include <stdlib.h>

#define MAX 5
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

// prototipos de funcao
void Menu(Fila *f);
void inicializarFila(Fila *f);
void inserir(Fila *f, Peca pp);
void remover(Fila *f, Peca *p);
void exibirFila(Fila *f);
void gerarPeca(Peca *p, int idGerado);
void mainMenu(Fila *f);

// funcao principal, onde o programa de fato roda
int main(){
    srand(time(NULL));

    Fila minhaFila;
    inicializarFila(&minhaFila);

    mainMenu(&minhaFila);

return 0;
}


void mainMenu(Fila *f) {
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
    printf("[3] - PECAS DISPONIVEIS\n");
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
        // literalmente isso mesmo. exibe as pecas que o usuario tem a disposicao
        printf("Peças atuais: \n");
        exibirFila(f);
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
        printf("[!] - Fila cheia\n\n");
        return;
    }
    f->conjunto[f->fim] = pp;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Peca *p){
    if(f->total == 0){
        printf("[!] - Fila vazia\n\n");
        return;
    }
    *p = f->conjunto[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

}

void exibirFila(Fila *f){
    if (f->total == 0){
    printf("[!] - Fila vazia\n\n");
    return;
    }

    printf("Fila:");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
    printf("\nPEÇA: %c (ID: %d)\n\n", f->conjunto[idx].tipo, f->conjunto[idx].id);        
    }
}

void gerarPeca(Peca* p, int idGerado) {
    char tipos [] = {'I', 'O', 'T', 'L'};
    p->tipo = tipos[rand() % 4];
    p->id = idGerado;
}