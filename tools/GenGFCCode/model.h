#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include "typeobject.h"

typedef std::vector<CTypeObject*> CTypeObjectList;

class CModel
{
public:
    CModel();
    ~CModel();
    CTypeObject *getTypeObject(int nIndex);
    int getTypeObjectCount(){return (int)m_oTypeObjectList.size();}
    void addTypeObject(CTypeObject* pTypeObject);
    CTypeObject *findTypeObject(const std::wstring& sTypeName);
    CModel* getRefModel() { return m_pRefModel; }
    void setRefModel(CModel* pRefModel) { m_pRefModel = pRefModel; }

	// ��չ�ӿڣ�ֻ����ָ����gfc�ļ���xuxp,2017-6-19
    void getTypeObjectList(CTypeObjectList& oTypeList/*,QStringList files = QStringList()*/);
private:
    CTypeObjectList m_oTypeObjectList;
    typedef std::map<std::wstring, CTypeObject*> CTypeMap;
    CTypeMap m_oTypeIndex;
    CModel* m_pRefModel;
};

#endif // MODEL_H