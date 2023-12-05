#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct{
    char wilayah;
    int persentase;
    int jumlahPendaftar;
    int kuotaWilayah;
}adminData;

typedef struct{
    char nama[100];
    char gender[10];
    int umur;
    char address[10];
    unsigned long long int no_ktp;
    unsigned long long int no_kk;
    int tanggungan;
    int gaji;
    int waktu_tunggu;
    int total_biaya;
    bool isInvalid;
}userdata;

typedef struct{
    int minwaktu;
    int kuota;
    int address;
}parameter;

void inputdatabase(adminData *admin);
void infouser(userdata *user, adminData *admin, int jumlah);
void prosesWaktu(userdata *user, adminData *admin, parameter *data, int jumlah);
void prosesBiaya(userdata *user);
void printData();

int main(){
    int jumlah;

    adminData *admin = (adminData*) malloc(5 * sizeof(adminData));
    inputdatabase(admin);

    printf("Masukkan Jumlah Pendaftar :");
    scanf("%d", &jumlah);

    userdata *user = (userdata*) malloc(jumlah * sizeof(userdata));
    infouser(user, admin, jumlah);

    parameter *data = (parameter*) malloc(5 * sizeof(parameter));
    prosesWaktu(user, admin, data, jumlah);
    prosesBiaya(user);
    printData();
}

void inputdatabase(adminData *admin){
    const char *wilayah[] = {"Jakarta", "Bogor", "Depok", "Tangerang", "Bekasi"};

    for (int i = 0; i < 5; i++) {
        strcpy(admin[i].wilayah, (wilayah + i));
    }
    int i, total;
    float total1 = 0, temp;

    printf("Masukkan Total Kuota : ");
    scanf("%d", &total);

    for(i = 0; i < 5; i++){
        printf("Masukkan Persentase Muslim di wilayah %s : ", wilayah[i]);
        scanf("%d", &admin[i].persentase);
        printf("Masukkan Jumlah Pendaftar Sementara Dari Wilayah %s : ", wilayah[i]);
        scanf("%d", &admin[i].jumlahPendaftar);
        total1 += (float)(admin[i].persentase / 100);
    }
    for(i = 0; i < 5; i++){
        temp = (float)(((admin[i].persentase / 100) / total1) * total);
        admin[i].kuotaWilayah = (int) round(temp);
    }
}

void infouser(userdata *user, adminData *admin, int jumlah){
    int i, j;

    for(i = 0;i < jumlah; i++){
        printf("///===Data Ke - %d===///\n", i+1);

        getchar();
        printf("Masukkan Nama :");
        scanf("%[^\n]s", user[i].nama);

        printf("Masukkan Umur :");
        scanf("%d", &user[i].umur);
        if(user[i].umur >= 17){
            printf("Masukkan Nomor KTP :");
            scanf("%llu", &user[i].no_ktp);
            printf("Masukkan Nomor KK :");
            scanf("%llu", &user[i].no_kk);
        } else if(user[i].umur < 17 && user[i].umur >= 12){
            printf("Masukkan Nomor KK :");
            scanf("%llu", &user[i].no_kk);
        } else if(user[i].umur < 12){
            printf("Data ke - %d Tidak Valid\n", i+1);
            user[i].isInvalid = true;
            continue;
        }
        getchar();
        printf("Masukkan Jenis Kelamin : ");
        scanf("%[^\n]s", user[i].gender);

        int found = 0;
        do{
            getchar();
            printf("Masukkan Domisili Provinsi : ");
            scanf("%[^\n]s", user[i].address);

            for(j = 0; j < 5; i++){
                if(strcmp(user[i].address, admin[j].wilayah) == 0){
                    found = 1;
                    break;
                }
            }
            if(!found){
                printf("Alamat tidak sesuai dengan wilayah yang ada atau penulisan tidak sesuai format\n");
            }
        } while (!found);

        printf("Masukkan Banyak Tanggungan : ");
        scanf("%d", &user[i].tanggungan);
        printf("Masukkan Gaji : ");
        scanf("%d", &user[i].gaji);
    }
}

void prosesWaktu(userdata *user, adminData *admin, parameter *data, int jumlah){
    int i,j;
    float temp;

    for(i = 0; i < 5; i++){
        data[i].kuota = admin[i].jumlahPendaftar % admin[i].kuotaWilayah;  //kuota tersedia di setiap tahunnya
        temp = admin[i].jumlahPendaftar / admin[i].kuotaWilayah;
        data[i].minwaktu = (int)floor(temp) + 1;  //waktu tunggu minimum
        data[i].address = i;
    }
    for(i = 0; i < jumlah; i++){
        for(j = 0; j < 5; j++){
            if(strcmp(user[i].address, admin[j].wilayah) == 0){
                user[i].waktu_tunggu = data[i].minwaktu;
            }   
        }
    }
    for(i = 0; i < jumlah; i++){
        if(user[i].umur < 20){
            user[i].waktu_tunggu += 16;
        } else if(user[i].umur >= 20 && user[i].umur < 40){
            user[i].waktu_tunggu += 12;
        } else if(user[i].umur >= 40 && user[i].umur < 60){
            user[i].waktu_tunggu += 8;
        } else if(user[i].umur >= 60 && user[i].umur < 80){
            user[i].waktu_tunggu += 4;
        }
        te
        data[j].kuota ++;
        for(j = 0; j < 5; j++){
            if(data[j].kuota > admin[j].kuotaWilayah){
                user[i].waktu_tunggu += 1;
            }
        }
    }

}

void prosesBiaya(userdata *user){

}

void printData(){

}


/*Ini Klo mau make login-loginan
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isAdmin; // Menandakan apakah pengguna merupakan admin (1) atau bukan (0)
};

struct User users[MAX_USERS];
int num_users = 0;

void registerUser() {
    if (num_users >= MAX_USERS) {
        printf("Maaf, jumlah pengguna sudah mencapai batas maksimum.\n");
        return;
    }

    printf("Pendaftaran Pengguna\n");
    printf("Masukkan username: ");
    scanf("%s", users[num_users].username);
    printf("Masukkan password: ");
    scanf("%s", users[num_users].password);
    users[num_users].isAdmin = 0; // Set default pengguna bukan admin

    num_users++;
    printf("Pendaftaran berhasil!\n");
}

void adminLogin() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Admin\n");
    printf("Masukkan username admin: ");
    scanf("%s", username);
    printf("Masukkan password admin: ");
    scanf("%s", password);

    // Lakukan verifikasi untuk login admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Login admin berhasil!\n");

        // Tampilkan daftar pengguna
        printf("Daftar Pengguna:\n");
        for (int i = 0; i < num_users; i++) {
            printf("%s\n", users[i].username);
        }
    } else {
        printf("Login admin gagal, periksa kembali username dan password admin Anda.\n");
    }
}

int loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Pengguna\n");
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Selamat datang, %s!\n", username);
            return users[i].isAdmin; // Kembalikan status apakah pengguna merupakan admin atau bukan
        }
    }

    printf("Login gagal, periksa kembali username dan password Anda.\n");
    return -1; // Login gagal
}

int main() {
    int choice;

    while (1) {
        printf("\nPilihan:\n");
        printf("1. Register\n");
        printf("2. Login Pengguna\n");
        printf("3. Login Admin\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan (1/2/3/4): ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    // Lakukan sesuatu setelah login pengguna berhasil
                }
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("Terima kasih! Sampai jumpa lagi.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan pilih 1, 2, 3, atau 4.\n");
        }
    }

    return 0;
}*/

