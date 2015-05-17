#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>
#include <QMessageBox>
#include <QVector>
#include <QCheckBox>

#include <nspCore.h>
#include <nspUAS.h>
#include <nspCustomClasses.h>

namespace nspGUI
{
    /*!
     * \brief The clsLoginDialog class
     */
    class clsLoginDialog : public QDialog
    {
        Q_OBJECT

    private:

        nspCore::clsLoginEngine *ptrLoginEngine;

        QLabel                              *ptrUserNickNameLabel;
        QLineEdit                           *ptrUserNickNameEdit;

        QLabel                              *ptrPasswordLabel;
        nspCustomClasses::clsPasswordLineEdit     *ptrPasswordEdit;
        nspCustomClasses::clsVisibilityButton     *ptrSetPasswordVisibleButton;

        QPushButton                         *ptrLoginButton;
        QGridLayout                         *ptrLayout;

    public:

        clsLoginDialog(
                nspCore::clsLoginEngine *ptrNewLoginEngine,
                QWidget *ptrParent = NULL);

    private slots:

        void slotLoginButtonClicked();

    signals:

        void signalBlockApplication();
    };

    /*!
     * \brief The clsPasswordSetDialog class
     */
    class clsPasswordSetDialog : public QDialog
    {
        Q_OBJECT

    private:

        nspCore::clsUser *ptrUser;

        QLabel      *ptrNewPasswordLabel,
                    *ptrNewPasswordAgainLabel;

        nspCustomClasses::clsPasswordLineEdit   *ptrNewPasswordLineEdit,
                                                *ptrNewPasswordAgainLineEdit;

        nspCustomClasses::clsVisibilityButton   *ptrSetPasswordsVisibleButton;

        QPushButton                             *ptrSetPasswordButton;

        QGridLayout *ptrLayout;

    public:

        clsPasswordSetDialog(
                nspCore::clsUser *ptrNewUser,
                QWidget *ptrParent);

    private slots:

        void slotSetPasswordButtonClicked();
    };

    /*!
     * \brief The clsPasswordChangeDialog class
     */
    class clsPasswordChangeDialog : public QDialog
    {
        Q_OBJECT

    private:

        nspCore::clsUser *ptrUser;

        QLabel      *ptrOldPasswordLabel,
                    *ptrNewPasswordLabel,
                    *ptrNewPasswordAgainLabel;

        nspCustomClasses::clsPasswordLineEdit   *ptrOldPasswordLineEdit,
                                                *ptrNewPasswordLineEdit,
                                                *ptrNewPasswordAgainLineEdit;

        nspCustomClasses::clsVisibilityButton   *ptrSetPasswordsVisibleButton;

        QPushButton                             *ptrChangePasswordButton;

        QGridLayout *ptrLayout;

    public:

        clsPasswordChangeDialog(
                nspCore::clsUser *ptrNewUser,
                QWidget *ptrParent = NULL);

    private slots:

        void slotChangePasswordButtonClicked();
    };

    /*!
     * \brief The clsAddUserDialog class
     */
    class clsAddUserDialog : public QDialog
    {
        Q_OBJECT

    private:

        nspCore::clsUsersEngine *ptrUsersEngine;

        QLabel          *ptrNickNameLabel;

        QLineEdit       *ptrNickNameLineEdit;

        QPushButton     *ptrAddButton;

        QGridLayout     *ptrLayout;

    public:

        clsAddUserDialog(
                nspCore::clsUsersEngine *ptrNewUsersEngine,
                QWidget *ptrParent = NULL);

    private slots:

        void slotAddButtonClicked();
    };

    /*!
     * \brief The clsUserSettingsDialog class
     */
    class clsUserSettingsDialog : public QDialog
    {
        Q_OBJECT

    private:

        nspCore::clsUser    *ptrUser;

        QLabel          *ptrNickNameLabel,
                        *ptrNickNameLabelText,
                        *ptrPasswordLabel,
                        *ptrPasswordLabelText;
        QCheckBox       *ptrIsPasswordRestrictedCheckBox,
                        *ptrIsUserBlockedCheckBox;
        QPushButton     *ptrCloseButton;
        QGridLayout     *ptrLayout;

    public:

        clsUserSettingsDialog(
                nspCore::clsUser *ptrNewUser,
                QWidget *ptrParent = NULL);

    private slots:

        void slotApplySettings();
    };

    /*!
     * \brief The clsUserSettingsButton class
     */
    class clsUserSettingsButton : public QPushButton
    {
        Q_OBJECT

    private:

        nspCore::clsUser *ptrAccount;

    public:

        clsUserSettingsButton(
                nspCore::clsUser *ptrNewUser,
                QWidget *ptrParent = NULL);

    private slots:

        void slotEmitSignalClicked();

    signals:

        void signalClicked(
                nspCore::clsUser *ptrUser);
    };

    /*!
     * \brief The clsUserWidget class
     */
    class clsUserWidget : public QWidget
    {
        Q_OBJECT

    private:

        nspCore::clsLoginEngine     *ptrLoginEngine;

        QLabel          *ptrWelcomeLabel;
        QPushButton     *ptrLoginButton,
                        *ptrLogOutButton,
                        *ptrChangePasswordButton;
        QVBoxLayout     *ptrGroupBoxLayout;
        QGroupBox       *ptrGroupBox;
        QVBoxLayout     *ptrLayout;

    public:

        clsUserWidget(
                nspCore::clsLoginEngine *ptrNewLoginEngine,
                QWidget *ptrParent = NULL);

    private slots:

        void slotLoginButtonClicked();
        void slotLogOutButtonClicked();
        void slotChangePasswordButtonClicked();
        void slotUpdateWidgets();

    signals:

        void signalBlockApplication();
    };

    /*!
     * \brief The clsUsersWidget class
     */
    class clsUsersWidget : public QWidget
    {
        Q_OBJECT

    private:

        nspCore::clsLoginEngine     *ptrLoginEngine;
        nspCore::clsUsersEngine     *ptrUsersEngine;
        nspCore::clsGroupsEngine    *ptrGroupsEngine;

        QLabel          *ptrStatusLabel;

        nspCustomClasses::clsGridScrollAreaWidget   *ptrUsersScrollArea;
        QGridLayout                                 *ptrUsersListGroupBoxLayout;
        QGroupBox                                   *ptrUsersListGroupBox;

        QPushButton     *ptrAddUserButton;

        QVBoxLayout     *ptrGroupBoxLayout;
        QGroupBox       *ptrGroupBox;
        QVBoxLayout     *ptrLayout;

    public:

        clsUsersWidget(
                nspCore::clsLoginEngine *ptrNewLoginEngine,
                nspCore::clsUsersEngine *ptrNewUsersEngine,
                nspCore::clsGroupsEngine *ptrNewGroupsEngine,
                QWidget *ptrParent = NULL);

    private slots:

        void slotAddUserButtonClicked();
        void slotChangeUserAccountButtonClicked(
                nspCore::clsUser *ptrUser);

    public slots:

        void slotUpdateWidgets();
    };
}
