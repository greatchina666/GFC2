#include "StdAfx.h"
#include "Gfc2BrepBodyTextSerializer.h"
#include "FieldCache.h"
#include "Gfc2BrepBody.h"

OBJECTBUF_IMP_OBJECT(Gfc2BrepBodyTextSerializer,"Gfc2BrepBodyT",0)

std::string Gfc2BrepBodyTextSerializer::serialize(glodon::objectbuf::Entity* pEntity) const
{
    Gfc2BrepBody* pEnt = (Gfc2BrepBody*)pEntity;
    std::string sResult = Gfc2BodyTextSerializer::serialize(pEnt);

    std::stringstream stream;
    stream.precision(numeric_limits<double>::digits10);
    {
        stream<<",(";
        for (int i = 0; i < pEnt->getFacesCount(); i++)
        {
            if(0==i)
                stream<<"#"<<pEnt->getFaces(i);
            else
                stream<<",#"<<pEnt->getFaces(i);
        }
        stream<<")";
    }

    {
        stream<<",(";
        for (int i = 0; i < pEnt->getEdgesCount(); i++)
        {
            if(0==i)
                stream<<"#"<<pEnt->getEdges(i);
            else
                stream<<",#"<<pEnt->getEdges(i);
        }
        stream<<")";
    }

    sResult += stream.str();
    if(sResult[0] == ',')
        sResult = sResult.substr(1,sResult.length() - 1);
    return sResult;
}

glodon::objectbuf::EnParseFieldState Gfc2BrepBodyTextSerializer::parseField(const std::string& input, int nFieldNum, glodon::objectbuf::Entity* pEntity)
{
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
    Gfc2BrepBody* pEnt = (Gfc2BrepBody*)pEntity;
    glodon::objectbuf::EnParseFieldState nState = Gfc2BodyTextSerializer::parseField(input, nFieldNum, pEnt);
    if (nState != glodon::objectbuf::PFS_IGNORE)
    {
        return nState;
    }

    switch(nFieldNum)
    {
    case 0:
        {
            glodon::objectbuf::EntityRef value;
            DO_((readEntityField(input, value)));
            pEnt->addFaces(value);
        }
        break;
    case 1:
        {
            glodon::objectbuf::EntityRef value;
            DO_((readEntityField(input, value)));
            pEnt->addEdges(value);
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

