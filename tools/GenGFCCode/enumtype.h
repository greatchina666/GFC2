#ifndef ENUMTYPE_H
#define ENUMTYPE_H

#include <vector>
#include "typeobject.h"

class CEnumType : public CTypeObject
{
public:
    CEnumType();
    CEnumType(const std::wstring& sName);
    virtual CTypeObjectEnum getType() const {return TOE_ENUM;}
    // ö��ֵ
    std::wstring& getEnum(int nIndex);
    int getEnumCount(){return (int)m_oEnumList.size();}
    void addEnum(const std::wstring& sEnum);
private:
    std::vector<std::wstring> m_oEnumList;
};

#endif // ENUMTYPE_H