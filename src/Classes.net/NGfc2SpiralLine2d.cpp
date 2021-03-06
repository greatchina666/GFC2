#include "StdAfx.h"
#include "NGfc2SpiralLine2d.h"
NGfc2SpiralLine2d::NGfc2SpiralLine2d()
{
    m_pEntity = new Gfc2SpiralLine2d;
    m_bOwner = true;
}

NGfc2SpiralLine2d::NGfc2SpiralLine2d(void* pEntity, bool bOwner):
    NGfc2Curve2d(pEntity, bOwner)
{
}

void NGfc2SpiralLine2d::setCoord(glodon::objectbuf::EntityRef nValue)
{
    ((Gfc2SpiralLine2d*)m_pEntity)->setCoord(nValue);
}

glodon::objectbuf::EntityRef NGfc2SpiralLine2d::getCoord()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->getCoord();
}

bool NGfc2SpiralLine2d::hasCoord()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->hasCoord();
}

NGfc2Coordinates2d^ NGfc2SpiralLine2d::getCoordPtr()
{
    return gcnew NGfc2Coordinates2d(((Gfc2SpiralLine2d*)m_pEntity)->getCoordPtr(), false);
}

void NGfc2SpiralLine2d::setRadius(NGfc2Double dValue)
{
    ((Gfc2SpiralLine2d*)m_pEntity)->setRadius(dValue);
}

NGfc2Double NGfc2SpiralLine2d::getRadius()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->getRadius();
}

bool NGfc2SpiralLine2d::hasRadius()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->hasRadius();
}

void NGfc2SpiralLine2d::setRange(glodon::objectbuf::EntityRef nValue)
{
    ((Gfc2SpiralLine2d*)m_pEntity)->setRange(nValue);
}

glodon::objectbuf::EntityRef NGfc2SpiralLine2d::getRange()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->getRange();
}

bool NGfc2SpiralLine2d::hasRange()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->hasRange();
}

NGfc2Intervald^ NGfc2SpiralLine2d::getRangePtr()
{
    return gcnew NGfc2Intervald(((Gfc2SpiralLine2d*)m_pEntity)->getRangePtr(), false);
}

void NGfc2SpiralLine2d::setClockSign(NGfc2Integer nValue)
{
    ((Gfc2SpiralLine2d*)m_pEntity)->setClockSign(nValue);
}

NGfc2Integer NGfc2SpiralLine2d::getClockSign()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->getClockSign();
}

bool NGfc2SpiralLine2d::hasClockSign()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->hasClockSign();
}

void NGfc2SpiralLine2d::setRadiusCoef(NGfc2Double dValue)
{
    ((Gfc2SpiralLine2d*)m_pEntity)->setRadiusCoef(dValue);
}

NGfc2Double NGfc2SpiralLine2d::getRadiusCoef()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->getRadiusCoef();
}

bool NGfc2SpiralLine2d::hasRadiusCoef()
{
    return ((Gfc2SpiralLine2d*)m_pEntity)->hasRadiusCoef();
}

