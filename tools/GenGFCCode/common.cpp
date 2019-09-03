#include "common.h"
#include <stdarg.h>
#include <algorithm>

std::wstring _FormatWstring(const wchar_t * lpcwszFormat, va_list _list)
{
    size_t nLength = _vscwprintf(lpcwszFormat, _list) + 1; //��ȡ��ʽ���ַ�������
    wchar_t* pszStr = new wchar_t[nLength];
    memset(pszStr, L'\0', nLength);
    _vsnwprintf_s(pszStr, nLength, nLength, lpcwszFormat, _list);
    std::wstring strResult(pszStr);
    delete[]pszStr;
    return strResult;
}

std::wstring FormatWstring(const wchar_t * lpcwszFormat, ...)
{
    std::wstring strResult;
    if (NULL != lpcwszFormat)
    {
        va_list marker = NULL;
        va_start(marker, lpcwszFormat); //��ʼ����������
        strResult = _FormatWstring(lpcwszFormat, marker);
        va_end(marker); //���ñ�������
    }
    return strResult;
}

std::wstring FormatWstring(const std::wstring sFormat, ...)
{
    va_list _va_list;
    va_start(_va_list, sFormat);      /* ��ʼ���䳤�����б� */
    std::wstring sResult = _FormatWstring(sFormat.c_str(), _va_list);    /* ���ݱ䳤���� */
    va_end(_va_list);         /* ����ʹ�ñ䳤�����б� */
    return sResult;
}

std::wstring UpperString(const std::wstring & sStr)
{
    std::wstring sTmp = sStr;
    transform(sTmp.begin(), sTmp.end(), sTmp.begin(), towupper);
    return sTmp;
}

std::wstring LowerString(const std::wstring & sStr)
{
    std::wstring sTmp = sStr;
    transform(sTmp.begin(), sTmp.end(), sTmp.begin(), towlower);
    return sTmp;
}
