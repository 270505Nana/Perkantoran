#include <iostream>
#include <string>
using namespace std;
// ini kodingannya mirip mirip kaya yang MLL UNGUIDED SOAL 1

// prajna
// Bikin struct proyek buat nanti nyimpen data dari proyek
struct Proyek {
    string namaProyek; //ada nama proyek
    string departemen; //ada departemen proyeknya itu dipegang sma departemen mana
    int durasi; //ada durasi
    Proyek* next; //ada next proyek(pointer ke proyek selanjutnya)
};

//prajna
// Bikin struct pegawai buat nanti nyimpen data dari pegawai
struct Pegawai {
    string namaPegawai; //nama pegawai
    string idPegawai; //id pegawai
    string departemen; //ada departemen, buat nanti nyimpen data dari pegawai di departemen mana
    string jabatan; //ada jabatan (staff/intern)
    string noTelp; //ada noTelp
    Proyek* proyek; //ada proyek, jadi buat nunjuk proyek yang dipunya sma pegawainya berdasarkan IDnya.
    Pegawai* next; //ada next pegawai
};

typedef Pegawai* addressPegawai; 
typedef Proyek* addressProyek;

// bikin list pegawai
struct ListPegawai {
    addressPegawai first;
};

// bikin MLL nya,list pegawainya
void createListPegawai(ListPegawai& L) {
    L.first = nullptr;
}

// bikin fungsi untuk alokasi memori baru, jadi dia bikin node gitu buat masing" data
// nama, id, departemen, jabatan sma no telp jadi parameter disini.
// allocate pegawai dengan menggunakan alamatnya
addressPegawai allocatePegawai(const string& nama, const string& id, const string& departemen, const string& jabatan, const string& noTelp) {
    addressPegawai P = new Pegawai; // inisiasiP sebagai address untuk membuat pegawai baru
    P->namaPegawai = nama; // P itu menginisiasikan sebagai address pegawai. Jadi P -> nama pegawai itu inisialnya nama
    P->idPegawai = id;
    P->departemen = departemen;
    P->jabatan = jabatan;
    P->noTelp = noTelp;
    P->proyek = nullptr;
    P->next = nullptr;
    return P;
}

// sama kaya pegawai tapi versi proyeknya.
addressProyek allocateProyek(const string& namaProyek, int durasi, const string& departemen) {
    addressProyek P = new Proyek;
    P->namaProyek = namaProyek;
    P->departemen = departemen;
    P->durasi = durasi;
    P->next = nullptr;
    return P;
}

// fungsi insert pegawai, ini nanti digunakan ketika ada pegawai baru yang ingin ditambahkan ke list
// dengan mengirim alamat list di inisiasikan sebagai L dan alamat dari pegawainya sebagai P
void insertPegawai(ListPegawai& L, addressPegawai P) {
    if (L.first == nullptr) { // pengkondisian kalau List pegawainya kosong maka pegawai yang baru ini jadi firstnya
        L.first = P;
    } else { // kalau list tidak kosong maka 
        addressPegawai temp = L.first; 
        // temp adalah pointer sementara yang digunakan untuk menjelajahi struktur MLL secara horizontal (antar pegawai) 
        // jadi temporary yang digunakan untuk
        while (temp->next != nullptr) {
            // jadi pointer sementara yang lgi dijelajahi itu kalao nextnya masih ada maka lanjutkan ke nextnya buat nyelipin datanya
            temp = temp->next; // bagian ini yang dia nerusin datanya
        }
        // nah disini nextnya diganti dengan P (data yang kita baru tambahin)
        temp->next = P;
        cout << "Pegawai baru berhasil ditambahkan.\n";
    }
}

//  function insert proyek baru -> sama seperti yang pegawai konsepnya
void insertProyek(addressPegawai pegawai, addressProyek P) {
    if (pegawai->proyek == nullptr) {
        pegawai->proyek = P;
    } else {
        addressProyek temp = pegawai->proyek;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = P;
    }
}

