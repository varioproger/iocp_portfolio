#pragma once
#include"ItemBase.h"
#include<list>
#include<memory>

class Inven // CharacterBase�� Lock�� ������ �����Ƿ� �ʿ䰡 ����.
{
public:
	Inven();
	virtual ~Inven();
	void Add(); // ������ �߰�
	void Create(ItemType type,int item_idx); // ������ ����
	void Delete(); // ������ ����
	void Use(); // ������ ���
	void Swap(); // �κ� ��ġ ����
	std::shared_ptr<ItemBase> Select();// ������ Ȯ��
	void clear();
private:
	std::list<std::shared_ptr<ItemBase>> m_litem; // ĳ���Ϳ��� �ŷ��� ����� �� ���� �ƴ� Ÿ�� �� ������ �ֱ� ������ shared�� �Ѵ�.
};

