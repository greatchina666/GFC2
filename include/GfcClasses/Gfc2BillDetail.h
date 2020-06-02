#ifndef GFC2BILLDETAIL_H
#define GFC2BILLDETAIL_H

#include "GfcClasses.h"
#include "GfcEngine/EntityFactory.h"
#include "Gfc2String.h"
#include "Gfc2String.h"
#include "Gfc2String.h"
#include "Gfc2String.h"
#include "TypeDef.h"
#include "GfcEngine/Document.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2BillDetail: public gfc2::engine::Entity
{
GFCENGINE_DEC_OBJECT(Gfc2BillDetail,gfc2::engine::EntityFactory)
public:
    Gfc2BillDetail();
    Gfc2BillDetail(bool bSetSchema);
    void setFloorNum(const Gfc2Integer& nValue);
    Gfc2Integer getFloorNum() const;
    bool hasFloorNum() const;
    void setEntityID(const Gfc2Integer& nValue);
    Gfc2Integer getEntityID() const;
    bool hasEntityID() const;
    void setUnit(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getUnit() const;
    bool hasUnit() const;
    std::shared_ptr<Gfc2String> getUnitPtr();
    void setExpress(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getExpress() const;
    bool hasExpress() const;
    std::shared_ptr<Gfc2String> getExpressPtr();
    void setQuantity(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getQuantity() const;
    bool hasQuantity() const;
    std::shared_ptr<Gfc2String> getQuantityPtr();
    void setMemo(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getMemo() const;
    bool hasMemo() const;
    std::shared_ptr<Gfc2String> getMemoPtr();

};
#endif