#include "optionclass.h"

OptionClass::OptionClass()
{

}

OptionClass::PRIORITY_TYPE OptionClass::getLevelPriority()
{
    return levelPriority;
}

void OptionClass::setLevelPriority(PRIORITY_TYPE type)
{
    levelPriority = type;
}

OptionClass::PRIORITY_TYPE OptionClass::getCountPriority()
{
    return countPriority;
}

void OptionClass::setCountPriority(PRIORITY_TYPE type)
{
    countPriority = type;
}

void OptionClass::setLevelPriority(int type)
{
    if(type == PRIORITY_TYPE_ABLE){
        levelPriority = PRIORITY_TYPE_ABLE;
    }else{
        levelPriority = PRIORITY_TYPE_DISABLE;
    }
}

void OptionClass::setCountPriority(int type)
{
    if(type == PRIORITY_TYPE_ABLE){
        countPriority = PRIORITY_TYPE_ABLE;
    }else{
        countPriority = PRIORITY_TYPE_DISABLE;
    }
}

OptionClass::INHERITREPEAT_TYPE OptionClass::getInheritRepeat()
{
    return inheritRepeat;
}

void OptionClass::setInheritRepeat(INHERITREPEAT_TYPE type)
{
    inheritRepeat = type;
}

void OptionClass::setInheritRepeat(int type)
{
    if(type == INHERITREPEAT_TYPE_TYPE_DISABLE){
        inheritRepeat = INHERITREPEAT_TYPE_TYPE_DISABLE;
    }else{
        inheritRepeat = INHERITREPEAT_TYPETYPE_ABLE;
    }
}

OptionClass::GENDER_TYPE OptionClass::getGender()
{
    return gender;
}

void OptionClass::setGender(GENDER_TYPE type)
{
    gender = type;
}

void OptionClass::setGender(int type)
{
    if(type == GENDER_TYPE_MALE){
        gender = GENDER_TYPE_MALE;
    }else if(type == GENDER_TYPE_FEMALE){
        gender = GENDER_TYPE_FEMALE;
    }else{
        gender = GENDER_TYPE_ALL;
    }
}
