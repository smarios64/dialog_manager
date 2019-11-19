#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <vector>
#include <libxml/parser.h>

class DialogEntry;
class Condition;

class DialogManager
{
public:
    static DialogManager *Instance();

    void parse(const char *xmlFile);
    DialogEntry *advance();
    DialogEntry *current();
    void reset();

private:
    DialogManager();
    DialogEntry *parseNode(xmlNode *node);

    DialogEntry *m_curDialog;
    std::vector<DialogEntry*> m_dialogEntries;
    std::vector<Condition*> m_conditions;
};

#endif // DIALOG_MANAGER_H