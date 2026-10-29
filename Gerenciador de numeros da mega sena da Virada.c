#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para calcular combinação C(n,k) = n! / (k! * (n-k)!)
long long combinacao(int n, int k) {
    if (k > n) return 0;
    if (k > n - k) k = n - k; // otimiza
    long long resultado = 1;
    for (int i = 1; i <= k; i++) {
        resultado = resultado * (n - k + i) / i;
    }
    return resultado;
}

void gerar_jogo(int *numeros, int qtd) {
    int usado[61] = {0};
    int count = 0;
    while (count < qtd) {
        int num = (rand() % 60) + 1; // 1 a 60
        if (!usado[num]) {
            usado[num] = 1;
            numeros[count] = num;
            count++;
        }
    }
    // Ordena para ficar igual o bilhete da Caixa
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (numeros[i] > numeros[j]) {
                int tmp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = tmp;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    
    int qtd_dezenas;
    printf("=== GERADOR MEGA DA VIRADA ===\n");
    printf("Quantos numeros voce quer jogar? (6 a 15): ");
    scanf("%d", &qtd_dezenas);

    if (qtd_dezenas < 6 || qtd_dezenas > 15) {
        printf("Valor invalido! A Mega permite de 6 a 15 numeros.\n");
        return 1;
    }

    int jogo[15];
    gerar_jogo(jogo, qtd_dezenas);

    printf("\nSeu jogo gerado: ");
    for (int i = 0; i < qtd_dezenas; i++) {
        printf("%02d ", jogo[i]);
    }
    printf("\n");

    // --- CALCULO DA CHANCE COM A FORMULA P(A) = n(A) / n(Omega) ---
    // n(Omega) = C(60, 6) = total de combinacoes possiveis
    // n(A) = C(qtd_dezenas, 6) = quantas combinacoes de 6 seu jogo cobre

    long long n_omega = combinacao(60, 6); // 50.063.860
    long long n_A = combinacao(qtd_dezenas, 6);

    // P(A) = n(A) / n(Omega)
    double P_A = (double)n_A / (double)n_omega;
    double uma_em = (double)n_omega / (double)n_A;

    printf("\n--- CALCULO DE PROBABILIDADE ---\n");
    printf("Formula usada: P(A) = n(A) / n(Omega)\n");
    printf("n(Omega) = C(60,6) = %lld combinacoes totais\n", n_omega);
    printf("n(A)     = C(%d,6) = %lld combinacoes que voce cobre\n", qtd_dezenas, n_A);
    printf("P(A)     = %lld / %lld\n", n_A, n_omega);
    printf("P(A)     = %.10f %%\n", P_A * 100);
    printf("\nSua chance e de 1 em %.0f\n", uma_em);

    if (qtd_dezenas == 6) {
        printf("(Exatamente 1 em 50.063.860)\n");
    }

    printf("\nBoa sorte na Virada!\n");
    return 0;
}