#include <iostream>
#include <Windows.h>
#include <cstdlib>

#define Buy_item 1
#define Anction_inventory 2
#define Anction_Equip 3
#define Add_Points 4
#define Buy_Skill 5
#define Battle 6
#define Show_info_player 7

#define Helmet 0
#define Glovess 1
#define Boots 2
#define Pants 3
#define Breastplate 4
#define Weapon1 5
#define Weapon2 6

#define No_Equip 7
#define consumable 8

#define MAX_EQUIP 7
#define MAX_BAG 30
#define MAX_ITEM 200

#define Guerreiro 0
#define Mago 1

using namespace std;

struct STRUCT_PERSONAGEM
{
	string Nome;
	string Classe;
	short HPMAX;
	short MPMAX;
	short HP;
	short MP;
	short Defense;
	short Pontos_add;
	short Gold;
	short Pontos_skill;
	short Level;
	short exp;
	short Str;
	short Int;
	short Con;
	short Skills[10];
	short Dano_Fisico;
	short Dano_Magico;
	string Equipados[MAX_EQUIP];
	string Mochila[MAX_BAG];
};

struct ITEM
{
	string Nome;
	string Classe;
	short EquipSlot;
	short HP_add;
	short MP_add;
	short DF_add;
	short DM_add;
	short Defense_add;
	short Venda;
	short Raridade;
};

class Personagem {

public:
	
	void Start();
	void Attack();
	void Action_player(short choise);
	void UpdateTittle();

private:

	STRUCT_PERSONAGEM personagem;
	ITEM item[MAX_ITEM];

	short Exp_MobKilled;
	const short Level_Exp[7] = { 0,10,30,40,50,60,100 };
	string Class[2] = { "Guerreiro","Mago" };
	string Rarity[10] = { "Normal","Incomum","Raro","Epico","Deus"};
	string EquipName[MAX_EQUIP] = { "Elmo","Luvas","Botas","Calca","Peitoral","Arma 1" "Arma 2"};

	void Level_UP();
	void UpdateHPMP(short hp, short mp);
	void Exp_receiv(short exp_new);
	void Create_character(std::string nick, short choose);
	void Buy_Item();
	void Show_status();
	void add_point();
	void PotionAction(int resposta, int list);
	void UpdateStatus();
	void initItem();
	void Show_inventory();
	void Show_equip();
	void Battle_end();
	bool PutItem(std::string item);
	void SellItem();

};