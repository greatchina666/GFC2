#ifndef UMLREADER_H
#define UMLREADER_H

#include <list>
#include <map>
#include <string>

class CModel;
class QXmlStreamReader;
class CAttribute;
class CTypeDef;
class CTypeObject;

struct CAssociation
{
    std::wstring OwnerTypeName;
	std::wstring FieldName;
	std::wstring TypeName;
    bool IsMultiplicity;
    bool IsOptional;
    CAssociation(): IsMultiplicity(false), IsOptional(false) {}
};

struct CAssociationEnd
{
    std::wstring Name;
	std::wstring TypeName;
	std::wstring Multiplicity;
};

class CUMLReader
{
public:
    CUMLReader(CModel* pModel);
    void load(const std::wstring& sFileName);
private:
    void initial();
    void finalize();
    void loadBody(QXmlStreamReader& reader);
    void loadModel(QXmlStreamReader& reader);
    void loadClass(QXmlStreamReader& reader);
    void doneGeneralization(QXmlStreamReader& reader);
    void doneAssociation(QXmlStreamReader& reader);
    bool initAssociation(CAssociationEnd& oEnd1, CAssociationEnd& oEnd2, CAssociation& oAssociation);
    CAssociationEnd getAssociationEnd(QXmlStreamReader& reader);
    CTypeObject* findTypeObjectByGUID(const std::wstring& sGUID);
    CAttribute* getAttribute(QXmlStreamReader& reader);
    std::wstring getAttributeName(QXmlStreamReader& reader);
    CAttribute* createAttribute(const std::wstring& sAttributeName, const std::wstring& sAttributeType,
                                bool bOptional, bool bRepeated);
private:
    CModel* m_pModel;
    typedef std::list<std::pair<CAttribute*, std::wstring>> CAttributeList;
    CAttributeList m_oAttributeList;
    typedef std::list<std::pair<CTypeDef*, std::wstring>> CTypeDefList;
    CTypeDefList m_oTypedefList;
    typedef std::map<std::wstring, CTypeObject*> CGuidTypeObjectMap;
    CGuidTypeObjectMap m_oTypeObjectMap;
    typedef std::list<std::pair<std::wstring, std::wstring>> CGeneralizationList;
    CGeneralizationList m_oGeneralizationList;
    typedef std::list<CAssociation> CAssociationList;
    CAssociationList m_oAssociationList;
};

#endif // UMLREADER_H