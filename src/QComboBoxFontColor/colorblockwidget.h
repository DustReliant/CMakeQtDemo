/**
 * @file colorblockwidget.h
 * @brief 
 * @author merlotRain (1198477036@qq.com)
 * @version 1.0
 * @date 2023-03-28
 * 
 */

#ifndef COLORBLOCKWIDGT_H
#define COLORBLOCKWIDGT_H

#include "colormosaicbar.h"

class ColorBlockWidget : public ColorMosaicBar {
    Q_OBJECT
public:
    explicit ColorBlockWidget(QWidget *parent = nullptr);
    ~ColorBlockWidget() override;
    void setColor(QColor color);
    QColor color() const;

protected:
    void paint(QPainter &painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void clicked();
    void colorChange(QColor previous, QColor current);

private:
    QColor _color;
};

#endif //COLORBLOCKWIDGT_H