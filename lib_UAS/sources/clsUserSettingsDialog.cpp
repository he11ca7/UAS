#include <nspGUI.h>

nspGUI::clsUserSettingsDialog::clsUserSettingsDialog(
        nspCore::clsUser *ptrNewUser,
        QWidget *ptrParent) : QDialog(ptrParent)
{
    ptrUser = ptrNewUser;

    ptrNickNameLabel = new QLabel("Никнейм");
    ptrNickNameLabelText = new QLabel(ptrUser->getNickName());
    ptrPasswordLabel = new QLabel("Пароль");
    QString passwordLabel;
    if(ptrUser->getPassword().size() != 0)
    {
        int charsCounter = ptrUser->getPassword().size();
        passwordLabel.fill('*', charsCounter);
    }
    else
    {
        passwordLabel.append("<b>Пароль не установлен!</b>");
    }
    ptrPasswordLabelText = new QLabel(passwordLabel);

    ptrIsPasswordRestrictedCheckBox = new QCheckBox("Ограничить пароль");
    connect(ptrIsPasswordRestrictedCheckBox,
            SIGNAL(clicked()),
            this,
            SLOT(slotApplySettings())
            );
    ptrIsPasswordRestrictedCheckBox->setChecked(ptrUser->getIsPasswordRestricted());
    ptrIsUserBlockedCheckBox = new QCheckBox("Заблокировать пользователя");
    connect(ptrIsUserBlockedCheckBox,
            SIGNAL(clicked()),
            this,
            SLOT(slotApplySettings())
            );
    ptrIsUserBlockedCheckBox->setChecked(ptrUser->getIsUserBlocked());

    ptrCloseButton = new QPushButton("Закрыть");
    connect(ptrCloseButton,
            SIGNAL(clicked()),
            this,
            SLOT(close())
            );

    ptrLayout = new QGridLayout;
    ptrLayout->addWidget(ptrNickNameLabel, 0, 0);
    ptrLayout->addWidget(ptrNickNameLabelText, 0, 1);
    ptrLayout->addWidget(ptrPasswordLabel, 1, 0);
    ptrLayout->addWidget(ptrPasswordLabelText, 1, 1);
    ptrLayout->addWidget(ptrIsPasswordRestrictedCheckBox, 2, 0, 1, 2);
    ptrLayout->addWidget(ptrIsUserBlockedCheckBox, 3, 0, 1, 2);
    ptrLayout->addWidget(ptrCloseButton, 4, 0, 1, 2);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить диалогу растягиваться

    this->setLayout(ptrLayout);
    this->setWindowTitle("Информация");
}

void nspGUI::clsUserSettingsDialog::slotApplySettings()
{
    ptrUser->setIsPasswordRestricted(ptrIsPasswordRestrictedCheckBox->isChecked());
    ptrUser->setIsUserBlocked(ptrIsUserBlockedCheckBox->isChecked());
}
