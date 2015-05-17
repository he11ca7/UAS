#include <nspCore.h>

QDataStream &operator <<(QDataStream &out, const nspCore::clsUser &ptrUser)
{
    out
            << ptrUser.getNickName()
            << ptrUser.getPassword()
            << ptrUser.getGroupIdentificator()
            << ptrUser.getIsPasswordRestricted()
            << ptrUser.getIsUserBlocked();
    return out;
}

QDataStream &operator >>(QDataStream &in, nspCore::clsUser &user)
{
    QString             nickName,
                        password;
    nspUAS::enmGroups   groupIdentificator;
    bool                flagIsPasswordRestricted,
                        flagIsUserBlocked;
    in
            >> nickName
            >> password
            >> groupIdentificator
            >> flagIsPasswordRestricted
            >> flagIsUserBlocked;
    user = nspCore::clsUser(nickName, password, groupIdentificator, flagIsPasswordRestricted, flagIsUserBlocked);
    return in;
}

// Напиши такой же метод, но для <<
QDataStream &operator >>(QDataStream &in, nspUAS::enmGroups &group)
{
    /*in >> ((quint32)&group);*/ //Anything wrong with this? It certainly feels dirty

    quint32 buffer;
    in >> buffer;
    group = nspUAS::enmGroups(buffer);

    return in;
}
