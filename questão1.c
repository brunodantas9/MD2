
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

//FUNÇÕES AUXILIARES

// Verifica se número eh composto
int ehComposto(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return 1;
    }
    return 0;
}

// Calcula MDC pelo Algoritmo de Euclides
int mdc(int a, int b) {
    int temp;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Metodo ? de Pollard para fator nao trivial
int pollardRho(int n) {
    int x = 2, y = 2, d = 1;
    int iter = 0;

    printf("\nIniciando Pollard Rho para n = %d\n", n);

    while (d == 1) {
        iter++;
        x = (x*x + 1) % n;
        y = (y*y + 1) % n;
        y = (y*y + 1) % n;

        int diff = x - y;
        if (diff < 0) diff = -diff;

        d = mdc(diff, n);
        printf("Iteração %d: x = %d, y = %d, mdc(|x-y|, n) = %d\n", iter, x, y, d);

        if (d == 1 || d == n || d == 2) d = 1;
    }
    return d;
}

// Algoritmo Estendido de Euclides para inverso modular
int inversoModular(int E, int z) {
    int t = 0, newt = 1;
    int r = z, newr = E;
    int quotient, temp;

    while (newr != 0) {
        quotient = r / newr;

        temp = t;
        t = newt;
        newt = temp - quotient * newt;

        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }

    if (r > 1) return -1;
    if (t < 0) t += z;

    return t;
}

// Exponenciação modular eficiente com passo a passo
int modExp(int M, int exp, int n) {
    int result = 1;
    M = M % n;
    printf("  Exponenciação modular: M=%d, exp=%d, n=%d\n", M, exp, n);
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * M) % n;
            printf("    Multiplicação: result = (result * M) mod n = %d\n", result);
        }
        exp = exp / 2;
        M = (M * M) % n;
        printf("    Quadrado: M = M*M mod n = %d, exp agora = %d\n", M, exp);
    }
    return result;
}

// Pre-codificaçao: letra -> numero
int letraParaNumero(char c) {
    if(c >= 'A' && c <= 'Z') return c - 'A' + 11;
    if(c == ' ') return 0;
    return -1;
}

// Numero -> letra (2 dígitos)
char numeroParaLetra(int n) {
    if(n == 0) return ' ';
    if(n >= 11 && n <= 36) return (char)('A' + n - 11);
    return '?';
}

// Indica e justifica qual teorema modular será usado
void indicarTeorema(int M, int n) {
    if (mdc(M, n) == 1) {
        printf("  Aplicando Teorema de Euler, pois mdc(%d,%d)=1\n", M, n);
    } else {
        printf("  Aplicando Divisão Euclidiana, pois mdc(%d,%d) != 1\n", M, n);
    }
}

// Criptografia
void criptografarMensagem(char mensagem[], int n, int E, int C_out[]) {
    printf("\nCriptografando mensagem...\n\n");

    int len = strlen(mensagem);
    for(int i = 0; i < len; i++) {
        int M = letraParaNumero(mensagem[i]);
        if(M == -1) { C_out[i] = -1; continue; }

        printf("Letra '%c':\n", mensagem[i]);
        indicarTeorema(M, n);
        int C = modExp(M, E, n);
        C_out[i] = C;
        printf("Resultado criptografado: C = %d\n\n", C);
    }
}

// Descriptografia
void descriptografarMensagem(int C_in[], int len, int n, int D) {
    printf("\nDescriptografando mensagem...\n\n");

    for(int i = 0; i < len; i++) {
        int C = C_in[i];
        if(C == -1) continue;

        printf("C=%d:\n", C);
        int M_decrypted = modExp(C, D, n);
        indicarTeorema(M_decrypted, n);
        char letra = numeroParaLetra(M_decrypted);
        printf("Letra decifrada: '%c'\n\n", letra);
    }
}

// -------------------- MAIN --------------------
int main() {
    int n1, n2;
    setlocale(LC_ALL, "Portuguese");
    printf("Questão 1 - Matemática Discreta 2 \nAluno: Bruno Dantas (241012104) \nAluno: Nicole Jovita (241012347) \n\n");
    
    printf("Um número composto é aquele que pode ser escrito como o produto entre dois primos distintos.\nDigite dois números compostos distintos entre 100 e 9999: \n");
    scanf("%d %d", &n1, &n2);

    if (n1 < 100 || n1 > 9999 || n2 < 100 || n2 > 9999) {
        printf("Erro: os números devem estar no intervalo entre 100 e 9999.\n");
        return 1;
    }
    if (n1 == n2) {
        printf("Erro: os números não podem ser iguais.\n");
        return 1;
    }
    if (!ehComposto(n1) || !ehComposto(n2)) {
        printf("Erro: ambos os números devem ser compostos.\n");
        return 0;
    }

    printf("Os números %d e %d são válidos e compostos!\n", n1, n2);

    // Etapa 1: Pollard Rho
    int p = pollardRho(n1);
    int q = pollardRho(n2);

    printf("\nFatores encontrados:\n");
    printf("p (fator de n1 = %d) = %d\n", n1, p);
    printf("q (fator de n2 = %d) = %d\n", n2, q);

    // Etapa 2: Chaves RSA
    int n = p * q;
    int z = (p-1)*(q-1);
    int E;
    for(E = 2; E < n; E++) {
        if(mdc(E, z) == 1) break;
    }
    int D = inversoModular(E, z);
    if(D == -1) {
        printf("Erro: não foi possível calcular o inverso modular.\n");
        return 1;
    }
    printf("\nChaves RSA:\nPública (n,E) = (%d,%d)\nPrivada (n,D) = (%d,%d)\n", n, E, n, D);

    // Etapa 3: Criptografia / Descriptografia
    char mensagem[100];
    int C_values[100];
    getchar(); // limpar buffer
    printf("\nDigite a mensagem (somente letras maiúsculas e espaços): ");
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = 0;

    int len = strlen(mensagem);
    criptografarMensagem(mensagem, n, E, C_values);
    descriptografarMensagem(C_values, len, n, D);

    // Confirmação de mensagem decifrada
    int iguais = 1;
    for(int i=0; i<len; i++) {
        int M_orig = letraParaNumero(mensagem[i]);
        if(M_orig == -1) continue;
        int M_dec = modExp(C_values[i], D, n);
        if(M_orig != M_dec) { iguais = 0; break; }
    }
    if(iguais) printf("\nMensagem decifrada CONFERE com a original!\n");
    else printf("\nMensagem decifrada NÃO confere com a original!\n");

    return 0;
}