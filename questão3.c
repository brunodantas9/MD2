#include <stdio.h>
#include <math.h>
#include <locale.h>

// Função para calcular a potência a^b (necessário para a fórmula de sigma)
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

// Função principal para calcular a Razão de Eficiência
void calcularRazaoEficiencia(int N) {
    // Tratamento do caso N=1, embora já feito no main
    if (N == 1) {
        printf("\n[Resultado Final] Razão de Eficiência de 1: 1.00\n");
        return;
    }

    long long tau = 1;
    long long sigma = 1;
    int temp_N = N;
    int passo = 1;
    int i_fator = 1; // Contador para a numeração dos fatores na saída

    printf("\n[Passo %d] Iniciando a Fatoração Prima de N = %d (Trial Division)\n", passo++, N);
    
    // --- 1. Fatoração Prima e Cálculo de Tau e Sigma ---

    // Trata o fator 2
    if (temp_N % 2 == 0) {
        int a = 0; 
        while (temp_N % 2 == 0) {
            a++;
            temp_N /= 2;
        }

        printf("  - Fator primo p%d = 2, Expoente a%d = %d\n", i_fator, i_fator, a);

        tau *= (a + 1);
        long long termo_sigma = (power(2, a + 1) - 1) / (2 - 1);
        sigma *= termo_sigma;
        i_fator++;
    }

    // Trata fatores primos ímpares
    // Loop vai até sqrt(temp_N), que é a otimização de Trial Division
    for (int p = 3; p * p <= temp_N; p += 2) {
        if (temp_N % p == 0) {
            int a = 0; 
            while (temp_N % p == 0) {
                a++;
                temp_N /= p;
            }

            printf("  - Fator primo p%d = %d, Expoente a%d = %d\n", i_fator, p, i_fator, a);

            tau *= (a + 1);
            long long termo_sigma = (power(p, a + 1) - 1) / (p - 1);
            sigma *= termo_sigma;
            i_fator++;
        }
    }

    // Trata o que resta (será um primo maior que sqrt(N) ou 1)
    if (temp_N > 1) {
        int p = temp_N;
        int a = 1; 
        
        printf("  - Fator primo p%d = %d, Expoente a%d = %d\n", i_fator, p, i_fator, a);

        tau *= (a + 1);
        long long termo_sigma = (power(p, a + 1) - 1) / (p - 1);
        sigma *= termo_sigma;
    }

    // --- 2. Resultados Intermediários ---

    printf("\n[Passo %d] Cálculo Intermediário de tau(N)\n", passo++);
    printf("  - tau(%d) = Número total de divisores = %lld\n", N, tau);

    printf("\n[Passo %d] Cálculo Intermediário de sigma(N)\n", passo++);
    printf("  - sigma(%d) = Soma de todos os divisores = %lld\n", N, sigma);
    
    // --- 3. Cálculo da Razão de Eficiência ---

    double razao_eficiencia = (double)sigma / tau;

    printf("\n[Passo %d] Cálculo Final da Razão de Eficiência\n", passo++);
    printf("  - Razão = sigma(N) / tau(N) = %lld / %lld = %.2f\n", sigma, tau, razao_eficiencia);

    printf("\n[Resultado Final] Razão de Eficiência de %d: %.2f\n", N, razao_eficiencia);
}

// O restante do main() permanece o mesmo
int main() {
    int N;
    setlocale(LC_ALL, "Portuguese");
    printf("Questão 4 - Matemática Discreta 2 \nAluno: Bruno Dantas (241012104) \nAluno: Nicole Jovita (241012347) \n\n");
    printf("Insira um inteiro N (1 <= N <= 105): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 105) {
        printf("Entrada inválida. N deve ser entre 1 e 105.\n");
        return 1;
    }
    
    // O caso N=1 é melhor tratado no main para a saída concisa
    if (N == 1) {
        printf("\n[Resultado Final] Razão de Eficiência de 1: 1.00\n");
        return 0;
    }

    calcularRazaoEficiencia(N);

    return 0;
}