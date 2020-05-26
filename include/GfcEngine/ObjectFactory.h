
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
    struct GFCENGINE_API RegItem
    {
        RegItem()
        {
            unMode = END_REG_ITEM;
        }

        RegItem(const Type& objType,int64_t mode)
        {
            unObjType = objType;
            unMode = mode;
        }

        Type unObjType;   //ע���ֵ
        int64_t unMode;   //��Ӧ����չ����
    };

    template<typename Type> 
    class GFCENGINE_API RegObjInfo
    {
    public:
        RegObjInfo()
        {
            m_pCreateFunPtr = NULL;
            m_pUserData = NULL;
        }

        RegObjInfo(CREATETHIS i_pThisFun,const RegItem<Type>& i_regItem)
        {
            m_pCreateFunPtr = i_pThisFun;
            regItem = i_regItem;
            m_pUserData = NULL;
        }

        RegObjInfo(const RegObjInfo<Type>& i_regObjInfo)
        {
            m_pCreateFunPtr = i_regObjInfo.m_pCreateFunPtr;
            regItem = i_regObjInfo.regItem;
            m_pUserData = i_regObjInfo.m_pUserData;
        }

        ~RegObjInfo()
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
        RegItem<Type> regItem;       //ע����������
        void* m_pUserData;            //�û�����
    };


    template<typename Type>
    class GFCENGINE_API ObjectFactory
    {
    public:
        ObjectFactory(unsigned int type)
        {
            m_type = type;
            //ȷ���ڲ�û���κ�����ע����
            m_regHelperMap.clear();
        }

        unsigned int GetType() const
        {
            return m_type;
        }

        virtual Object* Create(const Type& unObjType)
        {
            const RegObjInfo<Type>* pRegObjInfo = FindCreateHelper(unObjType);
            if(pRegObjInfo == NULL)
            {
                return NULL;
            }

            if(pRegObjInfo->GetFunPtr()!=NULL)
            {
                Object* pObj = dynamic_cast<Object*> (pRegObjInfo->GetFunPtr()());
                return pObj;
            }
            else
            {
                return NULL;
            }
        }

        bool IsExist(const Type& unObjType) const
        {
            typename std::map<Type, RegObjInfo<Type> *>::const_iterator iterator;
            iterator = m_regHelperMap.find(unObjType);
            return (iterator == m_regHelperMap.end()) ? false : true;
        }

        bool RegisterCreateHelper(const Type& unObjType,const RegObjInfo<Type>& regInfo) 
        {
            //��������жϣ���������ָ��
            if(regInfo.GetFunPtr() == NULL)
            {
                return false;
            }

            //����ע��,����Ѿ����ڣ��򸲸���ǰ��ע����Ϣ�����и���
            typename std::map<Type,RegObjInfo<Type>* >::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator != m_regHelperMap.end())
            {
                UnRegisterCreateHelper(unObjType);
            }
            RegObjInfo<Type>* pNewObjInfo = new RegObjInfo<Type>;
            *pNewObjInfo = regInfo;

            m_regHelperMap.insert(std::make_pair(unObjType,pNewObjInfo));
            return true;
        }

        bool UnRegisterCreateHelper(const Type& unObjType) 
        {
            typename std::map<Type,RegObjInfo<Type>*>::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator == m_regHelperMap.end())
            {
                return false;
            }
            else
            {
                RegObjInfo<Type>* pObjInfo = (*iterator).second;
                m_regHelperMap.erase(iterator);
                if(pObjInfo != NULL)
                {
                    delete pObjInfo;
                }

                return true;
            }
        }


        const RegObjInfo<Type>* FindCreateHelper(const Type& unObjType) const
        {
            typename std::map<Type,RegObjInfo<Type>*>::const_iterator iterator = m_regHelperMap.find(unObjType);
            if(iterator == m_regHelperMap.end())
            {
                return NULL;
            }
            else
            {
                return (*iterator).second;
            }
        }

        virtual ~ObjectFactory()
        {
            typename std::map<Type,RegObjInfo<Type>*>::iterator iterator;
            typename std::map<Type,RegObjInfo<Type>*>::iterator endIterator = m_regHelperMap.end();
            for(iterator = m_regHelperMap.begin(); iterator != endIterator; iterator++ )
            {
                RegObjInfo<Type>* pObjInfo = (*iterator).second;
                if(pObjInfo != NULL)
                {
                    delete pObjInfo;
                }
            }

            //�������ע����
            m_regHelperMap.clear();
        }

        typename std::map<Type, RegObjInfo<Type>*>::iterator begin()
        {
            return m_regHelperMap.begin();
        }

        typename std::map<Type, RegObjInfo<Type>*>::iterator end()
        {
            return m_regHelperMap.end();
        }

    private:
        std::map<Type,RegObjInfo<Type>*> m_regHelperMap;  //����ע����Ϣ��
        unsigned int m_type;                               //�೧������

    };

GFCENGINE_NAMESPACE_END

#endif