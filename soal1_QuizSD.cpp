#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Struktur Node Single Linked List
struct Mahasiswa {
    string nim;
    string nama;
    float nilai;
    Mahasiswa* next;
};

// Class untuk mengelola data mahasiswa
class DataMahasiswa {
private:
    Mahasiswa* head;
    vector<float> daftarNilai;

public:
    DataMahasiswa() {
        head = nullptr;
    }

    // Menambahkan data mahasiswa
    void tambahMahasiswa(string nim, string nama, float nilai) {
        Mahasiswa* baru = new Mahasiswa;

        baru->nim = nim;
        baru->nama = nama;
        baru->nilai = nilai;
        baru->next = nullptr;

        if (head == nullptr) {
            head = baru;
        } else {
            Mahasiswa* bantu = head;

            while (bantu->next != nullptr) {
                bantu = bantu->next;
            }

            bantu->next = baru;
        }

        daftarNilai.push_back(nilai);

        cout << "Data mahasiswa berhasil ditambahkan!\n";
    }

    // Menampilkan seluruh data mahasiswa
    void tampilkanMahasiswa() {
        if (head == nullptr) {
            cout << "Belum ada data mahasiswa.\n";
            return;
        }

        Mahasiswa* bantu = head;

        cout << "\n========== DATA MAHASISWA ==========\n";
        cout << left << setw(15) << "NIM"
             << setw(25) << "Nama"
             << "Nilai\n";

        cout << "-----------------------------------------------\n";

        while (bantu != nullptr) {
            cout << left << setw(15) << bantu->nim
                 << setw(25) << bantu->nama
                 << fixed << setprecision(2)
                 << bantu->nilai << endl;

            bantu = bantu->next;
        }
    }

    // Linear Search berdasarkan NIM
    void cariNIM(string nimCari) {
        Mahasiswa* bantu = head;
        int posisi = 1;

        while (bantu != nullptr) {
            if (bantu->nim == nimCari) {
                cout << "\nMahasiswa ditemukan!\n";
                cout << "NIM   : " << bantu->nim << endl;
                cout << "Nama  : " << bantu->nama << endl;
                cout << "Nilai : " << bantu->nilai << endl;
                cout << "Posisi: " << posisi << endl;
                return;
            }

            bantu = bantu->next;
            posisi++;
        }

        cout << "\nMahasiswa dengan NIM " << nimCari
             << " tidak ditemukan.\n";
    }

    // Insertion Sort untuk Dynamic Array
    void insertionSort() {
        if (daftarNilai.empty()) {
            cout << "Belum ada nilai untuk diurutkan.\n";
            return;
        }

        for (int i = 1; i < daftarNilai.size(); i++) {
            float key = daftarNilai[i];
            int j = i - 1;

            while (j >= 0 && daftarNilai[j] > key) {
                daftarNilai[j + 1] = daftarNilai[j];
                j--;
            }

            daftarNilai[j + 1] = key;
        }

        cout << "\nNilai berhasil diurutkan!\n";
        tampilkanNilai();
    }

    // Menampilkan Dynamic Array
    void tampilkanNilai() {
        cout << "\n========== DAFTAR NILAI ==========\n";

        for (int i = 0; i < daftarNilai.size(); i++) {
            cout << daftarNilai[i];

            if (i < daftarNilai.size() - 1) {
                cout << " -> ";
            }
        }

        cout << endl;
    }

    // Binary Search berdasarkan nilai
    void binarySearch(float nilaiCari) {
        if (daftarNilai.empty()) {
            cout << "Belum ada nilai untuk dicari.\n";
            return;
        }

        int kiri = 0;
        int kanan = daftarNilai.size() - 1;
        bool ditemukan = false;

        while (kiri <= kanan) {
            int tengah = kiri + (kanan - kiri) / 2;

            if (daftarNilai[tengah] == nilaiCari) {
                cout << "\nNilai " << nilaiCari
                     << " ditemukan pada indeks: ";

                // Menampilkan seluruh posisi nilai yang sama
                int awal = tengah;
                int akhir = tengah;

                while (awal > 0 &&
                       daftarNilai[awal - 1] == nilaiCari) {
                    awal--;
                }

                while (akhir < daftarNilai.size() - 1 &&
                       daftarNilai[akhir + 1] == nilaiCari) {
                    akhir++;
                }

                for (int i = awal; i <= akhir; i++) {
                    cout << i;

                    if (i < akhir) {
                        cout << ", ";
                    }
                }

                cout << endl;
                ditemukan = true;
                break;

            } else if (daftarNilai[tengah] < nilaiCari) {
                kiri = tengah + 1;
            } else {
                kanan = tengah - 1;
            }
        }

        if (!ditemukan) {
            cout << "\nNilai " << nilaiCari
                 << " tidak ditemukan.\n";
        }
    }

    // Destructor untuk membebaskan memori Linked List
    ~DataMahasiswa() {
        Mahasiswa* bantu = head;

        while (bantu != nullptr) {
            Mahasiswa* hapus = bantu;
            bantu = bantu->next;
            delete hapus;
        }
    }
};

// Program utama
int main() {
    DataMahasiswa data;
    int pilihan;

    do {
        cout << "\n====================================\n";
        cout << "    SISTEM DATA MAHASISWA\n";
        cout << "====================================\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Cari Mahasiswa berdasarkan NIM\n";
        cout << "4. Urutkan Nilai (Insertion Sort)\n";
        cout << "5. Cari Nilai (Binary Search)\n";
        cout << "6. Tampilkan Daftar Nilai\n";
        cout << "0. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string nim, nama;
                float nilai;

                cout << "\nMasukkan NIM   : ";
                cin >> nim;

                cin.ignore(10000, '\n');

                cout << "Masukkan Nama  : ";
                getline(cin, nama);

                cout << "Masukkan Nilai : ";
                cin >> nilai;

                if (cin.fail() || nilai < 0 || nilai > 100) {
                    cout << "Input nilai tidak valid! Nilai harus 0-100.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                data.tambahMahasiswa(nim, nama, nilai);
                break;
            }

            case 2:
                data.tampilkanMahasiswa();
                break;

            case 3: {
                string nimCari;

                cout << "Masukkan NIM yang dicari: ";
                cin >> nimCari;

                data.cariNIM(nimCari);
                break;
            }

            case 4:
                data.insertionSort();
                break;

            case 5: {
                float nilaiCari;

                cout << "Masukkan nilai yang dicari: ";
                cin >> nilaiCari;

                if (cin.fail()) {
                    cout << "Input nilai tidak valid!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                data.binarySearch(nilaiCari);
                break;
            }

            case 6:
                data.tampilkanNilai();
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
