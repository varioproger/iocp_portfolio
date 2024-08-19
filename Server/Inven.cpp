#include "Inven.h"
#include"ItemPrototype.h"

Inven::Inven()
{
	m_litem.clear();
}

Inven::~Inven()
{
}

void Inven::Add()
{
}

void Inven::Create(ItemType type, int item_idx)
{
	ItemBase* Base = nullptr;
	switch (type)
	{
	case ItemType::Potion:
	{
		// ������ ���̺��� item_idx�� ���� �����ͼ� ���� �־���
		Potion* item = dynamic_cast<Potion*>(ItemPrototypeFactory->CreatePrototype(ItemType::Potion));
		if (item == nullptr)
		{
			return;
		}
		item->SetItemInfo(ItemType::Potion, 1, 1);
		Base = item;
	}
	break;
	case ItemType::Equip:
	{
		// ������ ���̺��� item_idx�� ���� �����ͼ� ���� �־���
		Equip* item = dynamic_cast<Equip*>(ItemPrototypeFactory->CreatePrototype(ItemType::Equip));
		if (item == nullptr)
		{
			return;
		}
		item->SetItemInfo(ItemType::Equip, 1, 1);
		Base = item;
	}
	break;
	case ItemType::None:
	default:
		return;
	}
	m_litem.emplace_back(Base);
}

void Inven::Delete()
{
}

void Inven::Use()
{
}

void Inven::Swap()
{
}

std::shared_ptr<ItemBase> Inven::Select()
{
	return std::shared_ptr<ItemBase>();
}

void Inven::clear()
{
}
