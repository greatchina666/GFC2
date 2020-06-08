
#ifndef OB_OBJECT_FACTORY_H
#define OB_OBJECT_FACTORY_H

#include <map> 
#include <utility>
#include <string>
#include <stdint.h>
#include "GfcEngine\Object.h"

#pragma warning(disable : 4251)

GFCENGINE_NAMESPACE_BEGIN

#define    END_REG_ITEM        -1

    template<typename Type> 
    struct GFCENGINE_API CRegItem
    {
        CRegItem()
        {
            unMode = END_REG_ITEM;
        }

        CRegItem(const Type& objType,int64_t mode)
        {
            unObjType = objType;
            unMode = mode;
        }

        Type unObjType;   //ע���ֵ
        int64_t unMode;   //��Ӧ����չ����
    };

    template<typename Type> 
    class GFCENGINE_API CRegObjInfo
    {
    public:
        CRegObjInfo()
        {
            m_pCreateFunPtr = NULL;
            m_pUserData = NULL;
        }

        CRegObjInfo(CREATETHIS i_pThisFun,const CRegItem<Type>& i_regItem)
        {
            m_pCreateFunPtr = i_pThisFun;
            regItem = i_regItem;
            m_pUserData = NULL;
        }

        CRegObjInfo(const CRegObjInfo<Type>& i_regObjInfo)
        {
            m_pCreateFunPtr = i_regObjInfo.m_pCreateFunPtr;
            regItem = i_regObjInfo.regItem;
            m_pUserData = i_regObjInfo.m_pUserData;
        }

        ~CRegObjInfo()
        {
        }

        const Type& GetType() const
        {
            return regItem.unObjType;
        }

        int64_t GetMode() const
        {
            return regItem.unMode;
        }

        void SetUserData(void* pUserData)
        {
            m_pUserData = pUserData;
        }

        void* GetUserData() const
        {
            return m_pUserData;
        }

        CREATETHIS GetFunPtr() const
        {
            return m_pCreateFunPtr;
        }
    private:
        CREATETHIS m_pCreateFunPtr;   //����ָ��
        CRegItem<Type> regItem;       //ע����������
        void* m_pUserData;            //�û�����
    };


    template<typename Type>
    class GFCENGINE_API CObjectFactory
    {
    public:
        CObjectFactory(unsigned int type)
        {
            m_type = type;
            //ȷ���ڲ�û���κ�����ע����
            m_regHelperMap.clear();
        }

        unsigned int GetType() const
        {
            return m_type;
        }

        virtual CObject* Create(const Type& unObjType)
        {
            const CRegObjInfo<Type>* pRegObjInfo = FindCreateHelper(unObjType);
            if(pRegObjInfo == NULL)
            {
                return NULL;
            }

            if(pRegObjInfo->GetFunPtr()!=NULL)
            {
                CObject* pObj = dynamic_cast<CObject*> (pRegObjInfo->GetFunPtr()());
                return pObj;
            }
            else
            {
                return NULL;
            }
        }

        bool IsExist(const Type& unObjType) const
        {
            typename std::map<Type, CRegObjInfo<Type> *>::const_iterator iterator;
            iterator = m_regHelperMap.find(unObjType);
            return (iterator == m_regHelperMap.end()) ? false : true;
        }

        bool RegisterCreateHelper(const Type& unObjType,const CRegObjInfo<Type>& regInfo) 
        {
            //��������жϣ���������ָ��
            if(regInfo.GetFunPtr() == NULL)
            {
                return false;
            }

            //����ע��,����Ѿ����ڣ��򸲸���ǰ��ע����Ϣ�����и���
            typename std::map<Type,CRegObjInfo<Type>* >::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator != m_regHelperMap.end())
            {
                UnRegisterCreateHelper(unObjType);
            }
            CRegObjInfo<Type>* pNewObjInfo = new CRegObjInfo<Type>;
            *pNewObjInfo = regInfo;

            m_regHelperMap.insert(std::make_pair(unObjType,pNewObjInfo));
            return true;
        }

        bool UnRegisterCreateHelper(const Type& unObjType) 
        {
            typename std::map<Type,CRegObjInfo<Type>*>::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator == m_regHelperMap.end())
            {
                return false;
            }
            else
            {
                CRegObjInfo<Type>* pObjInfo = (*iterator).second;
                m_regHelperMap.erase(iterator);
                if(pObjInfo != NULL)
                {
                    delete pObjInfo;
                }

                return true;
            }
        }


        const CRegObjInfo<Type>* FindCreateHelper(const Type& unObjType) const
        {
            typename std::map<Type,CRegObjInfo<Type>*>::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator == m_regHelperMap.end())
            {
                return NULL;
            }
            else
            {
                return (*iterator).second;
            }
        }

        virtual ~CObjectFactory()
        {
            typename std::map<Type,CRegObjInfo<Type>*>::iterator iterator;
            typename std::map<Type,CRegObjInfo<Type>*>::iterator endIterator = m_regHelperMap.end();
            for(iterator = m_regHelperMap.begin(); iterator != endIterator; iterator++ )
            {
                CRegObjInfo<Type>* pObjInfo = (*iterator).second;
                if(pObjInfo != NULL)
                {
                    delete pObjInfo;
                }
            }

            //�������ע����
            m_regHelperMap.clear();
        }

        typename std::map<Type, CRegObjInfo<Type>*>::iterator begin()
        {
            return m_regHelperMap.begin();
        }

        typename std::map<Type, CRegObjInfo<Type>*>::iterator end()
        {
            return m_regHelperMap.end();
        }

    private:
        std::map<Type,CRegObjInfo<Type>*> m_regHelperMap;  //����ע����Ϣ��
        unsigned int m_type;                               //�೧������

    };

GFCENGINE_NAMESPACE_END

#endif