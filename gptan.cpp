#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Kontak {
    string nomor;
    string nama;
};

// Fungsi untuk menginputkan data kontak dan menyimpannya dalam file
void inputData(vector<Kontak>& kontakList) {
    string nomor, nama;
    bool found;
    Kontak kontak;
    cout << "Masukkan nomor telepon: ";
    cin >> nomor;
    cout << "Masukkan nama: ";
    cin.ignore(); // Membersihkan newline di buffer
    getline(cin, nama);

    // Menyimpan data kontak dalam vektor
    
    for (const Kontak& kontak : kontakList) {
        if (kontak.nama == nama || kontak.nomor == nomor) {
            cout << "Nama atau nomor sudah ada\n";
            found = true;
            break;
        }
    }
    if (!found){
        kontak.nomor = nomor;
        kontak.nama = nama;
        kontakList.push_back(kontak);
        ofstream file("db_kontakan.txt", ios::app);
        if (file.is_open()) {
            file << kontak.nomor << "\t" << kontak.nama << "\n";
            file.close();
        } else {
            cerr << "Gagal membuka file db_kontak.txt\n";
        }
    }
}
    // Menyimpan data kontak dalam file eksternal

// Fungsi untuk melakukan sequential search berdasarkan nama atau nomor telepon
void sequentialSearch(const vector<Kontak>& kontakList, const string& query) {
    bool found = false;
    for (const Kontak& kontak : kontakList) {
        if (kontak.nama == query || kontak.nomor == query) {
            cout << "Data ditemukan:\n";
            cout << "Nomor Telepon: " << kontak.nomor << "\n";
            cout << "Nama: " << kontak.nama << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Data dengan nama atau nomor telepon '" << query << "' tidak ditemukan.\n";
    }
}

// Fungsi untuk melakukan binary search berdasarkan nomor telepon
void binarySearch(const vector<Kontak>& kontakList, const string& query) {
    vector<string> nomorTeleponList;

    for (const Kontak& kontak : kontakList) {
        nomorTeleponList.push_back(kontak.nomor);
    }

    sort(nomorTeleponList.begin(), nomorTeleponList.end());

    // Mencari nomor telepon menggunakan binary search
    bool found = binary_search(nomorTeleponList.begin(), nomorTeleponList.end(), query);

    if (found) {
        cout << "Data ditemukan:\n";
        // Mencari data kontak sesuai dengan nomor telepon yang ditemukan
        auto it = find_if(kontakList.begin(), kontakList.end(),
                          [&query](const Kontak& k) { return k.nomor == query; });

        cout << "Nomor Telepon: " << it->nomor << "\n";
        cout << "Nama: " << it->nama << "\n";
    } else {
        cout << "Data dengan nomor telepon '" << query << "' tidak ditemukan.\n";
    }
}
void printData() {
    fstream database;
    database.open("db_kontakan.txt");
    
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


void waktuBin(const vector<Kontak>& kontakList, const string& query){
    auto start_time = chrono::high_resolution_clock::now();
    binarySearch(kontakList, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi binary search : " << duration.count() << " mikrodetik" << endl;
}
void waktuSeq(const vector<Kontak>& kontakList, const string& query){
    auto start_time = chrono::high_resolution_clock::now();
    sequentialSearch(kontakList, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi binary search : " << duration.count() << " mikrodetik" << endl;
}

/// @brief 
/// @return 
int main() {
    vector<Kontak> kontakList;
    fstream inputFile("db_kontakan.txt");

    // Membaca data kontak dari file eksternal saat program dimulai
    if (inputFile.is_open()) {
        string nomor, nama;
        while (inputFile >> nomor >> nama) {
            Kontak kontak;
            kontak.nomor = nomor;
            kontak.nama = nama;
            kontakList.push_back(kontak);
        }
        inputFile.close();
    }
    //ofstream outputFile("db_kontakan.txt");

    int pilihan;
    string query;

    do {
        cout << "\nMENU:\n";
        cout << "1. Input Data Kontak\n";
        cout << "2. Sequential Search\n";
        cout << "3. Binary Search\n";
        cout << "4. Print Data\n";
        cout << "5. Keluar\n";
        cout << "Pilih (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                inputData(kontakList);
                break;
            case 2:
                system("cls");
                cout << "Masukkan nama atau nomor telepon yang dicari: ";
                cin >> query;
                waktuSeq(kontakList, query);
                break;
            case 3:
                system("cls");
                cout << "Masukkan nomor telepon yang dicari: ";
                cin >> query;
                waktuBin(kontakList, query);
                break;
            case 4:
                system("cls");
                printData();
                break;
            case 5:
                system("cls");
                // Menyimpan data kontak ke file sebelum keluar
                /*for (const Kontak& kontak : kontakList) {
                    outputFile << kontak.nomor << "\t" << kontak.nama << "\n";
                }
                outputFile.close();*/
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}
