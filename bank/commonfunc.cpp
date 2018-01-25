#include "commonfunc.h"


CommonFunc::CommonFunc()
{

}

bool CommonFunc::isAllNumber(QString str)
{
    for(int i=0;i<str.length();i++){
        if(str[i]>'9'||str[i]<'0')
            return false;
    }
    if(str.length()==0)
        return false;
    return true;
}
