#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

const int size_str = 50;


struct date {
    int d;
    int m;
    int y;
};


struct stock {
    char name[size_str];
    char producer[size_str];
    double price;
    char group[size_str];
    char date[size_str];
    int expiration_date;
    int remaining_term;
};


bool IsLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    else {
        return false; 
    }
}


int countDay(int m1,int y) {
    if (m1 == 2) {
        if (IsLeapYear(y))return 29;
        else return 28;
    }
    if (m1 == 1 || m1 == 3 || m1 == 5 || m1 == 7 || m1 == 81 || m1 == 10 || m1 == 12)return 31;
    return 30;
}


bool prov_data(int d1, int m1, int y1) {
    if (d1 <= countDay(m1, y1))return true;
    return false;
}


int date_difference(int d1, int m1, int y1,date a) {
    int t=0;
    while (y1 < a.y) {
        if (IsLeapYear(y1))t += 366;
        else t += 365;
        y1++;
    }
    if (m1 < a.m) {
        while (m1 < a.m) {
            t += countDay(m1,a.y);
            m1++;
        }
    }
    
    if (m1 > a.m) {
        while (m1 > a.m) {
            t -= countDay(m1, a.y);
            m1--;
        }
    }
    if (d1 < a.d) {
        while (d1 < a.d) {
            t++;
            d1++;
        }
    }
    if(d1>a.d) {
        while (d1 > a.d) {
            t--;
            d1--;
        }
    }
    return t;

}


void my_date(int& d1, int& m1, int& y1, char* a) {
    d1 = (a[0] - '0') * 10 + (a[1] - '0');
    m1 = (a[3] - '0') * 10 + (a[4] - '0');
    y1 = (a[6]-'0') * 1000 + (a[7] - '0') * 100 + (a[8] - '0') * 10 + (a[9] - '0');
    
}


void print_stock(stock* a, int size) {
    cout << "\n\n";
    for (int i = 0; i < size; i++) {
        cout << "Название:        " << a[i].name << "\n";
        cout << "Производитель:   " << a[i].producer << "\n";
        cout << "Цена:            " << a[i].price << "\n";
        cout << "Группа:          " << a[i].group << "\n";
        cout << "Дата добавления: " << a[i].date << "\n";
        cout << "Срок годности:   " << a[i].expiration_date << "\n";
        cout << "Оставшийся срок годности:   " << a[i].remaining_term << "\n";
        cout << "\n\n";
    }

}


bool check(char a[], char b[]) {
    if (strlen(a) != strlen(b))return false;
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] != b[i])return false;
    }return true;
}


bool prov(stock* x, char a[], int size) {
    for (int i = 0; i < size; i++) {
        if (check(x[i].name, a))return true;
    }return false;
}


stock* add_product(stock* x, int size,date d) {
    stock a;
    while (true) {
        cout << "Введите название товара\n";
        cin >> a.name;
        if (prov(x, a.name, size)) {
            cout << "Такой товар уже есть!\n";
            continue;
        }
        break;
    }
    
    cout << "Введите производителя товара\n";
    cin >> a.producer;
    cout << "Введите цену товара\n";
    cin >> a.price;
    cout << "Введите группу товара\n";
    cin >> a.group;
    while (true) {
        int d1, m1, y1;
        cout << "Введите дату добавления товара\n";
        cin >> a.date;
        my_date(d1, m1, y1, a.date);
        if (prov_data(d1, m1, y1)) {
            if (y1 == d.y && m1 == d.m && d1 <= d.d)break;
            if (y1 == d.y && m1 < d.m)break;
            if (y1 < d.y)break;
        }
        cout << "Неправильная дата!\n";
    }
    cout << "Введите срок годности товара (в днях)\n";
    cin >> a.expiration_date;
    int d1, m1, y1;
    my_date(d1, m1, y1, a.date);
    if (d1 == d.d && m1 == d.m && y1 ==d. y)a.remaining_term = a.expiration_date;
    else a.remaining_term = a.expiration_date - date_difference(d1, m1, y1,d);
        
  


    stock* my_stock = new stock[size + 1];
    for (int i = 0; i < size; i++) {
        strcpy(my_stock[i].name, x[i].name);
        strcpy(my_stock[i].producer, x[i].producer);
        my_stock[i].price = x[i].price;
        strcpy(my_stock[i].group, x[i].group);
        strcpy(my_stock[i].date, x[i].date);
        my_stock[i].expiration_date = x[i].expiration_date;
        my_stock[i].remaining_term = x[i].remaining_term;
    }

    strcpy(my_stock[size].name, a.name);
    strcpy(my_stock[size].producer, a.producer);
    my_stock[size].price = a.price;
    strcpy(my_stock[size].group, a.group);
    strcpy(my_stock[size].date, a.date);
    my_stock[size].expiration_date = a.expiration_date;
    my_stock[size].remaining_term = a.remaining_term;
    return my_stock;
}


