/**
 * @file colorselectcombobox.h
 * @brief
 * @author MerlotRain (1198477036@qq.com)
 * @version 1.0
 * @date 2023-03-27
 * 
*/

#ifndef COLORSELECTCOMBOBOX_H
#define COLORSELECTCOMBOBOX_H

#include <QToolButton>

class ColorSelectComboBox : public QToolButton {
    Q_OBJECT
public:
    explicit ColorSelectComboBox(QWidget *parent = nullptr, QColor color = QColor(0, 0, 0));
    ~ColorSelectComboBox() override;
    void setColor(QColor color);
    QColor color() const;

Q_SIGNALS:
    void selectColorChange(QColor color);

private:
    QMenu *createColorMenu(const char *slot, const char *slotColrBoard);
    QIcon createColorToolButtonIcon(QColor color);
    QIcon createColorIcon(QColor color);
    void setButtonColor(QColor color);
private slots:
    void onColorChanged();
    void onShowColorBoard();
   

private:
    QColor _currentColor;
};


#endif//COLORSELECTCOMBOBOX_H
