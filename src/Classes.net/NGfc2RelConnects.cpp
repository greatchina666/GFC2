#include "StdAfx.h"
#include "NGfc2RelConnects.h"
NGfc2RelConnects::NGfc2RelConnects()
{
    m_pEntity = new Gfc2RelConnects;
    m_bOwner = true;
}

NGfc2RelConnects::NGfc2RelConnects(void* pEntity, bool bOwner):
    NGfc2RelationShip(pEntity, bOwner)
{
}
