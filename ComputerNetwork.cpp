#include <iostream>
#include "Network.h"

int main()
{
    setlocale(LC_ALL, "rus");
    //Network AlexeyShihalev(13, 4, 3, 4, 3);

   // AlexeyShihalev.Print_matrix_bandwidth();
    //AlexeyShihalev.Dijkstra_algorythm({ 0,5,3 });

    //Network IgorGladkov(11, 5, 3, 4, 2);
   
  //  Network NikitaRomashko(10, 3, 4, 3, 3);
    
    Network a(4,3,0,3,5);
   // Network GeorgyZoloev(7, 6, 1, 2, 3);

    //GeorgyZoloev.Print_matrix_bandwidth();
    //GeorgyZoloev.Dijkstra_algorythm({ 0,5,3 });

    a.Print_matrix_bandwidth();
    a.Dijkstra_algorythm({ 0,5,3 });
}


