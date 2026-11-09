#include "optionclass.h"

OptionClass::OptionClass()
{

}

OptionClass::PRIORITY_TYPE OptionClass::getPriority()
{
    return priority;
}

void OptionClass::setPriority(PRIORITY_TYPE type)
{
    priority = type;
}

void OptionClass::setPriority(int type)
{
    if(type == PRIORITY_TYPE_UNSELECTED){
        priority = PRIORITY_TYPE_UNSELECTED;
    }else if(type == PRIORITY_TYPE_LEVEL){
        priority = PRIORITY_TYPE_LEVEL;
    }else{
        priority = PRIORITY_TYPE_RANDOM;
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
    }else if(type == GENDER_TYPEFEMALE){
        gender = GENDER_TYPEFEMALE;
    }else{
        gender = GENDER_TYPE_ALL;
    }
}
