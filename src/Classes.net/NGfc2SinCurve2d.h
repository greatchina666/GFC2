#ifndef NGFC2SINCURVE2D_H
#define NGFC2SINCURVE2D_H

#include "NGfc2Curve2d.h"
#include "Gfc2SinCurve2d.h"
#include "NGfc2Vector2d.h"
#include "NGfc2Intervald.h"
#include "NTypeDef.h"
#include "glodon/objectbuf/Entity.h"

public ref class NGfc2SinCurve2d: public NGfc2Curve2d
{
public:
    NGfc2SinCurve2d();
    NGfc2SinCurve2d(void* pEntity, bool bOwner);
    void setPos(glodon::objectbuf::EntityRef nValue);
    glodon::objectbuf::EntityRef getPos();
    bool hasPos();
    NGfc2Vector2d^ getPosPtr();
    void setDirX(glodon::objectbuf::EntityRef nValue);
    glodon::objectbuf::EntityRef getDirX();
    bool hasDirX();
    NGfc2Vector2d^ getDirXPtr();
    void setA(NGfc2Double dValue);
    NGfc2Double getA();
    bool hasA();
    void setB(NGfc2Double dValue);
    NGfc2Double getB();
    bool hasB();
    void setRange(glodon::objectbuf::EntityRef nValue);
    glodon::objectbuf::EntityRef getRange();
    bool hasRange();
    NGfc2Intervald^ getRangePtr();
    void setClockSign(NGfc2Integer nValue);
    NGfc2Integer getClockSign();
    bool hasClockSign();

};
#endif
