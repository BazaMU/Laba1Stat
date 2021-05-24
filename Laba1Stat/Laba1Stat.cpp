#include <iostream>

using namespace std;

//структура вагон с параметрами вместимость и пассажиры
struct Vagon {

private:
    int c = 0, p = 0;

public:
    Vagon() {}
    Vagon(int p0, int c0) {
        c = c0;
        p = p0;
    }

    void SetP(int p0) {
        //cout << "p=" << p0 <<"\n";    
        if (p > c) { throw runtime_error("число пассажиров превышает число мест в вагоне"); }
        else { p = p0; }
    }

    void SetC(int c0) { c = c0; }
    int GetC() const { return c; }
    int GetP() const { return p; }

    friend istream& operator>>(istream&, Vagon&);
    //friend ostream& operator<<(ostream&, Train&);
};

class Train {

private:
    int n = 0;
    Vagon train[10];
public:
    Train() {}
    /*~Train() {
       // delete[] train;
    }*/
    int GetC(int l) const {
        int C = train[l].GetC();
        return C;
    }
    int GetP(int k) const {
        int P = train[k].GetP();
        return P;
    }

    int get_length() { return n; }

    void train_length(int n0) {
        if (n0 > 10) { throw runtime_error("число вагонов превышено"); }
        else { n = n0; }
    }
    /*void add_vagon() {
        if (n == 10) { throw runtime_error("число вагонов превышено"); }
        else { n++; }
    }*/

    friend istream& operator>>(istream&, Train&);
    friend ostream& operator<<(ostream&, const Train&);

    Train& operator()(int i, int new_pass) {

        int pass = train[i].GetP();
        if (new_pass > train[i].GetC() - pass) { throw runtime_error("число пассажиров превышено"); }
        else { train[i].SetP(pass + new_pass); }
        return *this;
    }

    void operator[](int n) {
        cout << "количество занятых мест в вагоне " << n << ": " << train[n].GetP() << endl;
    }

    Train& operator+=(Vagon new_vagon) {

        n++;
        train[n - 1].SetP(new_vagon.GetP());
        train[n - 1].SetC(new_vagon.GetC());
        return *this;

    }

    Train& operator+=(Train new_train) {
        n++;
        train[n - 1].SetP(new_train.GetP(0));
        train[n - 1].SetC(new_train.GetC(0));
        return *this;
    }

    int const Sum() {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum = sum + train[i].GetP();
        }
        return sum;
    }



    Train operator()(int vagon_number, int vagon_list[]) { // пример: Train b = a(2, arr[2] = {1, 3}) 
        if (vagon_number > n) { throw runtime_error("количество отцепленных вагонов должно быть меньше или равно длине поезда"); }
        Train new_train; //новый поезд из отцепленных вагонов
        Vagon buff[10]; //буферный массив вагонов
        int new_c;
        int new_p;
        Vagon new_vagon; //буферный вагон
        for (int i = 0; i < n; i++) { //копируем старый поезд в буферный массив
            buff[i].SetC(train[i].GetC());
            //cout << "buff " << train[i].GetP() << "\n";
            buff[i].SetP(train[i].GetP());
        }
        for (int i = 0; i < vagon_number; i++) { //копируем отцепленые вагоны в новый поезд
            new_c = train[vagon_list[i]].GetC();
            new_p = train[vagon_list[i]].GetP();
            //cout << "new_p " << train[vagon_list[i]].GetP() << "\n";
            new_vagon.SetC(new_c);
            new_vagon.SetP(new_p);
            new_train += new_vagon;
        }
        int k = 0;
        for (int i = 0; i < n; i++) { //копируем неотцепленные вагоны из буферного массива в старый поезд
            int list_length = 0;
            for (int j = 0; j < vagon_number; j++) {
                if (i != vagon_list[j]) { //если номер вагона из буфера не равен номеру вагона из списка отцепленных, копируем его в старый поезд
                    list_length++;
                }
                if (list_length == vagon_number) {
                    train[k].SetC(buff[i].GetC());
                    //cout << "train1 " << buff[i].GetP() << "//" << i << "\n";
                    train[k].SetP(buff[i].GetP());
                    k++;
                }
            }
        }
        n = n - vagon_number; //уменьшаем длину старого поезда
        return new_train;
    }


};

//дружеские операторы ввода и вывода
istream& operator>>(istream& intov, Vagon& obj) {

    intov >> obj.c >> obj.p;
    return intov;
}

istream& operator>>(istream& intot, Train& obj) {
    //intot >> obj.train[i];
    for (int i = 0; i < obj.n; i++) {
        intot >> obj.train[i];
    }
    return intot;
}
ostream& operator<<(ostream& out, const Train& obj) {
    int sum_pass = 0;
    int c1, p1;
    for (int i = 0; i < obj.n; i++) {
        c1 = obj.train[i].GetC();
        p1 = obj.train[i].GetP();
        sum_pass = sum_pass + c1 - p1;
    }
    string s = "количество свободных мест в поезде: ";
    out << s << sum_pass << "\n";
    return out;
}
int main()
{
    setlocale(0, "rus");
    Train a;
    Train c;
    a.train_length(5);
    c.train_length(1);
    //a.add_vagon();

    cin >> a;
    cin >> c;
 
    a += c;
    //Vagon vagonn = Vagon(6, 10);
    //a += vagonn;

    int list[2] = { 0, 1 };
    Train b = a(2, list);
    a[0];
    a[1];
    a[2];
    a[3];
    
    

    b[0];
    b[1];
         

    a.Sum();
    cout << a;
    cout << b;
    return 0;
}