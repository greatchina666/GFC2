#ifndef GFC2RELAGGREGATES_H
#define GFC2RELAGGREGATES_H

#include "GfcClasses.h"
#include "Gfc2RelDecomposes.h"
#include "glodon/objectbuf/Entity.h"

class GFCCLASSES_API Gfc2RelAggregates: public Gfc2RelDecomposes
{
OBJECTBUF_DEC_OBJECT(Gfc2RelAggregates,glodon::objectbuf::Entity)
public:
    int typeId() const;
    virtual glodon::objectbuf::EntitySchema* createSchema() const;
    virtual std::string entityName() const;

};
#endif
