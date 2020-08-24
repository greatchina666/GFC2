#ifndef NGFC2PROPERTYSET_H
#define NGFC2PROPERTYSET_H

#include "Gfc2PropertySet.h"
#include "NGfc2Property.h"
#include "NTypeDef.h"
#include "GfcEngine/Entity.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;

public ref class NGfc2PropertySet: public glodon::objectbufnet::Entity
{
public:
    NGfc2PropertySet();
    NGfc2PropertySet(void* pEntity, bool bOwner);
    void setName(NGfc2Label sValue);
    NGfc2Label getName();
    bool hasName();
    int getHasPropertiesCount();
    void clearHasProperties();
    void addHasProperties(gfc::engine::EntityRef nValue);
    gfc::engine::EntityRef getHasProperties(int nIndex);
    NGfc2Property^ getHasPropertiesPtr(int nIndex);

};
#endif
