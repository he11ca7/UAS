#include <nspGUI.h>

nspGUI::clsPasswordChangeDialog::clsPasswordChangeDialog(
        nspCore::clsUser *ptrNewUser,
        QWidget *ptrParent) : QDialog(ptrParent)
{
    ptrUser = ptrNewUser;

    ptrOldPasswordLabel = new QLabel("Старый пароль");
    ptrNewPasswordLabel = new QLabel("Новый пароль");
    ptrNewPasswordAgainLabel = new QLabel("Ещё раз");

    ptrOldPasswordLineEdit = new nspCustomClasses::clsPasswordLineEdit;
    ptrNewPasswordLineEdit = new nspCustomClasses::clsPasswordLineEdit;
    ptrNewPasswordAgainLineEdit = new nspCustomClasses::clsPasswordLineEdit;

    ptrChangePasswordButton = new QPushButton("Сменить");
    connect(ptrChangePasswordButton,
            SIGNAL(clicked()),
            this,
            SLOT(slotChangePasswordButtonClicked())
            );
    ptrChangePasswordButton->setDefault(true);

    ptrSetPasswordsVisibleButton = new nspCustomClasses::clsVisibilityButton;
    ptrSetPasswordsVisibleButton->setIconSize(QSize(64, 64));
    ptrSetPasswordsVisibleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    connect(ptrSetPasswordsVisibleButton,
            SIGNAL(signalClicked(bool)),
            ptrOldPasswordLineEdit,
            SLOT(slotSetTextVisible(bool))
            );
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
    ptrLayout->addWidget(ptrOldPasswordLabel, 0, 0);
    ptrLayout->addWidget(ptrOldPasswordLineEdit, 0, 1);
    ptrLayout->addWidget(ptrNewPasswordLabel, 1, 0);
    ptrLayout->addWidget(ptrNewPasswordLineEdit, 1, 1);
    ptrLayout->addWidget(ptrNewPasswordAgainLabel, 2, 0);
    ptrLayout->addWidget(ptrNewPasswordAgainLineEdit, 2, 1);
    ptrLayout->addWidget(ptrSetPasswordsVisibleButton, 0, 2, 3, 1);
    ptrLayout->addWidget(ptrChangePasswordButton, 3, 0, 1, 2);
    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить диалогу растягиваться

    this->setLayout(ptrLayout);
    this->setWindowTitle("Смена пароля");
}

void nspGUI::clsPasswordChangeDialog::slotChangePasswordButtonClicked()
{
    if(ptrNewPasswordLineEdit->text() == ptrNewPasswordAgainLineEdit->text())
    {
        switch (ptrUser->setPassword(ptrOldPasswordLineEdit->text(), ptrNewPasswordLineEdit->text()))
        {
        case nspUAS::passwordMessage_success:
        {
            (new nspCustomClasses::clsMessageBox("Успех (:", "Пароль успешно заменён!", this))->exec();
            this->close();
            break;
        }

        case nspUAS::passwordMessage_oldPasswordIncorrect:
            (new nspCustomClasses::clsMessageBox("Ошибка", "Старый пароль введён неверно!", this))->exec();
            break;

        case nspUAS::passwordMessage_newPasswordEmpty:
            (new nspCustomClasses::clsMessageBox("Ошибка", "Пароль не должен быть пустым!", this))->exec();
            break;

        case nspUAS::passwordMessage_oldPasswordAndNewPasswordTheSame:
            (new nspCustomClasses::clsMessageBox("Ошибка", "Новый и старый пароли не должны совпадать!", this))->exec();
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
