#include "Main.h"
#define _CRT_SECURE_NO_WARNINGS


void Personagem::Attack()
{

}

void Personagem::Battle_end()
{
    Exp_receiv(Exp_MobKilled);
}

void Personagem::Exp_receiv(short exp_new)
{
    personagem.exp += exp_new;

    if (Level_Exp[personagem.Level] <= personagem.exp)
    {
        Level_UP();
    }
    else {
        cout << "\nExp recebida " << exp_new;
    }
}

void Personagem::Level_UP()
{
    personagem.Level++;
    personagem.Pontos_add += 3;
    personagem.Pontos_skill += 1;

    cout << "\nLevel UP " << personagem.Level;

    UpdateHPMP(personagem.HPMAX, personagem.MPMAX);
}

void Personagem::UpdateHPMP(short hp, short mp)
{ 
    if (personagem.HP + hp >= personagem.HPMAX)
        personagem.HP = personagem.HPMAX;
    else
        personagem.HP += hp;

    if (personagem.MP + mp >= personagem.MPMAX)
        personagem.MP = personagem.MPMAX;
    else
        personagem.MP += mp;

    /*if (hp !=0 || mp !=0)
        cout << "\nHP: " << personagem.HP << "/" << personagem.HPMAX << "\nMP: " << personagem.MP << "/" << personagem.MPMAX;*/

    UpdateTittle();
}

void Personagem::UpdateStatus()
{
    initItem();

    if (personagem.Classe == Class[Guerreiro])
    {
        personagem.HPMAX = 25;
        personagem.MPMAX = 5;
        personagem.Defense = 3;
        personagem.Dano_Fisico = personagem.Str * 2;
        personagem.Dano_Magico = personagem.Int * 1;

        personagem.HPMAX += 3 * personagem.Con;
        personagem.MPMAX += 1 * personagem.Int;
    }
    if (personagem.Classe == Class[Mago])
    {
        personagem.HPMAX = 8;
        personagem.MPMAX = 23;
        personagem.Defense = 1;
        personagem.Dano_Fisico = personagem.Str * 1;
        personagem.Dano_Magico = personagem.Int * 3;

        personagem.HPMAX += 1 * personagem.Con;
        personagem.MPMAX += 3 * personagem.Int;
    }

    for (int i = 0; i < MAX_EQUIP; i++)
    {
        if (personagem.Equipados[i] == "")
            continue;

        for (int list = 0; list < MAX_ITEM; list++)
        {
            if (personagem.Equipados[i] == item[list].Nome)
            {
                personagem.HPMAX += item[list].HP_add;
                personagem.MPMAX += item[list].MP_add;
                personagem.Defense += item[list].Defense_add;
                personagem.Dano_Fisico += item[list].DF_add;
                personagem.Dano_Magico += item[list].DM_add;
            }
        }
    }  

    UpdateHPMP(0,0);

    //cout << "\nHP: " << personagem.HP <<
    //    "\nMP: " << personagem.MP <<
    //    "\nAtkF: " << personagem.Dano_Fisico <<
    //    "\nAtkM: " << personagem.Dano_Magico <<
    //    "\nDefesa: " << personagem.Defense;
}

