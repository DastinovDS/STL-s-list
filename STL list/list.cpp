#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cctype>
#include <list>
#include <iterator>

using namespace std;

class Info{
public:
    string m_name;
    int m_date;
    int m_amount;
    Info(string name, int date, int amount) : m_name(name), m_date(date), m_amount(amount){}
    string getName(){return m_name;}
    int getDate(){return m_date;}
    int getAmount(){return m_amount;}
};

bool find(list<Info> :: iterator &i, list<Info> l, int amount){
    int cnt = 0;
    for(i = l.begin(); i != l.end(); i++){
        if(i != l.end() && i->getAmount() == amount){
            cnt++;
            break;
        }
    }
    if(cnt != 0) return true;
    else return false;
}

bool add_el(list<Info> l, list<Info> &spec_l, int k){
    spec_l.clear();
    list<Info> :: iterator i;
    int cnt = 0;
    for(i = l.begin(); i != l.end(); i++){
        if(i != l.end() && i->m_amount < k){
            spec_l.push_back(*i);
        }
        else cnt++;
    }
    if(cnt == l.size()){
        cout << "Нет элементов, меньше k" << endl;
        return false;
    }
    else{
        cout << "Изменения внесены" << endl;
        return true;
    }
}

void out_n_choose(list<Info> &l){
    list<Info> :: iterator i;
    int cnt = 1;
    for(i = l.begin(); i != l.end(); i++){
        cout << cnt << ")" << i->getName() << endl;
        cnt++;
    }
    int ch;
    while(1){
        cout << "Выберете элемент, количество которого хотите изменить: ";
        cin >> ch;
        if(ch < 1 || ch > l.size()) cout << "Ошибка" << endl;
        else break;
    }
    i = l.begin();
    ch--;
    advance(i, ch);
    cout << "Изначальное количество: " << i->m_amount << endl;
    while(1){
        cout << "Введите новое количество: ";
        cin >> cnt;
        if(cnt < 0) cout << "Ошибка" << endl;
        else break;
    }
    i->m_amount = cnt;
}

void outp(list<Info> l){
    list<Info> :: iterator i;
    cout << endl;
    for(i = l.begin(); i != l.end(); i++){
        cout << "Название модели: " << i->getName() << endl;
        cout << "Дата изготовления: " << i->getDate() << endl;
        cout << "Количество: " << i->getAmount() << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    list<Info> info;
    list<Info> :: iterator it;
    list<Info> spec_info;
    while(1){
        int choice;
        while(1){
            cout << "Выберете действия:\n1)Добавить новый элемент в список\n2)Поиск элемента по полю Количество\n3)Заполнение подсписка элементами, меньше k\n4)Изменение поля Количество выбранного элемента\n5)Вывод подсписков\n6)Выход из программы\n";
            cin >> choice;
            if(choice < 1 || choice > 6) cout << "Ошибка" << endl;
            else break;
        }
        switch(choice){
            case 1:{
                string name;
                cin.ignore(32767, '\n');
                cout << "Введите наименование модели: ";
                getline(cin, name);
                int date;
                while(1){
                    cout << "Введите дату изготовления(Не ранее 1900 года): ";
                    cin >> date;
                    if(date < 1900 || date > 2022) cout << "Ошибка" << endl;
                    else break;
                }
                int amount;
                while(1){
                    cout << "Введите количество моделей: ";
                    cin >> amount;
                    if(amount < 0) cout << "Ошибка" << endl;
                    else break;
                }
                Info object(name, date, amount);
                info.push_back(object);
                cout << "Элемент добавлен" << endl;
                break;
            }
            case 2:{
                if(info.empty() == true) cout << "Список пуст!" << endl;
                else{
                    int cnt_find;
                    while(1){
                        cout << "Введите искомое Количество: ";
                        cin >> cnt_find;
                        if(cnt_find < 0) cout << "Ошибка" << endl;
                        else break;
                    }
                    if(find(it, info, cnt_find) == true){
                        cout << "Элемент найден!" << endl;
                        cout << "Название модели: " << it->m_name << endl;
                        cout << "Дата изготовления: " << it->m_date << endl;
                        cout << "Количество: " << it->m_amount << endl;
                        }
                    else cout << "Такого элемента не существует!" << endl;
                }
                break;
            }
            case 3:{
                if(info.empty() == true) cout << "Базовый список пуст!" << endl;
                else{
                    int k;
                    while(1){
                        cout << "Введите k, для заполнения подсписка по полю *Количество* меньше k: ";
                        cin >> k;
                        if(k < 0) cout << "Ошибка" << endl;
                        else if(add_el(info, spec_info, k) != true) cout << endl;
                        else break;
                    }
                }
                break;
            }
            case 4:{
                if(info.empty() == true) cout << "Список пуст" << endl;
                else{
                    out_n_choose(info);
                    cout << "Изменения внесены" << endl;
                }
                break;
            }
            case 5:{
                while(1){
                    cout << "Выберете, какой подсписок хотите вывести:\n1)Основной\n2)С элементами меньше k\n3)Оба\n";
                    cin >> choice;
                    if(choice < 1 || choice > 3) cout << "Ошибка" << endl;
                    else break;
                }
                switch(choice){
                    case 1:
                        if(info.empty() == true) cout << "Основной список пуст" << endl;
                        else outp(info);
                        break;
                    case 2:
                        if(spec_info.empty() == true) cout << "Подсписок пуст" << endl;
                        else outp(spec_info);
                        break;
                    case 3:
                        if(info.empty() == true || spec_info.empty() == true) cout << "Один из списков пуст, вывод двух невозможен" << endl;
                        else{
                            cout << "Основоной список:" << endl;
                            outp(info);
                            cout << "Список с элементами, меньше k:" << endl;
                            outp(spec_info);
                        }
                        break;
                }
                break;
            }
            case 6:
                return 0;
        }
    }
}