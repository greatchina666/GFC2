#ifndef GFCWRITER_H
#define GFCWRITER_H

#include "GfcEngine\Writer.h"
#include "GfcClasses.h"

class GFCCLASSES_API GfcWriter: public gfc::engine::CWriter
{
public:
    GfcWriter(const std::wstring& sProductCode = L"");
    ~GfcWriter();
};

#endif // !GFCWRITER_H