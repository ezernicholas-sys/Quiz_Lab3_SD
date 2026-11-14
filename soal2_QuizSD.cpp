
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <limits>
using namespace std;

// Struktur Node Binary Search Tree
struct Buku {
    int id;
    string judul;
    bool tersedia;
    Buku* kiri;
    Buku* kanan;
};

// Struktur data antrean peminjaman
struct Peminjaman {
    string nim;
    string nama;
    int idBuku;
};

// Struktur data riwayat pengembalian
struct Pengembalian {
    string nim;
    string nama;
    int idBuku;
    string judul;
};

// Class Sistem Perpustakaan
class Perpustakaan {
private:
    queue<Peminjaman> antrean;
    stack<Pengembalian> riwayat;
    Buku* root;

    // Menambahkan buku ke BST
    Buku* insertBuku(Buku* node, int id, string judul) {
        if (node == nullptr) {
            Buku* baru = new Buku;
            baru->id = id;
            baru->judul = judul;
            baru->tersedia = true;
            baru->kiri = nullptr;
            baru->kanan = nullptr;

            return baru;
        }

        if (id < node->id) {
            node->kiri = insertBuku(node->kiri, id, judul);
        } else if (id > node->id) {
            node->kanan = insertBuku(node->kanan, id, judul);
        }

        return node;
    }

    // Mencari buku berdasarkan ID
    Buku* cariBuku(Buku* node, int id) {
        if (node == nullptr || node->id == id) {
            return node;
        }

        if (id < node->id) {
            return cariBuku(node->kiri, id);
        }

        return cariBuku(node->kanan, id);
    }

    // Traversal Pre-Order
    void preOrder(Buku* node) {
        if (node != nullptr) {
            tampilkanBuku(node);
            preOrder(node->kiri);
            preOrder(node->kanan);
        }
    }

    // Traversal In-Order
    void inOrder(Buku* node) {
        if (node != nullptr) {
            inOrder(node->kiri);
            tampilkanBuku(node);
            inOrder(node->kanan);
        }
    }

    // Traversal Post-Order
    void postOrder(Buku* node) {
        if (node != nullptr) {
            postOrder(node->kiri);
            postOrder(node->kanan);
            tampilkanBuku(node);
        }
    }

    // Menampilkan informasi buku
    void tampilkanBuku(Buku* buku) {
        cout << "ID Buku : " << buku->id << endl;
        cout << "Judul   : " << buku->judul << endl;
        cout << "Status  : "
             << (buku->tersedia ? "Tersedia" : "Dipinjam")
             << endl;
        cout << "--------------------------\n";
    }

    // Membebaskan seluruh memori BST
    void hapusBST(Buku* node) {
        if (node != nullptr) {
            hapusBST(node->kiri);
            hapusBST(node->kanan);
            delete node;
        }
    }

public:
    Perpustakaan() {
        root = nullptr;
    }

    // Menambahkan buku
    void tambahBuku(int id, string judul) {
        if (cariBuku(root, id) != nullptr) {
            cout << "ID buku sudah terdaftar!\n";
            return;
        }

        root = insertBuku(root, id, judul);
        cout << "Buku berhasil ditambahkan!\n";
    }

    // Menambahkan mahasiswa ke Queue
    void tambahAntrean(string nim, string nama, int idBuku) {
        Buku* buku = cariBuku(root, idBuku);

        if (buku == nullptr) {
            cout << "ID buku tidak ditemukan!\n";
            return;
        }

        Peminjaman data;
        data.nim = nim;
        data.nama = nama;
        data.idBuku = idBuku;

        antrean.push(data);

        cout << "Mahasiswa berhasil masuk antrean!\n";
    }

    // Menampilkan antrean
    void tampilkanAntrean() {
        if (antrean.empty()) {
            cout << "Antrean peminjaman kosong.\n";
            return;
        }

        queue<Peminjaman> sementara = antrean;

        cout << "\n===== ANTREAN PEMINJAMAN =====\n";

        int nomor = 1;

        while (!sementara.empty()) {
            Peminjaman data = sementara.front();

            cout << "Antrean ke-" << nomor++ << endl;
            cout << "NIM     : " << data.nim << endl;
            cout << "Nama    : " << data.nama << endl;
            cout << "ID Buku : " << data.idBuku << endl;
            cout << "--------------------------\n";

            sementara.pop();
        }
    }

    // Memproses antrean peminjaman
    void prosesPeminjaman() {
        if (antrean.empty()) {
            cout << "Tidak ada mahasiswa dalam antrean.\n";
            return;
        }

        Peminjaman data = antrean.front();
        antrean.pop();

        Buku* buku = cariBuku(root, data.idBuku);

        if (buku == nullptr) {
            cout << "Buku tidak ditemukan. Permintaan dibatalkan.\n";
            return;
        }

        if (!buku->tersedia) {
            cout << "Buku sedang dipinjam.\n";
            cout << "Permintaan peminjaman tidak dapat diproses.\n";
            return;
        }

        buku->tersedia = false;

        cout << "\nPeminjaman berhasil diproses!\n";
        cout << "Nama    : " << data.nama << endl;
        cout << "NIM     : " << data.nim << endl;
        cout << "Judul   : " << buku->judul << endl;
        cout << "ID Buku : " << buku->id << endl;
    }

