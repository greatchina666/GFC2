#ifndef GFC2SINGLEPROPERTY_H
#define GFC2SINGLEPROPERTY_H

#include "GfcClasses.h"
#include "GfcEngine/EntityFactory.h"
#include "Gfc2SimpleProperty.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2SingleProperty: public Gfc2SimpleProperty
{
GFCENGINE_DEC_OBJECT(Gfc2SingleProperty,gfc2::engine::EntityFactory)
public:
    Gfc2SingleProperty();
    Gfc2SingleProperty(bool bSetSchema);

};
#endif