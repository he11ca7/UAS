#include <nspGUI.h>

nspGUI::clsUsersWidget::clsUsersWidget(
        nspCore::clsLoginEngine *ptrNewLoginEngine,
        nspCore::clsUsersEngine *ptrNewUsersEngine,
        nspCore::clsGroupsEngine *ptrNewGroupsEngine,
        QWidget *ptrParent) : QWidget(ptrParent)
{
    ptrLoginEngine = ptrNewLoginEngine;
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            this,
            SLOT(slotUpdateWidgets())
            );
    ptrUsersEngine = ptrNewUsersEngine;
    connect(ptrUsersEngine,
            SIGNAL(signalVectorUsersModified()),
            this,
            SLOT(slotUpdateWidgets())
            );
    ptrGroupsEngine = ptrNewGroupsEngine;

    ptrStatusLabel = new QLabel("<center>Недостаточно полномочий<br/>для работы со списком пользователей!</center>");
    ptrUsersScrollArea = new nspCustomClasses::clsGridScrollAreaWidget;
    ptrUsersListGroupBoxLayout = new QGridLayout;
    ptrUsersListGroupBoxLayout->addWidget(ptrUsersScrollArea);
    ptrUsersListGroupBox = new QGroupBox("Список пользователей");
    ptrUsersListGroupBox->setLayout(ptrUsersListGroupBoxLayout);

    ptrAddUserButton = new QPushButton("Добавить");
    connect(ptrAddUserButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotAddUserButtonClicked())
            );

    ptrGroupBoxLayout = new QVBoxLayout;
    ptrGroupBoxLayout->addWidget(ptrStatusLabel);
    ptrGroupBoxLayout->addWidget(ptrUsersListGroupBox);
    ptrGroupBoxLayout->addWidget(ptrAddUserButton);
    ptrGroupBox = new QGroupBox("Пользователи");
    ptrGroupBox->setLayout(ptrGroupBoxLayout);

    ptrLayout = new QVBoxLayout;
    ptrLayout->addWidget(ptrGroupBox);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить виджету растягиваться

    this->setLayout(ptrLayout);
}

void nspGUI::clsUsersWidget::slotUpdateWidgets()
{
    // Очистить лэйаут
    // Уберём виджеты
    ptrUsersScrollArea->clear();

    // Перерисуем в зависимости от ситуации
    if(ptrGroupsEngine->getGroup(ptrLoginEngine->getCurrentUser()->getGroupIdentificator())->getIsAdditionalRights())
    {
        ptrUsersListGroupBox->setVisible(true);
        ptrStatusLabel->setVisible(false);
        ptrAddUserButton->setEnabled(true);

        for(int accountsCounter = 1; accountsCounter < ptrUsersEngine->getUsersCount(); accountsCounter++)
        {
            nspGUI::clsUserSettingsButton *ptrChangeUserAccountButton = new nspGUI::clsUserSettingsButton(ptrUsersEngine->getUser(accountsCounter));
            ptrUsersScrollArea->addWidget(ptrChangeUserAccountButton, accountsCounter, 0);
            connect(ptrChangeUserAccountButton,
                    SIGNAL(signalClicked(nspCore::clsUser*)),
                    this,
                    SLOT(slotChangeUserAccountButtonClicked(nspCore::clsUser*))
                    );
            ptrUsersScrollArea->addWidget(new QLabel(ptrUsersEngine->getUser(accountsCounter)->getNickName()), accountsCounter, 1);
        }
    }
    else
    {
        ptrUsersListGroupBox->setVisible(false);
        ptrStatusLabel->setVisible(true);
        ptrAddUserButton->setEnabled(false);
    }
}

void nspGUI::clsUsersWidget::slotAddUserButtonClicked()
{
    (new nspGUI::clsAddUserDialog(ptrUsersEngine, this))->exec();
}

void nspGUI::clsUsersWidget::slotChangeUserAccountButtonClicked(
        nspCore::clsUser *ptrUser)
{
    (new nspGUI::clsUserSettingsDialog(ptrUser, this))->exec();
}