void print_product(stock* a, int i) {
    cout << "Название:        " << a[i].name << "\n";
    cout << "Производитель:   " << a[i].producer << "\n";
    cout << "Цена:            " << a[i].price << "\n";
    cout << "Группа:          " << a[i].group << "\n";
    cout << "Дата добавления: " << a[i].date << "\n";
    cout << "Срок годности:   " << a[i].expiration_date << "\n";
    cout << "Оставшийся срок годности:   " << a[i].remaining_term << "\n";
    cout << "\n\n";


}


void search_product(stock* a, int c,int size) {
    char s[size_str];
    int x;
    switch (c) {
        case 1:
            cout << "Введите название для поиска\n";
            cin >> s;
            break;
        case 2:
            cout << "Введите производителя для поиска\n";
            cin >> s;
            break;
        case 3:
            cout << "Введите группу для поиска\n";
            cin >> s;
            break;
        case 4:
            cout << "Введите дату для поиска\n";
            cin >> s;
            break;
        default:
            cout << "Неправильный ввод!\n";
            return;

    }
    int k = 0;
    cout << "\n\n";
    for (int i = 0; i < size; i++) {
        if (c == 1 && check(a[i].name, s)) { print_product(a, i); k++; }
        else if (c == 2 && check(a[i].producer, s)) { print_product(a, i); k++; }
        else if (c == 3 && check(a[i].group, s)) { print_product(a, i); k++; }
        else if (c == 4 && check(a[i].date, s)) { print_product(a, i); k++; }
    }
    if (k == 0)cout << "Ничего не найдено :(\n";
    else cout << "Найдено " << k << " товаров\n";
}


void search(stock* a, int size) {
    int c;
    cout << "Поиск по (1- названию, 2- производителю, 3- группе, 4- дате,)\n";
    cin >> c;
    if (c < 1 || c>4) {
        cout << "Неправильный ввод!\n";
        return;
    }
    search_product(a, c, size);

}


bool sort_str(char* a, char* b) {
    for (int i = 0; i < min(strlen(a), strlen(b)); i++)
        if (a[i] > b[i])return true;
        else if (a[i] < b[i])return false;
    return false;
}


void sort_product(stock* a, int c,int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (c == 1 && sort_str(a[j].name,a[j+1].name))swap(a[j], a[j + 1]);
            else if (c == 2 && sort_str(a[j].producer, a[j + 1].producer))swap(a[j], a[j + 1]);
            else if (c == 3 && sort_str(a[j].group, a[j + 1].group))swap(a[j], a[j + 1]);
            else if (c == 4 && sort_str(a[j].date, a[j + 1].date))swap(a[j], a[j + 1]);
            else if (c == 5 && a[j].price > a[j + 1].price)swap(a[j], a[j + 1]);
            else if (c == 6 && a[j].remaining_term > a[j + 1].remaining_term)swap(a[j], a[j + 1]);
        }
    }
}


void sort_stock(stock* a,int size) {
    int c;
    cout << "Сортировать по (1- названию, 2- производителю, 3- группе, 4- дате, 5- цене, 6- оставшийся сроку годности)\n"; 
    cin >> c;
    if (c < 1 || c>6) {
        cout << "Неправильный ввод!\n";
        return;
    }
    sort_product(a, c,size);
}


stock* delete_product(stock* a, int size)
 {
    if (size == 0) {
        cout << "Еще нет ни одного товара!\n";
        return a;
    }
    char s[size_str];
    int ind = -1;
    while (true) {
        cout << "Введите товар для удаления\n";
        cin >> s;
        
        for (int i = 0; i < size; i++) {
            if (check(a[i].name, s)) {
                ind = i;
                break;
            }
        }
        if (ind == -1) {
            cout << "Такого товара не существует!\n";
            continue;
        }break;
    }
    stock* ans = new stock[size-1];
    int c = 0;
    for (int i = 0; i < size; i++) {
        if (check(a[i].name, s))continue;
        ans[c] = a[i];
        c++;
    }
    
    return ans;

}


