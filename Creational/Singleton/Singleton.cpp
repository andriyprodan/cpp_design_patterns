// Singleton allows/enforces only the creation of one instance of a class.
#include <iostream>
#include <string>
#include <vector>

class Logger {
public:
    // Retrieve the single instance of the object
    // created, and we'll enforce, only 1 of these 
    // objects gets created, in our code logic
    static Logger& GetInstance() {
        // Static variables are only initialized once, and their values persist across multiple function calls. In this case, s_instance is initialized the first time GetInstance() is called and retains its value for subsequent calls.
        static Logger* s_instance = new Logger;
        return *s_instance;
    }

    void printMessages() {
        std::cout << "Accessing the log\n";
        for (std::string& s : m_messages) {
            std::cout << s << std::endl;
        }
    }

    void addMessage(std::string s) {
        m_messages.push_back(s);
    }

private:
    Logger() {
        std::cout << "Logger was created\n";
    }

    ~Logger() {
        std::cout << "Logger was destroyed\n";
    }
    
    static int numberOfLoggers;

    std::vector<std::string> m_messages;
};

int main() {
    Logger::GetInstance().addMessage("Hello");
    Logger::GetInstance().addMessage("World");
    Logger::GetInstance().printMessages();


    return 0;
}