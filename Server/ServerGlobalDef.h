#pragma once
constexpr int KB_1 = 1024;
constexpr int KB_4 = KB_1 << 2;// 2의 2 승은 4 이고 1024 * 4 이므로 4KB 크기가 된다. 
constexpr int KB_8 = KB_1 << 3;// 2의 3 승은 8 이고 1024 * 8 이므로 8KB 크기가 된다.
constexpr int KB_128 = KB_1 << 7;// 2의 7 승은 128 이고 1024 * 128 이므로 128KB 크기가 된다.

enum class CharacterType
{
	Warrior,
	Archer,
	Witch,
	None,
};

enum class ItemType {
	Potion,
	Equip,
	None,
};

enum class EquipType {
	Face,
	Hair,
	Armor,
	Helmet,
	Glove,
	Shoes,
	None,
};

struct CharacterBasicInfo {
	int str;
	int dex;
	int luck;
};