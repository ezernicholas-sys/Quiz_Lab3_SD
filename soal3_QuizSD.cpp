
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

const int JUMLAH_VERTEX = 6;
const int INF = numeric_limits<int>::max();

class Graph {
private:
    char vertex[JUMLAH_VERTEX] = {'A', 'B', 'C', 'D', 'E', 'F'};

    // Adjacency Matrix
    int matrix[JUMLAH_VERTEX][JUMLAH_VERTEX] = {};

    // Mengubah huruf vertex menjadi indeks
    int indeksVertex(char v) {
        if (v >= 'a' && v <= 'f') {
            v = v - 'a' + 'A';
        }

        if (v < 'A' || v > 'F') {
            return -1;
        }

        return v - 'A';
    }

    // Menampilkan rute
    void tampilkanRute(vector<int> rute) {
        for (int i = 0; i < rute.size(); i++) {
            cout << vertex[rute[i]];

            if (i < rute.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    // DFS menggunakan rekursi
    void DFSRekursif(int posisi, bool dikunjungi[]) {
        dikunjungi[posisi] = true;

        cout << vertex[posisi] << " ";

        for (int i = 0; i < JUMLAH_VERTEX; i++) {
            if (matrix[posisi][i] != 0 && !dikunjungi[i]) {
                DFSRekursif(i, dikunjungi);
            }
        }
    }

public:
    Graph() {
        // Membuat hubungan antarvertex
        tambahSisi('A', 'B', 4);
        tambahSisi('A', 'C', 2);
        tambahSisi('B', 'C', 1);
        tambahSisi('B', 'D', 5);
        tambahSisi('B', 'E', 3);
        tambahSisi('C', 'D', 8);
        tambahSisi('C', 'E', 6);
        tambahSisi('D', 'E', 2);
        tambahSisi('D', 'F', 4);
        tambahSisi('E', 'F', 3);
    }

    // Menambahkan sisi dua arah
    void tambahSisi(char asal, char tujuan, int bobot) {
        int a = indeksVertex(asal);
        int b = indeksVertex(tujuan);

        if (a == -1 || b == -1) {
            return;
        }

        matrix[a][b] = bobot;
        matrix[b][a] = bobot;
    }

    // Menampilkan Adjacency Matrix
    void tampilkanMatrix() {
        cout << "\n===== ADJACENCY MATRIX =====\n\n";

        cout << setw(8) << " ";

        for (int i = 0; i < JUMLAH_VERTEX; i++) {
            cout << setw(6) << vertex[i];
        }

        cout << endl;

        for (int i = 0; i < JUMLAH_VERTEX; i++) {
            cout << setw(8) << vertex[i];

            for (int j = 0; j < JUMLAH_VERTEX; j++) {
                cout << setw(6) << matrix[i][j];
            }

            cout << endl;
        }
    }

    // BFS menggunakan Queue
    void BFS(char awal) {
        int start = indeksVertex(awal);

        if (start == -1) {
            cout << "Vertex tidak valid!\n";
            return;
        }

        bool dikunjungi[JUMLAH_VERTEX] = {};
        queue<int> antrian;

        dikunjungi[start] = true;
        antrian.push(start);

        cout << "\nHasil BFS: ";

        while (!antrian.empty()) {
            int posisi = antrian.front();
            antrian.pop();

            cout << vertex[posisi] << " ";

            for (int i = 0; i < JUMLAH_VERTEX; i++) {
                if (matrix[posisi][i] != 0 &&
                    !dikunjungi[i]) {

                    dikunjungi[i] = true;
                    antrian.push(i);
                }
            }
        }

        cout << endl;
    }

    // DFS menggunakan rekursi
    void DFS(char awal) {
        int start = indeksVertex(awal);

        if (start == -1) {
            cout << "Vertex tidak valid!\n";
            return;
        }

        bool dikunjungi[JUMLAH_VERTEX] = {};

        cout << "\nHasil DFS: ";
        DFSRekursif(start, dikunjungi);
        cout << endl;
    }

    // Algoritma Dijkstra
    void dijkstra(char awal, char tujuan) {
        int start = indeksVertex(awal);
        int finish = indeksVertex(tujuan);

        if (start == -1 || finish == -1) {
            cout << "Vertex tidak valid!\n";
            return;
        }

        int jarak[JUMLAH_VERTEX];
        int sebelumnya[JUMLAH_VERTEX];

        bool dikunjungi[JUMLAH_VERTEX] = {};

        // Inisialisasi jarak
        for (int i = 0; i < JUMLAH_VERTEX; i++) {
            jarak[i] = INF;
            sebelumnya[i] = -1;
        }

        jarak[start] = 0;

        // Proses pencarian jarak terpendek
        for (int i = 0; i < JUMLAH_VERTEX; i++) {
            int posisi = -1;
            int minimum = INF;

            // Mencari vertex dengan jarak terkecil
            for (int j = 0; j < JUMLAH_VERTEX; j++) {
                if (!dikunjungi[j] && jarak[j] < minimum) {
                    minimum = jarak[j];
                    posisi = j;
                }
            }

            if (posisi == -1) {
                break;
            }

            dikunjungi[posisi] = true;

            if (posisi == finish) {
                break;
            }

            // Memperbarui jarak tetangga
            for (int j = 0; j < JUMLAH_VERTEX; j++) {
                if (matrix[posisi][j] != 0 &&
                    !dikunjungi[j] &&
                    jarak[posisi] + matrix[posisi][j] < jarak[j]) {

                    jarak[j] = jarak[posisi] + matrix[posisi][j];
                    sebelumnya[j] = posisi;
                }
            }
        }

        // Memeriksa apakah tujuan dapat dicapai
        if (jarak[finish] == INF) {
            cout << "\nTidak ada rute yang tersedia.\n";
            return;
        }

        // Menyusun rute dari tujuan ke awal
        vector<int> rute;

        int posisi = finish;

        while (posisi != -1) {
            rute.push_back(posisi);
            posisi = sebelumnya[posisi];
        }

        reverse(rute.begin(), rute.end());

        // Menampilkan hasil
        cout << "\n===== HASIL DIJKSTRA =====\n";
        cout << "Vertex Awal   : " << vertex[start] << endl;
        cout << "Vertex Tujuan : " << vertex[finish] << endl;

        cout << "Rute Terpendek: ";
        tampilkanRute(rute);

        cout << "Total Jarak   : " << jarak[finish] << endl;
    }
};

// Program utama
int main() {
    Graph graph;

    int pilihan;
    char awal, tujuan;

    do {
        cout << "\n====================================\n";
        cout << "   SISTEM PENCARIAN RUTE KAMPUS\n";
        cout << "====================================\n";
        cout << "1. Tampilkan Adjacency Matrix\n";
        cout << "2. BFS (Breadth First Search)\n";
        cout << "3. DFS (Depth First Search)\n";
        cout << "4. Dijkstra (Jarak Terpendek)\n";
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
            case 1:
                graph.tampilkanMatrix();
                break;

            case 2:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;
                graph.BFS(awal);
                break;

            case 3:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;
                graph.DFS(awal);
                break;

            case 4:
                cout << "Masukkan vertex awal (A-F): ";
                cin >> awal;

                cout << "Masukkan vertex tujuan (A-F): ";
                cin >> tujuan;

                graph.dijkstra(awal, tujuan);
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
