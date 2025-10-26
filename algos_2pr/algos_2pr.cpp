#include <random>
#include <windows.h>

#include "Dynamic_Arr.h"
#include "Timsort.h"

#include <iostream>
using namespace std;

void show_menu() {
    cout << "1. Создать пустой массив\n";
    cout << "2. Заполнить вручную\n";
    cout << "3. Сгенерировать случайно\n";
    cout << "4. Добавить элемент\n";
    cout << "5. Удалить элемент по индексу\n";
    cout << "6. Просмотреть массив\n";
    cout << "7. Размер массива\n";
    cout << "8. Сортировка Timsort\n";
    cout << "9. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Dynamic_Arr arr = Dynamic_Arr();

    show_menu();
    while (true) {
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }
        switch (choice) {
        
        case 1: {
            arr.clear();
            cout << " Создан пустой массив." << endl;
            break;
        }
        
        case 2: {
            arr.clear();
            cout << "Введите количество элементов: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++) {
                int value;
                cout << "Элемент " << i + 1 << ": ";
                cin >> value;
                arr.add(value);
            }
            cout << "Массив заполнен вручную." << endl;
            break;
        }
        
        case 3: {
            arr.clear();
            cout << "Введите количество элементов: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                int value = -10000 + rand() % 20001;
                arr.add(value);
            }
            cout << "Сгенерировано " << n << " случайных чисел." << endl;
            break;
        }
        
        case 4: {
            int value;
            cout << "Введите значение: ";
            cin >> value;
            arr.add(value);
            cout << "Элемент добавлен." << endl;
            break;
        }
        
        case 5: {
            if (arr.empty()) {
                cout << "Массив пуст.\n";
                break;
            }
            int index;
            cout << "Введите индекс для удаления (0–" << arr.get_size() - 1 << "): ";
            cin >> index;
            if (index < 0 || index >= arr.get_size()) {
                cout << "Неверный индекс.\n";
            }
            else {
                arr.remove(index);
                cout << "Элемент удалён." << endl;
            }
            break;
        }
        
        case 6: {
            if (arr.empty()) {
                cout << "Массив пуст." << endl;
            }
            else {
                arr.print();
                cout << endl;
            }
            break;
        }
        
        case 7: {
            cout << "Размер: " << arr.get_size() << endl;
            break;
        }
        
        case 8: {
            if (arr.empty()) {
                cout << "Массив пуст — сортировка не нужна." << endl;
            }
            else {
                Timsort sorter(arr);
                auto start = chrono::high_resolution_clock::now();
                sorter.sort();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
                cout << "Массив отсортирован." << endl;
            }
            break;
        }

        case 9:
            cout << "Выход." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}
