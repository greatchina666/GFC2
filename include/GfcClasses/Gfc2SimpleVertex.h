#ifndef GFC2SIMPLEVERTEX_H
#define GFC2SIMPLEVERTEX_H

#include "GfcClasses.h"
#include "GfcEngine/EntityFactory.h"
#include "Gfc2Topology.h"
#include "Gfc2Vector2d.h"
#include "TypeDef.h"
#include "GfcEngine/Document.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2SimpleVertex: public Gfc2Topology
{
GFCENGINE_DEC_OBJECT(Gfc2SimpleVertex,gfc2::engine::EntityFactory)
public:
    Gfc2SimpleVertex();
    Gfc2SimpleVertex(bool bSetSchema);
    void setPoint(const gfc2::engine::EntityRef& nValue);
    gfc2::engine::EntityRef getPoint() const;
    bool hasPoint() const;
    std::shared_ptr<Gfc2Vector2d> getPointPtr();
    void setRadius(const Gfc2Double& dValue);
    Gfc2Double getRadius() const;
    bool hasRadius() const;
    void setArcType(const Gfc2ArcType& nValue);
    Gfc2ArcType getArcType() const;
    bool hasArcType() const;

};
#endif