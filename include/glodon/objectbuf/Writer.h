#ifndef GLODON_OBJECTBUF_WRITER_H
#define GLODON_OBJECTBUF_WRITER_H

#include <string>
#include <memory>
#include "glodon\objectbuf\Entity.h"
#include "glodon\objectbuf\Document.h"

using namespace std;
namespace glodon {
namespace objectbuf {

class SerializerManager;
class WriterImp;

class OBJECTBUF_API Writer
{
public:
    Writer(void);
    ~Writer(void);
    bool open(const string& sFileName, const std::string& sFormatType, const string& sProductCode = "");
    void close();
    EntityRef writeEntity(Entity* pEntity); 
private:
    std::tr1::shared_ptr<SerializerManager> m_pSerializerManager;
    WriterImp* m_pImp;
    Document m_oDoc; // Ŀǰ������Ϊ�˼�¼Schema����ֹ����
};

}
}

#endif
