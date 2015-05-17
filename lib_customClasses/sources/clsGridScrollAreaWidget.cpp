#include <nspCustomClasses.h>

nspCustomClasses::clsGridScrollAreaWidget::clsGridScrollAreaWidget(
        QWidget *ptrParent) : QWidget(ptrParent)
{
    flagIsUpdateWidgetsEnabled = true;

    ptrScrollAreaWidgetLayout = new QGridLayout;
    ptrScrollArea = 0;

    ptrLayout = new QVBoxLayout;
    //    ptrLayout->setSizeConstraint(QLayout::SetFixedSize); // Запретить виджету растягиваться
    ptrLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(ptrLayout);
}
void nspCustomClasses::clsGridScrollAreaWidget::addWidget(
        QWidget *ptrWidget,
        int row,
        int col)
{
    ptrScrollAreaWidgetLayout->addWidget(ptrWidget, row, col);
    if(flagIsUpdateWidgetsEnabled) updateWidgets();
}

void nspCustomClasses::clsGridScrollAreaWidget::addWidget(
        QWidget *ptrWidget,
        int row,
        int col,
        int rowSpan,
        int colSpan)
{
    ptrScrollAreaWidgetLayout->addWidget(ptrWidget, row, col, rowSpan, colSpan);
    if(flagIsUpdateWidgetsEnabled) updateWidgets();
}

QWidget *nspCustomClasses::clsGridScrollAreaWidget::getWidget(
        int row,
        int col)
{
    if(ptrScrollAreaWidgetLayout->itemAtPosition(row, col) != 0)
    {
        return ptrScrollAreaWidgetLayout->itemAtPosition(row, col)->widget();
    }
    return 0;
}

void nspCustomClasses::clsGridScrollAreaWidget::updateWidgets()
{
    // Спасём лэйаут от удаления
    QWidget *ptrTempWidget = new QWidget;
    ptrTempWidget->setLayout(ptrScrollAreaWidgetLayout);

    // Удалим старую зону скролла
    if(ptrScrollArea != 0)
    {
        ptrLayout->removeWidget(ptrScrollArea);
        delete ptrScrollArea;
    }

    ptrScrollAreaWidget = new QWidget;
    ptrScrollAreaWidget->setLayout(ptrScrollAreaWidgetLayout);

    ptrScrollArea = new QScrollArea;
    ptrScrollArea->setWidget(ptrScrollAreaWidget);
    ptrScrollArea->setWidgetResizable(true);
    ptrScrollArea->setFrameShape(QFrame::NoFrame); // Убрать тонкую рамку вокруг
    //    ptrScrollArea->setStyleSheet("background-color: transparent");
    ptrScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ptrScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ptrLayout->addWidget(ptrScrollArea);

    delete ptrTempWidget;
}

bool nspCustomClasses::clsGridScrollAreaWidget::isEmpty()
{
    return ptrScrollAreaWidgetLayout->isEmpty();
}

void nspCustomClasses::clsGridScrollAreaWidget::clear()
{
    // Очистим коннекты
    for(int rowCounter = 0; rowCounter < ptrScrollAreaWidgetLayout->rowCount(); rowCounter++)
    {
        for(int colCounter = 0; colCounter < ptrScrollAreaWidgetLayout->columnCount(); colCounter++)
        {
            QObject::disconnect(getWidget(rowCounter, colCounter));
        }
    }
    // Уберём виджеты
    for(int rowCounter = 0; rowCounter < ptrScrollAreaWidgetLayout->rowCount(); rowCounter++)
    {
        for(int colCounter = 0; colCounter < ptrScrollAreaWidgetLayout->columnCount(); colCounter++)
        {
            ptrScrollAreaWidgetLayout->removeItem(
                        ptrScrollAreaWidgetLayout->itemAtPosition(
                            rowCounter,
                            colCounter)
                        );
        }
    }
    updateWidgets();
}

void nspCustomClasses::clsGridScrollAreaWidget::setWidgetsUpdates(
        bool on)
{
    flagIsUpdateWidgetsEnabled = on;
}
