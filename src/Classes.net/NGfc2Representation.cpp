#include "StdAfx.h"
#include "NGfc2Representation.h"
NGfc2Representation::NGfc2Representation()
{
    m_pEntity = new Gfc2Representation;
    m_bOwner = true;
}

NGfc2Representation::NGfc2Representation(void* pEntity, bool bOwner):
    glodon::objectbufnet::Entity(pEntity, bOwner)
{
}

void NGfc2Representation::setIdentifier(glodon::objectbuf::EntityRef nValue)
{
    ((Gfc2Representation*)m_pEntity)->setIdentifier(nValue);
}

glodon::objectbuf::EntityRef NGfc2Representation::getIdentifier()
{
    return ((Gfc2Representation*)m_pEntity)->getIdentifier();
}

bool NGfc2Representation::hasIdentifier()
{
    return ((Gfc2Representation*)m_pEntity)->hasIdentifier();
}

NGfc2String^ NGfc2Representation::getIdentifierPtr()
{
    return gcnew NGfc2String(((Gfc2Representation*)m_pEntity)->getIdentifierPtr(), false);
}

int NGfc2Representation::getitemsCount()
{
    return ((Gfc2Representation*)m_pEntity)->getitemsCount();
}

void NGfc2Representation::clearitems()
{
    ((Gfc2Representation*)m_pEntity)->clearitems();
}

void NGfc2Representation::additems(glodon::objectbuf::EntityRef nValue)
{
    ((Gfc2Representation*)m_pEntity)->additems(nValue);
}

glodon::objectbuf::EntityRef NGfc2Representation::getitems(int nIndex)
{
    return ((Gfc2Representation*)m_pEntity)->getitems(nIndex);
}

NGfc2RepresentationItem^ NGfc2Representation::getitemsPtr(int nIndex)
{
    return gcnew NGfc2RepresentationItem(((Gfc2Representation*)m_pEntity)->getitemsPtr(nIndex), false);
}

