#ifndef GFC2TORUS_H
#define GFC2TORUS_H

#include "GfcClasses.h"
#include "GfcEngine/EntityFactory.h"
#include "Gfc2Surface.h"
#include "Gfc2Coordinates3d.h"
#include "Gfc2Intervald.h"
#include "Gfc2Curve2d.h"
#include "TypeDef.h"
#include "GfcEngine/Document.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2Torus: public Gfc2Surface
{
GFCENGINE_DEC_OBJECT(Gfc2Torus,gfc2::engine::EntityFactory)
public:
    Gfc2Torus();
    Gfc2Torus(bool bSetSchema);
    void setCoord(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getCoord() const;
    bool hasCoord() const;
    std::shared_ptr<Gfc2Coordinates3d> getCoordPtr();
    void setRadius(const Gfc2Double& dValue);
    Gfc2Double getRadius() const;
    bool hasRadius() const;
    void setClockSign(const Gfc2Integer& nValue);
    Gfc2Integer getClockSign() const;
    bool hasClockSign() const;
    void setRangeV(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getRangeV() const;
    bool hasRangeV() const;
    std::shared_ptr<Gfc2Intervald> getRangeVPtr();
    void setCurve(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getCurve() const;
    bool hasCurve() const;
    std::shared_ptr<Gfc2Curve2d> getCurvePtr();

};
#endif