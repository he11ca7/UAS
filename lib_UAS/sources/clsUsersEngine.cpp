#include <nspCore.h>

nspCore::clsUsersEngine::clsUsersEngine(
        QObject *ptrParent) : QObject(ptrParent)
{
    ptrVectorUsers = new QVector<nspCore::clsUser *>;
    ptrFile = new QFile("usersEngineData.file");
}

void nspCore::clsUsersEngine::saveVectorUsersToFile()
{
    /*if (ptrFile->open(QIODevice::WriteOnly | QIODevice::Truncate)) ptrFile->close();*/    // Очищаем файл
    ptrFile->open(QIODevice::WriteOnly);
    QDataStream out(ptrFile);
    out.setVersion(QDataStream::Qt_4_3);
    for(int usersCounter = 0; usersCounter < ptrVectorUsers->size(); usersCounter++)
    {
        out << *ptrVectorUsers->at(usersCounter);
    }
    ptrFile->close();
}

void nspCore::clsUsersEngine::loadVectorUsersFromFile()
{
    if (ptrFile->open(QIODevice::ReadOnly))
    {
        // Файл есть
        ptrVectorUsers->clear();
        QDataStream in(ptrFile);
        in.setVersion(QDataStream::Qt_4_3);
        while(!in.atEnd())
        {
            nspCore::clsUser *ptrUser = new nspCore::clsUser;
            in >> *ptrUser;
            ptrVectorUsers->append(ptrUser);
        }
    }
    else
    {
        // Файла нет
        this->addUser(new nspCore::clsUser("guest", "guest", nspUAS::groups_guest));
        this->addUser(new nspCore::clsUser("admin", "", nspUAS::groups_adminisrator, false));
    }
    ptrFile->close();
}

void nspCore::clsUsersEngine::addUser(nspCore::clsUser *ptrNewUser)
{
    // Добавляем, если пользователя с таким ником нет
    if(!isUserExists(ptrNewUser->getNickName()))
    {
        ptrVectorUsers->append(ptrNewUser);
    }
    emit this->signalVectorUsersModified();
}

void nspCore::clsUsersEngine::removeUser(
        int userIdentificator)
{
    ptrVectorUsers->remove(userIdentificator);
    emit this->signalVectorUsersModified();
}

nspCore::clsUser *nspCore::clsUsersEngine::getUser(
        QString userNickName)
{
    int userIdentificator = 0;
    for(int accountsCounter = 0; accountsCounter < ptrVectorUsers->size(); accountsCounter++)
    {
        if(ptrVectorUsers->at(accountsCounter)->getNickName() == userNickName)
        {
            userIdentificator = accountsCounter;
            break;
        }
    }
    return ptrVectorUsers->at(userIdentificator);
}

nspCore::clsUser *nspCore::clsUsersEngine::getUser(
        int userIdentificator)
{
    return ptrVectorUsers->at(userIdentificator);
}

bool nspCore::clsUsersEngine::isUserExists(
        QString userNickName)
{
    bool flagUserExists = false;
    for(int accountsCounter = 0; accountsCounter < ptrVectorUsers->size(); accountsCounter++)
    {
        if(ptrVectorUsers->at(accountsCounter)->getNickName() == userNickName)
        {
            flagUserExists = true;
            break;
        }
    }
    return flagUserExists;
}

int nspCore::clsUsersEngine::getUsersCount()
{
    return ptrVectorUsers->size();
}
