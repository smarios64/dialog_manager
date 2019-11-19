#ifndef DIALOG_ENTRY_H
#define DIALOG_ENTRY_H

#include <string>
#include <vector>

#include "console_message.h"
#include "condition.h"

class DialogEntry {
public:
    DialogEntry(std::string text = "", Condition *condition = nullptr);
    ~DialogEntry();

    DialogEntry *response();
    std::string text() { return m_text; }
    void setText(std::string text) { m_text = text; }
    void setCondition(Condition *condition);
    void appendResponse(DialogEntry *response);

private:
    static Condition defaultCondition;
    Condition *m_condition;
    std::vector<DialogEntry*> m_responses;
    std::string m_text;
};

#endif // DIALOG_ENTRY_H