#pragma once

#include <QWidget>
#include <QLayout>
#include <QLayoutItem>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QMessageBox>

namespace nspCustomClasses
{
	/*!
     * \brief The clsMessageBox class
     */
    class clsMessageBox : public QMessageBox
    {
        Q_OBJECT

    public:

        clsMessageBox(
                QString title,
                QString text,
                QWidget *ptrParent = NULL);
    };
	
    /*!
     * \brief The clsGridScrollAreaWidget class
     * Класс реализует виджет с сеточным лэйаутом и полосой вертикальнйо прокрутки
     */
    class clsGridScrollAreaWidget : public QWidget
    {
        Q_OBJECT

    private:

        bool    flagIsUpdateWidgetsEnabled;     // Флаг, указывающий на то, что обновлять виджеты не нужно
                                                // Может включаться в случаях, когда нужно добавить большое количество виджетов
        QScrollArea     *ptrScrollArea;
        QWidget         *ptrScrollAreaWidget;
        QGridLayout     *ptrScrollAreaWidgetLayout;
        QVBoxLayout     *ptrLayout;

        void updateWidgets();

    public:

        clsGridScrollAreaWidget(
                QWidget *ptrParent = NULL);

        void addWidget(
                QWidget *ptrWidget,
                int row,
                int col);
        void addWidget(
                QWidget *ptrWidget,
                int row,
                int col,
                int rowSpan,
                int colSpan);
        QWidget *getWidget(
                int row,
                int col);

        bool isEmpty();
        void clear();

        void setWidgetsUpdates(
                bool on);
    };

    /*!
     * \brief The clsVisibilityButton class
     * Класс реализует кнопку скрытия/показа с сигналом
     */
    class clsVisibilityButton : public QPushButton
    {
        Q_OBJECT

    public:

        clsVisibilityButton(
                QWidget *ptrParent = NULL);

    private slots:

        void slotButtonClicked();

    signals:

        void signalClicked(
                bool isClicked);
    };

    /*!
     * \brief The clsPasswordLineEdit class
     * Класс реализует типичный эдит для ввода пароля
     */
    class clsPasswordLineEdit : public QLineEdit
    {
        Q_OBJECT

    public:

        clsPasswordLineEdit(
                QWidget *ptrParent = NULL);

    public slots:

        void slotSetTextVisible(
                bool isVisible);
    };
}
