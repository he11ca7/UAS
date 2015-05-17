#include <nspCore.h>

nspCore::clsGroupsEngine::clsGroupsEngine(
        QObject *ptrParent) : QObject(ptrParent)
{
    ptrVectorGroups = new QVector<nspCore::clsGroup *>;

    this->addGroup(nspUAS::groups_guest,
                   new nspCore::clsGroup("Гости",
                                         false));
    this->addGroup(nspUAS::groups_user,
                   new nspCore::clsGroup("Пользователи",
                                         false));
    this->addGroup(nspUAS::groups_adminisrator,
                   new nspCore::clsGroup("Администраторы",
                                         true));
}

void nspCore::clsGroupsEngine::addGroup(
        nspUAS::enmGroups groupIdentificator,
        nspCore::clsGroup *ptrNewGroup)
{
    // Добавляем, если группы с таким именем нет
    bool flagGroupExists = false;
    for(int groupsCounter = 0; groupsCounter < ptrVectorGroups->size(); groupsCounter++)
    {
        if(ptrVectorGroups->at(groupsCounter)->getName() == ptrNewGroup->getName())
        {
            flagGroupExists = true;
            return;
        }
    }
    if(!flagGroupExists)
    {
        ptrVectorGroups->insert(groupIdentificator, ptrNewGroup);
    }
}

nspCore::clsGroup *nspCore::clsGroupsEngine::getGroup(
        nspUAS::enmGroups groupIdentificator)
{
    return ptrVectorGroups->at(groupIdentificator);
}
