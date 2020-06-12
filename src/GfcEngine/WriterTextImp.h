#ifndef WRITERTEXTIMP_H
#define WRITERTEXTIMP_H

#include <string>
#include "WriterImp.h"
#include <fstream>

GFCENGINE_NAMESPACE_BEGIN

class CPropValue;

// �ڲ�ʵ�֣������⹫��
class CWriterTextImp: public CWriterImp
{
    GFCENGINE_DEC_OBJECT(CWriterTextImp, CWriterImp)
public:
    CWriterTextImp(void);
    virtual ~CWriterTextImp(void);
    virtual bool open(const std::wstring& sFileName, const std::wstring& sProductCode, const std::wstring& sVersion);
    virtual void close();
    virtual EntityRef writeEntity(CEntity* pEntity); 
private:
    void writeHead(const std::wstring& sFileName, const std::wstring& sProductCode, const std::wstring& sVersion);
    std::fstream* m_pTextStream;
};
// ���ڲ���
class CWriterTextUtils
{
public:
    static void writeEntity(std::iostream& out, CEntity* pEntity, EntityRef nRef);
    static void writeValue(std::iostream& out, gfc::schema::CTypeObject * pType, CPropValue* pValue);
    static void writeProperty(std::iostream& out, CProperty* pProp);
};

GFCENGINE_NAMESPACE_END

#endif
