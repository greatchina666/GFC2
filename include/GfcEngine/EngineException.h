#ifndef EXPENGINEEXCEPTION_H
#define EXPENGINEEXCEPTION_H

#include <exception>
#include "GfcEngine\GfcEngine.h"

GFCENGINE_NAMESPACE_BEGIN

class EMissMatchProperty : public std::exception
{
public:
    EMissMatchProperty() {}
public:
    virtual char const* what() const { return "Miss Match Property exception"; }  //��ȡ����Ĵ�����Ϣ
};

class ETypeMatchError : public std::exception
{
public:
    ETypeMatchError() {}
public:
    virtual char const* what() const { return "Type match error"; }  //��ȡ����Ĵ�����Ϣ
};

GFCENGINE_NAMESPACE_END

#endif // !EXPENGINEEXCEPTION_H

