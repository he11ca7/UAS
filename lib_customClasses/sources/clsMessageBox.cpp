#include <nspCustomClasses.h>

nspCustomClasses::clsMessageBox::clsMessageBox(
        QString title,
        QString text,
        QWidget *ptrParent) : QMessageBox(ptrParent)
{
    this->setWindowTitle(title);
    this->setText(text);
}