// function update proyek - prajna
void updateProyek(addressPegawai pegawai, const string& namaProyek) {
    // Mengecek apakah pegawai memiliki proyek, kalo punya maka
    if (pegawai->proyek != nullptr) {
        addressProyek temp = pegawai->proyek; // Membuat pointer temp untuk menelusuri list proyek
        while (temp != nullptr && temp->namaProyek != namaProyek) {
            temp = temp->next; // Bergerak ke proyek berikutnya hingga ditemukan proyek dengan nama yang sesuai
        }
        if (temp != nullptr) {
            // Jika proyek ditemukan, meminta input data baru untuk memperbarui proyek
            cout << "Proyek ditemukan. Masukkan data baru:\n";
            cout << "Nama proyek baru: ";
            cin.ignore();
            getline(cin, temp->namaProyek); // Memperbarui nama proyek
            cout << "Durasi proyek baru (bulan): ";
            cin >> temp->durasi; // Memperbarui durasi proyek
            cin.ignore();
            cout << "Departemen proyek baru: ";
            getline(cin, temp->departemen); // Memperbarui departemen proyek
            cout << "Data proyek berhasil diperbarui.\n";
        } else {
            // Jika proyek tidak ditemukan
            cout << "Proyek tidak ditemukan.\n";
        }
    } else {
        // Jika pegawai tidak memiliki proyek sama sekali
        cout << "Pegawai tidak memiliki proyek untuk diperbarui.\n";
    }
}

void hapusProyek(addressPegawai pegawai, const string& namaProyek) {
    // Mengecek apakah pegawai memiliki proyek
    if (pegawai->proyek != nullptr) {
        addressProyek temp = pegawai->proyek; // Membuat pointer temp untuk menelusuri list proyek
        addressProyek prev = nullptr; // Pointer prev untuk menyimpan node sebelumnya
        while (temp != nullptr && temp->namaProyek != namaProyek) {
            prev = temp; // Memindahkan prev ke proyek saat ini
            temp = temp->next; // Bergerak ke proyek berikutnya
        }
        if (temp != nullptr) {
            // Jika proyek ditemukan, menghapus proyek
            if (prev == nullptr) {
                pegawai->proyek = temp->next; // Jika proyek pertama yang dihapus
            } else {
                prev->next = temp->next; // Jika proyek selain yang pertama yang dihapus
            }
            delete temp; // Menghapus proyek dari memori
            cout << "Proyek berhasil dihapus.\n";
        } else {
            // Jika proyek tidak ditemukan
            cout << "Proyek tidak ditemukan.\n";
        }
    } else {
        // Jika pegawai tidak memiliki proyek sama sekali
        cout << "Pegawai tidak memiliki proyek.\n";
    }
}

void hapusPegawai(ListPegawai& L, const string& idPegawai) {
    addressPegawai temp = L.first; // Membuat pointer temp untuk menelusuri list pegawai
    addressPegawai prev = nullptr; // Pointer prev untuk menyimpan node sebelumnya
    while (temp != nullptr && temp->idPegawai != idPegawai) {
        prev = temp; // Memindahkan prev ke pegawai saat ini
        temp = temp->next; // Bergerak ke pegawai berikutnya
    }
    if (temp != nullptr) {
        // Jika pegawai ditemukan, menghapus pegawai
        if (prev == nullptr) {
            L.first = temp->next; // Jika pegawai pertama yang dihapus
        } else {
            prev->next = temp->next; // Jika pegawai selain yang pertama yang dihapus
        }
        // Menghapus semua proyek yang dimiliki pegawai
        while (temp->proyek != nullptr) {
            addressProyek proyekTemp = temp->proyek; // Menyimpan pointer ke proyek saat ini
            temp->proyek = proyekTemp->next; // Beralih ke proyek berikutnya
            delete proyekTemp; // Menghapus proyek dari memori
        }
        delete temp; // Menghapus pegawai dari memori
        cout << "Pegawai berhasil dihapus.\n";
    } else {
        // Jika pegawai tidak ditemukan
        cout << "Pegawai tidak ditemukan.\n";
    }
}


