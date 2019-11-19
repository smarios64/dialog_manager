#ifndef CONDITION_H
#define CONDITION_H

#include <cassert>

#include "console_message.h"

class Condition 
{
public:
    Condition() 
    {
        CONSOLE_INFO("Instantiating Condition [%p]...", this);
    }

    ~Condition() 
    {
        CONSOLE_INFO("Destroying Condition [%p]...", this);
    }

    virtual bool fulfilled() { return true; }
};

/////////////////////////////////////////////////////////

template <class T>
class EqualityCondition : public Condition
{
public:
    EqualityCondition(T *value_p, T targetValue) :
        Condition(),
        m_value(value_p),
        m_targetValue(targetValue)
    {
        assert(value_p != nullptr);
    }

    virtual bool fulfilled() { return *m_value == m_targetValue; }
    T *value() const { return m_value; }

protected:
    T *m_value;
    T m_targetValue;
};

/////////////////////////////////////////////////////////

template <class T>
class GreaterThanCondition : public EqualityCondition<T>
{
public:
    GreaterThanCondition(T *value_p, T targetValue)
        : EqualityCondition<T>(value_p, targetValue) { }
    virtual bool fulfilled() { return *this->m_value > this->m_targetValue; }
};

/////////////////////////////////////////////////////////

template <class T>
class LessThanCondition : public EqualityCondition<T>
{
public:
    LessThanCondition(T *value_p, T targetValue) 
        : EqualityCondition<T>(value_p, targetValue) { }
    virtual bool fulfilled() { return *this->m_value < this->m_targetValue; }
};

/////////////////////////////////////////////////////////

class CompoundCondition : public Condition
{
public:
    CompoundCondition(Condition *cond1, Condition *cond2) :
        Condition(),
        m_condition1(cond1),
        m_condition2(cond2)
    {
        assert(cond1 != nullptr);
        assert(cond2 != nullptr);
    }
    virtual bool fulfilled() { return m_condition1->fulfilled() && m_condition2->fulfilled(); }
    
private:
    Condition *m_condition1;
    Condition *m_condition2;
};

#endif // CONDITION_H