#include <iostream>

using namespace std;

void menu(string status = "-")
{
    system("cls");
    cout << "================ Keda Eskrim Vanilla Pak Vani ================" << endl;
    cout << "[1] Tambah Antrian" << endl;
    cout << "[2] Pindah Pembelian" << endl;
    cout << "[3] Selesai dan Rating" << endl;
    cout << "[4] Display Daftar Antrian" << endl;
    cout << "[5] Display Daftar Pembelian" << endl;
    cout << "[6] Display Daftar Selesai" << endl;
    cout << "[7] Display Average Usia" << endl;
    cout << "[8] Display Average Rating" << endl;
    cout << "[0] Exit" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "[Status] " << status << endl;
    cout << "--------------------------------------------------------------" << endl;
}

void hold()
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "[0] Back: ";
    string temp;
    cin >> temp;
}

struct Pelanggan
{
    string nama;
    int usia;
    char rating;
    Pelanggan *next;
    Pelanggan *prev;
};

class DaftarAntrian
{
private:
    Pelanggan *head;
    Pelanggan *tail;
    int sizeAntrian = 0;
    int totalUsia = 0;

public:
    DaftarAntrian()
    {
        head = tail = nullptr;
    }

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
        sizeAntrian++;
        menu("Berhasil menambahkan daftar antrian: " + temp->nama + ", " + to_string(temp->usia));
    }

    Pelanggan pindah()
    {
        if (head == nullptr)
            return Pelanggan();
        Pelanggan *temp = tail;
        Pelanggan removedPelanggan = *temp;
        if (head == tail)
            head = tail = nullptr;
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        sizeAntrian--;
        return removedPelanggan;
    }

    void averageUsia()
    {
        if (totalUsia == 0)
            menu("Average usia pelanggan: -");
        else
            menu("Average usia pelanggan: " + to_string(totalUsia / sizeAntrian));
    }

    void display()
    {
        menu("Menampilkan daftar Antrian");
        cout << "No  Nama\tUsia" << endl;
        if (tail == nullptr)
            cout << "-" << endl;
        else
        {
            Pelanggan *current = tail;
            int count = sizeAntrian;
            int i = 1;
            while (current != nullptr)
            {
                cout << i << ".  " << current->nama << "\t" << current->usia << endl;
                current = current->prev;
                count--;
                i++;
            }
        }
        hold();
        menu();
    }
};

class DaftarPembelian
{
private:
    Pelanggan *head;
    Pelanggan *tail;
    int sizePembelian = 0;

public:
    DaftarPembelian()
    {
        head = tail = nullptr;
    }

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
        sizePembelian++;
        menu("Berhasil memindahkan ke daftar pembelian: " + temp->nama + ", " + to_string(temp->usia));
    }

    Pelanggan pindah()
    {
        if (head == nullptr)
            return Pelanggan();
        Pelanggan *temp = tail;
        Pelanggan removedPelanggan = *temp;

        if (head == tail)
            head = tail = nullptr;
        else
        {
            tail = tail->prev;
            if (tail != nullptr)
                tail->next = nullptr;
            else
                head = nullptr;
        }
        delete temp;
        sizePembelian--;
        return removedPelanggan;
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
            int count = 1;
            while (current != nullptr)
            {
                cout << count << ".  " << current->nama << "\t" << current->usia << endl;
                current = current->next;
                count++;
            }
        }

        hold();
        menu();
    }
};

class DaftarSelesai
{
private:
    Pelanggan *head;
    Pelanggan *tail;
    int sizeSelesai = 0;

public:
    DaftarSelesai()
    {
        head = tail = nullptr;
    }

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
        char rating;
        menu("Pemberian rating oleh pelanggan " + temp->nama);
        cout << "> Rating A/B/C/-: ";
        cin >> rating;
        if (rating == 'a' || rating == 'b' || rating == 'c' || rating == 'A' || rating == 'B' || rating == 'C')
            temp->rating = rating;
        else
            temp->rating = '-';

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
        sizeSelesai++;
        menu("Berhasil memindahkan ke daftar selesai: " + temp->nama + ", " + to_string(temp->usia) + ", " + temp->rating);
    }

    void averageRating()
    {
        Pelanggan *temp = head;
        int countA = 0, countB = 0, countC = 0, countTidakRating = 0;
        while (temp != nullptr)
        {
            if (temp->rating == 'a' || temp->rating == 'A')
                countA++;
            else if (temp->rating == 'b' || temp->rating == 'B')
                countB++;
            else if (temp->rating == 'c' || temp->rating == 'C')
                countC++;
            else
                countTidakRating++;
            temp = temp->next;
        }
        if (countA == 0 && countB == 0 && countC == 0)
            menu("Average Rating Pelanggan: -");
        else if (countA >= countB && countA >= countC)
            if (countA == countB && countA == countC)
                menu("Average Rating Pelanggan: A / B / C");
            else if (countA == countB)
                menu("Average Rating Pelanggan: A / B");
            else if (countA == countC)
                menu("Average Rating Pelanggan: A / C");
            else
                menu("Average Rating Pelanggan: A");
        else if (countB > countA && countB >= countC)
            if (countB == countC)
                menu("Average Rating Pelanggan: B / C");
            else
                menu("Average Rating Pelanggan: B");
        else
            menu("Average Rating Pelanggan: C");
        cout << "Rating A : " << countA << endl;
        cout << "Rating B : " << countB << endl;
        cout << "Rating C : " << countC << endl;
        cout << "Rating - : " << countTidakRating << endl;
        hold();
        menu();
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
            int count = 1;
            while (current != nullptr)
            {
                cout << count << ".  " << current->nama << "\t" << current->usia << "\t" << current->rating << endl;
                current = current->next;
                count++;
            }
        }
        hold();
        menu();
    }
};

DaftarAntrian antrian;
DaftarPembelian pembelian;
DaftarSelesai selesai;

int main()
{
    int inputInt1;
    string inputStr1;
    menu();
    do
    {
        cout << "> Pilih Menu\t: ";
        cin >> inputInt1;
        cout << "--------------------------------------------------------------" << endl;
        switch (inputInt1)
        {
        case 1:
            antrian.tambahPelangganAntrian();
            break;
        case 2:
            pembelian.tambahPelangganPembelian(antrian);
            break;
        case 3:
            selesai.tambahPelangganSelesai(pembelian);
            break;
        case 4:
            antrian.display();
            break;
        case 5:
            pembelian.display();
            break;
        case 6:
            selesai.display();
            break;
        case 7:
            antrian.averageUsia();
            break;
        case 8:
            selesai.averageRating();
            break;
        }
    } while (inputInt1 != 0);

    return 0;
}