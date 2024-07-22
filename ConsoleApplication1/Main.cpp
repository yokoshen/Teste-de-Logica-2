#include "Main.h"

int main()
{
    cout << "Seja bem vindo ao Super Nova World!\n";
    cout << "vamos criar o seu personagem!\n";
    Personagem init;
    init.Start();

    while (true)
    {
        
        short escolha;
        cout << "\n\n[Escolha o seu destino]\n";
        cout << "\n    [1] Comprar item";
        cout << "\n    [2] listar inventario";
        cout << "\n    [3] listar Equipamento";
        cout << "\n    [4] adicionar pontos";
        cout << "\n    [5] Comprar skill";
        cout << "\n    [6] Batalhar";
        cout << "\n    [7] Monstrar informacoes do personagem\n";
        cin >> escolha;
        system("cls");

        init.Action_player(escolha);
    }
}