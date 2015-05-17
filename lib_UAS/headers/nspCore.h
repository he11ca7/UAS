#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QRegularExpression>
#include <QFile>
#include <QDataStream>
#include <QIODevice>

#include <QDebug>

#include <nspUAS.h>

namespace nspCore
{
    /*!
     * \brief The clsGroup class
     */
    class clsGroup
    {
    private:

        QString     *ptrName;
        bool        flagAdditionalRights;

    public:

        clsGroup(
                QString groupName,
                bool isFlagAdditionalRights);

        QString getName();

        bool getIsAdditionalRights();
    };

    /*!
     * \brief The clsGroupsEngine class
     */
    class clsGroupsEngine : public QObject
    {
        Q_OBJECT

    private:

        QVector<nspCore::clsGroup *>    *ptrVectorGroups;

    public:

        clsGroupsEngine(
                QObject *ptrParent = NULL);

        void addGroup(
                nspUAS::enmGroups groupIdentificator,
                nspCore::clsGroup *ptrNewGroup);
        nspCore::clsGroup *getGroup(
                nspUAS::enmGroups groupIdentificator);
    };

    /*!
     * \brief The clsUser class
     */
    class clsUser
    {
    private:

        QString             *ptrNickName,
                            *ptrPassword;
        nspUAS::enmGroups   groupIdentificator;
        bool                flagIsPasswordRestricted,
                            flagIsUserBlocked;

    public:

        clsUser();

        clsUser(
                QString userNickName,
                QString userPassword,
                nspUAS::enmGroups userGroupIdentificator,
                bool isPasswordRestricted = true,
                bool isUserBlocked = false);

        clsUser(
                QString userNickName);

        QString getNickName() const;

        nspUAS::enmGroups getGroupIdentificator() const;

        QString getPassword() const;
        nspUAS::enmSetPasswordMessages setPassword(
                QString oldPassword,
                QString newPassword);

        bool getIsPasswordRestricted() const;
        void setIsPasswordRestricted(
                bool on);

        bool getIsUserBlocked() const;
        void setIsUserBlocked(
                bool on);
    };

    /*!
     * \brief The clsUsersEngine class
     */
    class clsUsersEngine : public QObject
    {
        Q_OBJECT

    private:

        QVector<nspCore::clsUser *> *ptrVectorUsers;
        QFile                       *ptrFile;

    public:

        clsUsersEngine(
                QObject *ptrParent = NULL);

        void saveVectorUsersToFile();
        void loadVectorUsersFromFile();

        void addUser(
                nspCore::clsUser *ptrNewUser);
        void removeUser(
                int userIdentificator);

        nspCore::clsUser *getUser(
                QString userNickName);
        nspCore::clsUser *getUser(
                int userIdentificator);

        bool isUserExists(
                QString userNickName);
        int getUsersCount();

    signals:

        void signalVectorUsersModified();
    };

    /*!
     * \brief The clsLoginEngine class
     */
    class clsLoginEngine : public QObject
    {
        Q_OBJECT

    private:

        int loginAttempt;

        nspCore::clsUsersEngine  *ptrUsersEngine;
        nspCore::clsUser         *ptrCurrentUser;

        void setCurrentUser(
                nspCore::clsUser *ptrUser);

    public:

        clsLoginEngine(
                nspCore::clsUsersEngine  *ptrNewUsersEngine,
                QObject *ptrParent = NULL);

        nspUAS::enmLoginEngineMessages logIn(
                QString nickname,
                QString password);
        void logOut();

        int getLoginAttempt();

        nspCore::clsUser *getCurrentUser();

    public slots:

        void slotLogOut();

    signals:

        void signalCurrentUserUpdated();
    };
}

QDataStream &operator >>(QDataStream &in, nspUAS::enmGroups &group);
QDataStream &operator <<(QDataStream &out, const nspCore::clsUser &user);
QDataStream &operator >>(QDataStream &in, nspCore::clsUser &user);
