#include <iostream>
#include "MineSweeper.h"

int main()
{
    int width, height, bombs;
    std::cout << "Ola! Bem vindo ao Campo Minado!" << std::endl << std::endl;
    std::cout << "Digite a largura do campo: ";
    std::cin >> width;
    std::cout << "Digite a altura do campo: ";
    std::cin >> height;
    std::cout << "Digite o número de bombas no campo: ";
    std::cin >> bombs;

    MineSweeper ms(width, height, bombs);
    while(ms.stillPlaying())
    {
        ms.printField();
        std::cout << "\nDigite as coordenadas (x, y) da jogada: ";

        int x, y;
        std::cin >> x >> y;
        bool validPlay = ms.play(x, y);
        if(!validPlay)
            printf("Jogada inválida: posição do campo já explorada.\n");
    }

    if(ms.victory())
    {
        std::cout << "PARABÉNS VOCÊ GANHOU!!!\n";
        ms.printField(true);
    }
    else
    {
        std::cout << "VOCÊ PERDEU :(\nTENTE NOVAMENTE\n";
        ms.printField(true);
    }

    return 0;
}
