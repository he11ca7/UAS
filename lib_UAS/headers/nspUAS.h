#pragma once

namespace nspUAS
{
    /*!
     * \brief The enmGroups enum
     */
    enum enmGroups
    {
        groups_guest,           // Гость
        groups_user,            // Пользователь
        groups_adminisrator     // Администратор
    };

    // Следующие перечисления могли быть не взаимозаменяемыми
    // Например, если разделить accessGranted и passwordNotSet

    /*!
     * \brief The enmLoginEngineMessages enum
     */
    enum  enmLoginEngineMessages
    {
        loginMessage_accessGranted,                     // Успешный вход
        loginMessage_accessGrantedButPasswordNotSet,    // Успешный вход. Необходимо сменить пароль
        loginMessage_noSuchUser,                        // Нет такого пользователя
        loginMessage_userBlocked,                       // Пользователь заблокирован
        loginMessage_passwordIncorrect                  // Неверный пароль
    };

    /*!
     * \brief The enmSetPasswordMessages enum
     */
    enum enmSetPasswordMessages
    {
        passwordMessage_success,                            // Успешная смена пароля
        passwordMessage_oldPasswordIncorrect,               // Старый пароль введён неверно
        passwordMessage_newPasswordEmpty,                   // Новый пароль пустой
        passwordMessage_oldPasswordAndNewPasswordTheSame,   // Старый и новый пароли совпадают
        passwordMessage_newPasswordMismatchRestrictions     // Пароль не удовлетворяет требованиям ограничений пароля
    };
}