#include <iostream>

using namespace std;

void baris()
{
    cout << "--------------------------------------------------------------" << endl;
}

void menu(string pesan)
{
    system("cls");
    cout << "=============== Kedai Eskrim Vanilla Pak Vani ================" << endl;
    cout << "[1] Tambah Antrian" << endl;
    cout << "[2] Pindah Pembelian" << endl;
    cout << "[3] Selesai dan Rating" << endl;
    cout << "[4] Display Daftar Antrian" << endl;
    cout << "[5] Display Daftar Pembelian" << endl;
    cout << "[6] Display Daftar Selesai" << endl;
    cout << "[7] Average Usia Pelanggan" << endl;
    cout << "[8] Average Rating Pelanggan" << endl;
    cout << "[0] Exit" << endl;
    baris();
    cout << "[Pesan] " << pesan << endl;
    baris();
}

struct Pelanggan
{
    string nama;
    int usia;
    string rating;
    Pelanggan *next;
    Pelanggan *prev;
};

class DaftarAntrian
{
private:
    Pelanggan *head;
    Pelanggan *tail;
    int sizePelanggan = 0, totalUsia = 0;

public:
    DaftarAntrian() : head(nullptr), tail(nullptr) {}

    ~DaftarAntrian()
    {
        Pelanggan *current = head;
        while (current != nullptr)
        {
            Pelanggan *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void tambahPelangganAntrian()
    {
        menu("Mendata pelanggan");
        Pelanggan *temp = new Pelanggan;
        cout << "> Nama\t\t: ";
        cin >> temp->nama;
        cout << "> Usia\t\t: ";
        cin >> temp->usia;
        totalUsia += temp->usia;
        temp->next = nullptr;
        temp->prev = nullptr;
        if (head == nullptr)
            head = tail = temp;
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        sizePelanggan++;
        menu("Berhasil menambahkan daftar antrian: " + temp->nama + ", " + to_string(temp->usia));
    }

    Pelanggan pindah()
    {
        if (head == nullptr)
            return Pelanggan();
        Pelanggan *temp = tail;
        Pelanggan pindahPelanggan = *temp;
        if (head == tail)
            head = tail = nullptr;
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        return pindahPelanggan;
    }

    void averageUsia()
    {
        totalUsia == 0 ? menu("Average usia pelanggan: -") : menu("Average usia pelanggan: " + to_string(totalUsia / sizePelanggan));
    }

    void display()
    {
        menu("Menampilkan daftar antrian");
        cout << "No  Nama\tUsia" << endl;
        if (tail == nullptr)
            cout << "-" << endl;
        else
        {
            Pelanggan *current = tail;
            int i = 1;
            while (current != nullptr)
            {
                current->nama.size() < 4 ? cout << i << ".  " << current->nama << "\t\t" << current->usia << endl : cout << i << ".  " << current->nama << "\t" << current->usia << endl;
                current = current->prev;
                i++;
            }
        }
        baris();
    }
};

class DaftarPembelian
{
private:
    Pelanggan *head;
    Pelanggan *tail;

public:
    DaftarPembelian() : head(nullptr), tail(nullptr) {}

    ~DaftarPembelian()
    {
        Pelanggan *current = head;
        while (current != nullptr)
        {
            Pelanggan *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void tambahPelangganPembelian(DaftarAntrian &antrian)
    {
        Pelanggan pelanggan = antrian.pindah();
        if (pelanggan.nama.empty() && pelanggan.usia == 0)
        {
            menu("Tidak dapat memindah antrian karena tidak ada antrian");
            return;
        }
        Pelanggan *temp = new Pelanggan;
        *temp = pelanggan;
        temp->next = nullptr;

        if (tail != nullptr)
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        else
        {
            head = tail = temp;
            temp->prev = nullptr;
        }
        menu("Berhasil memindahkan ke daftar pembelian: " + temp->nama + ", " + to_string(temp->usia));
    }

    Pelanggan pindah()
    {
        if (head == nullptr)
            return Pelanggan();
        Pelanggan *temp = tail;
        Pelanggan pindahPelanggan = *temp;

        if (head == tail)
            head = tail = nullptr;
        else
        {
            tail = tail->prev;
            tail != nullptr ? tail->next = nullptr : head = nullptr;
        }
        delete temp;
        return pindahPelanggan;
    }

    void display()
    {
        menu("Menampilkan daftar pembelian");
        cout << "No  Nama\tUsia" << endl;
        if (head == nullptr)
            cout << "-" << endl;
        else
        {
            Pelanggan *current = head;
            int i = 1;
            while (current != nullptr)
            {
                current->nama.size() < 4 ? cout << i << ".  " << current->nama << "\t\t" << current->usia << endl : cout << i << ".  " << current->nama << "\t" << current->usia << endl;
                current = current->next;
                i++;
            }
        }
        baris();
    }
};

class DaftarSelesai
{
private:
    Pelanggan *head;
    Pelanggan *tail;

public:
    DaftarSelesai() : head(nullptr), tail(nullptr) {}

    ~DaftarSelesai()
    {
        Pelanggan *current = head;
        while (current != nullptr)
        {
            Pelanggan *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void tambahPelangganSelesai(DaftarPembelian &pembelian)
    {
        Pelanggan pelanggan = pembelian.pindah();
        if (pelanggan.nama.empty() && pelanggan.usia == 0)
        {
            menu("Tidak dapat memindah pembeli karena tidak ada pembeli");
            return;
        }
        Pelanggan *temp = new Pelanggan;
        *temp = pelanggan;
        temp->next = nullptr;
        string rating;
        menu("Pemberian rating oleh pelanggan " + temp->nama);
        cout << "> Rate (A/B/C/-): ";
        cin >> rating;
        rating == "a" || rating == "b" || rating == "c" || rating == "A" || rating == "B" || rating == "C" ? temp->rating = rating : temp->rating = "-";

        if (tail != nullptr)
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        else
        {
            head = tail = temp;
            temp->prev = nullptr;
        }
        menu("Berhasil memindahkan ke daftar selesai: " + temp->nama + ", " + to_string(temp->usia) + ", " + temp->rating);
    }

    void averageRating()
    {
        Pelanggan *temp = head;
        int countA = 0, countB = 0, countC = 0, countNetral = 0;
        while (temp != nullptr)
        {
            if (temp->rating == "a" || temp->rating == "A")
                countA++;
            else if (temp->rating == "b" || temp->rating == "B")
                countB++;
            else if (temp->rating == "c" || temp->rating == "C")
                countC++;
            else
                countNetral++;
            temp = temp->next;
        }
        if (countA == 0 && countB == 0 && countC == 0)
            menu("Average rating pelanggan: -");
        else if (countA >= countB && countA >= countC)
            if (countA == countB && countA == countC)
                menu("Average rating pelanggan: A / B / C");
            else if (countA == countB)
                menu("Average rating pelanggan: A / B");
            else if (countA == countC)
                menu("Average rating pelanggan: A / C");
            else
                menu("Average rating pelanggan: A");
        else if (countB > countA && countB >= countC)
            countB == countC ? menu("Average rating pelanggan: B / C") : menu("Average rating pelanggan: B");
        else
            menu("Average rating pelanggan: C");
        cout << "Rating A : " << countA << endl;
        cout << "Rating B : " << countB << endl;
        cout << "Rating C : " << countC << endl;
        cout << "Rating - : " << countNetral << endl;
        baris();
    }

    void display()
    {
        menu("Menampilkan daftar selesai");
        cout << "No  Nama\tUsia\tRating" << endl;
        if (head == nullptr)
            cout << "-" << endl;
        else
        {
            Pelanggan *current = head;
            int i = 1;
            while (current != nullptr)
            {
                current->nama.size() < 4 ? cout << i << ".  " << current->nama << "\t\t" << current->usia << "\t" << current->rating << endl : cout << i << ".  " << current->nama << "\t" << current->usia << "\t" << current->rating << endl;
                current = current->next;
                i++;
            }
        }
        baris();
    }
};

DaftarAntrian antrian;
DaftarPembelian pembelian;
DaftarSelesai selesai;
string input;

int main()
{
    menu("Selamat datang!");
    do
    {
        cout << "> Pilih Menu\t: ";
        cin >> input;
        input.size() > 1 ? input[0] = '-' : true;
        baris();
        switch (input[0])
        {
        case '1':
            antrian.tambahPelangganAntrian();
            break;
        case '2':
            pembelian.tambahPelangganPembelian(antrian);
            break;
        case '3':
            selesai.tambahPelangganSelesai(pembelian);
            break;
        case '4':
            antrian.display();
            break;
        case '5':
            pembelian.display();
            break;
        case '6':
            selesai.display();
            break;
        case '7':
            antrian.averageUsia();
            break;
        case '8':
            selesai.averageRating();
            break;
        default:
            menu("Input tidak sesuai");
        }
    } while (input[0] != '0');
    menu("Program selesai");
    return 0;
}