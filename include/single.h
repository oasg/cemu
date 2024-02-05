
#ifndef HEADER_SINGLE
#define HEADER_SINGLE
#include <memory>
#include <mutex>
template <typename T>
class Single_T
{
protected:
    Single_T() = default;
    Single_T(const Single_T<T> &st) = delete;
    Single_T &operator=(const Single_T<T> &st) = delete;
    ~Single_T()
    {
        //auto destruct
    }
public:
    static std::shared_ptr<T> GetInst()
    {
        if (single != nullptr)
        {
            return single;
        }
        s_mutex.lock();
        if (single != nullptr)
        {
            s_mutex.unlock();
            return single;
        }
        single = std::shared_ptr<T>(new T);
        s_mutex.unlock();
        return single;
    }
private:
    static std::shared_ptr<T> single;
    static std::mutex s_mutex;
};
#endif