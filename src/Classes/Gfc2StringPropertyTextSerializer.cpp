#include "StdAfx.h"
#include "Gfc2StringPropertyTextSerializer.h"
#include "FieldCache.h"
#include "Gfc2StringProperty.h"

OBJECTBUF_IMP_OBJECT(Gfc2StringPropertyTextSerializer,"Gfc2StringPropertyT",0)

std::string Gfc2StringPropertyTextSerializer::serialize(glodon::objectbuf::Entity* pEntity) const
{
    Gfc2StringProperty* pEnt = (Gfc2StringProperty*)pEntity;
    std::string sResult = Gfc2PropertyTextSerializer::serialize(pEnt);

    std::stringstream stream;
    stream.precision(numeric_limits<double>::digits10);
    if (pEnt->hasValue())
        stream<<",#"<<pEnt->getValue();
    else
        stream<<",$";

    sResult += stream.str();
    if(sResult[0] == ',')
        sResult = sResult.substr(1,sResult.length() - 1);
    return sResult;
}

glodon::objectbuf::EnParseFieldState Gfc2StringPropertyTextSerializer::parseField(const std::string& input, int nFieldNum, glodon::objectbuf::Entity* pEntity)
{
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    Gfc2StringProperty* pEnt = (Gfc2StringProperty*)pEntity;
    glodon::objectbuf::EnParseFieldState nState = Gfc2PropertyTextSerializer::parseField(input, nFieldNum, pEnt);
    if (nState != glodon::objectbuf::PFS_IGNORE)
    {
        return nState;
    }

    switch(nFieldNum)
    {
    case 1:
        {
            glodon::objectbuf::EntityRef value;
            DO_((readEntityField(input, value)));
            pEnt->setValue(value);
        }
        break;
    default:
        return glodon::objectbuf::PFS_IGNORE;
    }
    return glodon::objectbuf::PFS_SUCCESS;
failure:
    return glodon::objectbuf::PFS_FAIL;
#undef DO_
}

