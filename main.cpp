#include "Caesar.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argv[1] == "--cli" || argv[1] == "-t")
    {
        Caesar w;
        std::cout << "Hello, World!" << std::endl;
    }
    else
    {
        QApplication a(argc, argv);
        Caesar w;
        w.setWindowTitle(QObject::tr("Дешифратор шифра Цезаря"));
        w.show();
        return a.exec();
    }
}
