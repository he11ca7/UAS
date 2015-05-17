#include <nspCustomClasses.h>

nspCustomClasses::clsPasswordLineEdit::clsPasswordLineEdit(
        QWidget *ptrParent) : QLineEdit(ptrParent)
{
    this->setEchoMode(QLineEdit::Password);
}

void nspCustomClasses::clsPasswordLineEdit::slotSetTextVisible(
        bool isVisible)
{
    if(isVisible)
    {
        this->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        this->setEchoMode(QLineEdit::Password);
    }
}
