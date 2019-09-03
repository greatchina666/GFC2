#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class CTypeObject;

class CAttribute
{
public:
    CAttribute();
    std::wstring& getName() {return m_sName;}
    void SetName(const std::wstring& sName) {m_sName = sName;}
    CTypeObject* getType() {return m_pTypeObject;}
    void SetType(CTypeObject* pType);
    bool getOptionalFlag() {return m_bOptional;}
    void SetOptionalFlag(bool bOptional) {m_bOptional = bOptional;}
    bool getRepeatFlag() {return m_bRepeat;}
    void SetRepeatFlag(bool bRepeat) {m_bRepeat = bRepeat;}
    //bool getRefFlag();
    //void setRefFlag(bool bRefFlag);
private:
    std::wstring m_sName;
    CTypeObject* m_pTypeObject;
    bool m_bOptional;
    bool m_bRepeat;
    //bool m_bRefFlag;
};

#endif // ATTRIBUTE_H