#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct kontak {
    string nomor;
    string nama;
};
kontak dataKontak;

int jumlahData = 0;

void inputData(string nomor, string nama) {
    
    dataKontak.nomor = nomor;
    dataKontak.nama = nama;
    jumlahData++;

    // Simpan ke file eksternal
    ofstream file("db_kontak.txt", ios::app);
    if (file.is_open()) {
        file << nomor << "\t" << nama << "\n";
        file.close();
    } else {
        cout << "Gagal membuka file db_kontak.txt\n";
    }
}

void print() {
    fstream database;
    database.open("db_kontak.txt");
    
    if (!database.is_open()) {
        cout << "Gagal membuka file database.\n";
        return;
    }

    int i = 1;
    string listdata;
    
    cout << "========================================\n";
    cout << " No \t" << "Nomor \t\t" << "Nama \n";
    cout << "========================================\n";

    while (getline(database, listdata)) {
        cout << " "<< i << "\t" << listdata << "\n";
        i++;
    }

    cout << "========================================\n";
    
    database.close(); // Menutup database setelah penggunaan
}

int hitungJumlahBaris(const string &namaDatabase) {
    ifstream database(namaDatabase);
    int jumlahBaris = 0;
    string baris;

    if (database.is_open()) {
        while (getline(database, baris)) {
            jumlahBaris++;
        }
        database.close();
    } else {
        cout << "Gagal membuka database " << namaDatabase << endl;
    }

    return jumlahBaris;
}

void seqSearch(string nomor) {
    int idx = 1;
    string listdata;
    ifstream database;
    database.open("db_kontak.txt");

    while (getline(database, listdata)) {
        kontak dataKontak;  // Membuat objek kontak baru
        // Memisahkan nomor dan nama dari string
        size_t pos = listdata.find('\t');
        dataKontak.nomor = listdata.substr(0, pos);
        dataKontak.nama = listdata.substr(pos + 1);

        if (dataKontak.nomor == nomor) {
            cout << "Data ditemukan pada nomor " << idx << ":\n";
            cout << "Nomor Telepon: " << dataKontak.nomor << "\n";
            cout << "Nama: " << dataKontak.nama << "\n";
            break;  // Keluar dari loop setelah data ditemukan
        }

        idx++;
    }

    if (idx > jumlahData) {
        cout << "Data dengan nomor " << nomor << " tidak ditemukan\n";
    }

    database.close();
}



int main() {
    menu:
    system("cls");
    fstream database;
    string db = "db_kontak.txt";
    jumlahData = hitungJumlahBaris(db);
    int pilih;
    string nama, nomor, inputNo;

    cout << "\n\tMENU\n" << endl;
    cout << "1. Input Nomor Telpon\n2. Print Data\n4. Cari Data\n5. Keluar\n";
    cout << "Pilih (1/2/3) : ";
    cin >> pilih;
    while (pilih != 4) {
        switch (pilih) {
        case 1:
            system("cls");
            cout << "===== Input Biodata =====\n";
            cout << "Masukkan nomor       : ";
            cin >> nomor;
            cin.ignore();
            cout << "Masukkan Nama      : ";
            getline(cin, nama);
            inputData(nomor, nama);
            break;
        case 2:
            system("cls");
            cout << "\n\t    Menampilkan Data \n\n";
            print();
            break;
        case 3:
            system("cls");
            cout << "Masukkan Nomor yang ingin dicari : ";
            cin >> inputNo;
            seqSearch(inputNo);
            cout << "===== Program Selesai =====\n";
            break;

        default:
            break;
        }
        ulang:
        char ops;
        if (pilih != 3) {
            cout << "Lanjut? (y/n) : ";
            cin >> ops;
            if (ops == 'y') {
                goto menu;
            } else if (ops == 'n') {
                break;
            } else {
                goto ulang;
            }
        } else {
            break;
        }
    }
}
