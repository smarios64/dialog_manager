#include "dialog_entry.h"

Condition DialogEntry::defaultCondition;

DialogEntry::DialogEntry(std::string text, Condition *condition) :
    m_text(text), m_condition(condition)
{
    CONSOLE_INFO("Instantiating DialogEntry [%p]...", this);
    if(condition == nullptr) {
        m_condition = &defaultCondition;
    }
}

DialogEntry::~DialogEntry() 
{
    CONSOLE_INFO("Destroying DialogEntry [%p]...", this);
    m_condition = nullptr;
    m_responses.clear();
}

DialogEntry *DialogEntry::response()
{
    for (int i = 0; i < m_responses.size(); ++i) {
        if (m_responses[i]->m_condition->fulfilled()) {
            return m_responses[i];
        }
    }
    return nullptr;
}

void DialogEntry::setCondition(Condition *condition) 
{
    if (condition != nullptr) {
        m_condition = condition;
    }
    else {
        m_condition = &defaultCondition;
    }
}

void DialogEntry::appendResponse(DialogEntry *response)
{
    CONSOLE_INFO("Append response [%p] to DialogEntry [%p].", response, this);
    if (response != nullptr) {
        m_responses.push_back(response);
    }
}