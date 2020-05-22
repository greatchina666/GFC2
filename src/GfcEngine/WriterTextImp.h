#ifndef WRITERTEXTIMP_H
#define WRITERTEXTIMP_H

#include <string>
#include "WriterImp.h"
#include <fstream>

GFCENGINE_NAMESPACE_BEGIN

// �ڲ�ʵ�֣������⹫��
class WriterTextImp: public WriterImp
{
public:
    WriterTextImp(void);
    virtual ~WriterTextImp(void);
    virtual bool open(const string& sFileName, const string& sProductCode);
    virtual void close();
    virtual EntityRef writeEntity(Entity* pEntity); 
private:
    void writeHead(const string& sFileName, const string& sProductCode);
	std::fstream* m_pTextStream;
};

GFCENGINE_NAMESPACE_END

#endif
