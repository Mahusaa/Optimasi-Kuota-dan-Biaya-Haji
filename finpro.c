/*
Optimasi Kuota dan Biaya Haji
Muhammad Farhan Hanafi, 2206028062, Group 22
Usamah Hafizh Ammar Zaim, 2206055901, Group 22
6 Desember 2023 
ver 1.0
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    char wilayah[50];
    int persentase;
    int jumlahPendaftar;
    int kuotaWilayah;
    unsigned long long int biaya;
    unsigned long long int subsidi;
}adminData;

typedef struct{
    unsigned long long int no_ktp;
    unsigned long long int no_kk;
    long long total_biaya;
    char nama[100];
    char address[20];
    int gender;  
    int umur;
    int tanggungan;
    int gaji;
    int waktu_tunggu;
    int status;
}userdata;

typedef struct{
    int minwaktu;
    int kuota[100];
    int address;
}parameter;

void inputdatabase(adminData *admin);
void infouser(userdata *user, adminData *admin, int jumlah);
void prosesWaktu(userdata *user, adminData *admin, parameter *data, int jumlah);
void prosesBiaya(userdata *user, adminData *admin, int jumlah);
void printData(userdata *user, int jumlah);

int main(){
    int jumlah;

    system("color B");
    printf("\t\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\t\xB3                                                              \xB3\n");
    printf("\t\t\xB3        Selamat Datang di Database Pendaftaran Haji           \xB3\n");
    printf("\t\t\xB3                                                              \xB3\n");
    printf("\t\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n\n");
    printf("\n\n\n\t\tPress any key to continue ....\n");
    getchar();

    parameter *data = (parameter*) malloc(5 * sizeof(parameter));
    adminData *admin = (adminData*) malloc(5 * sizeof(adminData));
    inputdatabase(admin);

    system("cls");
    printf("\n\t\t\t\t******************************************************************************\n");
    printf("\t\t\t\t*                            Isi Informasi Pendaftar                         *\n");
    printf("\t\t\t\t******************************************************************************\n\n\n");
    printf("\t\t\t\tMasukkan Jumlah Pendaftar Haji yang Ingin diinput : ");
    scanf("%d", &jumlah);
    userdata *user = (userdata*) malloc(jumlah * sizeof(userdata));

    infouser(user, admin, jumlah);
    prosesWaktu(user, admin, data, jumlah);
    prosesBiaya(user, admin, jumlah);
    printData(user, jumlah);
    getchar();

// free memory buat alokasi memori
    free(admin);
    free(user);
    free(data);

    return 0;
}

void inputdatabase(adminData *admin){
	int i, total;
	float total1 = 0, temp;
	
    const char *wilayah[] = {"Jakarta", "Bogor", "Depok", "Tangerang", "Bekasi"};

    for (i = 0; i < 5; i++) {
        strcpy(admin[i].wilayah, wilayah[i]);
    }
    
    system("cls");
    printf("\n\t\t\t\t******************************************************************************\n");
    printf("\t\t\t\t*                         Isi Database Informasi Kuota                       *\n");
    printf("\t\t\t\t******************************************************************************\n\n\n");
    printf("\t\t\t\tMasukkan Total Kuota \t\t\t\t\t\t: ");
    scanf("%d", &total);

    for(i = 0; i < 5; i++){
        printf("\t\t\t\tMasukkan Persentase Muslim di wilayah %s\t\t\t: ", wilayah[i]);
        scanf("%d", &admin[i].persentase);
        printf("\t\t\t\tMasukkan Jumlah Pendaftar Sementara Dari Wilayah %s  \t: ", wilayah[i]);
        scanf("%d", &admin[i].jumlahPendaftar);
        total1 += (float)(admin[i].persentase / 100);
    }
    for(i = 0; i < 5; i++){
        temp = (float)(((admin[i].persentase / 100) / total1) * total);
        admin[i].kuotaWilayah = (int) round(temp);
    }

    system("cls");
    printf("\n\t\t\t\t******************************************************************************\n");
    printf("\t\t\t\t*                         Isi Database Informasi Biaya                       *\n");
    printf("\t\t\t\t******************************************************************************\n\n\n");
    printf("\t\t\t\tMasukkan Total Biaya Reguler Per Orang\t: Rp. ");
    scanf("%llu", &admin[0].biaya);
    printf("\t\t\t\tMasukkan Total Subsidi Keseluruhan\t: Rp. ");
    scanf("%llu", &admin[0].subsidi);
}

void infouser(userdata *user, adminData *admin, int jumlah){
    int i, j;
    int flag = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
    int digitcount = 0, digitcount1 = 0;
    unsigned long long int temp, temp1;

    for(i = 0;i < jumlah; i++){
        do{ 
            printf("\n\n\t\t\t\t///==============================Data Ke - %d===============================///\n\n", i+1);
            getchar();
            printf("\t\t\t\tMasukkan Nama\t\t\t: ");
            scanf("%[^\n]s", user[i].nama);

            printf("\t\t\t\tMasukkan Umur\t\t\t: ");
            scanf("%d", &user[i].umur);
            if(user[i].umur >= 12){
                flag = 1;
            } else {
                printf("\t\t\t\tSilakan Ulangi Input Data Ke-%d\n", i+1);
            }
        } while(!flag);

        if(user[i].umur >= 17){
            do{
                printf("\t\t\t\tMasukkan Nomor KTP\t\t: ");
                scanf("%llu", &user[i].no_ktp);
                printf("\t\t\t\tMasukkan Nomor KK\t\t: ");
                scanf("%llu", &user[i].no_kk);
                temp = user[i].no_ktp;
                temp1 = user[i].no_kk;
                while(temp != 0 && temp1 != 0){
                    temp /= 10;
                    digitcount++;
                    temp1 /= 10;
                    digitcount1++;
                }
                if (digitcount == 16 && digitcount1 == 16) {
                    flag1 = 1;
                } else {
                    printf("Input yang dimasukkan harus berjumlah 16 digit\n");
                }   
            } while(!flag1);
        } else if(user[i].umur < 17 && user[i].umur >= 12){
            do{
                printf("\t\t\t\tMasukkan Nomor KK\t\t\t: ");
                scanf("%llu", &user[i].no_kk);
                temp = user[i].no_kk;
                while(temp != 0){
                    temp /= 10;
                    digitcount++;
                }
                if (digitcount == 16) {
                    flag1 = 1;
                } else {
                    printf("Input yang dimasukkan harus berjumlah 16 digit\n");
                }  
            } while(!flag1);
        }
        
        do{
            getchar();
            printf("\t\t\t\tMasukkan Jenis Kelamin\n");
            printf("\t\t\t\t1. Laki - Laki\n");
            printf("\t\t\t\t2. Perempuan\n");
            printf("\t\t\t\tPilihan\t\t\t\t: ");
            scanf("%d", &user[i].gender);
            if(user[i].gender == 1 ||user[i].gender == 2){
                flag2 = 1;
            } else {
                printf("\t\t\t\tInput Tidak Valid\n");
            }
        } while(!flag2);

        do{
            getchar();
            printf("\t\t\t\tMasukkan Domisili wilayah\t: ");
            scanf("%[^\n]s", user[i].address);

            for(j = 0; j < 5; j++){
                if(strcmp(user[i].address, admin[j].wilayah) == 0){
                    flag3 = 1;
                }
            }
            if(!flag2){
                printf("\t\t\t\tAlamat tidak sesuai dengan wilayah yang ada atau penulisan tidak sesuai format\n");
            }
        } while (!flag3);

        printf("\t\t\t\tMasukkan Banyak Tanggungan\t: ");
        scanf("%d", &user[i].tanggungan);
        printf("\t\t\t\tMasukkan Gaji\t\t\t: Rp. ");
        scanf("%d", &user[i].gaji);

        do{
            printf("\t\t\t\tMasukkan Status\n");
            printf("\t\t\t\t1. Belum Menikah\n");
            printf("\t\t\t\t2. Menikah\n");
            printf("\t\t\t\t3. Janda/Duda\n");
            printf("\t\t\t\tPilihan\t\t\t\t: ");
            scanf("%d", &user[i].status);
            if(user[i].status == 1 ||user[i].status == 2||user[i].status == 3){
                flag4 = 1;
            } else {
                printf("\t\t\t\tInput Tidak Valid\n");
            }
        } while(!flag4);
    }
    getchar();
    getchar();
}

void prosesWaktu(userdata *user, adminData *admin, parameter *data, int jumlah){
    int i, j, temp1, flag = 0;
    float temp;

    for(i = 0; i < 5; i++){
        data[i].kuota[0] = admin[i].jumlahPendaftar % admin[i].kuotaWilayah;  //kuota tersedia di setiap tahunnya
        temp = admin[i].jumlahPendaftar / admin[i].kuotaWilayah;
        data[i].minwaktu = (int)floor(temp) + 1;  //waktu tunggu minimum
    }
    for(i = 0; i < jumlah; i++){
        for(j = 0; j < 5; j++){
            if(strcmp(user[i].address, admin[j].wilayah) == 0){
                user[i].waktu_tunggu = data[i].minwaktu;
                data[i].address = j;
            }   
        }
    }
    for(i = 0; i < jumlah; i++){
        if(user[i].umur < 20){
            user[i].waktu_tunggu += 16;
            flag = 16;
        } else if(user[i].umur >= 20 && user[i].umur < 40){
            user[i].waktu_tunggu += 12;
            flag = 12;
        } else if(user[i].umur >= 40 && user[i].umur < 60){
            user[i].waktu_tunggu += 8;
            flag = 8;
        } else if(user[i].umur >= 60 && user[i].umur < 80){
            user[i].waktu_tunggu += 4;
            flag = 4;
        } else if(user[i].umur >= 80){
            flag = 0;
        }

        temp1 = data[i].address;

        if(data[temp1].kuota[flag] < admin[temp1].kuotaWilayah){
            data[temp1].kuota[flag] += 1;
        } else if(data[temp1].kuota[flag] == admin[temp1].kuotaWilayah){
            do{
                user[i].waktu_tunggu += 1;
                flag ++;
                if(data[temp1].kuota[flag] < admin[temp1].kuotaWilayah){
                    data[temp1].kuota[flag] += 1;
                    break;
                }
            } while(data[temp1].kuota[flag] == admin[temp1].kuotaWilayah);
        }
    }
}

void prosesBiaya(userdata *user, adminData *admin, int jumlah){
    int i, frekuensi1 = 0, frekuensi2 = 0, frekuensi3 = 0;
    int frekuensi4 = 0, frekuensi5 = 0, frekuensi6 = 0;
    int frekuensi7 = 0, frekuensi8 = 0,frekuensi9 = 0;
    long double temp;
    int skala = 5000000;
    
    for(i = 0; i < jumlah; i++){
        //Screening Layak Subsidi
        if(user[i].gaji < skala){
            frekuensi1 ++;
        } else if(user[i].gaji >= skala && user[i].gaji < 2 * skala){
            frekuensi2 ++;
        } else if(user[i].gaji >= 2 * skala && user[i].gaji < 3 * skala){
            frekuensi3 ++;
        }
        //Screening Layak Tanggungan dan Status
        switch(user[i].status){
            case(1):
            if(user[i].tanggungan <= 2){
                frekuensi4++;
            } else if(user[i].tanggungan > 2){
                frekuensi5++;
            }
            break;
            case(2):
            if(user[i].tanggungan <= 2){
                frekuensi6++;
            } else if(user[i].tanggungan > 2){
                frekuensi7++;
            }
            break;
            case(3):
            if(user[i].tanggungan <= 2){
                frekuensi8++;
            } else if(user[i].tanggungan > 2){
                frekuensi9++;
            }
            break;
        }
    }

    for(i = 0; i < jumlah; i++){
    //Screening Gaji dan Subsidi
        if(user[i].gaji < skala){
            temp = (0.7 * admin[0].biaya) - ((1/frekuensi1) * 0.5 * 0.5 * admin[0].subsidi);
        } else if (user[i].gaji >= skala && user[i].gaji < 2 * skala){
            temp = (0.75 * admin[0].biaya) - ((1/frekuensi2) * 0.3 * 0.5 * admin[0].subsidi);
        } else if(user[i].gaji >= 2 * skala && user[i].gaji < 3 * skala){
            temp = (0.8 * admin[0].biaya) - ((1/frekuensi3) * 0.2 * 0.5 * admin[0].subsidi);
        } else if(user[i].gaji >= 3 * skala && user[i].gaji < 4 * skala){
            temp = 0.85 * admin[0].biaya;
        } else if(user[i].gaji >= 4 * skala && user[i].gaji < 5 * skala){
            temp = 0.9 * admin[0].biaya;
        } else if(user[i].gaji >= 5 * skala && user[i].gaji < 6 * skala){
            temp = 0.95 * admin[0].biaya;
        }
    //Screening Tanggungan dan Status
        switch(user[i].status){
            case(1):
            if(user[i].tanggungan <= 2){
                temp -= (1/frekuensi4) * 0.05 * 0.2 * admin[0].subsidi;
            } else if(user[i].tanggungan > 2){
                temp -= (1/frekuensi5) * 0.09 * 0.2 * admin[0].subsidi;
            }
            temp -= (1/(frekuensi4 + frekuensi5)) * 0.2 * 0.3 * admin[0].subsidi;
            break;
            case(2):
            if(user[i].tanggungan <= 2){
                temp -= (1/frekuensi6) * 0.14 * 0.2 * admin[0].subsidi;
            } else if(user[i].tanggungan > 2){
                temp -= (1/frekuensi7) * 0.19 * 0.2 * admin[0].subsidi;
            }
            temp -= (1/(frekuensi6 + frekuensi7)) * 0.5 * 0.3 * admin[0].subsidi;
            break;
            case(3):
            if(user[i].tanggungan <= 2){
                temp -= (1/frekuensi8) * 0.24 * 0.2 * admin[0].subsidi;
            } else if(user[i].tanggungan > 2){
                temp -= (1/frekuensi9) * 0.29 * 0.2 * admin[0].subsidi;
            }
            temp -= (1/(frekuensi8 + frekuensi9)) * 0.3 * 0.3 * admin[0].subsidi;
            break;
        }
        if(temp < 0){
            user[i].total_biaya = 0; 
        } else {
            user[i].total_biaya = (long long) round(temp);
        }
    }
}

void printData(userdata *user, int jumlah){
    int i, flag;
    int maxNamaLength = 0;
    int maxaddressLength = 0;
    int maxbiayaLength = 0;
    int maxstatusLength = 0;
    int maxktpLength = 0;
    char arr[3][20];
    char arr1[2][20];

    system("cls");
    printf("\n\t\t\t\t******************************************************************************\n");
    printf("\t\t\t\t*                              Daftar Calon Haji                             *\n");
    printf("\t\t\t\t******************************************************************************\n\n\n");

    for (i = 0; i < jumlah; i++) {
        //Periksa Panjang Maksimum Nama
        int namaLength = strlen(user[i].nama);
        if (namaLength > maxNamaLength) {
            maxNamaLength = namaLength;
        }
        //
        int addressLength = strlen(user[i].address);
        if (addressLength > maxaddressLength) {
            maxaddressLength = addressLength;
        }
        //Periksa panjang maksimum NPM
        int biayaLength = snprintf(NULL, 0, "%lld", user[i].total_biaya);
        if (biayaLength > maxbiayaLength) {
            maxbiayaLength = biayaLength;
        }
        //Periksa panjang maksimum NPM
        int ktpLength = snprintf(NULL, 0, "%llu", user[i].no_ktp);
        if (ktpLength > maxktpLength) {
            maxktpLength = ktpLength;
        }

        switch(user[i].status){
            case(1):
            strcpy(arr[0], "Belum Menikah");
            flag = 0;
            break;
            case(2):
            strcpy(arr[1], "Menikah");
            flag = 1;
            break;
            case(3):
            if(user[i].gender == 1){
                strcpy(arr[2], "Duda");
            } else if(user[i].gender == 2){
                strcpy(arr[2], "Janda");
            }
            flag = 2;
        }

        int statusLength;
        switch(flag){
            case(0):
            statusLength = strlen(arr[0]);
            break;
            case(1):
            statusLength = strlen(arr[1]);
            break;
            case(2):
            statusLength = strlen(arr[2]);
        }
        if (statusLength > maxstatusLength) {
            maxstatusLength = statusLength;
        }
    }
    //Masing" Max dikurangi dengan panjang string masing"
    printf("NO\tNO KK%*s\tNO KTP%*s\tNAMA%*s\tJENIS KELAMIN\tUMUR\t\tASAL%*s\tSTATUS%*s\tWAKTU TUNGGU\tTOTAL BIAYA\n",
            11, "", maxktpLength - 6, "", maxNamaLength - 4, "", maxaddressLength - 4, "", maxstatusLength - 6, "");

    //Dengan Menggunakan Format ini, maka Lebar Kolom akan lebih rapi menyesuaikan dengan panjang string max pada masing" jenis string
    for (i = 0; i < jumlah; i++) {
        printf("%d\t%llu\t%llu\t%-*s\t", i + 1, user[i].no_kk, user[i].no_ktp, maxNamaLength, user[i].nama);
        
        if(user[i].gender == 1){
            strcpy(arr1[0], "Laki-Laki");
            printf("%s\t", arr1[0]);
        } else if(user[i].gender == 2){
            strcpy(arr1[1], "Perempuan");
            printf("%s\t", arr1[1]);
        }
        printf("%d %s\t%s%*s\t", user[i].umur, "Tahun", user[i].address, (int)(maxaddressLength - strlen(user[i].address)), "");

        switch(user[i].status){
            case(1):
            strcpy(arr[0], "Belum Menikah");
            printf("%s%*s\t", arr[0], (int)(maxstatusLength - strlen(arr[0])),"");
            break;
            case(2):
            strcpy(arr[1], "Menikah");
            printf("%s%*s\t", arr[1], (int)(maxstatusLength - strlen(arr[1])),"");
            break;
            case(3):
            if(user[i].gender == 1){
                strcpy(arr[2], "Duda");
            } else if(user[i].gender == 2){
                strcpy(arr[2], "Janda");
            }
            printf("%s%*s\t", arr[2], (int)(maxstatusLength - strlen(arr[2])),"");
        }
        printf("%d %s\t\t%s %lld\n", user[i].waktu_tunggu, "Tahun", "Rp.", user[i].total_biaya);
    }
    printf("\n");
}