    // Proses pengembalian buku
    void kembalikanBuku(string nim, string nama, int idBuku) {
        Buku* buku = cariBuku(root, idBuku);

        if (buku == nullptr) {
            cout << "ID buku tidak ditemukan!\n";
            return;
        }

        if (buku->tersedia) {
            cout << "Buku belum tercatat sedang dipinjam!\n";
            return;
        }

        Pengembalian data;
        data.nim = nim;
        data.nama = nama;
        data.idBuku = idBuku;
        data.judul = buku->judul;

        riwayat.push(data);

        buku->tersedia = true;

        cout << "Buku berhasil dikembalikan!\n";
        cout << "Riwayat pengembalian berhasil disimpan.\n";
    }

    // Menampilkan riwayat pengembalian (LIFO)
    void tampilkanRiwayat() {
        if (riwayat.empty()) {
            cout << "Belum ada riwayat pengembalian.\n";
            return;
        }

        stack<Pengembalian> sementara = riwayat;

        cout << "\n===== RIWAYAT PENGEMBALIAN =====\n";
        cout << "(Pengembalian terbaru ditampilkan pertama)\n";

        int nomor = 1;

        while (!sementara.empty()) {
            Pengembalian data = sementara.top();

            cout << "\nRiwayat ke-" << nomor++ << endl;
            cout << "NIM     : " << data.nim << endl;
            cout << "Nama    : " << data.nama << endl;
            cout << "ID Buku : " << data.idBuku << endl;
            cout << "Judul   : " << data.judul << endl;

            sementara.pop();
        }
    }

    // Pencarian buku berdasarkan ID
    void pencarianBuku(int id) {
        Buku* hasil = cariBuku(root, id);

        if (hasil == nullptr) {
            cout << "Buku dengan ID " << id
                 << " tidak ditemukan.\n";
        } else {
            cout << "\nBuku berhasil ditemukan!\n";
            tampilkanBuku(hasil);
        }
    }

    // Menampilkan seluruh traversal BST
    void tampilkanTraversal() {
        if (root == nullptr) {
            cout << "BST masih kosong.\n";
            return;
        }

        cout << "\n===== PRE-ORDER =====\n";
        preOrder(root);

        cout << "\n===== IN-ORDER =====\n";
        inOrder(root);

        cout << "\n===== POST-ORDER =====\n";
        postOrder(root);
    }

    ~Perpustakaan() {
        hapusBST(root);
    }
};

// Program utama
int main() {
    Perpustakaan perpustakaan;
    int pilihan;

    do {
        cout << "\n====================================\n";
        cout << "   SISTEM PERPUSTAKAAN\n";
        cout << "====================================\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tambah Antrean Peminjaman\n";
        cout << "3. Tampilkan Antrean Peminjaman\n";
        cout << "4. Proses Peminjaman\n";
        cout << "5. Pengembalian Buku\n";
        cout << "6. Tampilkan Riwayat Pengembalian\n";
        cout << "7. Cari Buku berdasarkan ID\n";
        cout << "8. Tampilkan Traversal BST\n";
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
                int id;
                string judul;

                cout << "Masukkan ID Buku: ";
                if (!(cin >> id) || id <= 0) {
                    cout << "ID harus berupa angka positif!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);

                if (judul.empty()) {
                    cout << "Judul buku tidak boleh kosong!\n";
                    break;
                }

                perpustakaan.tambahBuku(id, judul);
                break;
            }

            case 2: {
                string nim, nama;
                int idBuku;

                cout << "Masukkan NIM: ";
                cin >> nim;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan Nama: ";
                getline(cin, nama);

                cout << "Masukkan ID Buku: ";
                if (!(cin >> idBuku)) {
                    cout << "ID buku harus berupa angka!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                perpustakaan.tambahAntrean(nim, nama, idBuku);
                break;
            }

            case 3:
                perpustakaan.tampilkanAntrean();
                break;

            case 4:
                perpustakaan.prosesPeminjaman();
                break;

            case 5: {
                string nim, nama;
                int idBuku;

                cout << "Masukkan NIM: ";
                cin >> nim;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan Nama: ";
                getline(cin, nama);

                cout << "Masukkan ID Buku: ";
                if (!(cin >> idBuku)) {
                    cout << "ID buku harus berupa angka!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                perpustakaan.kembalikanBuku(nim, nama, idBuku);
                break;
            }

            case 6:
                perpustakaan.tampilkanRiwayat();
                break;

            case 7: {
                int id;

                cout << "Masukkan ID Buku yang dicari: ";
                if (!(cin >> id)) {
                    cout << "ID buku harus berupa angka!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                perpustakaan.pencarianBuku(id);
                break;
            }

            case 8:
                perpustakaan.tampilkanTraversal();
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
