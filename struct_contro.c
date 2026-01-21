#include <stdio.h>
#include <stdlib.h>

struct sinhVien
{
    char ma[12];
    char ten[31];
    float dtoan,dly,dhoa;

};
void nhapSinhVien(sinhVien* sv)
{
	printf("Nhap thong tin sinh vien:\n");
	printf("Nhap ma:"); rewind(stdin); gets_s((*sv).ma);
	printf("Nhap ten:"); rewind(stdin); gets_s((*sv).ten);
	printf("Nhap diem toan:"); scanf("%f", &(*sv).dtoan);
    printf("Nhap diem ly:"); scanf("%f", &(*sv).dly);
    printf("Nhap diem hoa:"); scanf("%f", &(*sv).dhoa);
}

float tbc(sinhVien sv)
{
    return (sv.dtoan + sv.dly + sv.dhoa) / 3;
}
void xuatSinhVien(sinhVien* sv)
{
    

    printf("%-15s %-25s %12.2f %12.2f %12.2f %12.2f\n", 
        (*sv).ma,
        (*sv).ten,
        (*sv).dtoan,
        (*sv).dly,
        (*sv).dhoa,
        tbc(*sv));
}
sinhVien* taoDanhSach(int* n)
{
    do
    {
        printf("Nhap n: ");
        scanf("%d", n);
    } while (*n <= 0);

    sinhVien* a;
        a= (sinhVien*)malloc((*n) * sizeof(sinhVien));
    if (a == NULL)
    {
        printf("Khong du bo nho!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++)
    {
        printf("\nSinh vien %d\n", i + 1);
        nhapSinhVien(&a[i]);
    }

    return a;
}

void maxDTB(sinhVien* sv, int n)
{
    if (sv == NULL || n == 0)
    {
        printf("Chua co danh sach sinh vien!\n");
        return;
    }

    float max = tbc(sv[0]);

    for (int i = 1; i < n; i++)
        if (tbc(sv[i]) > max)
            max = tbc(sv[i]);

    printf("\nSINH VIEN CO DTB CAO NHAT\n");
    printf("\n%-15s %-25s %12s %12s %12s %12s\n", "Ma Sinh Vien", "Ten sinh vien", "Diem Toan", "Diem Ly", "Diem Hoa", "TBC");
    printf("===============================================================================================\n");
    for (int i = 0; i < n; i++)
        if (tbc(sv[i]) == max)
            xuatSinhVien(&sv[i]);
}

int demRot(sinhVien* sv, int n)
{
    int dem = 0;
    for (int i = 0; i < n; i++)
    {
        if (tbc(sv[i]) < 5)
        {
            dem++;
        }
    }
    return dem;
}
void swap(sinhVien* a, sinhVien* b)
{
    sinhVien temp = *a;
    *a = *b;
    *b = temp;
}
void sapXepTheoDiem(sinhVien* sv, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tbc(sv[i]) > tbc(sv[j]))
            {
                swap(&sv[i], &sv[j]);
            }
        }
    }
    printf("\nDANH SACH SINH VIEN SAU KHI SAP XEP THEO DIEM TANG DAN\n");
    printf("\n%-15s %-25s %12s %12s %12s %12s\n", "Ma Sinh Vien", "Ten sinh vien", "Diem Toan", "Diem Ly", "Diem Hoa", "TBC");
    printf("===============================================================================================\n");
    for (int i = 0; i < n; i++)
    {
        xuatSinhVien(&sv[i]);
    }
}
void menu()
{
    printf("\n========== MENU ==========\n");
    printf("1. Nhap danh sach sinh vien\n");
    printf("2. Xuat danh sach sinh vien\n");
    printf("3. Sinh vien co DTB cao nhat\n");
    printf("4. Dem sinh vien rot\n");
    printf("5. Sap xep theo DTB tang dan\n");
    printf("0. Thoat\n");
    printf("==========================\n");
    printf("Chon: ");
}

/* ===== MAIN ===== */
int main()
{
    sinhVien* ds = NULL;
    int n = 0;
    int thoat = 1;

    do
    {
        menu();
		int chon;
        printf("Chon bai thay muon xem: ");
        scanf("%d", &chon);

        switch (chon)
        {
        case 1:
            if (ds != NULL)
                free(ds);
            ds = taoDanhSach(&n);
            break;

        case 2:
            if (ds == NULL)
                printf("Chua co danh sach!\n");
            else
            {
                printf("\nDANH SACH SINH VIEN\n");
                printf("\n%-15s %-25s %12s %12s %12s %12s\n", "Ma Sinh Vien", "Ten sinh vien", "Diem Toan", "Diem Ly", "Diem Hoa", "TBC");
                printf("===============================================================================================\n");
               for(int i = 0 ; i < n ; i++)
                    xuatSinhVien(&ds[i]);
            }
            break;

        case 3:
            if (ds == NULL)
                printf("Chua co danh sach!\n");

            maxDTB(ds, n);
            break;

        case 4:
            if (ds == NULL)
                printf("Chua co danh sach!\n");

            printf("So sinh vien rot: %d\n", demRot(ds, n));
            break;

        case 5:
            if (ds == NULL)
                printf("Chua co danh sach!\n");

            sapXepTheoDiem(ds, n);
            break;

        case 0:
            printf("Thoat chuong trinh!\n");
            thoat = 0;
            break;

        default:
            printf("Lua chon khong hop le!\n");
        }

    } while (thoat ==1);

    if (ds != NULL)
        free(ds);

    return 0;
}
