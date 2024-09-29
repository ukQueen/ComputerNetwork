#include <iostream>
#include "Network.h"

int main() {

    setlocale(LC_ALL, "rus");
    Network AlexeyShihalev(13, 4, 3, 4, 3);
    Network IgorGladkov(11, 5, 3, 4, 2);
    Network NikitaRomashko(10, 3, 4, 3, 3);
    Network GeorgyZoloev(7, 6, 3, 2, 3);

    Network a(7, 2, 1, 3, 5);

    cout << "Программа, моделирующая работу механизма передачи сообщения в коммуникационной сети суперкомпьютера" << endl;

    while (true) {

        cout << "\n Выберите студента: \n";
        cout << " [1] Алексей Шихалев \n";
        cout << " [2] Игорь Гладков \n";
        cout << " [3] Никита Ромашко\n";
        cout << " [4] Георгий Золоев\n";
        cout << " [5] Тестовый вариант\n";
        cout << " [0] Выход из программы\n";

        int b = a.checking_input(5);

        switch (b) {

        case 1:
            //AlexeyShihalev.Print_matrix_bandwidth();
            AlexeyShihalev.printInfo();

            AlexeyShihalev.menu();
            break;

        case 2: 
            //IgorGladkov.Print_matrix_bandwidth();
            IgorGladkov.printInfo();

            IgorGladkov.menu();
            break;

        case 3:
            //NikitaRomashko.Print_matrix_bandwidth();
            NikitaRomashko.printInfo();

            NikitaRomashko.menu();
            break;

        case 4:
            //GeorgyZoloev.Print_matrix_bandwidth();
            GeorgyZoloev.printInfo();

            GeorgyZoloev.menu();
            break;

        case 5:
            a.printInfo();
            a.menu();
            break;

        case 0:
            cout << "Выход из программы...\n";
            return 0;
        }

    }


    //a.Print_matrix_bandwidth();
    //a.Dijkstra_algorythm({ 0,5,3 });

}