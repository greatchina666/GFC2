#include "ModelCompatibility.h"
#include "ClassCompatibility.h"
#include "Model.h"
#include "EntityClass.h"
#include <assert.h>

GFC_NAMESPACE_BEGIN

CModelCompatibility::CModelCompatibility(void)
{
}


CModelCompatibility::~CModelCompatibility(void)
{
    clear();
}

void CModelCompatibility::init(CModel * pFrom, CModel * pTo)
{
    // �ж�����ģ�͵ļ�����
    assert(pFrom); assert(pTo);
    for (int i = 0; i < pFrom->getTypeObjectCount(); i++)
    {
        auto pFromType = pFrom->getTypeObject(i);
        auto pFromBaseType = pFromType->getBaseType();
        if (pFromBaseType->getType() == TOE_CLASS)
        {
            auto pToType = pTo->findTypeObject(pFromBaseType->getName());
            if (pToType && pToType->getType() == TOE_CLASS)
            {
                // ������ͬ������
                auto pCompatibility = new CClassCompatibility;
                pCompatibility->init((CClass*)pFromBaseType, (CClass*)pToType);
                add(pCompatibility);
            }// �����������Σ�����Ϊδ�ҵ�ƥ����࣬���Լ��ݣ�ȡ���������Ƿ������ã�
        }
    }
}

CClassCompatibility * CModelCompatibility::find(const std::wstring & sName)
{
    auto itr = m_oClassIndex.find(sName);
    return itr == m_oClassIndex.end() ? nullptr : itr->second;
}

CClassCompatibility * CModelCompatibility::getItems(int nIndex)
{
    return m_oClassList[nIndex];
}

int CModelCompatibility::getCount()
{
    return (int)m_oClassList.size();
}

void CModelCompatibility::add(CClassCompatibility * pObject)
{
    m_oClassList.push_back(pObject);
    m_oClassIndex.insert(std::make_pair(pObject->getName(), pObject));
}

void CModelCompatibility::clear()
{
    for each (auto pClass in m_oClassList)
    {
        delete pClass;
    }
    m_oClassList.clear();
    m_oClassIndex.clear();
}

GFC_NAMESPACE_END