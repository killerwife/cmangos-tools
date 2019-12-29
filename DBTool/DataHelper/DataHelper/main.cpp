#include "datahelper.h"
#include <QtWidgets/QApplication>
#include "XMLReader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLReader reader("Data.xml");
    DataHelper w(reader);
    w.show();
    return a.exec();
}
