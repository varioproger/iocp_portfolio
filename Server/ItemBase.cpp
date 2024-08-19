#include "ItemBase.h"

ItemBase::ItemBase()
{
	m_uuid = 0;// 여기서 고유 번호 만들어 줌
	m_type = ItemType::None;
	m_idx = 0;
	m_visual_idx = 0;
}

ItemBase::~ItemBase()
{
}

void ItemBase::SetItemInfo(ItemType type, unsigned int idx, unsigned int visual_idx)
{
	m_uuid = 0;// 여기서 고유 번호 만들어 줌
	m_type = type;
	m_idx = idx;
	m_visual_idx = visual_idx;
}
