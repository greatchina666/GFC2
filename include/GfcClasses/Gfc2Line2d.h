#ifndef GFC2LINE2D_H
#define GFC2LINE2D_H

#include "GfcClasses.h"
#include "Gfc2Curve2d.h"
#include "Gfc2Vector2d.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2Line2d: public Gfc2Curve2d
{
GFCENGINE_DEC_OBJECT(Gfc2Line2d, gfc::engine::CEntity)
public:
    Gfc2Line2d();
    Gfc2Line2d(bool bSetSchema);
    void setStartPt(const gfc::engine::EntityRef& nValue);
    gfc::engine::EntityRef getStartPt() const;
    bool hasStartPt() const;
    std::shared_ptr<Gfc2Vector2d> getStartPtPtr();
    void setEndPt(const gfc::engine::EntityRef& nValue);
    gfc::engine::EntityRef getEndPt() const;
    bool hasEndPt() const;
    std::shared_ptr<Gfc2Vector2d> getEndPtPtr();

};
#endif
