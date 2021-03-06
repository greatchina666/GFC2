#ifndef NGFC2ENTITYSHAPE_H
#define NGFC2ENTITYSHAPE_H

#include "Gfc2EntityShape.h"
#include "NGfc2String.h"
#include "NGfc2Shape.h"
#include "glodon/objectbuf/Entity.h"

public ref class NGfc2EntityShape: public glodon::objectbufnet::Entity
{
public:
    NGfc2EntityShape();
    NGfc2EntityShape(void* pEntity, bool bOwner);
    void setIdentifier(glodon::objectbuf::EntityRef nValue);
    glodon::objectbuf::EntityRef getIdentifier();
    bool hasIdentifier();
    NGfc2String^ getIdentifierPtr();
    void setShape(glodon::objectbuf::EntityRef nValue);
    glodon::objectbuf::EntityRef getShape();
    bool hasShape();
    NGfc2Shape^ getShapePtr();

};
#endif
