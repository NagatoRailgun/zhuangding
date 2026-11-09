#ifndef OPTIONCLASS_H
#define OPTIONCLASS_H


class OptionClass
{
public:
    typedef enum{
        PRIORITY_TYPE_RANDOM,//随机
        PRIORITY_TYPE_UNSELECTED,//未选中的
        PRIORITY_TYPE_LEVEL,//优先级设置
    }PRIORITY_TYPE;
    typedef enum{
        INHERITREPEAT_TYPETYPE_ABLE,//重复次数继承
        INHERITREPEAT_TYPE_TYPE_DISABLE,//重复次数不继承
    }INHERITREPEAT_TYPE;
    typedef enum{
        GENDER_TYPE_ALL,//全部
        GENDER_TYPE_MALE,//男生
        GENDER_TYPEFEMALE, //女生
    }GENDER_TYPE;
public:
    OptionClass();
    PRIORITY_TYPE getPriority();
    void setPriority(PRIORITY_TYPE type);
    void setPriority(int type);
    INHERITREPEAT_TYPE getInheritRepeat();
    void setInheritRepeat(INHERITREPEAT_TYPE type);
    void setInheritRepeat(int type);
    GENDER_TYPE getGender();
    void setGender(GENDER_TYPE type);
    void setGender(int type);
private:
    PRIORITY_TYPE priority;
    INHERITREPEAT_TYPE inheritRepeat;
    GENDER_TYPE gender;
};

#endif // OPTIONCLASS_H
