#include "paint.h"
#include "dialog.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Paint w;
    w.show();

    return a.exec();
}
