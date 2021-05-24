#include "Caesar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Caesar w;
    w.setWindowTitle(QObject::tr("Дешифратор шифра Цезаря"));
    w.show();
    return a.exec();
}
