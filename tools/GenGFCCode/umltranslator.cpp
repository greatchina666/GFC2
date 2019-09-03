#include "umltranslator.h"
#include "model.h"
#include "umlreader.h"
#include "buildintype.h"
#include "codewriter.h"
#include "expresswriter.h"
#include <iostream>
#include <QString>
#include <windows.h>

std::wstring getExePath()
{
    WCHAR exeFullPath[MAX_PATH]; // MAX_PATH��WINDEF.h�ж����ˣ�����260
    memset(exeFullPath, 0, MAX_PATH);

    GetModuleFileName(NULL, exeFullPath, MAX_PATH);
    WCHAR *p = wcsrchr(exeFullPath, L'\\');
    *p = 0x00;
    return  std::wstring(exeFullPath);
}

CUMLTranslator::CUMLTranslator()
{
}


CUMLTranslator::~CUMLTranslator()
{
}

void CUMLTranslator::done(CTranslateInfo & oInfo)
{
    std::wstring sCoreUML = getExePath() + L"\\GFC2Core.uml";
    CModel oModel;
    initModel(&oModel);
    loadModelData(&oModel, oInfo.sUMLFile.empty() ? sCoreUML : oInfo.sUMLFile);

    CModel* pRefModel = nullptr;
    if (!oInfo.sUMLFile.empty())
    {
        pRefModel = new CModel();
        oModel.setRefModel(pRefModel);
        initModel(pRefModel);
        loadModelData(pRefModel, sCoreUML);
    }

    if (!oInfo.sExpressFile.empty())
    {
        CExpressWriter oWriter(&oModel);
        oWriter.write(oInfo.sExpressFile, L"GFC2X0");
    }
    if (!(oInfo.sCPPPath.empty() && oInfo.sHeadPath.empty() && oInfo.sNETPath.empty()))
    {
        CCodeWriter oCodeWriter(&oModel);
        oCodeWriter.write(oInfo.sHeadPath, 
            oInfo.sCPPPath, 
            oInfo.sNETPath);
    }
    delete pRefModel;
    std::wcout << L"������ɣ�" << std::endl;
}

void CUMLTranslator::initModel(CModel * pModel)
{
    pModel->addTypeObject(new CBuildinType(L"REAL"));
    pModel->addTypeObject(new CBuildinType(L"STRING"));
    pModel->addTypeObject(new CBuildinType(L"INTEGER"));
    pModel->addTypeObject(new CBuildinType(L"BOOLEAN"));
}

void CUMLTranslator::loadModelData(CModel * pModel, const std::wstring & sFileName)
{
    CUMLReader reader(pModel);
    reader.load(sFileName);
}