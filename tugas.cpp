#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

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
        cout << "Harga barang : ";
        cin >> baru->harga;
        cout << "Kode barang : ";
        cin >> baru->kode;
        cout << "Jumlah stok : ";
        cin >> baru->stok;
        
        baru->next = head;
        head = baru;
    }
    cout << "\nData berhasil ditambahkan!\n";
}

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

void tampilkanBarang(Barang* head, bool termurah = true) {
    if (head == NULL) {
        cout << "Stok barang kosong!\n";
        return;
    }
    
    int count = 0;
    Barang* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    Barang** arr = new Barang*[count];
    current = head;
    for (int i = 0; i < count; i++) {
        arr[i] = current;
        current = current->next;
    }
    
    bubbleSort(arr, count, termurah);
    
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
    
    for (int i = 0; i < count; i++) {
        cout << "| " << setw(6) << left << arr[i]->kode
             << "| " << setw(20) << left << arr[i]->nama
             << "| " << setw(8) << right << arr[i]->harga
             << " | " << setw(5) << right << arr[i]->stok << " |\n";
    }
    cout << "=====================================================\n";
    
    delete[] arr;
}

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
    
    tampilkanBarang(head);
}

int main() {
    Barang* head = NULL;
    int pilihan;
    
    do {
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
    
    Barang* current = head;
    while (current != NULL) {
        Barang* temp = current;
        current = current->next;
        delete temp;
    }
    
    return 0;
}
