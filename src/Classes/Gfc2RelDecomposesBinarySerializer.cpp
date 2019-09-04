#include "StdAfx.h"
#include "Gfc2RelDecomposesBinarySerializer.h"
#include "FieldCache.h"
#include "Gfc2RelDecomposes.h"

OBJECTBUF_IMP_OBJECT(Gfc2RelDecomposesBinarySerializer,"Gfc2RelDecomposesB",0)

int Gfc2RelDecomposesBinarySerializer::byteSize(glodon::objectbuf::Entity* pEntity) const
{
    Gfc2RelDecomposes* pEnt = (Gfc2RelDecomposes*)pEntity;
    int total_size = Gfc2RelationShipBinarySerializer::byteSize(pEnt);

    if (pEnt->hasRelatingObject())
    {
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::Int32Size(pEnt->getRelatingObject());
    }

    if (pEnt->getRelatedObjectsCount() > 0)
        total_size += 1 + ::google::protobuf::internal::WireFormatLite::Int32Size(pEnt->getRelatedObjectsCount());
    for (int i = 0; i < pEnt->getRelatedObjectsCount(); i++)
    {
        total_size += ::google::protobuf::internal::WireFormatLite::Int32Size(pEnt->getRelatedObjects(i));
    }

    return total_size;
}

void Gfc2RelDecomposesBinarySerializer::serializeWithCachedSizes(google::protobuf::io::CodedOutputStream* output, glodon::objectbuf::Entity* pEntity) const
{
    Gfc2RelDecomposes* pEnt = (Gfc2RelDecomposes*)pEntity;
    Gfc2RelationShipBinarySerializer::serializeWithCachedSizes(output, pEnt);

    if (pEnt->hasRelatingObject())
    {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(1, pEnt->getRelatingObject(), output);
    }

    if (pEnt->getRelatedObjectsCount() > 0)
    {
        ::google::protobuf::internal::WireFormatLite::WriteTag(2, google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
        ::google::protobuf::internal::WireFormatLite::WriteInt32NoTag(pEnt->getRelatedObjectsCount(), output);
        for (int i = 0; i < pEnt->getRelatedObjectsCount(); i++)
        {
            ::google::protobuf::internal::WireFormatLite::WriteInt32NoTag(pEnt->getRelatedObjects(i), output);
        }
    }

}

google::protobuf::uint8* Gfc2RelDecomposesBinarySerializer::serializeWithCachedSizesToArray(google::protobuf::uint8* target, glodon::objectbuf::Entity* pEntity) const
{
    Gfc2RelDecomposes* pEnt = (Gfc2RelDecomposes*)pEntity;
    target = Gfc2RelationShipBinarySerializer::serializeWithCachedSizesToArray(target, pEnt);

    if (pEnt->hasRelatingObject())
    {
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, pEnt->getRelatingObject(), target);
    }

    if (pEnt->getRelatedObjectsCount() > 0)
    {
        target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(2, google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, target);
        target = ::google::protobuf::internal::WireFormatLite::WriteInt32NoTagToArray(pEnt->getRelatedObjectsCount(), target);
        for (int i = 0; i < pEnt->getRelatedObjectsCount(); i++)
        {
            target = ::google::protobuf::internal::WireFormatLite::WriteInt32NoTagToArray(pEnt->getRelatedObjects(i), target);
        }
    }

    return target;
}

glodon::objectbuf::EnParseFieldState Gfc2RelDecomposesBinarySerializer::parseField(google::protobuf::io::CodedInputStream* input, int nFieldNum, glodon::objectbuf::Entity* pEntity)
{
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    Gfc2RelDecomposes* pEnt = (Gfc2RelDecomposes*)pEntity;
    glodon::objectbuf::EnParseFieldState nState = Gfc2RelationShipBinarySerializer::parseField(input, nFieldNum, pEnt);
    if (nState != glodon::objectbuf::PFS_IGNORE)
    {
        return nState;
    }

    if (nFieldNum == _FieldCache->_Gfc2RelDecomposes_RelatingObject)
    {
        glodon::objectbuf::EntityRef value;
        DO_((google::protobuf::internal::WireFormatLite::ReadPrimitive<google::protobuf::int32, google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value)));
        pEnt->setRelatingObject(value);
        goto success;
    }

    if (nFieldNum == _FieldCache->_Gfc2RelDecomposes_RelatedObjects)
    {
        int nSize = 0;
        DO_((google::protobuf::internal::WireFormatLite::ReadPrimitive<google::protobuf::int32, google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &nSize)));
        for(int i = 0; i < nSize; ++i)
        {
            glodon::objectbuf::EntityRef value;
            DO_((google::protobuf::internal::WireFormatLite::ReadPrimitive<google::protobuf::int32, google::protobuf::internal::WireFormatLite::TYPE_INT32>(input, &value)));
            pEnt->addRelatedObjects(value);
        }
        goto success;
    }

    return glodon::objectbuf::PFS_IGNORE;
success:
    return glodon::objectbuf::PFS_SUCCESS;
failure:
    return glodon::objectbuf::PFS_FAIL;
#undef DO_
}
