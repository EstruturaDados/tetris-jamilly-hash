#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.

#define MAX_FILA 10   // tamanho da fila de peças futuras
#define MAX_PILHA 3   // tamanho da pilha de reserva

// Struct da peça 
typedef struct {
    char nome;  // tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // identificador único
} Peca;

//  Fila Circular
typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;


//Pilha Linear
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;


//  Geração automática de peças 
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Funções da fila circular
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == MAX_FILA;
}

// Inserir peça no final
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        // Não imprime erro crítico aqui; chamadas externas validam antes.
        return;
    }


    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;

}

// Remover peça da frente
Peca dequeue(Fila *f) {
    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return removida;
}

void exibirFila(Fila *f) {
    printf("\nFila de peças futuras:\n");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->tamanho; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}


// Funções da Pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p))
        return;

    p->topo++;
    p->itens[p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca r = p->itens[p->topo];
    p->topo--;
    return r;
}

// Exibir todos os elementos da reserva (da base até o topo)
void exibirReserva(Pilha *p) {
    printf("\nPeça reservada:\n");
    if (pilhaVazia(p)) {
        printf("(nenhuma)\n");
    } else {
        printf("[%c %d]\n", p->itens[p->topo].nome, p->itens[p->topo].id);
    }
}

// Troca a peça da frente da fila com o topo da pilha
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("\n A fila está vazia. Não há peça para trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("\n A pilha está vazia. Não há peça na reserva para trocar.\n");
        return;
    }

    int idxFila = f->frente;
    int idxPilha = p->topo; // índice do topo na array da pilha

    // Troca direta nos arrays
    Peca temp = f->itens[idxFila];
    f->itens[idxFila] = p->itens[idxPilha];
    p->itens[idxPilha] = temp;

    printf("\n Troca realizada: frente da fila <--> topo da pilha.\n");
    printf("  Nova frente: [%c %d]\n", f->itens[idxFila].nome, f->itens[idxFila].id);
    printf("  Novo topo da pilha: [%c %d]\n", p->itens[idxPilha].nome, p->itens[idxPilha].id);
}

// Troca os 3 primeiros da fila com as 3 peças da pilha
// Map: fila[frente + 0] <-> pilha[topo]
//      fila[frente + 1] <-> pilha[topo-1]
//      fila[frente + 2] <-> pilha[topo-2]
void trocarTresPrimeiros(Fila *f, Pilha *p) {
    if (f->tamanho < 3) {
        printf("\n A fila não tem pelo menos 3 peças. Operação inválida.\n");
        return;
    }
    if (p->topo != 2) { // topo == 2 significa exatamente 3 peças (0,1,2)
        printf("\n A pilha não tem exatamente 3 peças. Operação inválida.\n");
        return;
    }

    // índices circulares para os 3 primeiros da fila
    int idxFila0 = f->frente;
    int idxFila1 = (f->frente + 1) % MAX_FILA;
    int idxFila2 = (f->frente + 2) % MAX_FILA;

    // índices da pilha: topo, topo-1, topo-2
    int idxPilhaTop = p->topo;       // 2
    int idxPilhaMid = p->topo - 1;   // 1
    int idxPilhaBot = p->topo - 2;   // 0

    // Trocas em ordem: fila0 <-> pilhaTop, fila1 <-> pilhaMid, fila2 <-> pilhaBot
    Peca temp;

    temp = f->itens[idxFila0];
    f->itens[idxFila0] = p->itens[idxPilhaTop];
    p->itens[idxPilhaTop] = temp;

    temp = f->itens[idxFila1];
    f->itens[idxFila1] = p->itens[idxPilhaMid];
    p->itens[idxPilhaMid] = temp;

    temp = f->itens[idxFila2];
    f->itens[idxFila2] = p->itens[idxPilhaBot];
    p->itens[idxPilhaBot] = temp;

    printf("\n Troca de 3 peças realizada com sucesso.\n");
    printf("  (Fila: 3 primeiros) <--> (Pilha: de topo até base)\n");
}


//  Programa principal
int main() {
    Fila fila;
    Pilha reserva;
    int opcao;
    int contadorID = 0;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&reserva);


    // Inicializa a fila com 10 peças automáticas
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    printf("=== TETRIS STACK ===\n");

    do {
        exibirFila(&fila);
        exibirReserva(&reserva);

            printf("\nMENU:\n");
        printf("1 - Jogar próxima peça\n");
        printf("2 - Reservar peça (enviar para pilha)\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            // limpar entrada inválida
            while (getchar() != '\n');
            printf("\nEntrada inválida. Tente novamente.\n");
            continue;
        }

        switch (opcao) {

            // Jogar peça (remove da fila e repõe outra peça)
            case 1: {
                if (filaVazia(&fila)) {
                    printf("\nFila vazia! ERRO.\n");
                    break;
                }

                Peca jogada = dequeue(&fila);
                printf("\n Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

                // Repor nova peça automaticamente
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            }

            // Reservar peça (push na pilha) - aceita até MAX_PILHA peças
            case 2: {
                if (pilhaCheia(&reserva)) {
                    printf("\n Pilha cheia! Não é possível reservar mais peças.\n");
                    break;
                }

                Peca frente = dequeue(&fila);
                push(&reserva, frente);

                // Repor nova peça automática na fila
                enqueue(&fila, gerarPeca(contadorID++));

                printf("\n Peça [%c %d] movida para reserva.\n", frente.nome, frente.id);
                break;
            }

            // Usar peça da reserva (pop) - considera a peça usada e repõe a fila
            case 3: {
                if (pilhaVazia(&reserva)) {
                    printf("\n Nenhuma peça reservada!\n");
                    break;
                }

                Peca usada = pop(&reserva);
                printf("\n Usando peça da reserva: [%c %d]\n", usada.nome, usada.id);

                // Após usar a reserva, ela é considerada "jogada"
                // então geramos nova peça e colocamos na fila para manter o tamanho
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            }

            // Opção 4: trocar frente da fila com topo da pilha
            case 4: {
                // validar e executar troca
                trocarFrenteTopo(&fila, &reserva);
                break;
            }

            // Opção 5: trocar 3 primeiros da fila com 3 da pilha
            case 5: {
                // validar e executar troca
                trocarTresPrimeiros(&fila, &reserva);
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);


return 0;
}
