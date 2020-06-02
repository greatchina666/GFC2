#ifndef GFC2ELLIPSE2D_H
#define GFC2ELLIPSE2D_H

#include "GfcClasses.h"
#include "GfcEngine/EntityFactory.h"
#include "Gfc2Curve2d.h"
#include "Gfc2Vector2d.h"
#include "Gfc2Vector2d.h"
#include "Gfc2Intervald.h"
#include "TypeDef.h"
#include "GfcEngine/Document.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2Ellipse2d: public Gfc2Curve2d
{
GFCENGINE_DEC_OBJECT(Gfc2Ellipse2d,gfc2::engine::EntityFactory)
public:
    Gfc2Ellipse2d();
    Gfc2Ellipse2d(bool bSetSchema);
    void setCenterPt(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getCenterPt() const;
    bool hasCenterPt() const;
    std::shared_ptr<Gfc2Vector2d> getCenterPtPtr();
    void setMajorAxis(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getMajorAxis() const;
    bool hasMajorAxis() const;
    std::shared_ptr<Gfc2Vector2d> getMajorAxisPtr();
    void setdMajorRad(const Gfc2Double& dValue);
    Gfc2Double getdMajorRad() const;
    bool hasdMajorRad() const;
    void setdMinorRad(const Gfc2Double& dValue);
    Gfc2Double getdMinorRad() const;
    bool hasdMinorRad() const;
    void setRange(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getRange() const;
    bool hasRange() const;
    std::shared_ptr<Gfc2Intervald> getRangePtr();
    void setClockSign(const Gfc2Integer& nValue);
    Gfc2Integer getClockSign() const;
    bool hasClockSign() const;

};
#endif