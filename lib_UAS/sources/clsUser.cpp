#include <nspCore.h>

nspCore::clsUser::clsUser()
{

}

nspCore::clsUser::clsUser(QString userNickName,
                          QString userPassword,
                          nspUAS::enmGroups userGroupIdentificator,
                          bool isPasswordRestricted,
                          bool isUserBlocked)
{
    ptrNickName = new QString(userNickName);
    ptrPassword = new QString(userPassword);
    groupIdentificator = userGroupIdentificator;
    flagIsPasswordRestricted = isPasswordRestricted;
    flagIsUserBlocked = isUserBlocked;
}

nspCore::clsUser::clsUser(QString userNickName)
{
    ptrNickName = new QString(userNickName);
    ptrPassword = new QString("");
    groupIdentificator = nspUAS::groups_user;
    flagIsPasswordRestricted = false;
    flagIsUserBlocked = false;
}

QString nspCore::clsUser::getNickName() const
{
    return *ptrNickName;
}

nspUAS::enmGroups nspCore::clsUser::getGroupIdentificator() const
{
    return groupIdentificator;
}

QString nspCore::clsUser::getPassword() const
{
    return *ptrPassword;
}

nspUAS::enmSetPasswordMessages nspCore::clsUser::setPassword(
        QString oldPassword,
        QString newPassword)
{
    nspUAS::enmSetPasswordMessages setPasswordMessage;
    // Если старый пароль введён верно
    if(oldPassword == *ptrPassword)
    {
        // Если новый пароль не пустой
        if(newPassword != "")
        {
            // Если старый и новый пароль не идентичны
            if(oldPassword != newPassword)
            {
                // Если пароль пользователя ограничен
                if(flagIsPasswordRestricted)
                {
                    // Если пароль соответствует ограничению
                    // В пароле д.б. строчные, прописные и знаки препинания
                    if(
                            (newPassword.contains(QRegularExpression(QString("[a-z]"))))
                            &&
                            (newPassword.contains(QRegularExpression(QString("[A-Z]"))))
                            &&
                            (newPassword.contains(QRegularExpression(QString("[!@#$%^&*()_+.,-:]"))))
                            )
                    {
                        // Меняем пароль
                        ptrPassword->clear();
                        ptrPassword->append(newPassword);
                        setPasswordMessage = nspUAS::passwordMessage_success;
                    }
                    else
                    {
                        setPasswordMessage = nspUAS::passwordMessage_newPasswordMismatchRestrictions;
                    }
                }
                else
                {
                    // Меняем пароль
                    ptrPassword->clear();
                    ptrPassword->append(newPassword);
                    setPasswordMessage = nspUAS::passwordMessage_success;
                }
            }
            else
            {
                setPasswordMessage = nspUAS::passwordMessage_oldPasswordAndNewPasswordTheSame;
            }
        }
        else
        {
            setPasswordMessage = nspUAS::passwordMessage_newPasswordEmpty;
        }
    }
    else
    {
        setPasswordMessage = nspUAS::passwordMessage_oldPasswordIncorrect;
    }
    return setPasswordMessage;
}

bool nspCore::clsUser::getIsPasswordRestricted() const
{
    return flagIsPasswordRestricted;
}

bool nspCore::clsUser::getIsUserBlocked() const
{
    return flagIsUserBlocked;
}

void nspCore::clsUser::setIsPasswordRestricted(
        bool on)
{
    flagIsPasswordRestricted = on;
}

void nspCore::clsUser::setIsUserBlocked(
        bool on)
{
    flagIsUserBlocked = on;
}
