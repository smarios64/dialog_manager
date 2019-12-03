#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H

#include <map>
#include <cassert>
#include <string>

#include "console_message.h"

class VariableManager {
public:
    static VariableManager *Instance()
    {
        static VariableManager instance;
        return &instance;
    }

    void registerVariable(const char *name, void *variable)
    {
        std::map<std::string, void*>::iterator it = m_vars.find(name);
        assert(it == m_vars.end() || variable == it->second);
        m_vars[name] = variable;
        CONSOLE_INFO("Registered [\"%s\": %p].", name, variable);
    }

    void deregisterVariable(const char *name)
    {
        std::map<std::string, void*>::iterator it = m_vars.find(name);
        if (it != m_vars.end()) {
            CONSOLE_INFO("Deregistered [\"%s\": %p].", name, it->second);
            m_vars.erase(it);
        }
    }

    void *getVariable(const char *name)
    {
        std::map<std::string, void*>::iterator it = m_vars.find(name);
        return it->second;
    }

private:
    VariableManager() 
    {
        CONSOLE_INFO("Instantiating VariableManager [%p]...", this);
    }
    ~VariableManager()
    {
        CONSOLE_INFO("Destroying VariableManager [%p]...", this);
    }
    
    std::map<std::string, void*> m_vars;
};

#endif // VARIABLE_MANAGER_H