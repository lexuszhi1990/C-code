#include <QApplication>
#include "plate.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // your code here
    Plate w;
    w.showMaximized();


    return app.exec();
}
