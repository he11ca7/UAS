#include <nspGUI.h>

nspGUI::clsPasswordSetDialog::clsPasswordSetDialog(
        nspCore::clsUser *ptrNewUser,
        QWidget *ptrParent) : QDialog(ptrParent)
{
    ptrUser = ptrNewUser;

    ptrNewPasswordLabel = new QLabel("Новый пароль");
    ptrNewPasswordAgainLabel = new QLabel("Ещё раз");

    ptrNewPasswordLineEdit = new nspCustomClasses::clsPasswordLineEdit;
    ptrNewPasswordAgainLineEdit = new nspCustomClasses::clsPasswordLineEdit;

    ptrSetPasswordButton = new QPushButton("Сменить");
    connect(ptrSetPasswordButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotSetPasswordButtonClicked())
            );
    ptrSetPasswordButton->setDefault(true);

    ptrSetPasswordsVisibleButton = new nspCustomClasses::clsVisibilityButton;
    ptrSetPasswordsVisibleButton->setIconSize(QSize(48, 48));
    ptrSetPasswordsVisibleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    connect(ptrSetPasswordsVisibleButton,
            SIGNAL(signalClicked(bool)),
            ptrNewPasswordLineEdit,
            SLOT(slotSetTextVisible(bool))
            );
    connect(ptrSetPasswordsVisibleButton,
            SIGNAL(signalClicked(bool)),
            ptrNewPasswordAgainLineEdit,
            SLOT(slotSetTextVisible(bool))
            );

    ptrLayout = new QGridLayout;
    ptrLayout->addWidget(ptrNewPasswordLabel, 0, 0);
    ptrLayout->addWidget(ptrNewPasswordLineEdit, 0, 1);
    ptrLayout->addWidget(ptrNewPasswordAgainLabel, 1, 0);
    ptrLayout->addWidget(ptrNewPasswordAgainLineEdit, 1, 1);
    ptrLayout->addWidget(ptrSetPasswordsVisibleButton, 0, 2, 2, 1);
    ptrLayout->addWidget(ptrSetPasswordButton, 2, 0, 1, 2);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить диалогу растягиваться

    this->setLayout(ptrLayout);
    this->setWindowTitle("Создайте пароль");
}

void nspGUI::clsPasswordSetDialog::slotSetPasswordButtonClicked()
{
    if(ptrNewPasswordLineEdit->text() == ptrNewPasswordAgainLineEdit->text())
    {
        switch (ptrUser->setPassword("", ptrNewPasswordLineEdit->text()))
        {
        case nspUAS::passwordMessage_success:
        {
            (new nspCustomClasses::clsMessageBox("Успех (:", "Пароль успешно установлен!", this))->exec();
            this->close();
            break;
        }

        case nspUAS::passwordMessage_newPasswordEmpty:
            (new nspCustomClasses::clsMessageBox("Ошибка", "Пароль не должен быть пустым!", this))->exec();
            break;

        case nspUAS::passwordMessage_newPasswordMismatchRestrictions:
            (new nspCustomClasses::clsMessageBox("Ошибка",
                                       "Пароль не соответствует правилу:"
                                       "в пароле д.б. строчные и прописные символы и знаки препинания",
                                       this)
                    )->exec();
            break;

        default:
            (new nspCustomClasses::clsMessageBox("Ошибка", "Неизвестная ошибка!", this))->exec();
            break;
        }
    }
    else
    {
        (new nspCustomClasses::clsMessageBox("Ошибка", "Новый пароль и подтверждение не совпадают!", this))->exec();
    }
}