void Personagem::Show_equip()
{
    bool have_item = false;
	
    for (int i = 0; i < MAX_EQUIP; i++)
    {
        if (personagem.Equipados[i] == "")
            continue;

        for (int list = 0; list < MAX_ITEM; list++)
        {
            if (personagem.Equipados[i] == item[list].Nome)
            {
                cout << "\n[" << i << "]" << item[list].Nome << " HP+" << item[list].HP_add << " MP+" << item[list].MP_add
                    << " DEF+" << item[list].Defense_add << " ATF+" << item[list].DF_add << " ATM+" << item[list].DM_add;

                have_item = true;
            }
        }
    }

    if (have_item)
    {
        string resposta;
        cout << "\nDeseja Desequipar algum item? [s/n]\n";
        cin >> resposta;

        if (resposta == "S" || resposta == "s")
        {
            short resposta;
            short mochila = -1;
            cout << "\ndigite o ID slot do item que deseja Desequipar\n";
            cin >> resposta;

            if (resposta < 0 || resposta >= MAX_EQUIP)
            {
                cout << "\nSlot invalido";
                return;
            }

            if (personagem.Equipados[resposta] == "")
            {
                cout << "\nNao exite item nesse slot";
                return;
            }

            for (int bag = 0; bag < MAX_BAG; bag++)
            {
                if (personagem.Mochila[bag] == "")
                {
                    mochila = bag;
                    break;
                }
            }

            if (mochila == -1)
            {
                cout << "\nSua mochila esta cheia";
                return;
            }
         
            personagem.Mochila[mochila] = personagem.Equipados[resposta];
            personagem.Equipados[resposta] = "";

            cout << "\nitem Desequipado com sucesso.";
            UpdateStatus();    
        }
    }
    else
        cout << "\nVoce nao possui itens equipados";
}

void Personagem::Show_inventory()
{
    bool have_item = false;

    for (int i = 0; i < MAX_BAG; i++)
    {
        if (personagem.Mochila[i] == "")
            continue;

        for (int list = 0; list < MAX_ITEM; list++)
        {
            if (personagem.Mochila[i] == item[list].Nome)
            {
                personagem.HPMAX += item[list].HP_add;
                personagem.MPMAX += item[list].MP_add;
                personagem.Defense += item[list].Defense_add;
                personagem.Dano_Fisico += item[list].DF_add;
                personagem.Dano_Magico += item[list].DM_add;

                cout << "\n[" << i << "]" << item[list].Nome << " [" << item[list].Classe << "]" << " HP+" << item[list].HP_add << " MP+" << item[list].MP_add
                    << " DEF+" << item[list].Defense_add << " ATF+" << item[list].DF_add << " ATM+" << item[list].DM_add << " Raridade:" << Rarity[item[list].Raridade]
                    << " Valor de venda:" << item[list].Venda;

                have_item = true;
            }
        }
    }

    if (have_item)
    {
        string resposta;
        cout << "\nDeseja Equipar ou consumir algum item? [s/n]\n";
        cin >> resposta;

        if (resposta == "S" || resposta == "s")
        {
            short resposta;
            cout << "\ndigite o ID slot do item que deseja Equipar\n";
            cin >> resposta;

            if (resposta < 0 || resposta >= MAX_BAG)
            {
                cout << "\nSlot invalido";
                return;
            }

            if (personagem.Mochila[resposta] == "")
            {
                cout << "\nNao exite item nesse slot";
                return;
            }

            for (int list = 0; list < MAX_ITEM; list++)
            {
                if (personagem.Mochila[resposta] == item[list].Nome)
                {
                    if (item[list].EquipSlot == consumable)
                    {
                        PotionAction(resposta, list);
                        return;
                    }

                    if (personagem.Classe != item[list].Classe)
                    {
                        cout << "\nEste item nao pertence a sua classe";
                        return;
                    }

                    string temporario = personagem.Equipados[item[list].EquipSlot];
                    personagem.Equipados[item[list].EquipSlot] = personagem.Mochila[resposta];
                    personagem.Mochila[resposta] = temporario;

                    system("cls");
                    cout << "\nitem Equipado com sucesso.";
                    UpdateStatus();
                    Show_inventory();
                    break;
                }

                if (list == 199)
                    cout << "\nError item nao encontrado na lista de itens";
            }

        }
    }
    else
        cout << "\nInvetario vazio";
}

bool Personagem::PutItem(std::string item)
{
    for (int i = 0; i < MAX_BAG; i++)
    {
        if (personagem.Mochila[i] != "")
            continue;

        personagem.Mochila[i] = item;

        cout << "\nVoce recebeu o item: [" << item << "]";
        return true;
    }

    cout << "\nVoce esta com o inventario cheio.";
    return false;
}

