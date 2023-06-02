#include "colorselectcombobox.h"
#include <QApplication>

// 本次的demo是按照 https://github.com/MerlotRain/colorSelector 原封不动搬过来

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    ColorSelectComboBox w;
    w.show();
    return a.exec();
}