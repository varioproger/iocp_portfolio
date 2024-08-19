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
	unsigned int m_uuid; // ����Ű
	unsigned int m_idx; // ���̺� ��
	unsigned int m_visual_idx; // ������ ��
};