#include <nspCore.h>

nspCore::clsLoginEngine::clsLoginEngine(
        nspCore::clsUsersEngine *ptrNewUsersEngine,
        QObject *ptrParent) : QObject(ptrParent)
{
    loginAttempt = 0;
    ptrUsersEngine = ptrNewUsersEngine;
}

nspUAS::enmLoginEngineMessages nspCore::clsLoginEngine::logIn(
        QString nickname,
        QString password)
{
    nspUAS::enmLoginEngineMessages loginEngineMessage;
    if(ptrUsersEngine->isUserExists(nickname))
    {
        if(!ptrUsersEngine->getUser(nickname)->getIsUserBlocked())
        {
            if(ptrUsersEngine->getUser(nickname)->getPassword() == password)
            {
                loginAttempt = 0;
                this->setCurrentUser(ptrUsersEngine->getUser(nickname));
                if(!(ptrUsersEngine->getUser(nickname)->getPassword() == ""))
                {
                    loginEngineMessage = nspUAS::loginMessage_accessGranted;
                }
                else
                {
                    loginEngineMessage = nspUAS::loginMessage_accessGrantedButPasswordNotSet;
                }
            }
            else
            {
                loginEngineMessage = nspUAS::loginMessage_passwordIncorrect;
                loginAttempt++;
            }
        }
        else
        {
            loginEngineMessage = nspUAS::loginMessage_userBlocked;
        }
    }
    else
    {
        loginEngineMessage = nspUAS::loginMessage_noSuchUser;
    }
    return loginEngineMessage;
}

void nspCore::clsLoginEngine::logOut()
{
    this->setCurrentUser(ptrUsersEngine->getUser(0));
}

int nspCore::clsLoginEngine::getLoginAttempt()
{
    return loginAttempt;
}

void nspCore::clsLoginEngine::setCurrentUser(
        nspCore::clsUser *ptrUser)
{
    ptrCurrentUser = ptrUser;
    emit signalCurrentUserUpdated();
}

nspCore::clsUser *nspCore::clsLoginEngine::getCurrentUser()
{
    return ptrCurrentUser;
}

void nspCore::clsLoginEngine::slotLogOut()
{
    this->logOut();
}
