#include "imageviewerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewerWindow w;
    w.show();
    
    return a.exec();
}
