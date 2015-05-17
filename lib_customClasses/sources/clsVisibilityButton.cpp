#include <nspCustomClasses.h>

nspCustomClasses::clsVisibilityButton::clsVisibilityButton(
        QWidget *ptrParent) : QPushButton(ptrParent)
{
    this->setIcon(QIcon(":/icons/closed_eye_128.png"));
    connect(this,
            SIGNAL(pressed()),
            this,
            SLOT(slotButtonClicked())
            );
    connect(this,
            SIGNAL(released()),
            this,
            SLOT(slotButtonClicked())
            );
}

void nspCustomClasses::clsVisibilityButton::slotButtonClicked()
{
    if(this->isDown())
    {
        this->setIcon(QIcon(":/icons/open_eye_128.png"));
    }
    else
    {
        this->setIcon(QIcon(":/icons/closed_eye_128.png"));
    }
    emit signalClicked(this->isDown());
}
