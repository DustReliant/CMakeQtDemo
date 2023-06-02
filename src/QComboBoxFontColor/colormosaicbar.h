/**
 * @file colormosaicbar.h
 * @brief Mosaic color bar.
          Draws a mosaic background color for the control.
 * @author MerlotRain (1198477036@qq.com)
 * @version 1.0
 * @date 2023-03-28
 *  
 */

#ifndef COLORMOSAICBAE_H
#define COLORMOSAICBAE_H

#include <QWidget>

class ColorMosaicBar : public QWidget {
    Q_OBJECT
public:
    explicit ColorMosaicBar(QWidget *parent = nullptr);
    virtual ~ColorMosaicBar(){};
    void setDrawMosaic(bool);
    bool drawMosaic() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void paint(QPainter &painter) = 0;

private:
    bool _drawMosaic;
};

#endif //COLORMOSAICBAE_H