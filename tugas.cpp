#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>  // Untuk menyimpan data ke file
#include <sstream>  // Untuk parsing string dari file
using namespace std;

// Struktur data barang
struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

// Fungsi untuk membaca data dari file ke linked list
void bacaDariFile(Barang* &head) {
    ifstream in("data_barang.txt");
    if (!in) {
        // File tidak ada, tidak perlu apa-apa
        return;
    }
    string kode, nama;
    int harga, stok;
    while (in >> kode) {
        in >> ws; // buang spasi sebelum nama
        getline(in, nama, ' ');
        in >> harga >> stok;
        Barang* baru = new Barang();
        baru->kode = kode;
        baru->nama = nama;
        baru->harga = harga;
        baru->stok = stok;
        baru->next = head;
        head = baru;
    }
    in.close();
}

// Simpan data ke file teks
void simpanKeFile(Barang* head) {
    ofstream out("data_barang.txt");
    Barang* current = head;
    while (current != NULL) {
        out << current->kode << " " << current->nama << " " 
            << current->harga << " " << current->stok << endl;
        current = current->next;
    }
    out.close();
    cout << "Data telah disimpan ke file.\n";
}

void tambahBarang(Barang* &head) {
    int jumlah;
    cout << "Jumlah barang yang akan ditambahkan: ";
    cin >> jumlah;
    
    for (int i = 0; i < jumlah; i++) {
        Barang* baru = new Barang();
        cout << "\nBarang ke-" << i+1 << endl;
        cout << "Nama barang : ";
        cin.ignore();
        getline(cin, baru->nama);
        
        // Validasi harga tidak boleh negatif
        do {
            cout << "Harga barang : ";
            cin >> baru->harga;
            if (baru->harga < 0) {
                cout << "Harga tidak boleh negatif!\n";
            }
        } while (baru->harga < 0);
        
        cout << "Kode barang : ";
        cin >> baru->kode;
        
        // Validasi stok tidak boleh negatif
        do {
            cout << "Jumlah stok : ";
            cin >> baru->stok;
            if (baru->stok < 0) {
                cout << "Stok tidak boleh negatif!\n";
            }
        } while (baru->stok < 0);
        
        // Tambah ke awal linked list
        baru->next = head;
        head = baru;
    }

    cout << "\nData berhasil ditambahkan!\n";
    simpanKeFile(head); // Simpan setelah input
}


// Sorting berdasarkan harga
void bubbleSort(Barang** arr, int count, bool ascending = true) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool condition = ascending 
                             ? (arr[j]->harga > arr[j + 1]->harga) 
                             : (arr[j]->harga < arr[j + 1]->harga);
            if (condition) {
                Barang* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Menampilkan daftar barang yang tersimpan
void tampilkanBarang(Barang* head, bool termurah = true) {
    if (head == NULL) {
        cout << "Stok barang kosong!\n";
        return;
    }

    // Hitung jumlah barang
    int count = 0;
    Barang* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Masukkan pointer barang ke array untuk sorting
    Barang** arr = new Barang*[count];
    current = head;
    for (int i = 0; i < count; i++) {
        arr[i] = current;
        current = current->next;
    }

    bubbleSort(arr, count, termurah); // Urutkan

    // Header tampilan
    if (termurah) {
        cout << "\nDaftar Barang (Termurah):\n";
    } else {
        cout << "\nDaftar Barang (Termahal):\n";
    }

    cout << "=====================================================\n";
    cout << "| " << setw(6) << left << "Kode" 
         << "| " << setw(20) << left << "Nama Barang" 
         << "| " << setw(8) << right << "Harga" 
         << " | " << setw(5) << right << "Stok" << " |\n";
    cout << "=====================================================\n";

    // Tampilkan data
    for (int i = 0; i < count; i++) {
        cout << "| " << setw(6) << left << arr[i]->kode
             << "| " << setw(20) << left << arr[i]->nama
             << "| " << setw(8) << right << arr[i]->harga
             << " | " << setw(5) << right << arr[i]->stok << " |\n";
    }
    cout << "=====================================================\n";

    delete[] arr;
}

// Hapus barang dari list berdasarkan nama
void hapusBarang(Barang* &head) {
    if (head == NULL) {
        cout << "Stok barang kosong!\n";
        return;
    }

    string nama;
    cout << "Masukkan nama barang yang akan dihapus: ";
    cin.ignore();
    getline(cin, nama);

    Barang* current = head;
    Barang* prev = NULL;
    bool found = false;

    // Cari barang berdasarkan nama
    while (current != NULL) {
        if (current->nama == nama) {
            found = true;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Barang '" << nama << "' berhasil dihapus!\n";
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        cout << "Barang '" << nama << "' tidak ditemukan!\n";
        return;
    }

    simpanKeFile(head); // Simpan ke file setelah menghapus
    tampilkanBarang(head); // Tampilkan sisa data
}

int main() {
    Barang* head = NULL;
    // Tambahan: baca data dari file sebelum menu
    bacaDariFile(head);

    int pilihan;

    do {
        // Menu utama
        cout << "\nSISTEM MANAJEMEN STOK GUDANG\n";
        cout << "=============================\n";
        cout << "1. Input stok barang\n";
        cout << "2. Lihat daftar stok\n";
        cout << "3. Hapus barang dari stok\n";
        cout << "9. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                tambahBarang(head);
                break;
            case 2: {
                char subPilihan;
                cout << "\na. Urutkan dari termurah\n";
                cout << "b. Urutkan dari termahal\n";
                cout << "Pilihan: ";
                cin >> subPilihan;
                if (subPilihan == 'a') {
                    tampilkanBarang(head);
                } else if (subPilihan == 'b') {
                    tampilkanBarang(head, false);
                } else {
                    cout << "Pilihan tidak valid!\n";
                }
                break;
            }
            case 3:
                hapusBarang(head);
                break;
            case 9:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 9);

    // Bersihkan memori
    Barang* current = head;
    while (current != NULL) {
        Barang* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
