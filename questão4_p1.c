#include <stdio.h>

#ifdef _WIN32
#include <windows.h> 
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    while (b != 0) { // Euclides: repete enquanto o divisor b for diferente de 0
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;   // passo do Euclides: novo divisor passa a ser o resto (b ← a mod b)
    }
    return a;
}
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    int g = mdcComPassos(a, m); // calcula o MDC(a, m) e exibe passos (verifica se inverso existe)

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0; // se o inverso saiu negativo, ajusta para o intervalo [0, m0-1]
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 != 0)  // se o expoente é ímpar: aplica o passo 'multiply' (res *= b % mod)
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp /= 2;
    }
    return (int)res;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;
    printf("Questão 4 - Matemática Discreta 2 \nAluno: Bruno Dantas (241012104) \nAluno: Nicole Jovita (241012347) \n\n");
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // encontra G^{-1} (mod Zn) via Euclides estendido
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d ≡ %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1);  
    printf("Valor final da congruência: %d\n", resultado);

    return 0;
}
