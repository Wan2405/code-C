#include <stdio.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535

// Khai bao ham xu ly

void xuLyFile(const char *, const char *,
              int *, int *, int *, int *, char *);

void xuatFile(const char *, const char *, float *, float *, float *);
void inputLoi(float *, float *, float *, int);

int checkFibonacci(int);

int tongUocSoRieng(int);

float banhChung(int);

float banhGiay(int);

void khongNau(float *, float *, float *, int);

void toiUuDungNhieuNepNhat(int n, int dc, int dg, int ld, float *bc, float *bg, float *nd);

void thoiTietFog(int, int, int, int, int, int *, float *, float *, float *);

void thoiTietWind(int, int, int, int, int, int *, float *, float *, float *);

void thoiTietCloud(int, int, int, int, int, int *, float *, float *, float *);

void thoiTietSun(int *, int, int, int *, char *);

void thoiTietRain(int, int, int, int, int, int *, float *, float *, float *);

// Ham main
int main()
{
    int n, dc, dg, ld, a, b;
    float bc = 0, bg = 0, nd = 0;
    char thoiTiet[100];

    xuLyFile("input.inp", "output.out", &n, &dc, &dg, &ld, thoiTiet);
    if (dc < 0 || dg < 0 || n <= 0 || n > 2000 || ld < 1 || ld > 600)
    {
        inputLoi(&bc, &bg, &nd, n);
        xuatFile("input.inp", "output.out", &bc, &bg, &nd);
        return 0;
    }
    if (dc < 8)
        a = 1;
    else
        a = 2;
    if (dg < 5)
        b = 1;
    else
        b = 2;
    if (strcmp(thoiTiet, "Sun") == 0)
        thoiTietSun(&n, dc, dg, &ld, thoiTiet);
    if (strcmp(thoiTiet, "Wind") == 0)
        thoiTietWind(n, dc, dg, a, b, &ld, &bc, &bg, &nd);
    if (strcmp(thoiTiet, "Fog") == 0)
        thoiTietFog(n, dc, dg, a, b, &ld, &bc, &bg, &nd);
    if (strcmp(thoiTiet, "Rain") == 0)
        thoiTietRain(n, dc, dg, a, b, &ld, &bc, &bg, &nd);
    if (strcmp(thoiTiet, "Cloud") == 0)
    {
        if (tongUocSoRieng(n) == ld && tongUocSoRieng(ld) == n)
            khongNau(&bc, &bg, &nd,n);
        else
            thoiTietCloud(n, dc, dg, a, b, &ld, &bc, &bg, &nd);
    };

    xuatFile("input.inp", "output.out", &bc, &bg, &nd);
    return 0;
}

// Ham de xu ly du lieu tu file input.inp
void xuLyFile(const char *tenFileIn, const char *tenFileOut,
              int *nep, int *canh, int *duongKinh, int *laDong, char *thoiTiet)
{
    FILE *fin = fopen(tenFileIn, "r");
    fscanf(fin, "%d %d %d %d %s", nep, canh, duongKinh, laDong, thoiTiet);
    fclose(fin);
}

// Ham de xuat cac gia tri ra file output.out
void xuatFile(const char *tenFileIn, const char *tenFileOut, float *bc, float *bg, float *nd)
{
    FILE *fout = fopen(tenFileOut, "w");
    fprintf(fout, "%.0f %.0f %.3f", *bc, *bg, *nd);
    fclose(fout);
}

void inputLoi(float *bc, float *bg, float *nd, int n)
{
    *bc = -1;
    *bg = -1;
    *nd = n;
}

// Ham kiem tra coi dc voi dg co thuoc day fibinacci hay khong
int checkFibonacci(int n)
{
    int a = 0, b = 1;
    if (n == a || n == b)
        return 1;

    while (b <= n)
    {
        int temp = a + b;
        a = b;
        b = temp;
        if (b == n)
            return 1;
    }
    return 0;
}

// Ham kiem tra coi dc voi dg co phai la so ban be khong
int tongUocSoRieng(int n)
{
    int tong = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            tong += i;
        }
    }
    return tong;
}

// Tinh so nep can cho 1 banh chung
float banhChung(int dc)
{
    return pow(dc, 2) * sqrt(dc);
}

// Tinh so nep can cho 1 banh giay
float banhGiay(int dg)
{
    return (pow(dg, 2) * PI) / 3;
}

// Tra ve gia tri 0
void khongNau(float *bc, float *bg, float *nd, int n)
{
    *bc = 0;
    *bg = 0;
    *nd = n;
}

//Tính so banh chung va banh giay toi uu nhat
void toiUuDungNhieuNepNhat(int n, int dc, int dg, int ld, float *bc, float *bg, float *nd) {
    float ndItNhat = n + 1;
    float bcToiUu = 0, bgToiUu = 0, ndToiUu = n;

    int max_bc = fmin(ld, floor(n / banhChung(dc)));
    for (int i = 0; i <= max_bc; i++) {
        int max_bg = fmin(ld - i, floor((n - i * banhChung(dc)) / banhGiay(dg)));
        for (int j = 0; j <= max_bg; j++) {
            float used = i * banhChung(dc) + j * banhGiay(dg);
            float ndConLai = n - used;

            if (ndConLai >= 0 && ndConLai < ndItNhat) {
                ndItNhat = ndConLai;
                bcToiUu = i;
                bgToiUu = j;
                ndToiUu = ndConLai;
            }
        }
    }

    *bc = bcToiUu;
    *bg = bgToiUu;
    *nd = ndToiUu;
}