stock* replace_product(stock* a, int size,date d) {
    if (size == 0) {
        cout << "Еще нет ни одного товара!\n";
        return a;
    }
    char s[size_str];
    int ind = -1;
    while (true) {
        cout << "Введите товар для замены\n";
        cin >> s;

        for (int i = 0; i < size; i++) {
            if (check(a[i].name, s)) {
                ind = i;
                break;
            }
        }
        if (ind == -1) {
            cout << "Такого товара не существует!\n";
            continue;
        }break;
    }
    stock* ans = new stock[size];
    for (int i = 0; i < ind; i++) {
        strcpy(ans[i].name, a[i].name);
        strcpy(ans[i].producer, a[i].producer);
        ans[i].price = a[i].price;
        strcpy(ans[i].group, a[i].group);
        strcpy(ans[i].date, a[i].date);
        ans[i].expiration_date = a[i].expiration_date;
        ans[i].remaining_term = a[i].remaining_term;
    }
    cout << "Введите название товара\n";
    cin >> ans[ind].name;

    cout << "Введите производителя товара\n";
    cin >> ans[ind].producer;
    cout << "Введите цену товара\n";
    cin >> ans[ind].price;
    cout << "Введите группу товара\n";
    cin >> ans[ind].group;
    while (true) {
        int d1, m1, y1;
        cout << "Введите дату добавления товара\n";
        cin >> ans[ind].date;
        my_date(d1, m1, y1, ans[ind].date);
        if (prov_data(d1, m1, y1)) {
            if (y1 == d.y && m1 == d.m && d1 <= d.d)break;
            if (y1 == d.y && m1 < d.m)break;
            if (y1 < d.y)break;
        }
        cout << "Неправильная дата!\n";
    }
    
    cout << "Введите срок годности товара (в днях)\n";
    cin >> ans[ind].expiration_date;
    int d1, m1, y1;
    my_date(d1, m1, y1, ans[ind].date);
    ans[ind].remaining_term = ans[ind].expiration_date - date_difference(d1, m1, y1,d) + 1;
    if (d1 == d.d && m1 == d.m && y1 == d.y)ans[ind].remaining_term = ans[ind].expiration_date;
    else ans[ind].remaining_term = ans[ind].expiration_date - date_difference(d1, m1, y1, d);

    for (int i = ind+1; i < size; i++) {
        strcpy(ans[i].name, a[i].name);
        strcpy(ans[i].producer, a[i].producer);
        ans[i].price = a[i].price;
        strcpy(ans[i].group, a[i].group);
        strcpy(ans[i].date, a[i].date);
        ans[i].expiration_date = a[i].expiration_date;
        ans[i].remaining_term = a[i].remaining_term;
    }

    return ans;

}


void create_old_data(stock* a, int size,FILE* data,const char* path) {
    if (fopen_s(&data, path, "rb") != NULL) {
        cout << "The file cannot be opened";
    }
    else {
        fread(a, sizeof(stock), size, data);
    }
    
}


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(NULL));
    char* str = new char[size_str];
    date today;
    while (true) {
        cout << "Введите сегодняшнюю дату (дд.мм.гггг)\n";
        cin >> str;
        my_date(today.d, today.m, today.y, str);
        if (today.d <= countDay(today.m, today.y) && strlen(str)==10 && today.m<=12)break;
        cout << "неправильная дата!\n";
    }
    
    
    

    const char* path = "Stock_data.txt";
    FILE* data;
    if (fopen_s(&data, path, "rb") != NULL) {
        cout << "The file cannot be opened";
        return 0;
    }

    fseek(data, 0, SEEK_END);
    int size = ftell(data);
    size /= sizeof(stock);
    stock* my_stock = new stock[size];
    fseek(data, 0, SEEK_SET);
    fread(my_stock, sizeof(stock), size, data);

    fclose(data);


    while (true) {
        cout << "\n\nВведите команду:\nдобавить товар - 1\nпосмотреть список товаров - 2\nпоиск - 3\nсортировать - 4\nудаление -  5\nзамена - 6\nвыход - 7)\n";
        int choose;
        cin >> choose;
        switch (choose) {
        case 1:
            my_stock = add_product(my_stock, size,today);
            size++;
            break;
        case 2:
            print_stock(my_stock, size);
            break;
        case 3:
            search(my_stock,size);
            break;
        case 4:
            sort_stock(my_stock, size);
            break;
        case 5:
            my_stock=delete_product(my_stock, size);
            size--;
            break;
        case 6:
            my_stock=replace_product(my_stock, size,today);
            break;
        case 7:
            cout << "Good bye...";
            if (fopen_s(&data, path, "wb") != NULL)
                cout << "The file cannot be opened";
            else {
                fwrite(my_stock, sizeof(stock), size, data);
                fclose(data);
            }
            
            return 0;
        default:
            cout << "Неправильный ввод!\n";
            continue;
       }
    }
    
}

