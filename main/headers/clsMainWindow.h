#pragma once

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>

#include <nspCore.h>
#include <nspGUI.h>

class clsMainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QMenu       *ptrFileMenu;
    QAction     *ptrAboutAction,
                *ptrExitAction;

    QMenu       *ptrUserMenu;
    QAction     *ptrLogInAction,
                *ptrChangePasswordAction,
                *ptrLogOutAction;

    nspCore::clsUsersEngine     *ptrUsersEngine;
    nspCore::clsGroupsEngine    *ptrGroupsEngine;
    nspCore::clsLoginEngine     *ptrLoginEngine;

    nspGUI::clsUserWidget       *ptrUserWidget;
    nspGUI::clsUsersWidget      *ptrUsersWidget;

    QHBoxLayout                 *ptrCentralWidgetLayout;
    QWidget                     *ptrCentralWidget;

    void closeEvent(QCloseEvent *event);

public:

    clsMainWindow();

private slots:

    void slotAboutMessageBox();
    void slotExitAction();

    void slotUpdateActions();
    void slotUpdateWindowSize();
    void slotLogInActionClicked();
    void slotChangePasswordActionClicked();

};