void Personagem::SellItem()
{
    system("cls");

    bool Have_item = false;
    for (int i = 0; i < MAX_BAG; i++)
    {
        if (personagem.Mochila[i] == "")
            continue;

        for (int list = 0; list < MAX_ITEM; list++)
        {
            if (personagem.Mochila[i] == item[list].Nome)
            {
                cout << "\n[" << i << "]" << " Valor de venda:[" << item[list].Venda << "]" << " Item:" << item[list].Nome;
            }

            Have_item = true;
        }
    }

    if (Have_item)
    {
        string escolha;

        cout << "\nDeseja vendar algum item? [S/N]\n";
        cin >> escolha;

        if (escolha == "S" || escolha == "s")
        {   
            short Bag = -1;

            cout << "\nInforme o slot do item que deseja vender\n";
            cin >> Bag;

            if (Bag == -1 || Bag < 0 || Bag >= MAX_BAG)
                return;

            if (personagem.Mochila[Bag] == "")
            {
                cout << "\nNao exite item nesse slot";
                return;
            }

            for (int list = 0; list < MAX_ITEM; list++)
            {
                if (personagem.Mochila[Bag] == item[list].Nome)
                {
                    personagem.Gold += item[list].Venda;
                    cout << "\nVenda feita com sucesso valor recebido [" << item[list].Venda << "]";
                    UpdateTittle();
                    break;
                }
            }

            personagem.Mochila[Bag] = "";
            SellItem();
        }
        else
            cout << "\nSaindo da Loja";
    }
    else
        cout << "\nVoce nao possui itens para venda.";
}

void Personagem::PotionAction(int resposta,int list)
{
    /*Codigo da Potion*/
    system("cls");
    personagem.Mochila[resposta] = "";
    cout << "\nitem " << item[list].Nome << " consumido com sucesso.";
    UpdateHPMP(item[list].HP_add, item[list].MP_add);
    UpdateStatus();
}

void Personagem::add_point()
{
    if (personagem.Pontos_add <= 0)
    {
        cout << "\nVoce nao possui pontos para add";
        return;
    }

    do {
        short pontos = 0;
        short escolha = 0;
        cout << "\nVoce possui " << personagem.Pontos_add << " pontos para adicionar";
        cout << "\n[Escolha]\n[1]STR\n[2]INT\n[3]CON\n";
        cin >> escolha;

        cout << "\n[Digite Quantos pontos deseja adicionar]\n";
        cin >> pontos;

        if (personagem.Pontos_add < pontos || pontos <= -1)
            pontos = personagem.Pontos_add;

        personagem.Pontos_add -= pontos;

        if (escolha == 1)
            personagem.Str += pontos;
        else if (escolha == 2)
            personagem.Int += pontos;
        else
            personagem.Con += pontos;

    } while (personagem.Pontos_add > 0);

    UpdateStatus();
}

void Personagem::Start()
{
    string nick;
    short escolha;
    string criar;

    do
    {
        cout << "\n[Nome do Personagem]\n";
        cin >> nick;

        cout << "\n[Escolha uma Classe]";

        cout << "\n[1]GUERREIRO\n[2]MAGO\n";
        cin >> escolha;

        cout << "\nDesejar Criar o personagem? [S/N]";
        cin >> criar;

        if (escolha != 1 && escolha != 2)
            criar = "n";

    } while (criar != "s" && criar != "S");

    Create_character(nick, escolha-1);   
}

