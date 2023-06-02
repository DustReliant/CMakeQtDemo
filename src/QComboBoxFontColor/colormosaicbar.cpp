#include "colormosaicbar.h"
#include <QColor>
#include <QImage>
#include <QPainter>

ColorMosaicBar::ColorMosaicBar(QWidget *parent)
    : QWidget(parent), _drawMosaic(true) {
}

void ColorMosaicBar::setDrawMosaic(bool val) {
    _drawMosaic = val;
}

bool ColorMosaicBar::drawMosaic() const {
    return _drawMosaic;
}

void ColorMosaicBar::paintEvent(QPaintEvent *event) {
    auto *painter = new QPainter(this);

    //draw mosaic background
    if (_drawMosaic) {
        int wi = width();
        int hi = height();
        QImage img = QImage(this->rect().width(), this->rect().height(), QImage::Format_RGB32);
        uint *pixel = (uint *) img.scanLine(0);
        for (int y = 0; y < hi; y++) {
            uint *end = pixel + wi;
            int x = 0;
            while (pixel < end) {
                bool bx = ((x / 3) % 2) == 0;
                bool by = ((y / 3) % 2) == 0;
                QColor color = (bx && by) ? QColor(Qt::white) : QColor(204, 204, 204);
                uint *halt = pixel + 3;
                std::fill(pixel, halt, color.rgb());
                x += 3;
                pixel = halt;
            }
            pixel = end;
        }

        QRect rect(0, 0, wi, hi);
        QPixmap pix = QPixmap::fromImage(img);
        painter->drawPixmap(rect, pix);
    }

    paint(*painter);
}