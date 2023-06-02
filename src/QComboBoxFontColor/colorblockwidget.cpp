#include "colorblockwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>

ColorBlockWidget::ColorBlockWidget(QWidget *parent)
    : ColorMosaicBar(parent) {
}

ColorBlockWidget::~ColorBlockWidget() = default;

void ColorBlockWidget::setColor(QColor color) {
    emit colorChange(_color, color);
    _color = std::move(color);
}

QColor ColorBlockWidget::color() const {
    return _color;
}

void ColorBlockWidget::paint(QPainter &painter) {
    if (_color.alpha() != 0) {
        painter.restore();
        int wi = width();
        int hi = height();
        QImage img = QImage(this->rect().width(), this->rect().height(), QImage::Format_RGB32);
        uint *pixel = (uint *) img.scanLine(0);
        for (int y = 0; y < hi; y++) {
            uint *end = pixel + wi;
            std::fill(pixel, end, _color.rgb());
            pixel = end;
        }

        QRect rect(0, 0, wi, hi);
        QPixmap pix = QPixmap::fromImage(img);
        painter.drawPixmap(rect, pix);
        painter.save();
    }

}

void ColorBlockWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
}

void ColorBlockWidget::mouseMoveEvent(QMouseEvent *event) {
    return QWidget::mouseMoveEvent(event);
}

void ColorBlockWidget::mouseReleaseEvent(QMouseEvent *event) {
    emit clicked();
    return QWidget::mouseReleaseEvent(event);
}