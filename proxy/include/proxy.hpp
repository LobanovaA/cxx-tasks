/* Proxy object.
 * @file
 * @date 2018-08-07
 * @author Anonymous
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>

template<class T>
class ptr_holder
{
public:
    ptr_holder(T* ptr): ptr_(ptr) {}

    //{ describe proxy object
    class proxy : std::unique_lock<std::mutex>
    {
    public:
        proxy (T* ptr, std::mutex& mutex_): std::unique_lock<std::mutex>(mutex_), ptr_ (ptr) { }

        T* operator ->() const {
            return ptr_ ;
        }
		
    private:
        T* ptr_ ;
    };

    proxy operator -> () const
    {
        return proxy(ptr_, mutex_);
    }
    //}

private:
    T* ptr_;
    mutable std::mutex mutex_;
};

#endif // __PROXY_HPP__