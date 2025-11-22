#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.

#define MAX_FILA 10   // tamanho da fila de peças futuras
#define MAX_PILHA 1   // tamanho da pilha de reserva

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
        printf("\n❌ A fila já está cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % MAX_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;

    printf("✔ Peça [%c %d] inserida.\n", p.nome, p.id);
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

void exibirReserva(Pilha *p) {
    printf("\nPeça reservada:\n");
    if (pilhaVazia(p)) {
        printf("(nenhuma)\n");
    } else {
        printf("[%c %d]\n", p->itens[p->topo].nome, p->itens[p->topo].id);
    }
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

    printf("=== TETRIS STACK - NÍVEL AVENTUREIRO ===\n");

    do {
        exibirFila(&fila);
        exibirReserva(&reserva);

        printf("\nMENU:\n");
        printf("1 - Jogar próxima peça\n");
        printf("2 - Reservar peça (enviar para pilha)\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            // Jogar peça (remove da fila e repõe outra peça)
            case 1: {
                if (filaVazia(&fila)) {
                    printf("\nFila vazia! ERRO.\n");
                    break;
                }

                Peca jogada = dequeue(&fila);
                printf("\n🧩 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

                // Repor nova peça automaticamente
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            }

            // Reservar peça (somente se pilha estiver vazia)
            case 2: {
                if (pilhaCheia(&reserva)) {
                    printf("\n❌ Já existe peça reservada!\n");
                    break;
                }

                Peca frente = dequeue(&fila);
                push(&reserva, frente);

                // Repor nova peça automática na fila
                enqueue(&fila, gerarPeca(contadorID++));

                printf("\n✔ Peça [%c %d] movida para reserva.\n", frente.nome, frente.id);
                break;
            }

            // Usar peça da reserva
            case 3: {
                if (pilhaVazia(&reserva)) {
                    printf("\n❌ Nenhuma peça reservada!\n");
                    break;
                }

                Peca usada = pop(&reserva);
                printf("\n🔄 Usando peça da reserva: [%c %d]\n", usada.nome, usada.id);

                // Após usar a reserva, ela é considerada "jogada"
                // então geramos nova peça e colocamos na fila
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


   
return 0;
}
