#include <stdio.h>
#include <locale.h>


// Definindo a constante do limite de ano
#define LIMITE_ANO 50 
// O número máximo de chaves N é 10.
#define MAX_CHAVES 10 

/**
 * @brief Implementação do Algoritmo de Euclides para calcular o Máximo Divisor Comum (MDC).
 */
long long mdc(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Função para calcular o Mínimo Múltiplo Comum (MMC) de dois números.
 */
long long mmc_dois(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / mdc(a, b)) * b;
}

/**
 * @brief Resolve o problema "Chaves Periódicas" encontrando o MMC dos ciclos C_i.
 */
int main() {
    setlocale(LC_ALL, "Portuguese"); 
        
        int N; // Número de chaves (1 <= N <= 10)
    int C[MAX_CHAVES]; // Vetor para armazenar os ciclos (2 <= C_i <= 20)
    int leitura_valida; // Variável para controlar o loop de validação
    printf("Questão 2 - Matemática Discreta 2 \nAluno: Bruno Dantas (241012104) \nAluno: Nicole Jovita (241012347) \n\n");
    printf("  RESOLUTOR: SINCRONIZAÇÃO DE CHAVES (CÁLCULO DE MMC)   \n");
    
    // ----------------------------------------------------
    // 1. Leitura e Validação do número de chaves N
    // ----------------------------------------------------
    do {
        printf("1. Digite o número de chaves (N). (Limite: 1 a %d):\n-> ", MAX_CHAVES);
        leitura_valida = scanf("%d", &N);
        
        // Limpa o buffer de entrada (em caso de entrada não numérica)
        while (getchar() != '\n'); 

        // Verifica se a leitura foi bem-sucedida E se o valor está dentro do limite
        if (leitura_valida != 1 || N < 1 || N > MAX_CHAVES) {
            printf("ERRO: Número inválido. Informe um número que respeite o limite (1 a %d).\n\n", MAX_CHAVES);
        }
    } while (leitura_valida != 1 || N < 1 || N > MAX_CHAVES);
    
    // ----------------------------------------------------
    // 2. Leitura e Validação dos N ciclos C1, C2, ..., Cn
    // ----------------------------------------------------
    printf("\n2. Digite os %d ciclos (C_i). (Limite de 2 a 20 para cada ciclo):\n", N);
    for (int i = 0; i < N; i++) {
        do {
            printf("-> Ciclo C%d (2 a 20): ", i + 1);
            leitura_valida = scanf("%d", &C[i]);
            
            // Limpa o buffer de entrada
            while (getchar() != '\n'); 

            // Verifica se a leitura foi bem-sucedida E se o valor está dentro do limite [2, 20]
            if (leitura_valida != 1 || C[i] < 2 || C[i] > 20) {
                printf("ERRO: Valor do ciclo C%d inválido. Informe um valor entre 2 e 20.\n", i + 1);
            }
        } while (leitura_valida != 1 || C[i] < 2 || C[i] > 20);
    }

    // Inicializa o MMC com o primeiro ciclo.
    long long mmc_total = C[0]; 

    // Informa o início do processo (Passo a Passo Visível)
    printf("\n--- Processo de Sincronização de Chaves (Cálculo do MMC) ---\n");
    printf("Ciclo inicial: %lld\n", mmc_total);


    // ----------------------------------------------
    // 3. Cálculo Iterativo do MMC
    // ----------------------------------------------
    for (int i = 1; i < N; i++) {
        long long mmc_anterior = mmc_total; 
        
        mmc_total = mmc_dois(mmc_total, C[i]);
        
        // Exibição do passo a passo do cálculo do MMC
        printf("Passo %d: Calculando MMC(%lld, %d) -> Resultado Parcial = %lld\n", 
                i, mmc_anterior, C[i], mmc_total); 

        // Verificação de Limite no Meio do Cálculo
        if (mmc_total > LIMITE_ANO) {
            printf("\nO MMC final excede o limite de %d anos.\n", LIMITE_ANO);
            printf("Impossibilidade.\n"); 
            return 0;
        }
    }

    // ----------------------------------------------
    // 4. Saída Final
    // ----------------------------------------------
    printf("--------------------------------------------------------\n");
    if (mmc_total <= LIMITE_ANO) {
        printf("RESULTADO FINAL: Primeiro ano sincronizado: %lld\n", mmc_total);
    } else {
        printf("RESULTADO FINAL: Impossibilidade (MMC excede o limite de %d anos).\n", LIMITE_ANO);
    }
   
    return 0;
}