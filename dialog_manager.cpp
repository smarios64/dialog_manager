#include "dialog_manager.h"
#include "dialog_entry.h"
#include "variable_manager.h"

DialogManager::DialogManager() : m_curDialog(nullptr) 
{
    CONSOLE_INFO("Instantiating DialogManager [%p]...", this);
}
DialogManager::~DialogManager() 
{
    reset();
    CONSOLE_INFO("Destroying DialogManager [%p]...", this);
}

DialogManager *DialogManager::Instance()
{
    static DialogManager instance;
    return &instance;
}

void DialogManager::parse(const char *xmlFile)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    reset();
    doc = xmlReadFile(xmlFile, NULL, 0);
    assert(doc != nullptr);
 
    root_element = xmlDocGetRootElement(doc);
    m_curDialog = parseNode(root_element);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

DialogEntry *DialogManager::parseNode(xmlNode *node)
{
    DialogEntry *dialog = nullptr;
    if (node != nullptr && xmlStrcmp(node->name, (const xmlChar*)"entry") == 0) {
        xmlChar *text = xmlGetProp(node, (const xmlChar*)"text");
        dialog = new DialogEntry();
        if (text != nullptr) {
            dialog->setText((const char*)text);
        }
        xmlFree(text);
        m_dialogEntries.push_back(dialog);
        node = node->xmlChildrenNode;
        while (node != nullptr) {
            if (xmlStrcmp(node->name, (const xmlChar*)"entry") == 0) {
                DialogEntry *nestedDialog = parseNode(node);
                if (nestedDialog != nullptr) {
                    dialog->appendResponse(nestedDialog);
                }
            }
            else if (xmlStrcmp(node->name, (const xmlChar*)"condition") == 0) {
                xmlChar *valueName = xmlGetProp(node, (const xmlChar*)"valueName");
                xmlChar *valueType = xmlGetProp(node, (const xmlChar*)"valueType");
                xmlChar *targetValue = xmlGetProp(node, (const xmlChar*)"targetValue");
                if (valueName != nullptr && valueType != nullptr && targetValue != nullptr) {
                    if (xmlStrcmp(valueType, (const xmlChar*)"int") == 0) {
                        int *value_p = (int*)VariableManager::Instance()->getVariable((const char*)valueName);
                        if (value_p != nullptr) {
                            EqualityCondition<int> *cond = new EqualityCondition<int>(value_p, atoi((const char*)targetValue));
                            m_conditions.push_back(cond);
                            dialog->setCondition(cond);
                        }
                        else {
                            CONSOLE_INFO("Unsupported condition value name [\"%s\"].", (const char*)valueName);
                        }
                    }
                    else {
                        CONSOLE_INFO("Unsupported condition value type [\"%s\"].", (const char*)valueType);
                    }
                }
                else {
                    CONSOLE_INFO("Unable to create condition due to missing 'valueName', 'valueType' or 'targetValue' attributes.");
                }
                xmlFree(valueName);
                xmlFree(valueType);
                xmlFree(targetValue);
            }
            node = node->next;
        }
    }
    return dialog;
}

DialogEntry *DialogManager::advance()
{
    if (m_curDialog != nullptr) {
        m_curDialog = m_curDialog->response();
    }
    return m_curDialog;
}

DialogEntry *DialogManager::current()
{
    return m_curDialog;
}

void DialogManager::reset() 
{
    m_curDialog = nullptr;
    for (int i = 0; i < m_dialogEntries.size(); ++i) {
        delete m_dialogEntries[i];
    }
    for (int i = 0; i < m_conditions.size(); ++i) {
        delete m_conditions[i];
    }
    m_dialogEntries.clear();
    m_conditions.clear();
}