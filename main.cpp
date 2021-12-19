#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <stdexcept>
#include "Graph.h"
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bool A [5][5] = {{1,1,0,0,0},
                     {1,0,0,0,1},
                     {0,0,1,1,0},
                     {1,0,0,0,1},
                     {0,1,0,1,0}};
    Bi_Graph bi_graph(A);
    int answer = bi_graph.maximum_weight_matching();
    std::cout << answer;
}
