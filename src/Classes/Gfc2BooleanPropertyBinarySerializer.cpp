#include "StdAfx.h"
#include "Gfc2BooleanPropertyBinarySerializer.h"
#include "FieldCache.h"
#include "Gfc2BooleanProperty.h"

OBJECTBUF_IMP_OBJECT(Gfc2BooleanPropertyBinarySerializer,"Gfc2BooleanPropertyB",0)

int Gfc2BooleanPropertyBinarySerializer::byteSize(glodon::objectbuf::Entity* pEntity) const
{
    Gfc2BooleanProperty* pEnt = (Gfc2BooleanProperty*)pEntity;
    int total_size = Gfc2PropertyBinarySerializer::byteSize(pEnt);

    if (pEnt->hasValue())
    {
        total_size += 1 + 1;
    }

    return total_size;
}

void Gfc2BooleanPropertyBinarySerializer::serializeWithCachedSizes(google::protobuf::io::CodedOutputStream* output, glodon::objectbuf::Entity* pEntity) const
{
    Gfc2BooleanProperty* pEnt = (Gfc2BooleanProperty*)pEntity;
    Gfc2PropertyBinarySerializer::serializeWithCachedSizes(output, pEnt);

    if (pEnt->hasValue())
    {
        ::google::protobuf::internal::WireFormatLite::WriteBool(2, pEnt->getValue(), output);
    }

}

google::protobuf::uint8* Gfc2BooleanPropertyBinarySerializer::serializeWithCachedSizesToArray(google::protobuf::uint8* target, glodon::objectbuf::Entity* pEntity) const
{
    Gfc2BooleanProperty* pEnt = (Gfc2BooleanProperty*)pEntity;
    target = Gfc2PropertyBinarySerializer::serializeWithCachedSizesToArray(target, pEnt);

    if (pEnt->hasValue())
    {
        target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, pEnt->getValue(), target);
    }

    return target;
}

glodon::objectbuf::EnParseFieldState Gfc2BooleanPropertyBinarySerializer::parseField(google::protobuf::io::CodedInputStream* input, int nFieldNum, glodon::objectbuf::Entity* pEntity)
{
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    Gfc2BooleanProperty* pEnt = (Gfc2BooleanProperty*)pEntity;
    glodon::objectbuf::EnParseFieldState nState = Gfc2PropertyBinarySerializer::parseField(input, nFieldNum, pEnt);
    if (nState != glodon::objectbuf::PFS_IGNORE)
    {
        return nState;
    }

    if (nFieldNum == _FieldCache->_Gfc2BooleanProperty_Value)
    {
        Gfc2Boolean value;
        DO_((google::protobuf::internal::WireFormatLite::ReadPrimitive<bool, google::protobuf::internal::WireFormatLite::TYPE_BOOL>(input, &value)));
        pEnt->setValue(value);
        goto success;
    }

    return glodon::objectbuf::PFS_IGNORE;
success:
    return glodon::objectbuf::PFS_SUCCESS;
failure:
    return glodon::objectbuf::PFS_FAIL;
#undef DO_
}

