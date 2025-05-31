#include <stdio.h>
#include <string.h>

#define ESTADOS 26
//Questão 1 
typedef struct {
    char nome[30];
    int veiculos;
    int acidentes;
} Estado;

void cadastrarEstados(Estado estados[]) {
    for (int i = 0; i < ESTADOS; i++) {
        printf("Estado %d:\n", i+1);
        printf("Nome: ");
        scanf(" %[^\n]", estados[i].nome);
        printf("Nº de veículos: ");
        scanf("%d", &estados[i].veiculos);
        printf("Nº de acidentes: ");
        scanf("%d", &estados[i].acidentes);
    }
}

void maiorMenorAcidentes(Estado estados[]) {
    int maior = 0, menor = 0;
    for (int i = 1; i < ESTADOS; i++) {
        if (estados[i].acidentes > estados[maior].acidentes)
            maior = i;
        if (estados[i].acidentes < estados[menor].acidentes)
            menor = i;
    }
    printf("Estado com mais acidentes: %s (%d)\n", estados[maior].nome, estados[maior].acidentes);
    printf("Estado com menos acidentes: %s (%d)\n", estados[menor].nome, estados[menor].acidentes);
}

float percentualVeiculos(Estado estados[], int pos) {
    int total = 0;
    for (int i = 0; i < ESTADOS; i++) {
        total += estados[i].veiculos;
    }
    return (estados[pos].veiculos * 100.0) / total;
}

float mediaAcidentes(Estado estados[]) {
    int total = 0;
    for (int i = 0; i < ESTADOS; i++) {
        total += estados[i].acidentes;
    }
    return total / (float)ESTADOS;
}

