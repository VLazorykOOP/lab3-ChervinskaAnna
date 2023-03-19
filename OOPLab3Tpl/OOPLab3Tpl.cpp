// OOPLab3Tpl.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №3. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

// Ваші файли загловки 
//
#include "Lab3Example.h"

void SelectTask() {
    char ch;

    do {
        cout << "\n  Select Task:   \n";
        cout << "    1.  Task 1 \n";
        cout << "    2.  Task 2 \n";
        cout << "    3.  Task 3 \n";
        cout << "    4.  Exit \n";

        ch = _getch();
        switch (ch) {
        case '1': Task1(); break;
        case '2': Task2(); break;
        case '3': Task3(); break;
        }
    } while (ch != '4');
}

int main()
{
    std::cout << " Lab #3  !\n";
    //  Код виконання завдань
    //  Головне меню завдань
    //  Функції та класи можуть знаходитись в інших файлах проекту

    SelectTask();

    return 1;
}
