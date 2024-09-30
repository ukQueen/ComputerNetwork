#include <iostream>
#include "Network.h"

int main() {

    setlocale(LC_ALL, "rus");
    Network AlexeyShihalev(13, 4, 3, 4, 3);
    Network IgorGladkov(11, 5, 3, 4, 2);
    Network NikitaRomashko(10, 3, 4, 3, 3);
    Network GeorgyZoloev(7, 6, 3, 2, 3);

    Network a(7, 2, 1, 5, 3);

    cout << "Программа, моделирующая работу механизма передачи сообщения в коммуникационной сети суперкомпьютера" << endl;

    while (true) {

        cout << "\n Выберите студента: \n";
        cout << " [1] Алексей Шихалев {13, 4, 3, 4, 3} \n";
        cout << " [2] Игорь Гладков {11, 5, 3, 4, 2}\n";
        cout << " [3] Никита Ромашко {10, 3, 4, 3, 3}\n";
        cout << " [4] Георгий Золоев {7, 6, 3, 2, 3}\n";
        cout << " [0] Выход из программы\n";

        int b = a.checking_input(4);

        switch (b) {

        case 1:
            AlexeyShihalev.printInfo();
            AlexeyShihalev.menu();
            break;

        case 2: 
            IgorGladkov.printInfo();
            IgorGladkov.menu();
            break;

        case 3:
            NikitaRomashko.printInfo();
            NikitaRomashko.menu();
            break;

        case 4:
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
}