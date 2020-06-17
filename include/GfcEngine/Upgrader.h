#ifndef TEXTUPDATER_H
#define TEXTUPDATER_H

#include "GfcEngine\GfcEngine.h"
#include "GfcSchema\SchemaMacro.h"
#include <string>

GFC_NAMESPACE_BEGIN

class CModel;
class CAttributeValue;

GFC_NAMESPACE_END

GFCENGINE_NAMESPACE_BEGIN

class CModelCompatibility;
class CClassCompatibility;
class CEntity;

class GFCENGINE_API CEntityUpgrader
{
public:
    CEntityUpgrader() : m_pModelCompatibility(nullptr) {}
    ~CEntityUpgrader();
    void init(gfc::schema::CModel* pDest, gfc::schema::CModel* pSrc);
    CEntity* update(CEntity* pEntity);
    // for test
    void transform(CClassCompatibility* pClassCompatibility, CEntity* pSrcEntity, CEntity* pDestEntity);
    CModelCompatibility* model() { return m_pModelCompatibility; }
private:
    void clear();
    gfc::schema::CModel* m_pDestModel;
    gfc::schema::CModel* m_pSrcModel;
    CModelCompatibility* m_pModelCompatibility;
};

GFCENGINE_NAMESPACE_END

#endif // !TEXTUPDATER_H