// Thoi tiet Wind
void thoiTietWind(int n, int dc, int dg, int a, int b, int *ld, float *bc, float *bg, float *nd)
{

    *bc = floor(n / banhChung(dc));
    *nd = n - (*bc * banhChung(dc));
    *ld -= (*bc * a);

    if (*ld > 0)
    {
        *ld -= (*bg * b);
        *bg = floor(*nd / banhGiay(dg));
        if (*bg > *ld)
            *bg = *ld;
        *nd -= (*bg * banhGiay(dg));
    }
    if (*ld <= 0)
    {
        toiUuDungNhieuNepNhat(n, dc, dg, *ld + (*bc * a + *bg * b), bc, bg, nd);
        *ld -= (*bc * a + *bg * b);
    }
}

// Thoi tiet Fog
void thoiTietFog(int n, int dc, int dg, int a, int b, int *ld, float *bc, float *bg, float *nd)
{
    if (checkFibonacci(dc) && checkFibonacci(dg))
    {
        dc = floor(dc/2);
        dg = floor(dg / 2);
    }
    else
    {
        dc *= 2;
        dg *= 2;
    }

    *bc = floor(n / banhChung(dc));
    *nd = n - (*bc * banhChung(dc));
    *ld -= (*bc * a);

    if (*ld > 0)
    {
        *bg = floor(*nd / banhGiay(dg));
        if (*bg > *ld)
            *bg = *ld;
        *nd -= (*bg * banhGiay(dg));
        *ld -= (*bg * b);
    }
    if (*ld <= 0)
    {
        toiUuDungNhieuNepNhat(n, dc, dg, *ld + (*bc * a + *bg * b), bc, bg, nd);
        *ld -= (*bc * a + *bg * b);
    }
}

// Thoi tiet Sun
void thoiTietSun(int *n, int dc, int dg, int *ld, char *w)
{
    int X = 0,
        G = dc % 6,
        H = *ld % 5;
    if (G == H)
        X = 5;
    else if (G - H == 1)
        X = 7;
    else if (G - H == 2 || H - G == 4)
        X = 10;
    else if (G - H == 3 || H - G == 3)
        X = 12;
    else if (G - H == 4 || H - G == 2)
        X = 15;
    else if (G - H == 5 || H - G == 1)
        X = 20;
    *n = *n + (*n * X) / 100;
    *ld = *ld - X;
    if ((dc + dg) % 3 == 0)
        strcpy(w, "Rain");
    else if ((dc + dg) % 3 == 1)
        strcpy(w, "Wind");
    else if ((dc + dg) % 3 == 2)
        strcpy(w, "Cloud");
}

// Thoi tiet Rain
void thoiTietRain(int n, int dc, int dg, int a, int b, int *ld, float *bc, float *bg, float *nd)
{
    int ladong = *ld,
        bChung,
        bGiay;
    float nepdu = 0;

    bChung = *ld / 2;
    bGiay = bChung;
    nepdu = n - (bChung * (banhChung(dc) + banhGiay(dg)));
    ladong -= (bChung * (a + b));
    if (ladong > 0 || nepdu < 0)
    {
        bChung = 0;
        bGiay = 0;
        ladong = *ld;
        nepdu = 0;
        bChung = floor(n / (banhChung(dc) + banhGiay(dg)));
        nepdu = n - (bChung * (banhChung(dc)));
        ladong -= (bChung * (a));
        if (ladong > 0)
        {
            bGiay = floor(nepdu / banhGiay(dg));
            nepdu -= (bGiay * banhGiay(dg));
            if (bGiay > ladong)
                bGiay = ladong;
            ladong -= (bGiay * b);
            nepdu = n - (bChung * (banhChung(dc)));
            nepdu -= (bGiay * banhGiay(dg));
        }
        else if (ladong < 0)
        {
            bChung = *ld;
            bGiay = 0;
            nepdu = n - (bChung * (banhChung(dc)));
            ladong = 0;
        }
        *bc = bChung;
        *bg = bGiay;
        *nd = nepdu;
        *ld = ladong;
    }
    else
    {
        *bc = bChung;
        *bg = bGiay;
        *nd = nepdu;
        *ld = ladong;
    }
}

// Thoi tiet Cloud
void thoiTietCloud(int n, int dc, int dg, int a, int b, int *ld, float *bc, float *bg, float *nd)
{

    *bg = floor(n / banhGiay(dg));
    *nd = n - (*bg * banhGiay(dg));
    *ld -= (*bg * b);

    if (*ld > 0)
    {
        *bc = floor(*nd / banhChung(dc));
        if (*bc > *ld)
            *bc = *ld;
        *nd -= (*bc * banhChung(dc));
        *ld -= (*bc * a);
    }
    if (*ld <= 0)
    {
        toiUuDungNhieuNepNhat(n, dc, dg, *ld + (*bc * a + *bg * b), bc, bg, nd);
        *ld -= (*bc * a + *bg * b);
    }
}