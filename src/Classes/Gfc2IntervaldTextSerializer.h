#ifndef GFC2INTERVALDTEXTSERIALIZER_H
#define GFC2INTERVALDTEXTSERIALIZER_H

#include "Gfc2GeometryTextSerializer.h"

class Gfc2IntervaldTextSerializer: public Gfc2GeometryTextSerializer
{
OBJECTBUF_DEC_OBJECT(Gfc2IntervaldTextSerializer,glodon::objectbuf::EntitySerializer)
public:
    virtual std::string serialize(glodon::objectbuf::Entity* pEntity) const;

protected:
    virtual glodon::objectbuf::EnParseFieldState parseField(const std::string& input, int nFieldNum, glodon::objectbuf::Entity* pEntity);

};
#endif