#include <QApplication>
#include <QFont>

#include <clsMainWindow.h>

int main(int argc, char *argv[])
{
    QApplication ptrApp(argc, argv);
    QFont myFont("Tahoma", 10);
    QApplication::setFont(myFont);

    clsMainWindow *ptrMainWindow = new clsMainWindow;
    ptrMainWindow->show();

    return ptrApp.exec();
}
