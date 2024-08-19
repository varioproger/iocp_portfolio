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
		// 아이템 테이블에서 item_idx로 정보 가져와서 만들어서 넣어줌
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
		// 아이템 테이블에서 item_idx로 정보 가져와서 만들어서 넣어줌
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
