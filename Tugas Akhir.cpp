#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Kontak
{
    string nomor;
    string nama;
};

// Fungsi untuk menginputkan data kontak dan menyimpannya dalam file

// Fungsi untuk melakukan sequential search berdasarkan nama atau nomor telepon
void sequentialSearch1(const vector<Kontak> &kontakList, const string &query)
{
    int i = 0;
    bool found = false;
    for (const Kontak &kontak : kontakList)
    {
        if (kontakList[i].nama == query)
        {
            cout << "Data ditemukan:\n";
            cout << "Nomor Telepon: " << kontak.nomor << "\n";
            cout << "Nama: " << kontak.nama << "\n";
            found = true;
            break;
        }
        i++;
    }

    if (!found)
    {
        cout << "Data dengan nama '" << query << "' tidak ditemukan.\n";
    }
}

void sequentialSearch2(const vector<Kontak> &kontakList, const string &query)
{
    int i = 0;
    bool found = false;
    for (const Kontak &kontak : kontakList)
    {
        if (kontakList[i].nomor == query)
        {
            cout << "Data ditemukan:\n";
            cout << "Nomor Telepon: " << kontak.nomor << "\n";
            cout << "Nama: " << kontak.nama << "\n";
            found = true;
            break;
        }
        i++;
    }

    if (!found)
    {
        cout << "Data dengan nomor '" << query << "' tidak ditemukan.\n";
    }
}

// Fungsi untuk melakukan binary search berdasarkan nama atau nomor telepon
void binarySearch(const vector<Kontak> &sortedList, const string &query)
{
    bool found = false;

    // Binary search
    int low = 0;
    int high = sortedList.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (sortedList[mid].nama == query)
        {        cout << "Data ditemukan:\n";
            cout << "Nomor Telepon: " << sortedList[mid].nomor << "\n";
            cout << "Nama: " << sortedList[mid].nama << "\n";
            found = true;
            break;
        }
        else if (sortedList[mid].nama < query)
        {
            low = mid + 1;
        }
        else
        {
       
    high = mid - 1;
        }
    }

    if (!found)
    {
        cout << "Data dengan nama atau nomor telepon '" << query << "' tidak ditemukan.\n";
    }
}
void binarySearch1(const vector<Kontak> &sortedListNomor, const string &query)
{
    bool found = false;

    int low = 0;
    int high = sortedListNomor.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (sortedListNomor[mid].nomor == query)
        {
            cout << "Data ditemukan:\n";
            cout << "Nomor Telepon: " << sortedListNomor[mid].nomor << "\n";
            cout << "Nama: " << sortedListNomor[mid].nama << "\n";
            found = true;
            break;
        }
        else if (sortedListNomor[mid].nomor < query)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
     }

    if (!found)
    {
        cout << "Data dengan nama atau nomor telepon '" << query << "' tidak ditemukan.\n";
    }
}


vector<Kontak> sortListByName(const vector<Kontak> &kontakList)
{
    vector<Kontak> sortedList = kontakList;
    sort(sortedList.begin(), sortedList.end(), [](const Kontak &a, const Kontak &b)
         { return a.nama < b.nama; });

    fstream outputFile; // Membuka file untuk penulisan
    outputFile.open("sorted_contacts.txt");

    if (!outputFile.is_open())
    {
        ofstream isi("sorted_contacts.txt", ios::app);
        for (const Kontak &kontak : sortedList) {
        isi << "Nomor Telepon: " << kontak.nomor << "\t";
        isi << "Nama: " << kontak.nama << "\n";
    }
        isi.close();
    }
    

    outputFile.close(); // Menutup file

    return sortedList;
}
vector<Kontak> sortListByNo(const vector<Kontak> &kontakList)
{
    vector<Kontak> sortedList = kontakList;
    sort(sortedList.begin(), sortedList.end(), [](const Kontak &a, const Kontak &b)
         { return a.nomor < b.nomor; });

    fstream outputFile;
    outputFile.open("sorted_contactsNo.txt");

    if (!outputFile.is_open())
    {
        ofstream isi("sorted_contactsNo.txt", ios::app);
        for (const Kontak &kontak : sortedList) {
        isi << "Nomor Telepon: " << kontak.nomor << "\t";
        isi << "Nama: " << kontak.nama << "\n";
    }
        isi.close();
    }

    outputFile.close(); // Menutup file

    return sortedList;
}
void printData()
{
    fstream database;
    database.open("db_kontakan.txt");

    if (!database.is_open())
    {
        cout << "Gagal membuka file database.\n";
        return;
    }

    int i = 1;
    string listdata;

    cout << "========================================\n";
    cout << " No \t"
         << "Nomor \t\t"
         << "Nama \n";
    cout << "========================================\n";

    while (getline(database, listdata))
    {
        cout << " " << i << "\t" << listdata << "\n";
        i++;
    }

    cout << "========================================\n";

    database.close(); // Menutup database setelah penggunaan
}

