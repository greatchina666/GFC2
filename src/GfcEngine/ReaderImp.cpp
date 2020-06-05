#include "GfcEngine\Reader.h"
#include "ContainerImp.h"
#include "ReaderImp.h"
#include "FileMap.h"
#include "Common.h"
#include "GfcSchema\TypeObject.h"
#include "GfcSchema\EntityClass.h"
#include "GfcEngine\GfcEngineUtils.h"
#include "Upgrader.h"
#include <algorithm>

GFCENGINE_NAMESPACE_BEGIN

GFCENGINE_IMP_FACTORY(ReaderImp, 0)

class ReaderIterator : public Iterator<EntityPtr>
{
public:
    ReaderIterator(ReaderImp* pReader, std::shared_ptr<Iterator<EntityInfo>> pIterator): m_pReader(pReader), m_pIterator(pIterator) {}
    virtual void first() { m_pIterator->first(); }
    virtual void next() { m_pIterator->next(); }
    virtual bool isDone() { return m_pIterator->isDone(); }
    virtual EntityPtr current() { 
        return m_pReader->getEntity(m_pIterator->current().id);
    }
private:
    std::shared_ptr<Iterator<EntityInfo>> m_pIterator;
    ReaderImp* m_pReader;
};

ReaderImp::ReaderImp() : m_pFileMap(nullptr), m_pModel(nullptr), m_pContainer(nullptr), m_pFileModel(nullptr), m_pUpgrader(nullptr)
{
}


ReaderImp::~ReaderImp(void)
{
    delete m_pFileModel;
}

bool ReaderImp::open(const std::wstring & sFileName)
{
    m_pFileMap = new FileMap(sFileName);
    if (m_pFileMap->init())
    {
        auto sFileVer = readFileVersion();
        if (sFileVer != m_pModel->version())
        {
            // �汾��ͬ����Ҫ�����򽵼�
            if (!openFileModel(sFileVer))
                return false;
            delete m_pUpgrader; m_pUpgrader = nullptr;
            m_pUpgrader = new Upgrader;
            m_pUpgrader->init(m_pModel, m_pFileModel);
        }
        buildIndex();
        return true;
    }
    return false;
}

void ReaderImp::close()
{
    delete m_pFileMap;
    m_pFileMap = nullptr;
    delete m_pContainer;
    m_pContainer = nullptr;
}

EntityPtr ReaderImp::getEntity(EntityRef nId)
{
    if (m_pContainer)
    {
        auto oInfo = m_pContainer->getItem(nId);
        auto pEntity = (oInfo.type != nullptr) ? createEntity(oInfo) : nullptr;
        if (pEntity)
        {
            if (needUpdate()) 
            {
                auto pOldEntity = pEntity;
                pEntity = m_pUpgrader->update(pEntity);
                delete pOldEntity;
                if (pEntity == nullptr) // �����޷�����
                    return nullptr;
            }
            pEntity->setContainer(this);
        }
        return EntityPtr(pEntity);
    }
    else
    {
        return nullptr;
    }
}

EntityIteratorPtr ReaderImp::getEntities(const std::wstring & sType, bool bIncludeSubType)
{
    if (m_pContainer)
        return EntityIteratorPtr(new ReaderIterator(this, m_pContainer->getItems(sType, bIncludeSubType)));
    else
        return nullptr;
}

EntityIteratorPtr ReaderImp::getIterator()
{
    if (m_pContainer)
        return EntityIteratorPtr(new ReaderIterator(this, m_pContainer->iterator()));
    else
        return nullptr;
}

void ReaderImp::addInfo(const EntityInfo & oInfo)
{
    if (m_pContainer)
        m_pContainer->add(oInfo.id, oInfo);
}

bool ReaderImp::openFileModel(const std::wstring & sFileVer)
{
    delete m_pFileModel; m_pFileModel = nullptr;
    auto sFileName = getFullPath(m_sSchemaPath + L"\\" + sFileVer + L".exp");
    if (!fileExists(sFileName))
        return false;
    m_pFileModel = new gfc::schema::CModel();
    return GfcEngineUtils::loadSchema(sFileName, m_pFileModel);
}

bool ReaderImp::needUpdate()
{
    return m_pUpgrader != nullptr;
}

void ReaderImp::buildIndex()
{
    //std::map<std::string, std::vector<EntityRef>*> o;
    //auto a = o.begin();
    //a->second->empty()
    m_pContainer = new ContainerImp<EntityInfo>(schema());
    EntityInfo oInfo;
    m_pFileMap->setPos(0);
    while (getIndex(oInfo))
    {
        addInfo(oInfo);
    }
    //sort();
}

gfc::schema::CModel * ReaderImp::schema()
{
    return m_pUpgrader ? m_pFileModel : m_pModel;
}

gfc::schema::CClass * EntityInfo::getClass() const
{
    return dynamic_cast<gfc::schema::CClass*>(type->getBaseType());
}

EntityInfo * EntityInfo::get() const
{
    return (EntityInfo *)this;
}

GFCENGINE_NAMESPACE_END