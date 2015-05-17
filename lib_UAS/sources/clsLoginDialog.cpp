#include <nspGUI.h>

nspGUI::clsLoginDialog::clsLoginDialog(
        nspCore::clsLoginEngine *ptrNewLoginEngine,
        QWidget *ptrParent) : QDialog(ptrParent)
{
    ptrLoginEngine = ptrNewLoginEngine;

    ptrUserNickNameLabel = new QLabel("Никнейм");
    ptrUserNickNameEdit = new QLineEdit;

    ptrPasswordLabel = new QLabel("Пароль");
    ptrPasswordEdit = new nspCustomClasses::clsPasswordLineEdit;
    ptrSetPasswordVisibleButton = new nspCustomClasses::clsVisibilityButton;
    connect(ptrSetPasswordVisibleButton,
            SIGNAL(signalClicked(bool)),
            ptrPasswordEdit,
            SLOT(slotSetTextVisible(bool))
            );

    ptrLoginButton = new QPushButton("Вход");
    ptrLoginButton->setDefault(true);
    connect(ptrLoginButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotLoginButtonClicked())
            );

    ptrLayout = new QGridLayout;
    ptrLayout->addWidget(ptrUserNickNameLabel, 0, 0);
    ptrLayout->addWidget(ptrUserNickNameEdit, 0, 1);
    ptrLayout->addWidget(ptrPasswordLabel, 1, 0);
    ptrLayout->addWidget(ptrPasswordEdit, 1, 1);
    ptrLayout->addWidget(ptrSetPasswordVisibleButton, 1, 2);
    ptrLayout->addWidget(ptrLoginButton, 2, 0, 1, 2);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить диалогу растягиваться

    this->setLayout(ptrLayout);
    this->setWindowTitle("Вход");
}

void nspGUI::clsLoginDialog::slotLoginButtonClicked()
{
    switch (ptrLoginEngine->logIn(ptrUserNickNameEdit->text(), ptrPasswordEdit->text()))
    {
    case nspUAS::loginMessage_accessGranted:
        this->close();
        break;

    case nspUAS::loginMessage_accessGrantedButPasswordNotSet:
        (new nspGUI::clsPasswordSetDialog(ptrLoginEngine->getCurrentUser(), this))->exec();
        // Если диалог установки пароля будет проигнорирован, пользователь будет сменён на гостя
        if(ptrLoginEngine->getCurrentUser()->getPassword() == "")
        {
            ptrLoginEngine->logOut();
        }
        this->close();
        break;

    case nspUAS::loginMessage_noSuchUser:
        (new nspCustomClasses::clsMessageBox("Ошибка", "Нет такого пользователя!", this))->exec();
        break;

    case nspUAS::loginMessage_userBlocked:
        (new nspCustomClasses::clsMessageBox("Ошибка", "Пользователь заблокирован!", this))->exec();
        break;

    case nspUAS::loginMessage_passwordIncorrect:
    {
        QString message;
        message.append("Введён неверный пароль! Осталось попыток: ");
        message.append(QString::number(3 - ptrLoginEngine->getLoginAttempt()));
        if(ptrLoginEngine->getLoginAttempt() == 3)
        {
            message.clear();
            message.append("Программа будет закрыта!");
        }
        (new nspCustomClasses::clsMessageBox("Ошибка", message, this))->exec();
        if(ptrLoginEngine->getLoginAttempt() == 3)
        {
            emit this->signalBlockApplication();
        }
        break;
    }

    default:
        (new nspCustomClasses::clsMessageBox("Ошибка", "Неизвестная ошибка!", this))->exec();
        break;
    }
}
