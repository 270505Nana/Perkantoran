#include <iostream>
#include <string>
using namespace std;

struct Proyek
{
    string namaProyek;
    string departemen;
    int durasi;
    Proyek *next;
};

struct Pegawai
{
    string namaPegawai;
    string idPegawai;
    string departemen;
    string jabatan;
    string noTelp;
    Proyek *proyek;
    Pegawai *next;
};

typedef Pegawai *addressPegawai;
typedef Proyek *addressProyek;

struct ListPegawai
{
    addressPegawai first;
};

void createListPegawai(ListPegawai &L)
{
    L.first = nullptr;
}

addressPegawai allocatePegawai(const string &nama, const string &id, const string &departemen, const string &jabatan, const string &noTelp)
{
    addressPegawai P = new Pegawai;
    P->namaPegawai = nama;
    P->idPegawai = id;
    P->departemen = departemen;
    P->jabatan = jabatan;
    P->noTelp = noTelp;
    P->proyek = nullptr;
    P->next = nullptr;
    return P;
}

addressProyek allocateProyek(const string &namaProyek, int durasi, const string &departemen)
{
    addressProyek P = new Proyek;
    P->namaProyek = namaProyek;
    P->departemen = departemen;
    P->durasi = durasi;
    P->next = nullptr;
    return P;
}

void insertPegawai(ListPegawai &L, addressPegawai P)
{
    if (L.first == nullptr)
    {
        L.first = P;
    }
    else
    {
        addressPegawai temp = L.first;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = P;
    }
    cout << "Pegawai baru berhasil ditambahkan.\n";
}

void insertProyek(addressPegawai pegawai, addressProyek P)
{
    if (pegawai->proyek == nullptr)
    {
        pegawai->proyek = P;
    }
    else
    {
        addressProyek temp = pegawai->proyek;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = P;
    }
    cout << "Proyek baru berhasil ditambahkan.\n";
}

void updateProyek(addressPegawai pegawai, const string &namaProyek)
{
    if (pegawai->proyek != nullptr)
    {
        addressProyek temp = pegawai->proyek;
        while (temp != nullptr && temp->namaProyek != namaProyek)
        {
            temp = temp->next;
        }
        if (temp != nullptr)
        {
            cout << "Proyek ditemukan. Masukkan data baru:\n";
            cout << "Nama proyek baru: ";
            cin.ignore();
            getline(cin, temp->namaProyek);
            cout << "Durasi proyek baru (bulan): ";
            cin >> temp->durasi;
            cin.ignore();
            cout << "Departemen proyek baru: ";
            getline(cin, temp->departemen);
            cout << "Data proyek berhasil diperbarui.\n";
        }
        else
        {
            cout << "Proyek tidak ditemukan.\n";
        }
    }
    else
    {
        cout << "Pegawai tidak memiliki proyek untuk diperbarui.\n";
    }
}

void hapusProyek(addressPegawai pegawai, const string &namaProyek)
{
    if (pegawai->proyek != nullptr)
    {
        addressProyek temp = pegawai->proyek;
        addressProyek prev = nullptr;
        while (temp != nullptr && temp->namaProyek != namaProyek)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr)
        {
            if (prev == nullptr)
            {
                pegawai->proyek = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Proyek berhasil dihapus.\n";
        }
        else
        {
            cout << "Proyek tidak ditemukan.\n";
        }
    }
    else
    {
        cout << "Pegawai tidak memiliki proyek.\n";
    }
}

void hapusPegawai(ListPegawai &L, const string &idPegawai)
{
    addressPegawai temp = L.first;
    addressPegawai prev = nullptr;
    while (temp != nullptr && temp->idPegawai != idPegawai)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp != nullptr)
    {
        if (prev == nullptr)
        {
            L.first = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }
        while (temp->proyek != nullptr)
        {
            addressProyek proyekTemp = temp->proyek;
            temp->proyek = proyekTemp->next;
            delete proyekTemp;
        }
        delete temp;
        cout << "Pegawai berhasil dihapus.\n";
    }
    else
    {
        cout << "Pegawai tidak ditemukan.\n";
    }
}

void printListPegawai(const ListPegawai &L)
{
    const string departments[] = {"IT", "Marketing", "Accounting", "Finance"};

    for (const string &dept : departments)
    {
        cout << "============================================\n";
        cout << "Departemen: " << dept << "\n";
        cout << "============================================\n";
        cout << "| ID Pegawai | Nama Pegawai       | Jabatan  | No. Telepon  |\n";
        cout << "--------------------------------------------\n";

        addressPegawai P = L.first;
        bool found = false;
        while (P != nullptr)
        {
            if (P->departemen == dept)
            {
                cout << "| " << P->idPegawai << "\t  | "
                     << P->namaPegawai << "\t    | "
                     << P->jabatan << "\t | "
                     << P->noTelp << " |\n";
                found = true;
            }
            P = P->next;
        }

        if (!found)
        {
            cout << "Tidak ada data karyawan untuk departemen ini.\n";
        }

        cout << "============================================\n\n";
    }
}

