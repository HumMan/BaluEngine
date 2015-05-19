#pragma once

//Another on delegate implementation with c++ 11 support http://habrahabr.ru/sandbox/48020/

//Container interface
template<typename... Args>
class IContainer
{
public:
    virtual void Call(Args...) {}
    virtual ~IContainer() {}
    IContainer<Args...> *next;
};

//Container realization
template< typename T, typename M, typename... Args > class MContainer : public IContainer<Args...>
{
public:
    MContainer( T* c, M m ) : mClass( c ), mMethod( m ) {}
    void Call(Args... args)
    {
        (mClass->*mMethod)( args... );
    }

private:
    T *mClass;
    M mMethod;
};

template< typename M, typename... Args > class FContainer : public IContainer<Args...>
{
public:
    FContainer( M m ) : mMethod( m ) {}
    void Call(Args... args)
    {
        (mMethod)( args... );
    }

private:
    M mMethod;
};

//Delegate
template<typename... Args>
class Delegate
{
public:
    Delegate()
    {
        mContainerHead = new IContainer<Args...>();
        mContainerTail = mContainerHead;
        mContainerHead->next = 0;
    }
    ~Delegate()
    {
        IContainer<Args...> *container = mContainerHead;
        while(container)
        {
            IContainer<Args...> *temp = container->next;
            delete container;
            container = temp;
        }
    }

    void Clear()
    {
        IContainer<Args...> *container = mContainerHead->next;
        while(container)
        {
            IContainer<Args...> *temp = container->next;
            delete container;
            container = temp;
        }
        mContainerHead->next = 0;
        mContainerTail = mContainerHead;
    }

    template<typename T, typename M>
    void Connect(T *c, M m)
    {
        mContainerTail->next = new MContainer< T, M, Args... >(c,m);
        mContainerTail->next->next = 0;
        mContainerTail = mContainerTail->next;
    }

    template<typename M>
    void Connect(M m)
    {
        mContainerTail->next = new FContainer< M, Args... >(m);
        mContainerTail->next->next = 0;
        mContainerTail = mContainerTail->next;
    }

    template<typename T, typename M>
    void Disconnect(T *c, M m)
    {
        IContainer<Args...> *container = mContainerHead;
        while(container->next)
        {
            MContainer<T, M, Args...> *temp = dynamic_cast< MContainer<T, M, Args...>* >(container->next);

            if(temp)
            {
                if(container->next == mContainerTail)
                {
                    mContainerTail = container;
                }
                container->next = container->next->next;
                delete temp;
                break;
            }
            container = container->next;
        }
    }

    template<typename M>
    void Disconnect(M m)
    {
        IContainer<Args...> *container = mContainerHead;
        while(container->next)
        {
            FContainer<M, Args...> *temp = dynamic_cast< FContainer<M, Args...>* >(container->next);

            if(temp)
            {
                if(container->next == mContainerTail)
                {
                    mContainerTail = container;
                }
                container->next = container->next->next;
                delete temp;
                break;
            }
            container = container->next;
        }
    }

    void operator ()(Args... args)
    {
        Call(args...);
    }

    void Call(Args... args)
    {
        IContainer<Args...> *container = mContainerHead;
        while(container)
        {
            container->Call(args...);
            container = container->next;
        }
    }
private:
    IContainer<Args...> *mContainerHead;
    IContainer<Args...> *mContainerTail;
};