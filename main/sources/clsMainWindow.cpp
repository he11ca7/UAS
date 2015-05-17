#include <clsMainWindow.h>

clsMainWindow::clsMainWindow()
{
    Q_INIT_RESOURCE(customClasses_res);
    Q_INIT_RESOURCE(UAS_res);

    this->setWindowTitle("User Attributions System");
    this->setWindowIcon(QIcon(":/icons/users128.png"));

    // Движки
    ptrGroupsEngine = new nspCore::clsGroupsEngine;
    ptrUsersEngine = new nspCore::clsUsersEngine;
    ptrUsersEngine->loadVectorUsersFromFile();
    ptrLoginEngine = new nspCore::clsLoginEngine(ptrUsersEngine);
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            this,
            SLOT(slotUpdateActions())
            );

    // Меню
    ptrFileMenu = new QMenu("Файл");
    ptrAboutAction = new QAction("О программе", this);
    connect(ptrAboutAction,
            SIGNAL(triggered()),
            this,
            SLOT(slotAboutMessageBox())
            );
    ptrExitAction = new QAction("Выход из программы", this);
    connect(ptrExitAction,
            SIGNAL(triggered()),
            this,
            SLOT(slotExitAction())
            );
    ptrFileMenu->addAction(ptrAboutAction);
    ptrFileMenu->addSeparator();
    ptrFileMenu->addAction(ptrExitAction);
    //
    ptrUserMenu = new QMenu("Пользователь");
    ptrLogInAction = new QAction("Вход", this);
    connect(ptrLogInAction,
            SIGNAL(triggered()),
            this,
            SLOT(slotLogInActionClicked())
            );
    ptrLogOutAction = new QAction("Выход", this);
    connect(ptrLogOutAction,
            SIGNAL(triggered()),
            ptrLoginEngine,
            SLOT(slotLogOut())
            );
    ptrChangePasswordAction = new QAction("Сменить пароль", this);
    connect(ptrChangePasswordAction,
            SIGNAL(triggered()),
            this,
            SLOT(slotChangePasswordActionClicked())
            );
    ptrUserMenu->addAction(ptrLogInAction);
    ptrUserMenu->addAction(ptrLogOutAction);
    ptrUserMenu->addAction(ptrChangePasswordAction);
    //
    this->menuBar()->addMenu(ptrFileMenu);
    this->menuBar()->addMenu(ptrUserMenu);

    // Виджеты
    ptrUserWidget = new nspGUI::clsUserWidget(ptrLoginEngine, this);
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            ptrUserWidget,
            SLOT(slotUpdateWidgets())
            );
    connect(ptrUserWidget,
            SIGNAL(signalBlockApplication()),
            this,
            SLOT(close())
            );
    ptrUsersWidget = new nspGUI::clsUsersWidget(ptrLoginEngine, ptrUsersEngine, ptrGroupsEngine, this);
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            ptrUsersWidget,
            SLOT(slotUpdateWidgets())
            );

    ptrCentralWidgetLayout = new QHBoxLayout;
    ptrCentralWidgetLayout->addWidget(ptrUserWidget);
    ptrCentralWidgetLayout->addWidget(ptrUsersWidget);
    ptrCentralWidget = new QWidget;
    ptrCentralWidget->setLayout(ptrCentralWidgetLayout);

    this->setCentralWidget(ptrCentralWidget);

    // Учим окно принимать правильные размеры
    connect(ptrLoginEngine,
            SIGNAL(signalCurrentUserUpdated()),
            this,
            SLOT(slotUpdateWindowSize())
            );

    // Разлогинимся, чтобы установить гостя в качестве текущего пользователя и обновить виджеты
    ptrLoginEngine->logOut();
}

// Перехватим событие, чтобы сохранить данные перед закрытием программы
void clsMainWindow::closeEvent(QCloseEvent *event)
{
    ptrUsersEngine->saveVectorUsersToFile();
    event->accept();
}

void clsMainWindow::slotAboutMessageBox()
{
    QMessageBox *ptrMessageBox = new QMessageBox(this);
    ptrMessageBox->setText("<h1>О программе</h1>");
    ptrMessageBox->setInformativeText(
                "<center>"
                "<img src=':/icons/users128.png' /><br/><br/>"
                "«User Attributions System»<br/><br/>"
                "Выполнил <b>Шамаев А.</b>, группа А-07-11, вариант 13."
                "</center>"
                );
    ptrMessageBox->setStandardButtons(QMessageBox::Ok);
    ptrMessageBox->setDefaultButton(QMessageBox::Ok);
    ptrMessageBox->setWindowTitle("О программе");
    ptrMessageBox->exec();
}

void clsMainWindow::slotExitAction()
{
    this->close();
}

void clsMainWindow::slotUpdateActions()
{
    if(ptrLoginEngine->getCurrentUser()->getGroupIdentificator() == nspUAS::groups_guest)
    {
        ptrLogInAction->setEnabled(true);
        ptrLogOutAction->setEnabled(false);
        ptrChangePasswordAction->setEnabled(false);
    }
    else
    {
        ptrLogInAction->setEnabled(false);
        ptrLogOutAction->setEnabled(true);
        ptrChangePasswordAction->setEnabled(true);
    }
}

void clsMainWindow::slotUpdateWindowSize()
{
    this->adjustSize(); // Нихрена не работает так, как мне надо
                        // То ли сигнал рано приходит, то ли ещё что-то: лэйаут стягивается не до конца
}

void clsMainWindow::slotLogInActionClicked()
{
    nspGUI::clsLoginDialog *ptrLoginDialog = new nspGUI::clsLoginDialog(ptrLoginEngine, this);
    connect(ptrLoginDialog,
            SIGNAL(signalBlockApplication()),
            this,
            SLOT(close())
            );
    ptrLoginDialog->exec();
}

void clsMainWindow::slotChangePasswordActionClicked()
{
    (new nspGUI::clsPasswordChangeDialog(ptrLoginEngine->getCurrentUser(), this))->exec();
}