void Personagem::Create_character(std::string nick, short choose)
{
    personagem.Nome = nick;
    personagem.Classe = Class[choose];
    personagem.HPMAX = 0;
    personagem.MPMAX = 0;
    personagem.HP = 0;
    personagem.MP = 0;
    personagem.Pontos_add = 5;
    personagem.Gold = 0;
    personagem.Pontos_skill = 0;
    personagem.Level = 1;
    personagem.exp = 0;
    personagem.Str = 0;
    personagem.Int = 0;
    personagem.Con = 0;
    personagem.Defense = 0;
    personagem.Dano_Fisico = 0; 
    personagem.Dano_Magico = 0;

    cout << "\nPersonagem criado com sucesso\n";
    add_point();

    //cout << "\nLevel:" << personagem.Level << " Exp:0" << " STR:" << personagem.Str <<" INT:"<< personagem.Int << " CON:"<< personagem.Con << " GOLD:" << personagem.Gold;

    if (personagem.Classe == "Mago")
    {
        personagem.Mochila[0] = "Luva de iniciante Mago";
        personagem.Mochila[1] = "Capuz de iniciante Mago";
        personagem.Mochila[2] = "Tunica de iniciante Mago";
        personagem.Mochila[3] = "Saia de iniciante Mago";
        personagem.Mochila[4] = "Botas de iniciante Mago";
        personagem.Mochila[5] = "Potion MP(1)";
    }
    else
    {
        personagem.Mochila[0] = "Luva de iniciante Guerreiro";
        personagem.Mochila[1] = "Capacete de iniciante Guerreiro";
        personagem.Mochila[2] = "Peitoral de iniciante Guerreiro";
        personagem.Mochila[3] = "Saia de iniciante Guerreiro";
        personagem.Mochila[4] = "Botas de iniciante Guerreiro";
        personagem.Mochila[5] = "Potion HP(1)";
        personagem.Mochila[6] = "Espada curta";
    }
 
    UpdateStatus(); 
    UpdateHPMP(personagem.HPMAX, personagem.MPMAX);
}

void Personagem::Action_player(short choise)
{
    switch (choise)
    {
        case Buy_item:
        {
           Buy_Item();
           break;
        }
        case Anction_inventory:
        {
            Show_inventory();
            break;
        }
        case Anction_Equip:
        {
            Show_equip();
            break;
        }
        case Add_Points:
        {
            add_point();
            break;
        }
        case Buy_Skill:
        {
            break;
        }
        case Battle:
        {
            break;
        }
        case Show_info_player:
        {
            Show_status();
            break;
        }
    }
}

void Personagem::Buy_Item()
{
    system("cls");

    bool local_256 = false;
    short SlotFree = -1;
    for (int i = 0; i < MAX_BAG; i++)
    {
        if (personagem.Mochila[i] != "")
            continue;

        local_256 = true;
        SlotFree = i;
        break;
    }

    if (local_256)
    {
        short option = 0;
        cout << "\nEscolha 1 Tipo de Item";
        cout << "\n[0]Elmo";
        cout << "\n[1]Luvas";
        cout << "\n[2]Botas";
        cout << "\n[3]Calca";
        cout << "\n[4]Peitoral";
        cout << "\n[5]Armas1";
        cout << "\n[6]Armas2";
        cout << "\n[8]Consumivel\n";
        cin >> option;

        if (option < 0 || option > 5)
        {
            if (option != 8)
            {
                cout << "\nSlot invalido";
                return;
            }
        }

        for (int lista = 0; lista < MAX_ITEM; lista++)
        {
            if (option == consumable)
            {
                if (item[lista].EquipSlot == consumable)
                {
                    cout << "\n[" << lista << "]" << " Valor:[" << item[lista].Venda*5<< "]" << " Item:" << item[lista].Nome << " HP+" << item[lista].HP_add << " MP+" << item[lista].MP_add
                        << " Raridade:" << Rarity[item[lista].Raridade];
                }
            }
            else
            {
                if (item[lista].Classe == personagem.Classe && item[lista].EquipSlot == option)
                {
                    cout << "\n[" << lista << "]" << " Valor:[" << item[lista].Venda * 5 << "]" << " Item:" << item[lista].Nome << " HP+" << item[lista].HP_add << " MP+" << item[lista].MP_add
                        << " DEF+" << item[lista].Defense_add << " ATF+" << item[lista].DF_add << " ATM+" << item[lista].DM_add << " Raridade:" << Rarity[item[lista].Raridade];
                }
            }
        }

        short escolha = -1;
        cout << "\nInforme o ID do item que deseja comprar:\n";
        cin >> escolha;
    
        if (escolha < 0 || escolha > 5)
        {
            if (escolha != 8)
            {
                cout << "\nSlot invalido";
                return;
            }
        }

        if (personagem.Gold >= item[escolha].Venda * 5)
        {
            if (item[escolha].Classe == personagem.Classe || item[escolha].Classe == "Consumivel")
            {
                personagem.Gold -= item[escolha].Venda * 5;         
                personagem.Mochila[SlotFree] = item[escolha].Nome;
                UpdateTittle();
                cout << "\nItem comprado com sucesso.";

                string resposta;

                cout << "\nDeseja comprar mais itens?[S/N]:\n";
                cin >> resposta;

                if (resposta == "s" || resposta == "S")
                    Buy_Item();

                return;
            }
            else
            {
                cout << "\nItem incorreto para a sua classe.";
                return;
            }
        }
        else
        {
            cout << "\nGold insuficiente.";
            return;

        }
    }
    else
        cout << "\nVoce nao possui espaco na mochila.";
}

