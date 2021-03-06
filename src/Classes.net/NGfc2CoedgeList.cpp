#include "StdAfx.h"
#include "NGfc2CoedgeList.h"
NGfc2CoedgeList::NGfc2CoedgeList()
{
    m_pEntity = new Gfc2CoedgeList;
    m_bOwner = true;
}

NGfc2CoedgeList::NGfc2CoedgeList(void* pEntity, bool bOwner):
    NGfc2Geometry(pEntity, bOwner)
{
}

int NGfc2CoedgeList::getCoedgesCount()
{
    return ((Gfc2CoedgeList*)m_pEntity)->getCoedgesCount();
}

void NGfc2CoedgeList::clearCoedges()
{
    ((Gfc2CoedgeList*)m_pEntity)->clearCoedges();
}

void NGfc2CoedgeList::addCoedges(glodon::objectbuf::EntityRef nValue)
{
    ((Gfc2CoedgeList*)m_pEntity)->addCoedges(nValue);
}

glodon::objectbuf::EntityRef NGfc2CoedgeList::getCoedges(int nIndex)
{
    return ((Gfc2CoedgeList*)m_pEntity)->getCoedges(nIndex);
}

NGfc2Curve2d^ NGfc2CoedgeList::getCoedgesPtr(int nIndex)
{
    return gcnew NGfc2Curve2d(((Gfc2CoedgeList*)m_pEntity)->getCoedgesPtr(nIndex), false);
}

