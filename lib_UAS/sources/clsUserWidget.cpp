#include <nspGUI.h>

nspGUI::clsUserWidget::clsUserWidget(
        nspCore::clsLoginEngine *ptrNewLoginEngine,
        QWidget *ptrParent) : QWidget(ptrParent)
{
    ptrLoginEngine = ptrNewLoginEngine;
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            this,
            SLOT(slotUpdateWidgets())
            );

    ptrWelcomeLabel = new QLabel;

    ptrLoginButton = new QPushButton("Вход");
    connect(ptrLoginButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotLoginButtonClicked())
            );
    ptrChangePasswordButton = new QPushButton("Сменить пароль");
    connect(ptrChangePasswordButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotChangePasswordButtonClicked())
            );
    ptrLogOutButton = new QPushButton("Выход");
    connect(ptrLogOutButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotLogOutButtonClicked())
            );

    ptrGroupBoxLayout = new QVBoxLayout;
    ptrGroupBoxLayout->addWidget(ptrWelcomeLabel);
    ptrGroupBoxLayout->addWidget(ptrLoginButton);
    ptrGroupBoxLayout->addWidget(ptrChangePasswordButton);
    ptrGroupBoxLayout->addWidget(ptrLogOutButton);

    ptrGroupBox = new QGroupBox("Пользователь");
    ptrGroupBox->setLayout(ptrGroupBoxLayout);

    ptrLayout = new QVBoxLayout;
    ptrLayout->addWidget(ptrGroupBox);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить виджету растягиваться

    this->setLayout(ptrLayout);
}

void nspGUI::clsUserWidget::slotLoginButtonClicked()
{
    nspGUI::clsLoginDialog *ptrLoginDialog = new nspGUI::clsLoginDialog(ptrLoginEngine, this);
    connect(ptrLoginDialog,
            SIGNAL(signalBlockApplication()),
            this,
            SIGNAL(signalBlockApplication())
            );
    ptrLoginDialog->exec();
}

void nspGUI::clsUserWidget::slotLogOutButtonClicked()
{
    ptrLoginEngine->logOut();
}

void nspGUI::clsUserWidget::slotChangePasswordButtonClicked()
{
    (new nspGUI::clsPasswordChangeDialog(ptrLoginEngine->getCurrentUser(), this))->exec();
}

void nspGUI::clsUserWidget::slotUpdateWidgets()
{
    QString welcomeString;
    welcomeString.append("Привет, ");
    welcomeString.append(ptrLoginEngine->getCurrentUser()->getNickName());
    welcomeString.append("!");
    ptrWelcomeLabel->setText(welcomeString);

    if(ptrLoginEngine->getCurrentUser()->getGroupIdentificator() == nspUAS::groups_guest)
    {
        ptrLoginButton->setVisible(true);
        ptrLogOutButton->setVisible(false);
        ptrChangePasswordButton->setVisible(false);
    }
    else
    {
        ptrLoginButton->setVisible(false);
        ptrLogOutButton->setVisible(true);
        ptrChangePasswordButton->setVisible(true);
    }
}
