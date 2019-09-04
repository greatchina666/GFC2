#ifndef GFC2BEVELBINARYSERIALIZER_H
#define GFC2BEVELBINARYSERIALIZER_H

#include "Gfc2SurfaceBinarySerializer.h"

class Gfc2BevelBinarySerializer: public Gfc2SurfaceBinarySerializer
{
OBJECTBUF_DEC_OBJECT(Gfc2BevelBinarySerializer,glodon::objectbuf::EntitySerializer)
public:
    int byteSize(glodon::objectbuf::Entity* pEntity) const;

protected:
    virtual void serializeWithCachedSizes(google::protobuf::io::CodedOutputStream* output, glodon::objectbuf::Entity* pEntity) const;
    virtual google::protobuf::uint8* serializeWithCachedSizesToArray(google::protobuf::uint8* target, glodon::objectbuf::Entity* pEntity) const;
    virtual glodon::objectbuf::EnParseFieldState parseField(google::protobuf::io::CodedInputStream* input, int nFieldNum, glodon::objectbuf::Entity* pEntity);

};
#endif