
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int UKURAN = 20;

// Struktur data mahasiswa
struct Mahasiswa {
    long long nim;
    string nama;
};

// Struktur Hash Table
class HashTable {
private:
    enum Status {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Slot {
        Mahasiswa data;
        Status status;
    };

    Slot tabel[UKURAN];

    // Hash Function 1
    int hash1(long long key) {
        return key % UKURAN;
    }

    // Hash Function 2
    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    // Constructor
    HashTable() {
        for (int i = 0; i < UKURAN; i++) {
            tabel[i].status = EMPTY;
        }
    }

    // INSERT
    void insert(long long nim, string nama) {
        int awal = hash1(nim);
        int langkah = hash2(nim);

        // Memeriksa apakah NIM sudah ada
        if (search(nim) != -1) {
            cout << "NIM sudah terdaftar!\n";
            return;
        }

        for (int i = 0; i < UKURAN; i++) {
            int indeks = (awal + i * langkah) % UKURAN;

            if (tabel[indeks].status == EMPTY ||
                tabel[indeks].status == DELETED) {

                tabel[indeks].data.nim = nim;
                tabel[indeks].data.nama = nama;
                tabel[indeks].status = OCCUPIED;

                cout << "Data berhasil ditambahkan!\n";
                cout << "NIM       : " << nim << endl;
                cout << "Nama      : " << nama << endl;
                cout << "Indeks    : " << indeks << endl;

                if (i > 0) {
                    cout << "Collision : Terjadi " << i
                         << " kali percobaan sebelum menemukan slot.\n";
                }

                return;
            }
        }

        cout << "Data gagal ditambahkan!\n";
        cout << "Tidak ditemukan slot kosong pada jalur probing.\n";
    }

    // SEARCH
    int search(long long nim) {
        int awal = hash1(nim);
        int langkah = hash2(nim);

        for (int i = 0; i < UKURAN; i++) {
            int indeks = (awal + i * langkah) % UKURAN;

            if (tabel[indeks].status == EMPTY) {
                return -1;
            }

            if (tabel[indeks].status == OCCUPIED &&
                tabel[indeks].data.nim == nim) {
                return indeks;
            }
        }

        return -1;
    }

    // REMOVE
    void remove(long long nim) {
        int indeks = search(nim);

        if (indeks == -1) {
            cout << "Data mahasiswa tidak ditemukan!\n";
            return;
        }

        tabel[indeks].status = DELETED;

        cout << "Data mahasiswa berhasil dihapus!\n";
        cout << "NIM   : " << nim << endl;
        cout << "Indeks: " << indeks << endl;
    }

    // DISPLAY
    void display() {
        cout << "\n========== HASH TABLE ==========\n";

        cout << left
             << setw(10) << "Indeks"
             << setw(18) << "NIM"
             << setw(25) << "Nama"
             << "Status\n";

        cout << "---------------------------------------------------------\n";

        for (int i = 0; i < UKURAN; i++) {
            cout << left << setw(10) << i;

            if (tabel[i].status == OCCUPIED) {
                cout << setw(18) << tabel[i].data.nim
                     << setw(25) << tabel[i].data.nama
                     << "Terisi\n";
            } else if (tabel[i].status == DELETED) {
                cout << setw(18) << "-"
                     << setw(25) << "-"
                     << "Deleted\n";
            } else {
                cout << setw(18) << "-"
                     << setw(25) << "-"
                     << "Kosong\n";
            }
        }

        cout << "============================================\n";
    }

    // Menampilkan hasil pencarian
    void cariMahasiswa(long long nim) {
        int indeks = search(nim);

        if (indeks == -1) {
            cout << "Mahasiswa dengan NIM " << nim
                 << " tidak ditemukan.\n";
        } else {
            cout << "\nMahasiswa ditemukan!\n";
            cout << "NIM   : " << tabel[indeks].data.nim << endl;
            cout << "Nama  : " << tabel[indeks].data.nama << endl;
            cout << "Indeks: " << indeks << endl;
        }
    }

    // Pengujian otomatis minimal 15 data
    void pengujianOtomatis() {
        long long nim[] = {
            114, 494, 874, 1254, 1634,
            2014, 2394, 2774, 3154, 3534,
            3914, 4294, 4674, 5054, 5434
        };

        string nama[] = {
            "Andi", "Budi", "Citra", "Dina", "Eko",
            "Fajar", "Gita", "Hendra", "Indah", "Joko",
            "Kiki", "Lina", "Maya", "Nanda", "Oscar"
        };

        cout << "\n===== PENGUJIAN OTOMATIS =====\n";

        for (int i = 0; i < 15; i++) {
            cout << "\nData ke-" << i + 1 << endl;
            insert(nim[i], nama[i]);
        }

        cout << "\n===== HASIL PENGUJIAN INSERT =====\n";
        display();

        cout << "\n===== PENGUJIAN SEARCH =====\n";
        cariMahasiswa(1634);

        cout << "\n===== PENGUJIAN REMOVE =====\n";
        remove(874);

        cout << "\n===== HASIL SETELAH REMOVE =====\n";
        display();

        cout << "\n===== PENGUJIAN SEARCH SETELAH REMOVE =====\n";
        cariMahasiswa(874);

        cout << "\n===== PENGUJIAN DATA SETELAH REMOVE =====\n";
        cariMahasiswa(1254);
    }
};

// Program utama
int main() {
    HashTable hash;

    int pilihan;

    do {
        cout << "\n====================================\n";
        cout << "   SISTEM DATA MAHASISWA\n";
        cout << "       HASH TABLE\n";
        cout << "====================================\n";
        cout << "1. Insert Data Mahasiswa\n";
        cout << "2. Search Data Mahasiswa\n";
        cout << "3. Remove Data Mahasiswa\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Pengujian Otomatis (15 Data)\n";
        cout << "0. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (pilihan) {
            case 1: {
                long long nim;
                string nama;

                cout << "Masukkan NIM: ";

                if (!(cin >> nim) || nim <= 0) {
                    cout << "NIM harus berupa angka positif!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan Nama: ";
                getline(cin, nama);

                if (nama.empty()) {
                    cout << "Nama tidak boleh kosong!\n";
                    break;
                }

                hash.insert(nim, nama);
                break;
            }

            case 2: {
                long long nim;

                cout << "Masukkan NIM yang dicari: ";

                if (!(cin >> nim) || nim <= 0) {
                    cout << "NIM tidak valid!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                hash.cariMahasiswa(nim);
                break;
            }

            case 3: {
                long long nim;

                cout << "Masukkan NIM yang akan dihapus: ";

                if (!(cin >> nim) || nim <= 0) {
                    cout << "NIM tidak valid!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                hash.remove(nim);
                break;
            }

            case 4:
                hash.display();
                break;

            case 5:
                hash.pengujianOtomatis();
                break;

            case 0:
                cout << "Program selesai. Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}
