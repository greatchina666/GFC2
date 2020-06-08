#ifndef GFC2RELCONNECTSWITHREALIZINGELEMENTS_H
#define GFC2RELCONNECTSWITHREALIZINGELEMENTS_H

#include "GfcClasses.h"
#include "Gfc2RelConnectsElements.h"
#include "Gfc2Element.h"
#include "GfcEngine/Entity.h"

class GFCCLASSES_API Gfc2RelConnectsWithRealizingElements: public Gfc2RelConnectsElements
{
GFCENGINE_DEC_OBJECT(Gfc2RelConnectsWithRealizingElements, gfc::engine::CEntity)
public:
    Gfc2RelConnectsWithRealizingElements();
    Gfc2RelConnectsWithRealizingElements(bool bSetSchema);
    void setRealizingElements(const gfc::engine::EntityRef& nValue);
    gfc::engine::EntityRef getRealizingElements() const;
    bool hasRealizingElements() const;
    std::shared_ptr<Gfc2Element> getRealizingElementsPtr();

};
#endif
