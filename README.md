# Quiz_Lab3_SD
Quiz Lab 3 SD untuk pemahaman materi modul 1 sampai modul 8
# TUGAS INDIVIDU STRUKTUR DATA

## Identitas Mahasiswa

- **Nama:** Ezer Nicholas Purba
- **NIM:** 251401062
- **Program Studi:** Ilmu Komputer
- **Kelas:** KOM B

## Deskripsi Proyek

Proyek ini berisi implementasi beberapa konsep struktur data dan algoritma menggunakan bahasa pemrograman C++. Terdapat empat program yang dibuat berdasarkan soal tugas individu Struktur Data.

---

## Daftar Program

### 1. Pengelolaan Data Mahasiswa (`soal1.cpp`)

Program ini digunakan untuk mengelola data mahasiswa yang terdiri dari NIM, nama, dan nilai.

**Struktur data dan algoritma yang digunakan:**
- **Dynamic Array:** Menyimpan kumpulan nilai mahasiswa.
- **Single Linked List:** Menyimpan data mahasiswa berupa NIM, nama, dan nilai.
- **Insertion Sort:** Mengurutkan nilai mahasiswa secara ascending.
- **Linear Search:** Mencari mahasiswa berdasarkan NIM.
- **Binary Search:** Mencari nilai mahasiswa setelah data diurutkan.

**Fitur program:**
- Menambahkan data mahasiswa.
- Menampilkan seluruh data mahasiswa.
- Mencari mahasiswa berdasarkan NIM.
- Mengurutkan nilai mahasiswa.
- Mencari nilai menggunakan Binary Search.
- Menampilkan daftar nilai.

### 2. Sistem Peminjaman dan Pengembalian Buku Perpustakaan (`soal2.cpp`)

Program ini merupakan simulasi sederhana sistem peminjaman dan pengembalian buku perpustakaan.

**Struktur data yang digunakan:**
- **Queue:** Mengelola antrean peminjaman mahasiswa dengan prinsip FIFO (First In, First Out).
- **Stack:** Menyimpan riwayat pengembalian buku dengan prinsip LIFO (Last In, First Out).
- **Binary Search Tree (BST):** Menyimpan dan mencari data buku berdasarkan ID buku.

**Fitur program:**
- Menambahkan data buku.
- Menambahkan mahasiswa ke antrean peminjaman.
- Menampilkan antrean peminjaman.
- Memproses peminjaman buku.
- Melakukan pengembalian buku.
- Menampilkan riwayat pengembalian.
- Mencari buku berdasarkan ID.
- Menampilkan data BST menggunakan Pre-Order, In-Order, dan Post-Order Traversal.

### 3. Pencarian Rute Menggunakan Graph (`soal3.cpp`)

Program ini digunakan untuk mencari rute pada sebuah graph yang memiliki enam simpul, yaitu A, B, C, D, E, dan F.

**Struktur data dan algoritma yang digunakan:**
- **Graph:** Merepresentasikan hubungan antar simpul.
- **Adjacency Matrix:** Menyimpan hubungan dan bobot antar simpul.
- **Breadth-First Search (BFS):** Melakukan penelusuran graph secara melebar.
- **Depth-First Search (DFS):** Melakukan penelusuran graph secara mendalam.
- **Dijkstra:** Mencari rute dengan total bobot minimum.

**Fitur program:**
- Menampilkan adjacency matrix.
- Melakukan penelusuran menggunakan BFS.
- Melakukan penelusuran menggunakan DFS.
- Mencari rute terpendek menggunakan Dijkstra.
- Menampilkan jalur dan total jarak rute.

### 4. Hash Table Data Mahasiswa (`soal4.cpp`)

Program ini digunakan untuk menyimpan dan mengelola data mahasiswa menggunakan NIM sebagai key dan nama mahasiswa sebagai value.

**Struktur data dan algoritma yang digunakan:**
- **Hash Table:** Menyimpan data mahasiswa dalam tabel berukuran 20 slot.
- **Double Hashing:** Menangani collision atau tabrakan ketika beberapa key memiliki indeks hash yang sama.
- **Hash Function 1:** `Hash1(key) = key % 20`
- **Hash Function 2:** `Hash2(key) = 19 - (key % 19)`

**Fitur program:**
- Menambahkan data mahasiswa.
- Mencari mahasiswa berdasarkan NIM.
- Menghapus data mahasiswa.
- Menampilkan isi Hash Table.
- Menjalankan pengujian otomatis menggunakan minimal 15 data mahasiswa.

---

## Struktur Folder

Simpan seluruh file program dalam satu folder dengan susunan berikut:

```text
Tugas-Struktur-Data/
│
├── soal1.cpp
├── soal2.cpp
├── soal3.cpp
├── soal4.cpp
└── README.md
```

## Cara Menjalankan Program

Pastikan compiler C++ seperti **G++ (MinGW-w64)** sudah terpasang dan dapat digunakan melalui terminal.

### 1. Membuka Folder Proyek

Buka terminal atau Visual Studio Code, kemudian arahkan terminal ke folder proyek:

```bash
cd "Tugas-Struktur-Data"
```

### 2. Menjalankan Soal 1

```bash
g++ soal1.cpp -o soal1
```

```bash
.\soal1
```

### 3. Menjalankan Soal 2

```bash
g++ soal2.cpp -o soal2
```

```bash
.\soal2
```

### 4. Menjalankan Soal 3

```bash
g++ soal3.cpp -o soal3
```

```bash
.\soal3
```

### 5. Menjalankan Soal 4

```bash
g++ soal4.cpp -o soal4
```

```bash
.\soal4
```

**Catatan:** Perintah `.\nama_program` digunakan pada terminal Windows PowerShell. Jika menggunakan Linux atau macOS, jalankan program dengan format `./nama_program`.

---

## Tautan Youtube Penjelasan
https://youtu.be/smlZUIG_aPQ?si=eSkM86fcLOmd4K4G

## Penutup

Melalui empat program ini, mahasiswa dapat memahami penerapan berbagai struktur data dan algoritma dalam menyelesaikan permasalahan menggunakan bahasa pemrograman C++. Setiap program dibuat untuk menunjukkan cara kerja struktur data, proses pengolahan informasi, serta penerapan algoritma pencarian dan pengurutan.
