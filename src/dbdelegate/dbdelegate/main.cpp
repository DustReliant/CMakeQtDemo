#include "frmmain.h"
#include "quihelper.h"

int main(int argc, char *argv[])
{
    QUIHelper::initMain(false);
    QApplication a(argc, argv);
    QUIHelper::initAll();

    frmMain w;
    w.resize(1050, 750);
    w.setWindowTitle(QString("自定义委托全家桶 V20220426 %1").arg(AppData::TitleFlag));
    QUIHelper::showForm(&w);

    return a.exec();
}
