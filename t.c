#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.1415926535

int isFriendly(int a, int b) {
    int sumA = 0, sumB = 0;
    for (int i = 1; i < a; i++) if (a % i == 0) sumA += i;
    for (int i = 1; i < b; i++) if (b % i == 0) sumB += i;
    return (sumA == b && sumB == a);
}

int isFibonacci(int n) {
    long long x1 = 5LL * n * n + 4;
    long long x2 = 5LL * n * n - 4;
    long long s1 = sqrt(x1), s2 = sqrt(x2);
    return (s1 * s1 == x1 || s2 * s2 == x2);
}

int main() {
    FILE *input = fopen("input.inp", "r");
    FILE *output = fopen("output.out", "w");
    if (!input || !output) return 1;

    int n, dc, dg, ld;
    char weather[20];
    fscanf(input, "%d %d %d %d %s", &n, &dc, &dg, &ld, weather);

    if (n < 0 || dc < 0 || dg < 0 || ld < 1 || ld > 600 || (dc == 0 && dg == 0)) {
        fprintf(output, "-1 -1 %d\n", n);
        fclose(input); fclose(output);
        return 0;
    }

    if (strcmp(weather, "Sun") == 0) {
        int G = dc % 6, H = ld % 5;
        int percentTable[5][6] = {
            {5, 7, 10, 12, 15, 20},
            {20, 5, 7, 10, 12, 15},
            {15, 20, 5, 7, 10, 12},
            {12, 15, 20, 5, 7, 10},
            {10, 12, 15, 20, 5, 7}
        };
        int X = percentTable[H][G];
        n += (n * X + 50) / 100; // làm tròn
        ld -= X;

        int sum = dc + dg;
        if (sum % 3 == 0) strcpy(weather, "Rain");
        else if (sum % 3 == 1) strcpy(weather, "Wind");
        else strcpy(weather, "Cloud");
    }

    if (strcmp(weather, "Fog") == 0) {
        int dc_fib = isFibonacci(dc);
        int dg_fib = isFibonacci(dg);
        if (dc_fib && dg_fib) {
            dc /= 2; dg /= 2;
        } else {
            dc *= 2; dg *= 2;
        }
    }

    double nepBC = dc * dc * sqrt(dc);
    double nepBG = (dg * dg * PI) / 3.0;
    int laBC = dc < 8 ? 1 : 2;
    int laBG = dg < 5 ? 1 : 2;

    int bc = 0, bg = 0;
    double nep_dư = 0;

    if (strcmp(weather, "Wind") == 0) {
        bc = (int)(n / nepBC);
        while (bc > 0 && bc * laBC > ld) bc--;
        n -= bc * nepBC;
        ld -= bc * laBC;
        bg = (int)(n / nepBG);
        while (bg > 0 && bg * laBG > ld) bg--;
        nep_dư = n - bg * nepBG;
    } else if (strcmp(weather, "Rain") == 0) {
        int max = (n / (nepBC + nepBG));
        for (int i = max; i >= 0; i--) {
            int j = i;
            double totalNep = i * (nepBC + nepBG);
            int totalLa = i * (laBC + laBG);
            if (totalNep <= n && totalLa <= ld) {
                bc = bg = i;
                nep_dư = n - totalNep;
                break;
            }
        }
    } else if (strcmp(weather, "Cloud") == 0) {
        if (isFriendly(n, ld)) {
            fprintf(output, "0 0 %d\n", n);
            fclose(input); fclose(output);
            return 0;
        }
        bg = (int)(n / nepBG);
        while (bg > 0 && bg * laBG > ld) bg--;
        n -= bg * nepBG;
        ld -= bg * laBG;
        bc = (int)(n / nepBC);
        while (bc > 0 && bc * laBC > ld) bc--;
        nep_dư = n - bc * nepBC;
    } else if (strcmp(weather, "Fog") == 0) {
        int minNep = 1e9, minBC = 0, minBG = 0;
        for (int i = 0; i <= (n / nepBC); i++) {
            for (int j = 0; j <= (n / nepBG); j++) {
                double tongNep = i * nepBC + j * nepBG;
                int tongLa = i * laBC + j * laBG;
                if (tongNep <= n && tongLa <= ld) {
                    if (i + j < minBC + minBG || (i + j == minBC + minBG && (n - tongNep) < minNep)) {
                        minNep = n - tongNep;
                        minBC = i;
                        minBG = j;
                    }
                }
            }
        }
        bc = minBC;
        bg = minBG;
        nep_dư = n - (bc * nepBC + bg * nepBG);
    }

    fprintf(output, "%d %d %.3f\n", bc, bg, nep_dư);
    fclose(input);
    fclose(output);
    return 0;
}