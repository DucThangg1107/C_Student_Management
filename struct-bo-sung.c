#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ===== STRUCT ===== */
typedef struct sinhVien
{
    char ma[12];
    char ten[31];
    float dtoan, dly, dhoa;
} sinhVien;

/* ===== NHAP 1 SINH VIEN ===== */
void nhapSinhVien(sinhVien* sv)
{
    printf("Nhap ma: ");
    scanf("%s", sv->ma);

    printf("Nhap ten: ");
    getchar();                 // xoa '\n'
    gets_s(sv->ten);

    printf("Nhap diem toan: ");
    scanf("%f", &sv->dtoan);

    printf("Nhap diem ly: ");
    scanf("%f", &sv->dly);

    printf("Nhap diem hoa: ");
    scanf("%f", &sv->dhoa);
}

/* ===== TINH TBC ===== */
float tbc(sinhVien sv)
{
    return (sv.dtoan + sv.dly + sv.dhoa) / 3;
}

/* ===== XUAT 1 SINH VIEN ===== */
void xuatSinhVien(sinhVien* sv)
{
    printf("%-15s %-25s %10.2f %10.2f %10.2f %10.2f\n",
        sv->ma,
        sv->ten,
        sv->dtoan,
        sv->dly,
        sv->dhoa,
        tbc(*sv));
}

/* ===== TAO DANH SACH ===== */
sinhVien* taoDanhSach(int* n)
{
    do
    {
        printf("Nhap so luong sinh vien: ");
        scanf("%d", n);
    } while (*n <= 0);

    sinhVien* ds = (sinhVien*)malloc((*n) * sizeof(sinhVien));
    if (ds == NULL)
    {
        printf("Khong du bo nho!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++)
    {
        printf("\nSinh vien %d\n", i + 1);
        nhapSinhVien(&ds[i]);
    }

    return ds;
}

/* ===== SINH VIEN DTB CAO NHAT ===== */
void maxDTB(sinhVien* sv, int n)
{
    if (sv == NULL || n == 0)
    {
        printf("Chua co danh sach!\n");
        return;
    }

    float max = tbc(sv[0]);
    for (int i = 1; i < n; i++)
        if (tbc(sv[i]) > max)
            max = tbc(sv[i]);

    printf("\nSINH VIEN CO DTB CAO NHAT\n");
    printf("============================================================\n");
    for (int i = 0; i < n; i++)
        if (tbc(sv[i]) == max)
            xuatSinhVien(&sv[i]);
}

/* ===== DEM SINH VIEN ROT ===== */
int demRot(sinhVien* sv, int n)
{
    int dem = 0;
    for (int i = 0; i < n; i++)
        if (tbc(sv[i]) < 5)
            dem++;
    return dem;
}

/* ===== HOAN DOI ===== */
void swap(sinhVien* a, sinhVien* b)
{
    sinhVien temp = *a;
    *a = *b;
    *b = temp;
}

/* ===== SAP XEP THEO DTB ===== */
void sapXepTheoDiem(sinhVien* sv, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tbc(sv[i]) > tbc(sv[j]))
                swap(&sv[i], &sv[j]);

    printf("\nDANH SACH SAU KHI SAP XEP\n");
    printf("============================================================\n");
    for (int i = 0; i < n; i++)
        xuatSinhVien(&sv[i]);
}

/* ===== GHI FILE ===== */
void ghiFile(sinhVien* sv, int n, const char* tenFile)
{
    if (sv == NULL || n == 0)
    {
        printf("Khong co du lieu de ghi!\n");
        return;
    }

    FILE* f = fopen(tenFile, "w");
    if (f == NULL)
    {
        printf("Khong mo duoc file!\n");
        return;
    }

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%s;%s;%.2f;%.2f;%.2f\n",
            sv[i].ma,
            sv[i].ten,
            sv[i].dtoan,
            sv[i].dly,
            sv[i].dhoa);
    }

    fclose(f);
    printf("Da ghi file: %s\n", tenFile);
}

/* ===== DOC FILE ===== */
sinhVien* docFile(int* n, const char* tenFile)
{
    FILE* f = fopen(tenFile, "r");
    if (f == NULL)
    {
        printf("Khong mo duoc file!\n");
        return NULL;
    }

    fscanf(f, "%d\n", n);

    sinhVien* ds = (sinhVien*)malloc((*n) * sizeof(sinhVien));
    if (ds == NULL)
    {
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *n; i++)
    {
        fscanf(f, "%[^;];%[^;];%f;%f;%f\n",
            ds[i].ma,
            ds[i].ten,
            &ds[i].dtoan,
            &ds[i].dly,
            &ds[i].dhoa);
    }

    fclose(f);
    printf("Da doc file: %s\n", tenFile);
    return ds;
}

/* ===== MENU ===== */
void menu()
{
    printf("\n========== MENU ==========\n");
    printf("1. Nhap danh sach sinh vien\n");
    printf("2. Xuat danh sach sinh vien\n");
    printf("3. Sinh vien DTB cao nhat\n");
    printf("4. Dem sinh vien rot\n");
    printf("5. Sap xep theo DTB\n");
    printf("6. Ghi danh sach ra file\n");
    printf("7. Doc danh sach tu file\n");
    printf("0. Thoat\n");
    printf("==========================\n");
    printf("Chon: ");
}

/* ===== MAIN ===== */
int main()
{
    sinhVien* ds = NULL;
    int n = 0;
    int chon;

    do
    {
        menu();
        scanf("%d", &chon);

        switch (chon)
        {
        case 1:
            if (ds != NULL) free(ds);
            ds = taoDanhSach(&n);
            break;

        case 2:
            if (ds == NULL) break;
            for (int i = 0; i < n; i++)
                xuatSinhVien(&ds[i]);
            break;

        case 3:
            maxDTB(ds, n);
            break;

        case 4:
            printf("So sinh vien rot: %d\n", demRot(ds, n));
            break;

        case 5:
            sapXepTheoDiem(ds, n);
            break;

        case 6:
            ghiFile(ds, n, "sinhviencontro.txt");
            break;

        case 7:
            if (ds != NULL) free(ds);
            ds = docFile(&n, "sinhviencontro.txt");
            break;

        case 0:
            printf("Thoat chuong trinh!\n");
            break;
        }
    } while (chon != 0);

    if (ds != NULL) free(ds);
    return 0;
}
