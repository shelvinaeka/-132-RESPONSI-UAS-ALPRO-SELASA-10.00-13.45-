#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Bandara {
    int kodePenerbangan;
    string namaMaskapai;
    string asal;
    string tujuan;
    string tanggalPenerbangan;
    string jamKeberangkatan;
    string jamKedatangan;
    int harga;
};

class SistemBandara {
private:
    vector<Bandara> dataBandara;
    const string namaFile = "data_bandara.txt";

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int cariBandara(int kode) {
        for (size_t i = 0; i < dataBandara.size(); i++) {
            if (dataBandara[i].kodePenerbangan == kode) {
                return i;
            }
        }
        return -1;
    }

    bool simpanKeFile() {
        ofstream file(namaFile);
        if (!file) return false;

        for (const auto& bdr : dataBandara) {
            file << bdr.kodePenerbangan << "|" << bdr.namaMaskapai << "|"
                 << bdr.asal << "|" << bdr.tujuan << "|"
                 << bdr.tanggalPenerbangan << "|" << bdr.jamKeberangkatan << "|"
                 << bdr.jamKedatangan << "|" << bdr.harga << "\n";
        }
        return true;
    }

    void bacaDariFile() {
        ifstream file(namaFile);
        dataBandara.clear();

        if (!file) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 8) {
                Bandara bdr;
                bdr.kodePenerbangan = stoi(tokens[0]);
                bdr.namaMaskapai = tokens[1];
                bdr.asal = tokens[2];
                bdr.tujuan = tokens[3];
                bdr.tanggalPenerbangan = tokens[4];
                bdr.jamKeberangkatan = tokens[5];
                bdr.jamKedatangan = tokens[6];
                bdr.harga = stoi(tokens[7]);
                dataBandara.push_back(bdr);
            }
        }
    }

public:
    SistemBandara() {
        bacaDariFile();
    }

    void inputData() {
        Bandara bdr;
        cout << "\nMasukkan Kode Penerbangan: ";
        cin >> bdr.kodePenerbangan;
        clearInputBuffer();

        if (cariBandara(bdr.kodePenerbangan) != -1) {
            cout << "Kode sudah ada!\n";
            return;
        }

        cout << "Nama Maskapai: ";
        getline(cin, bdr.namaMaskapai);

        cout << "Asal: ";
        getline(cin, bdr.asal);

        cout << "Tujuan: ";
        getline(cin, bdr.tujuan);

        cout << "Tanggal (DD-MM-YYYY): ";
        getline(cin, bdr.tanggalPenerbangan);

        cout << "Jam Keberangkatan (HH:MM): ";
        getline(cin, bdr.jamKeberangkatan);

        cout << "Jam Kedatangan (HH:MM): ";
        getline(cin, bdr.jamKedatangan);

        cout << "Harga: ";
        cin >> bdr.harga;
        clearInputBuffer();

        dataBandara.push_back(bdr);
        simpanKeFile();
        cout << "Data tersimpan!\n";
    }

    void sortingData() {
        cout << "\n1. Sort by Kode\n"
             << "2. Sort by Harga (Murah)\n"
             << "3. Sort by Harga (Mahal)\n"
             << "Pilihan: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            sort(dataBandara.begin(), dataBandara.end(), [](const Bandara& a, const Bandara& b) {
                return a.kodePenerbangan < b.kodePenerbangan;
            });
        }
        else if (choice == 2) {
            sort(dataBandara.begin(), dataBandara.end(), [](const Bandara& a, const Bandara& b) {
                return a.harga < b.harga;
            });
        }
        else if (choice == 3) {
            sort(dataBandara.begin(), dataBandara.end(), [](const Bandara& a, const Bandara& b) {
                return a.harga > b.harga;
            });
        }

        simpanKeFile();
        cout << "Data tersortir!\n";
    }

    void searchingData() {
        cout << "\n1. Cari by Kode\n"
             << "2. Cari by Maskapai\n"
             << "Pilihan: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            cout << "Masukkan Kode: ";
            int kode;
            cin >> kode;
            clearInputBuffer();

            int index = cariBandara(kode);
            if (index != -1) {
                cout << "\nKode: " << dataBandara[index].kodePenerbangan
                     << "\nMaskapai: " << dataBandara[index].namaMaskapai
                     << "\nAsal: " << dataBandara[index].asal
                     << "\nTujuan: " << dataBandara[index].tujuan
                     << "\nTanggal: " << dataBandara[index].tanggalPenerbangan
                     << "\nJam Berangkat: " << dataBandara[index].jamKeberangkatan
                     << "\nJam Datang: " << dataBandara[index].jamKedatangan
                     << "\nHarga: " << dataBandara[index].harga << "\n";
            }
            else {
                cout << "Tidak ditemukan!\n";
            }
        }
        else if (choice == 2) {
            cout << "Masukkan Nama Maskapai: ";
            string nama;
            getline(cin, nama);

            bool found = false;
            for (const auto& bdr : dataBandara) {
                if (bdr.namaMaskapai == nama) {
                    cout << "\nKode: " << bdr.kodePenerbangan
                         << "\nMaskapai: " << bdr.namaMaskapai
                         << "\nAsal: " << bdr.asal
                         << "\nTujuan: " << bdr.tujuan
                         << "\nTanggal: " << bdr.tanggalPenerbangan
                         << "\nJam Berangkat: " << bdr.jamKeberangkatan
                         << "\nJam Datang: " << bdr.jamKedatangan
                         << "\nHarga: " << bdr.harga << "\n";
                    found = true;
                }
            }

            if (!found) {
                cout << "Tidak ditemukan!\n";
            }
        }
    }

    void cetakLaporan() {
        if (dataBandara.empty()) {
            cout << "Tidak ada data!\n";
            return;
        }

        cout << "\n=== LAPORAN PENERBANGAN ===\n";
        for (const auto& bdr : dataBandara) {
            cout << bdr.kodePenerbangan << " | "
                 << bdr.namaMaskapai << " | "
                 << bdr.asal << " -> "
                 << bdr.tujuan << " | "
                 << bdr.tanggalPenerbangan << " | "
                 << bdr.jamKeberangkatan << "-"
                 << bdr.jamKedatangan << " | Rp"
                 << bdr.harga << "\n";
        }
    }

    void menuUtama() {
        while (true) {
            cout << "\n=== SISTEM PEMESANAN TIKET ===" << endl;
            cout << "1. Input Data" << endl;
            cout << "2. Sorting Data" << endl;
            cout << "3. Cari Data" << endl;
            cout << "4. Cetak Laporan" << endl;
            cout << "5. Keluar" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            clearInputBuffer();

            switch (pilihan) {
                case 1: inputData(); break;
                case 2: sortingData(); break;
                case 3: searchingData(); break;
                case 4: cetakLaporan(); break;
                case 5: return;
                default: cout << "Pilihan salah!\n";
            }
        }
    }
};

int main() {
    SistemBandara sistem;
    sistem.menuUtama();
    return 0;
}

