#include <iostream>
#include <string>
#include <thread>
#include <mutex>

class Singleton {
    private:
        static Singleton* pInstance;
        static std::mutex mtx;
    protected:
        std::string value;
        Singleton(const std::string value_) : value(value_) {}
        ~Singleton() {}
    public:
        Singleton(Singleton& other) = delete;
        void operator=(const Singleton&) = delete;
        static Singleton* getInstance(const std::string& value_);
        void someBusinessLogic() {}
        std::string getValue() const {
            return value;
        }
};

Singleton* Singleton::pInstance{nullptr};
std::mutex Singleton::mtx;

Singleton* Singleton::getInstance(const std::string& value_) {
    std::lock_guard<std::mutex> lock(mtx);
    if (pInstance == nullptr) {
        pInstance = new Singleton(value_);
    }
    return pInstance;
}

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::getInstance("FOO");
    std::cout << singleton->getValue() << "\n";
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::getInstance("BAR");
    std::cout << singleton->getValue() << "\n";
}

int main() {
    std::cout << "If you see the same value, then the singleton was reused (yay!).\n" <<
        "If you see different values, then 2 singletons were created (booo!!).\n\n" <<
        "Result:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
}

/* Possible output:
If you see the same value, then the singleton was reused (yay!).
If you see different values, then 2 singletons were created (booo!!).

Result:
FOO
FOO
*/