#include <stdio.h>
#include <stdlib.h>

int **buildMat(int n) {
        int **mat = (int **)malloc(sizeof(int *) * n);
        for (int i = 0; i < n; i++) {
            mat[i] = (int *)malloc(sizeof(int) * n);
        }
        return mat;
}

int **fillMat(int n, int **a, int rs, int re, int cs, int ce) {
        int **mat = buildMat(n);
        for (int i = rs; i <= re; i++) {
            for (int j = cs; j <= ce; j++) {
                mat[i - rs][j - cs] = a[i][j];
            }
        }
        return mat;
}

int **matrix_Addition(int n, int **a, int **b) {
        int **mat = buildMat(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = a[i][j] + b[i][j];
            }
        }
        return mat;
}

void combineMat(int **final, int **a, int rs, int re, int cs, int ce) {
        for (int i = rs; i <= re; i++) {
            for (int j = cs; j <= ce; j++) {
                final[i][j] = a[i - rs][j - cs];
            }
        }
}

int **strassen_Multiply(int **a, int **b) {
        int A = a[0][0], B = a[0][1], C = a[1][0], D = a[1][1];
        int E = b[0][0], F = b[0][1], G = b[1][0], H = b[1][1];
        int M1 = (A + C) * (E + F);
        int M2 = (B + D) * (G + H);
        int M3 = (A - D) * (E + H); 
        int M4 = A * (F - H);
        int M5 = E * (C + D);
        int M6 = H * (A + B);
        int M7 = D * (G - E);
        int **ret = buildMat(2);
        ret[0][0] = M2 + M3 - (M6 + M7);
        ret[0][1] = M4 + M6;
        ret[1][0] = M5 + M7;
        ret[1][1] = M1 - (M3 + M4 + M5);
        return ret;
}

int  **matrix_Multiplication(int n, int **a, int **b) {
        if (n == 2) {
            return strassen_Multiply(a, b);
        }
        int m = n / 2;
        int **a11 = fillMat(n / 2, a, 0, n / 2 - 1, 0, n / 2 - 1);
        int **a12 = fillMat(n / 2, a, 0, n / 2 - 1, n / 2, n - 1);
        int **a21 = fillMat(n / 2, a, n / 2, n - 1, 0, n / 2 - 1);
        int **a22 = fillMat(n / 2, a, n / 2, n - 1, n / 2, n - 1);
        
        int **b11 = fillMat(n / 2, b, 0, n / 2 - 1, 0, n / 2 - 1);
        int **b12 = fillMat(n / 2, b, 0, n / 2 - 1, n / 2, n - 1);
        int **b21 = fillMat(n / 2, b, n / 2, n - 1, 0, n / 2 - 1);
        int **b22 = fillMat(n / 2, b, n / 2, n - 1, n / 2, n - 1);
        
        int **res11 = matrix_Addition(n / 2, matrix_Multiplication(n / 2, a11, b11), matrix_Multiplication(n / 2, a12, b21));
        int **res12 = matrix_Addition(n / 2, matrix_Multiplication(n / 2, a11, b12), matrix_Multiplication(n / 2, a12, b22));
        int **res21 = matrix_Addition(n / 2, matrix_Multiplication(n / 2, a21, b11), matrix_Multiplication(n / 2, a22, b21));
        int **res22 = matrix_Addition(n / 2, matrix_Multiplication(n / 2, a21, b12), matrix_Multiplication(n / 2, a22, b22));
        
        int **ret = buildMat(n);
        
        combineMat(ret, res11, 0, n / 2 - 1, 0, n / 2 - 1);
        combineMat(ret, res12, 0, n / 2 - 1, n / 2, n - 1);
        combineMat(ret, res21, n / 2, n - 1, 0, n / 2 - 1);
        combineMat(ret, res22, n / 2, n - 1, n / 2, n - 1);
        
        return ret;
}

// Square Matrices Multiplication having dimension in power of 2 only!

int main() {
        int n;
        scanf("%d", &n);
        int **a = buildMat(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int **b = buildMat(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &b[i][j]);
            }
        }
        int **res = matrix_Multiplication(n, a, b);
        
        printf("A : \n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        printf("B : \n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", b[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        printf("A x B : \n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", res[i][j]);
            }
            printf("\n");
        }
}