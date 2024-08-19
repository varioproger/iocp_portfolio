#pragma once
#include"ServerGlobalDef.h"
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();
	void SetItemInfo(ItemType m_type, unsigned int m_idx, unsigned int m_visual_idx);
protected:
	ItemType m_type;
	unsigned int m_uuid; // 고유키
	unsigned int m_idx; // 테이블 값
	unsigned int m_visual_idx; // 아이콘 값
};