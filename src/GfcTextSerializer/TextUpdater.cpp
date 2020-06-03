#include "TextUpdater.h"
#include <Windows.h>
#include <assert.h>
#include "resource.h"
#include "GfcTextSerializer.h"
//#include "glodon\objectbuf\Entity.h"
#include "Scanner.h"
#include "Parser.h"
#include <algorithm>
#include "Common.h"
#include "ModelCompatibility.h"
#include "ClassCompatibility.h"
#include "AttributeCompatibility.h"
#include "Converter.h"
#include "EntityParser\Parser.h"
#include "EntityParser\Scanner.h"
#include "AttributeValue.h"
#include "GfcSchema/BuildinType.h"

namespace glodon {
namespace objectbuf {

TextUpdater::~TextUpdater()
{
    clear();
}

void TextUpdater::init(const std::string & sVersion)
{
    clear();
    // ��ȣ�����Ҫ����
    /* //todo
    if (_stricmp(sVersion.c_str(), Entity::Version().c_str()) == 0)
        return;
        */
    // Load File model
    auto sSchema = sVersion;
    std::replace(sSchema.begin(), sSchema.end(), '.', 'X');
    m_pTempModel = new gfc::schema::CModel;
    loadFileModel(sSchema);
    // Load dll model
    loadDllModel();
    if (m_pDllModel && m_pFileModel)
    {
        m_pModelCompatibility = new gfc::schema::CModelCompatibility;
        m_pModelCompatibility->init(m_pFileModel, m_pDllModel);
    }
}

void TextUpdater::update(std::string & sLine)
{
    if (m_pModelCompatibility == nullptr)
        return; // no update
    gfc::Scanner oScanner((unsigned char*)sLine.c_str(), sLine.length());
    gfc::Parser oParser(&oScanner);
    oParser.Parse();
    if (oParser.errors->count > 0)
    { 
        // ���� DATA;����
        //assert(false);
        return;
    }
    auto pClassCompatibility = m_pModelCompatibility->find(oParser.m_sEntityName);
    if (pClassCompatibility == nullptr)
    {
        sLine = ""; // no read
        return;
    }
    std::string sParams;
    transform(pClassCompatibility, &oParser.m_oParameterList, sParams);
    sLine = UnicodeToUtf8(oParser.m_sInstance) + "=" + UnicodeToUtf8(oParser.m_sEntityName) + "(" + sParams + ");";
}

void TextUpdater::transform(gfc::schema::CClassCompatibility * pClassCompatibility, gfc::schema::CAttributeValue * pParamList, std::string& sOutput)
{
    std::map<int, gfc::schema::CAttributeValuePtr> oNewMap;
    for (int i = 0; i < pClassCompatibility->getCount(); i++)
    {
        auto pAttributeCompatibility = pClassCompatibility->getCompatibilityAttribute(i);
        int  nIndex = pAttributeCompatibility->toIndex();
        auto pConverter = pAttributeCompatibility->converter();
        if (nIndex != -1)
        {
            auto pValue = i < (int)pParamList->getCount() ? pParamList->getItems(i) : gfc::schema::CAttributeValuePtr(new gfc::schema::CLeafAttributeValue(L"$"));
            if (pConverter)
                pConverter->transform(pValue);
            else
                pValue = gfc::schema::CAttributeValuePtr(new gfc::schema::CLeafAttributeValue(L"$"));
            oNewMap[nIndex] = pValue;
        }
    }
    sOutput = "";
    for each (auto oPair in oNewMap)
    {
        sOutput += UnicodeToUtf8(oPair.second->asString()) + ",";
    }
    sOutput = sOutput.substr(0, sOutput.length() - 1);
}

void TextUpdater::clear()
{
    delete m_pDllModel;  m_pDllModel = nullptr;
    delete m_pFileModel; m_pFileModel = nullptr;
    delete m_pTempModel; m_pTempModel = nullptr;
    delete m_pModelCompatibility; m_pModelCompatibility = nullptr;
}

void TextUpdater::loadDllModel()
{
    // ������Դ
    HINSTANCE hInst = g_nDLLHandle;
    HRSRC hRsrc = FindResource(hInst, MAKEINTRESOURCE(IDR_EXP1), L"EXP");
    if (!hRsrc)
        return;
    DWORD dwSize = SizeofResource(hInst, hRsrc);
    HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
    LPVOID pBuffer = LockResource(hGlobal);
    BYTE* pByte = new BYTE[dwSize + 1];
    memcpy(pByte, pBuffer, dwSize);
    GlobalUnlock(hGlobal);
    // ����
    Scanner oScanner(pByte, dwSize);
    Parser oParser(&oScanner);
    m_pDllModel = new gfc::schema::CModel;
    initModel(m_pDllModel);
    oParser.m_pModel = m_pDllModel;
    oParser.m_pTempModel = m_pTempModel;
    oParser.Parse();
}

void TextUpdater::loadFileModel(const std::string& sFileSchema)
{
    //
    if (m_sSchemaPath.empty())
        return;
    auto sFileName = toWstring(m_sSchemaPath + "\\" + sFileSchema + ".exp");
    if (!fileExists(sFileName))
        return;
    // ����
    Scanner oScanner(sFileName.c_str());
    Parser oParser(&oScanner);
    m_pFileModel = new gfc::schema::CModel;
    initModel(m_pFileModel);
    oParser.m_pModel = m_pFileModel;
    oParser.m_pTempModel = m_pTempModel;
    oParser.Parse();
    if (oParser.errors->count > 0)
    {
        assert(false);
    }
}

void TextUpdater::initModel(gfc::schema::CModel * pModel)
{
    //pModel->addTypeObject(new gfc::schema::CBuildinType(L"BOOLEAN"));
    //pModel->addTypeObject(new gfc::schema::CBuildinType(L"REAL"));
    //pModel->addTypeObject(new gfc::schema::CBuildinType(L"STRING"));
    //pModel->addTypeObject(new gfc::schema::CBuildinType(L"INTEGER"));
}

}
}