void printListPegawai(const ListPegawai& L) {
    const string departments[] = {"IT", "Marketing", "Accounting", "Finance"}; // membuat arraynya untuk menyimpan nama departemennya

    for (const string& dept : departments) {
        cout << "============================================\n";
        cout << "Departemen: " << dept << "\n"; // disini dia kaan print sesuai dengan departemennya, masing- masing
        cout << "============================================\n";
        cout << "| ID Pegawai | Nama Pegawai       | Jabatan  | No. Telepon  |\n";
        cout << "--------------------------------------------\n";

        addressPegawai P = L.first;
        bool found = false;
        while (P != nullptr) {
            if (P->departemen == dept) {
                cout << "| " << P->idPegawai << "\t  | " //memanggil masing masing dri id pegawa, nama, jabatan dan no telp
                     << P->namaPegawai << "\t    | "
                     << P->jabatan << "\t | "
                     << P->noTelp << " |\n";
                found = true;
            }
            P = P->next;
        }

        if (!found) {
            cout << "Tidak ada data karyawan untuk departemen ini.\n";
        }

        cout << "============================================\n\n";
    }
}


void printProyek(const ListPegawai& L) { // sama aja kaya yang diatas
    addressPegawai P = L.first;
    while (P != nullptr) {
        addressProyek Q = P->proyek;
        while (Q != nullptr) {
            cout << "Proyek: " << Q->namaProyek << ", Durasi: " << Q->durasi << " bulan, Departemen: " << Q->departemen << endl;
            // manggil buat nama proyek, durasi sama departemennya
            Q = Q->next;
        }
        P = P->next;
    }
}

int main() {
    ListPegawai L;
    createListPegawai(L);

    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah karyawan\n";
        cout << "2. Tambah proyek\n";
        cout << "3. Menampilkan seluruh karyawan sesuai dengan departemennya\n";
        cout << "4. Menampilkan seluruh proyek\n";
        cout << "5. Menghapus data karyawan\n";
        cout << "6. Menghapus data proyek\n";
        cout << "7. Update data proyek\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            string nama, id, departemen, jabatan, noTelp;
            cout << "Masukkan nama karyawan: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan ID karyawan: ";
            getline(cin, id);
            cout << "List departemen: \n";
            cout << "1. IT\n";
            cout << "2. Marketing \n";
            cout << "3. Accounting\n";
            cout << "4. Finance\n";
            cout << "Masukkan departemen : \n";
            getline(cin, departemen);
            cout << "Masukkan jabatan (Staff/intern): ";
            getline(cin, jabatan);
            cout << "Masukkan no telepon: ";
            getline(cin, noTelp);
            insertPegawai(L, allocatePegawai(nama, id, departemen, jabatan, noTelp));
            break;
        }
        case 2: {
            string idPegawai, namaProyek, departemen;
            int durasi;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai) {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr) {
                cout << "Masukkan nama proyek: ";
                getline(cin, namaProyek);
                cout << "Masukkan durasi proyek (bulan): ";
                cin >> durasi;
                cin.ignore();
                cout << "Masukkan departemen proyek: ";
                getline(cin, departemen);
                insertProyek(pegawai, allocateProyek(namaProyek, durasi, departemen));
            } else {
                cout << "Karyawan tidak ditemukan.\n";
            }
            break;
        }
        case 3:
            printListPegawai(L);
            break;
        case 4:
            printProyek(L);
            break;
        case 5: {
            string idPegawai;
            cout << "Masukkan ID karyawan yang akan dihapus: ";
            cin.ignore();
            getline(cin, idPegawai);
            hapusPegawai(L, idPegawai);
            break;
        }
        case 6: {
            string idPegawai, namaProyek;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai) {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr) {
                cout << "Masukkan nama proyek yang akan dihapus: ";
                getline(cin, namaProyek);
                hapusProyek(pegawai, namaProyek);
            } else {
                cout << "Karyawan tidak ditemukan.\n";
            }
            break;
        }
        case 7: {
            string idPegawai, namaProyek;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai) {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr) {
                cout << "Masukkan nama proyek yang akan diperbarui: ";
                getline(cin, namaProyek);
                updateProyek(pegawai, namaProyek);
            } else {
                cout << "Karyawan tidak ditemukan.\n";
            }
            break;
        }
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);

    return 0;
}