#include "commonfunc.h"


CommonFunc::CommonFunc()
{

}

bool CommonFunc::isAllNumber(QString str)
{
    if(str.isEmpty())
        return false;
    for(int i = 0;i<str.length();i++){
        if(str[i]>'9'||str[i]<'0')
            return false;
    }
    return true;
}