void Personagem::Show_status()
{
    cout << "\n[Equipamentos]";

    for (int i = 0; i < MAX_EQUIP; i++)
    {
        if (personagem.Equipados[i] == "")
            continue;

        for (int list = 0; list < MAX_ITEM; list++)
        {
            if (personagem.Equipados[i] == item[list].Nome)
            {
                cout << "\n    Tipo[" << EquipName[item[i].EquipSlot] << "] " << item[list].Nome << " HP+" << item[list].HP_add << " MP+" << item[list].MP_add
                    << " DEF+" << item[list].Defense_add << " ATF+" << item[list].DF_add << " ATM+" << item[list].DM_add << " Raridade:" << Rarity[item[list].Raridade];
            }
        }
    }


    cout << "\n\n[Ficha Geral]";
    cout << 
        "\n    Classe: " << personagem.Classe <<
        "\n    Level: " << personagem.Level <<
        "\n    Exp: " << personagem.exp <<
        "\n    Ouro: " << personagem.Gold <<
        "\n    HP: " << personagem.HP <<
        "\n    MP: " << personagem.MP <<
        "\n    Str: " << personagem.Str <<
        "\n    Int: " << personagem.Int <<
        "\n    Con: " << personagem.Con <<
        "\n    AtkF: " << personagem.Dano_Fisico <<
        "\n    AtkM: " << personagem.Dano_Magico <<
        "\n    Defesa: " << personagem.Defense <<
        "\n    Pontos: " << personagem.Pontos_add <<
        "\n    Pontos Skill: " << personagem.Pontos_skill;

    UpdateTittle();
}

void Personagem::UpdateTittle()
{
    short bagfree = 0;

    for (int bag = 0; bag < MAX_BAG; bag++)
    {
        if (personagem.Mochila[bag] != "")
            bagfree++;
    }

    const int max_length = 256;
    char* titulo = (char*)malloc(max_length * sizeof(char));

    sprintf_s(titulo, max_length, "%s - HP[%d/%d] - MP[%d/%d] - Lv[%d] - Exp[%d/%d] - Classe[%s] - Gold[%d] - ATKF[%d] - ATKM[%d] - DEF[%d] - STR[%d] - INT[%d] - CON[%d] - BAG[%d/%d]",
        personagem.Nome.c_str(), personagem.HP, personagem.HPMAX, personagem.MP, personagem.MPMAX,
        personagem.Level, personagem.exp, Level_Exp[personagem.Level], personagem.Classe.c_str(), personagem.Gold,
        personagem.Dano_Fisico,personagem.Dano_Magico,personagem.Defense,personagem.Str,personagem.Int,personagem.Con, bagfree, MAX_BAG);

    wchar_t tituloW[max_length];
    MultiByteToWideChar(CP_ACP, 0, titulo, -1, tituloW, max_length);

    SetConsoleTitle(tituloW);
}

