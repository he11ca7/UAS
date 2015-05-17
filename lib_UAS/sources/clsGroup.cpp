#include <nspCore.h>

nspCore::clsGroup::clsGroup(QString groupName,
        bool isFlagAdditionalRights)
{
    ptrName = new QString(groupName);
    flagAdditionalRights = isFlagAdditionalRights;
}

QString nspCore::clsGroup::getName()
{
    return *ptrName;
}

bool nspCore::clsGroup::getIsAdditionalRights()
{
    return this->flagAdditionalRights;
}