void waktuBin(const vector<Kontak> &kontakList, const string &query)
{
    auto sortedList = sortListByName(kontakList);

    auto start_time = chrono::high_resolution_clock::now();
    binarySearch(sortedList, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi binary search : " << duration.count() << " mikrodetik" << endl;
}
void waktuBin1(const vector<Kontak> &kontakList, const string &query)
{
    auto sortedListNomor = sortListByNo(kontakList);

    auto start_time = chrono::high_resolution_clock::now();
    binarySearch1(sortedListNomor, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi binary search : " << duration.count() << " mikrodetik" << endl;
}

void waktuSeq(const vector<Kontak> &kontakList, const string &query)
{
    auto sortedListNama = sortListByName(kontakList);
    auto start_time = chrono::high_resolution_clock::now();
    sequentialSearch1(sortedListNama, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi sequential search : " << duration.count() << " mikrodetik" << endl;
}

void waktuSeq1(const vector<Kontak> &kontakList, const string &query)
{
    auto sortedListNo = sortListByNo(kontakList);
    auto start_time = chrono::high_resolution_clock::now();
    sequentialSearch2(sortedListNo, query);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "\nWaktu eksekusi sequential search : " << duration.count() << " mikrodetik" << endl;
}

int main()
{
    vector<Kontak> kontakList;
    vector<Kontak> kontakList1;
    fstream inputFile("db_kontakan.txt");

    // Membaca data kontak dari file eksternal saat program dimulai
    if (inputFile.is_open())
    {
        string nomor, nama;
        while (inputFile >> nomor >> nama)
        {
            Kontak kontak;
            kontak.nomor = nomor;
            kontak.nama = nama;
            kontakList.push_back(kontak);
        }
        inputFile.close();
    }

    int pilihan, pil1, pil2;
    string query;

    do
    {

        cout << "\nMENU:\n";
        cout << "1. Sequential Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Print Data\n";
        cout << "4. Keluar\n";
        cout << "Pilih (1-4): ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            system("cls");
            cout << "1. Cari menggunakan nama\n2. Cari menggunakan nomor" ;
            cout << "\nPilih (1/2) : ";
            cin >> pil2 ;
            if (pil2 == 1)
            {
                cout << "Masukkan nama yang dicari: ";
                cin >> query;
                waktuSeq(kontakList, query);
            }
            else if (pil2 == 2)
            {
                cout << "Masukkan nomor telepon yang dicari: ";
                cin >> query;
                waktuSeq1(kontakList, query);
            }
            break;
        case 2:
            system("cls");
            cout << "1. Cari Menggunakan Nama\n2. Cari Menggunakan Nomor\n";
            cout << "Pilih (1/2) : ";
            cin >> pil1;
            if (pil1 == 1)
            {
                cout << "Masukkan nama yang dicari: ";
                cin >> query;
                waktuBin(kontakList, query);
            }
            else if (pil1 == 2)
            {
                cout << "Masukkan nomor telepon yang dicari: ";
                cin >> query;
                waktuBin1(kontakList, query);
            }
            break;
        case 3:
            system("cls");
            printData();
            break;
        case 4:
            system("cls");
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    } while (pilihan != 4);

    return 0;
}
