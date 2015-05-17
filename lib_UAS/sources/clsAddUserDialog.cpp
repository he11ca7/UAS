#include <nspGUI.h>

nspGUI::clsAddUserDialog::clsAddUserDialog(
        nspCore::clsUsersEngine *ptrNewUsersEngine,
        QWidget *ptrParent) : QDialog(ptrParent)
{
    ptrUsersEngine = ptrNewUsersEngine;

    ptrNickNameLabel = new QLabel("Никнейм");
    ptrNickNameLineEdit = new QLineEdit;

    ptrAddButton = new QPushButton("Добавить");
    connect(ptrAddButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotAddButtonClicked())
            );

    ptrLayout = new QGridLayout;
    ptrLayout->addWidget(ptrNickNameLabel, 0, 0);
    ptrLayout->addWidget(ptrNickNameLineEdit, 0, 1);
    ptrLayout->addWidget(ptrAddButton, 1, 0, 1, 2);

    this->setLayout(ptrLayout);
    this->setWindowTitle("Добавить пользователя");
}

void nspGUI::clsAddUserDialog::slotAddButtonClicked()
{
    if(!ptrUsersEngine->isUserExists(ptrNickNameLineEdit->text()))
    {
        ptrUsersEngine->addUser(new nspCore::clsUser(ptrNickNameLineEdit->text()));
        (new nspCustomClasses::clsMessageBox("Успех (:", "Пользователь успешно создан!", this))->exec();
        this->close();
    }
    else
    {
        (new nspCustomClasses::clsMessageBox("Ошибка", "Такой никнейм уже занят!", this))->exec();
    }
}