void acimaMedia(Estado estados[], float media) {
    printf("Estados acima da média de acidentes:\n");
    for (int i = 0; i < ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s (%d acidentes)\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[ESTADOS];
    cadastrarEstados(estados);

    maiorMenorAcidentes(estados);

    int pos;
    printf("Informe o índice do estado (0 a 25) para saber o percentual de veículos: ");
    scanf("%d", &pos);
    printf("Percentual: %.2f%%\n", percentualVeiculos(estados, pos));

    float media = mediaAcidentes(estados);
    printf("Média de acidentes: %.2f\n", media);

    acimaMedia(estados, media);

    return 0;
}

//Questão 2
#include <stdio.h>
#include <string.h>

#define TAM 40

typedef struct {
    int codigo;
    char descricao[50];
    float preco;
    int estoque;
} Produto;

void cadastrarProduto(Produto produtos[], int *n) {
    if (*n >= TAM) {
        printf("Estoque cheio!\n");
        return;
    }
    printf("Código: ");
    scanf("%d", &produtos[*n].codigo);
    printf("Descrição: ");
    scanf(" %[^\n]", produtos[*n].descricao);
    printf("Preço: ");
    scanf("%f", &produtos[*n].preco);
    printf("Quantidade: ");
    scanf("%d", &produtos[*n].estoque);
    (*n)++;
}

void alterarPreco(Produto produtos[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Novo preço: ");
            scanf("%f", &produtos[i].preco);
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void entradaEstoque(Produto produtos[], int n, int codigo) {
    int qtd;
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Quantidade a adicionar: ");
            scanf("%d", &qtd);
            produtos[i].estoque += qtd;
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void saidaEstoque(Produto produtos[], int n, int codigo) {
    int qtd;
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Quantidade a retirar: ");
            scanf("%d", &qtd);
            if (qtd > produtos[i].estoque) {
                printf("Estoque insuficiente!\n");
            } else {
                produtos[i].estoque -= qtd;
            }
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void listarProdutos(Produto produtos[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Código: %d | Descrição: %s | Preço: %.2f | Estoque: %d\n",
               produtos[i].codigo, produtos[i].descricao, produtos[i].preco, produtos[i].estoque);
    }
}

int main() {
    Produto produtos[TAM];
    int n = 0;
    int op, cod;

    do {
        printf("\n1-Cadastrar\n2-Alterar Preço\n3-Entrada Estoque\n4-Saída Estoque\n5-Listar\n0-Sair\n");
        scanf("%d", &op);
        switch (op) {
            case 1: cadastrarProduto(produtos, &n); break;
            case 2: 
                printf("Código: ");
                scanf("%d", &cod);
                alterarPreco(produtos, n, cod);
                break;
            case 3: 
                printf("Código: ");
                scanf("%d", &cod);
                entradaEstoque(produtos, n, cod);
                break;
            case 4: 
                printf("Código: ");
                scanf("%d", &cod);
                saidaEstoque(produtos, n, cod);
                break;
            case 5: listarProdutos(produtos, n); break;
        }
    } while (op != 0);

    return 0;
}

//Questão 3 

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int numeroConta;
    char nome[50];
    char cpf[15];
    char telefone[15];
    float saldo;
} Conta;

int busca(Conta contas[], int n, int numConta) {
    for (int i = 0; i < n; i++) {
        if (contas[i].numeroConta == numConta) {
            return i;
        }
    }
    return -1;
}

void cadastrar(Conta contas[], int *n) {
    if (*n >= MAX) {
        printf("Cadastro cheio!\n");
        return;
    }
    printf("Número da conta: ");
    scanf("%d", &contas[*n].numeroConta);
    printf("Nome: ");
    scanf(" %[^\n]", contas[*n].nome);
    printf("CPF: ");
    scanf(" %[^\n]", contas[*n].cpf);
    printf("Telefone: ");
    scanf(" %[^\n]", contas[*n].telefone);
    printf("Saldo inicial: ");
    scanf("%f", &contas[*n].saldo);
    (*n)++;
}

void consultarSaldo(Conta contas[], int n) {
    int numConta;
    printf("Número da conta: ");
    scanf("%d", &numConta);
    int pos = busca(contas, n, numConta);
    if (pos >= 0) {
        printf("Saldo: %.2f\n", contas[pos].saldo);
    } else {
        printf("Conta não encontrada!\n");
    }
}

void depositar(Conta contas[], int n) {
    int numConta;
    printf("Número da conta: ");
    scanf("%d", &numConta);
    int pos = busca(contas, n, numConta);
    if (pos >= 0) {
        float valor;
        printf("Valor a depositar: ");
        scanf("%f", &valor);
        contas[pos].saldo += valor;
    } else {
        printf("Conta não encontrada!\n");
    }
}

void sacar(Conta contas[], int n) {
    int numConta;
    printf("Número da conta: ");
    scanf("%d", &numConta);
    int pos = busca(contas, n, numConta);
    if (pos >= 0) {
        float valor;
        printf("Valor a sacar: ");
        scanf("%f", &valor);
        if (valor <= contas[pos].saldo) {
            contas[pos].saldo -= valor;
        } else {
            printf("Saldo insuficiente!\n");
        }
    } else {
        printf("Conta não encontrada!\n");
    }
}

void exibir(Conta contas[], int n) {
    int numConta;
    printf("Número da conta: ");
    scanf("%d", &numConta);
    int pos = busca(contas, n, numConta);
    if (pos >= 0) {
        printf("Conta: %d\n", contas[pos].numeroConta);
        printf("Nome: %s\n", contas[pos].nome);
        printf("CPF: %s\n", contas[pos].cpf);
        printf("Telefone: %s\n", contas[pos].telefone);
        printf("Saldo: %.2f\n", contas[pos].saldo);
    } else {
        printf("Conta não encontrada!\n");
    }
}

int main() {
    Conta contas[MAX];
    int n = 0, op;

    do {
        printf("\n1-Cadastrar\n2-Consultar saldo\n3-Depositar\n4-Sacar\n5-Exibir dados\n0-Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: cadastrar(contas, &n); break;
            case 2: consultarSaldo(contas, n); break;
            case 3: depositar(contas, n); break;
            case 4: sacar(contas, n); break;
            case 5: exibir(contas, n); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
