#pragma once
#include"ServerGlobalDef.h"
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();
protected:
	ItemType m_type;
	unsigned int m_uuid; // ����Ű
	unsigned int m_idx; // ���̺� ��
	unsigned int m_visual_idx; // ������ ��
};