// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#ifndef STDAFX_H
#define STDAFX_H

//#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
// #include <windows.h>
// 
// // C ����ʱͷ�ļ�
// #include <stdlib.h>
// #include <malloc.h>
// #include <memory.h>
// #include <tchar.h>

#include <google/protobuf/wire_format_lite.h>
//#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/stubs/common.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "glodon/objectbuf/EntitySchema.h"
#include "glodon/objectbuf/Entity.h"
#include "glodon/objectbuf/FieldCacheInitializer.h"
#include "glodon/objectbuf/Document.h"
#include "glodon/objectbuf/EntityTextSerializer.h"
#include "glodon/objectbuf/EntityBinarySerializer.h"
#include "FieldCache.h"

#include <vector>
#include <sstream>
#include <string>
#include <limits>
using namespace std;
#endif

