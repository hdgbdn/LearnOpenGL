#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace hdgbdn
{
	template<typename T>
    class Singleton
    {
    public:
        static T* GetInstance(){
            if(nullptr == m_instance)
                m_instance = new T();
            return m_instance;
        }
    protected:
        Singleton() = default;
        inline static T* m_instance;
        
        Singleton(Singleton &other) = delete;
        void operator=(const Singleton &) = delete;
    };
}

#endif