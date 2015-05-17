#include <nspGUI.h>

nspGUI::clsUserSettingsButton::clsUserSettingsButton(
        nspCore::clsUser *ptrNewUser,
        QWidget *ptrParent) : QPushButton(ptrParent)
{
    ptrAccount = ptrNewUser;
    connect(this,
            SIGNAL(clicked()),
            this,
            SLOT(slotEmitSignalClicked())
            );
    this->setIcon(QIcon(":/icons/user128.png"));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void nspGUI::clsUserSettingsButton::slotEmitSignalClicked()
{
    emit signalClicked(ptrAccount);
}