void printProyek(const ListPegawai &L)
{
    addressPegawai P = L.first;
    while (P != nullptr)
    {
        addressProyek Q = P->proyek;
        while (Q != nullptr)
        {
            cout << "Proyek: " << Q->namaProyek << ", Durasi: " << Q->durasi << " bulan, Departemen: " << Q->departemen
                 << ", Dikerjakan oleh: " << P->namaPegawai << " (ID: " << P->idPegawai << ")\n";
            Q = Q->next;
        }
        P = P->next;
    }
}

int main()
{
    ListPegawai L;
    createListPegawai(L);
    const string validDepartments[] = {"IT", "Marketing", "Accounting", "Finance"};

    int pilihan;
    do
    {
        cout << "\n======================>> MENU MANAJEMEN PENGELOLAAN DATA KARYAWAN & PROJEK <<======================\n";
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

        switch (pilihan)
        {
        case 1:
        {
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
            cout << "Masukkan departemen (bukan angka): ";
            getline(cin, departemen);

            bool valid = false;
            for (const string &validDept : validDepartments)
            {
                if (departemen == validDept)
                {
                    valid = true;
                    break;
                }
            }

            if (!valid)
            {
                cout << "Departemen tidak tersedia. Silakan pilih dari daftar berikut:\n";
                cout << "1. IT\n";
                cout << "2. Marketing \n";
                cout << "3. Accounting\n";
                cout << "4. Finance\n";
                continue; // Kembali ke awal menu
            }

            cout << "Masukkan jabatan (Staff/intern): ";
            getline(cin, jabatan);
            cout << "Masukkan no telepon: ";
            getline(cin, noTelp);

            insertPegawai(L, allocatePegawai(nama, id, departemen, jabatan, noTelp));

            break;
        }
        case 2:
        {
            string idPegawai, namaProyek, departemen;
            int durasi;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai)
            {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr)
            {
                cout << "Masukkan nama proyek: ";
                getline(cin, namaProyek);
                cout << "Masukkan durasi proyek (bulan): ";
                cin >> durasi;
                cin.ignore();
                cout << "1. IT\n";
                cout << "2. Marketing \n";
                cout << "3. Accounting\n";
                cout << "4. Finance\n";
                cout << "Masukkan departemen (bukan angka): ";
                getline(cin, departemen);
                // misal departemen gak sesuai dengan yang sistem tampilkan
                bool valid = false;
                for (const string &validDept : validDepartments)
                {
                    if (departemen == validDept)
                    {
                        valid = true;
                        break;
                    }
                }

                if (!valid)
                {
                    cout << "Departemen tidak tersedia. Silakan pilih dari daftar berikut:\n";
                    cout << "1. IT\n";
                    cout << "2. Marketing \n";
                    cout << "3. Accounting\n";
                    cout << "4. Finance\n";
                    continue; // Kembali ke awal menu
                }

                insertProyek(pegawai, allocateProyek(namaProyek, durasi, departemen));
            }
            else
            {
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
         case 5:
        {
            string idPegawai;
            cout << "Masukkan ID karyawan yang akan dihapus: ";
            cin.ignore();
            getline(cin, idPegawai);
            hapusPegawai(L, idPegawai);
            break;
        }
        case 6:
        {
            string idPegawai, namaProyek;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai)
            {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr)
            {
                cout << "Masukkan nama proyek yang akan dihapus: ";
                getline(cin, namaProyek);
                hapusProyek(pegawai, namaProyek);
            }
            else
            {
                cout << "Karyawan tidak ditemukan.\n";
            }
            break;
        }
        case 7:
        {
            string idPegawai, namaProyek;
            cout << "Masukkan ID karyawan: ";
            cin.ignore();
            getline(cin, idPegawai);
            addressPegawai pegawai = L.first;
            while (pegawai != nullptr && pegawai->idPegawai != idPegawai)
            {
                pegawai = pegawai->next;
            }
            if (pegawai != nullptr)
            {
                cout << "Masukkan nama proyek yang akan diperbarui: ";
                getline(cin, namaProyek);
                updateProyek(pegawai, namaProyek);
            }
            else
            {
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
    } while (pilihan != 0);

    return 0;
}