void Personagem::initItem()
{
    short list = 0;

    item[list].Nome = "Capuz de iniciante Mago";
    item[list].Classe = Class[Mago];
    item[list].EquipSlot = Helmet;
    item[list].HP_add = 0;
    item[list].MP_add = 1;
    item[list].DF_add = 0;
    item[list].DM_add = 1;
    item[list].Defense_add = 1;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Luva de iniciante Mago";
    item[list].Classe = Class[Mago];
    item[list].EquipSlot = Glovess;
    item[list].HP_add = 0;
    item[list].MP_add = 1;
    item[list].DF_add = 0;
    item[list].DM_add = 1;
    item[list].Defense_add = 1;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Tunica de iniciante Mago";
    item[list].Classe = Class[Mago];
    item[list].EquipSlot = Breastplate;
    item[list].HP_add = 0;
    item[list].MP_add = 10;
    item[list].DF_add = 0;
    item[list].DM_add = 1;
    item[list].Defense_add = 2;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Saia de iniciante Mago";
    item[list].Classe = Class[Mago];
    item[list].EquipSlot = Pants;
    item[list].HP_add = 0;
    item[list].MP_add = 8;
    item[list].DF_add = 0;
    item[list].DM_add = 1;
    item[list].Defense_add = 2;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Botas de iniciante Mago";
    item[list].Classe = Class[Mago];
    item[list].EquipSlot = Boots;
    item[list].HP_add = 0;
    item[list].MP_add = 2;
    item[list].DF_add = 0;
    item[list].DM_add = 1;
    item[list].Defense_add = 0;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Capacete de iniciante Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Helmet;
    item[list].HP_add = 1;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 2;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Luva de iniciante Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Glovess;
    item[list].HP_add = 0;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 2;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Peitoral de iniciante Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Breastplate;
    item[list].HP_add = 2;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 5;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Saia de iniciante Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Pants;
    item[list].HP_add = 1;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 4;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Botas de iniciante Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Boots;
    item[list].HP_add = 0;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 2;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Espada curta";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Weapon1;
    item[list].HP_add = 0;
    item[list].MP_add = 0;
    item[list].DF_add = 5;
    item[list].DM_add = 0;
    item[list].Defense_add = 0;
    item[list].Venda = 1;
    item[list].Raridade = 0;
    list++;

    item[list].Nome = "Potion HP(1)";
    item[list].Classe = "Consumivel";
    item[list].EquipSlot = consumable;
    item[list].HP_add = 10;
    item[list].MP_add = 0;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 0;
    item[list].Venda = 5;
    item[list].Raridade = 1;
    list++;

    item[list].Nome = "Potion MP(1)";
    item[list].Classe = "Consumivel";
    item[list].EquipSlot = consumable;
    item[list].HP_add = 0;
    item[list].MP_add = 10;
    item[list].DF_add = 0;
    item[list].DM_add = 0;
    item[list].Defense_add = 0;
    item[list].Venda = 5;
    item[list].Raridade = 1;
    list++;

    item[list].Nome = "Botas de Veterano Guerreiro";
    item[list].Classe = Class[Guerreiro];
    item[list].EquipSlot = Boots;
    item[list].HP_add = 10;
    item[list].MP_add = 2;
    item[list].DF_add = 10;
    item[list].DM_add = 20;
    item[list].Defense_add = 12;
    item[list].Venda = 201;
    item[list].Raridade = 3;
    list++;
}