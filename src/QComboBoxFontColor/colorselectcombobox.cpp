#include "colorselectcombobox.h"
#include "colorblockwidget.h"
#include <QAction>
#include <QGridLayout>
#include <QMenu>
#include <QString>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

struct color_info {
    QColor color;
    QString color_name;
    color_info(QString _name, QColor _color)
        : color(std::move( _color)), color_name(std::move( _name)) {}
};

// clang-format off
const color_info colorInfos[10][12] = {
        {
            {"Arctic White",        QColor(255, 255, 255)},
            {"Rose Quartz",         QColor(255, 190, 190)},
            {"Sahara Sand",         QColor(255, 235, 190)},
            {"Topaz Sand",          QColor(255, 235, 175)},
            {"Yucca Yellow",        QColor(255, 255, 190)},
            {"Olivine Yellow",      QColor(233, 255, 190)},
            {"Tzavorite Green",     QColor(211, 255, 190)},
            {"Indicolite Green",    QColor(190, 255, 232)},
            {"Sodalite Blue",       QColor(190, 232, 255)},
            {"Sugilite Sky",        QColor(190, 210, 255)},
            {"Lepidolite Lilac",    QColor(232, 190, 255)},
            {"Rhodolite Rose",      QColor(255, 190, 232)}
        },
        {
            {"Gray 10%",            QColor(225, 225, 225)},
            {"Medium Coral Light",  QColor(255, 127, 127)},
            {"Cantaloupe",          QColor(255, 167, 127)},
            {"Mango",               QColor(255, 211, 127)},
            {"Autunite Yellow",     QColor(255, 255, 115)},
            {"Lemongrass",          QColor(209, 255, 115)},
            {"Light Apple",         QColor(163, 255, 115)},
            {"Beryl Green",         QColor(115, 255, 223)},
            {"Apatite Blue",        QColor(115, 223, 255)},
            {"Yogo Blue",           QColor(115, 178, 255)},
            {"Heliotrope",          QColor(223, 115, 255)},
            {"Fushia Pink",         QColor(255, 115, 223)}
        },
        {   
            {"Gray 20%",            QColor(204, 204, 204)},
            {"Mars Red",            QColor(255,   0,   0)},
            {"Fire Red",            QColor(255,  85,   0)},
            {"Electron Gold",       QColor(255, 170,   0)},
            {"Solar Yellow",        QColor(255, 255,   0)},
            {"Peridot Green",       QColor(170, 255,   0)},
            {"Medium Apple",        QColor( 85, 255,   0)},
            {"Tourmaline Green",    QColor(  0, 255, 197)},
            {"Big Sky Blue",        QColor(  0, 197, 255)},
            {"Cretean Blue",        QColor(  0, 130, 255)},
            {"Amethyst",            QColor(197,   0, 255)},
            {"Ginger Pink",         QColor(255,   0, 197)}
        },
        {
            {"Gray 30%",            QColor(178, 178, 178)},
            {"Poinsettia Red",      QColor(230,   0,   0)},
            {"Flame Red",           QColor(230,  76,   0)},
            {"Seville Orange",      QColor(230, 152,   0)},
            {"Citroen Yellow",      QColor(230, 230,   0)},
            {"Macaw Green",         QColor(152, 230,   0)},
            {"Quetzel Green",       QColor( 76, 230,   0)},
            {"Chrysophase",         QColor(  0, 230, 169)},
            {"Moorea Blue",         QColor(  0, 169, 230)},
            {"Lapis Lazuli",        QColor(  0,  92, 230)},
            {"Anemone Violet",      QColor(169,   0, 230)},
            {"Peony Pink",          QColor(230,   0, 169)}
        },
        {
            {"Gray 40%",            QColor(156, 156, 156)},
            {"Tuscan Red",          QColor(168,   0,   0)},
            {"Cherry Cola",         QColor(168,  56,   0)},
            {"Raw Umber",           QColor(168, 112,   0)},
            {"Olivenite Green",     QColor(168, 168,   0)},
            {"Tarragon Green",      QColor(112, 168,   0)},
            {"Leaf Green",          QColor( 56, 168,   0)},
            {"Malachite Green",     QColor(  0, 168, 132)},
            {"Delft Blue",          QColor(  0, 132, 168)},
            {"Ultra Blue",          QColor(  0,  77, 168)},
            {"Dark Amethyst",       QColor(132,   0, 168)},
            {"Cattleya Orchid",     QColor(168,   0, 132)}
        },
        {
            {"Gray 50%",            QColor(130, 130, 130)},
            {"Dark Umber",          QColor(115,   0,   0)},
            {"Cherrywood Brown",    QColor(115,  38,   0)},
            {"Burnt Umber",         QColor(115,  76,   0)},
            {"Dark Olivenite",      QColor(115, 115,   0)},
            {"Spruce Green",        QColor( 76, 115,   0)},
            {"Fir Green",           QColor( 38, 115,   0)},
            {"Peacock Green",       QColor(  0, 115,  76)},
            {"Steel Blue",          QColor(  0,  76, 115)},
            {"Dark Navy",           QColor(  0,  38, 115)},
            {"Ultramarine",         QColor( 76,   0, 115)},
            {"Purple Heart",        QColor(115,   0,  76)}
        },
        {
            {"Gray 60%",            QColor(104, 104, 104)},
            {"Rose Dust",           QColor(215, 158, 158)},
            {"Soapstone Dust",      QColor(215, 176, 158)},
            {"Tecate Dust",         QColor(215, 194, 158)},
            {"Lime Dust",           QColor(215, 215, 158)},
            {"Apple Dust",          QColor(199, 215, 158)},
            {"Sage Dust",           QColor(180, 215, 158)},
            {"Turquoise Dust",      QColor(158, 215, 194)},
            {"Blue Gray Dust",      QColor(158, 187, 215)},
            {"Violet Dust",         QColor(158, 170, 215)},
            {"Lilac Dust",          QColor(194, 158, 215)},
            {"Tudor Rose Dust",     QColor(214, 157, 188)}
        },
        {
            {"Gray 70%",            QColor( 78,  78,  78)},
            {"Medium Coral",        QColor(245, 122, 122)},
            {"Orange Dust",         QColor(245, 162, 122)},
            {"Medium Sand",         QColor(245, 202, 122)},
            {"Medium Yellow",       QColor(245, 245, 122)},
            {"Medium Lime",         QColor(205, 245, 122)},
            {"Medium Key Lime",     QColor(165, 245, 122)},
            {"Light Vert",          QColor(122, 245, 202)},
            {"Oxide Blue",          QColor(122, 182, 245)},
            {"Medium Azul",         QColor(122, 142, 245)},
            {"Medium Lilac",        QColor(202, 122, 245)},
            {"Medium Fushia",       QColor(245, 122, 182)}
        },
        {
            {"Gray 80%",            QColor( 52,  52,  52)},
            {"Tulip Pink",          QColor(205, 102, 102)},
            {"Nubuck Tan",          QColor(205, 137, 102)},
            {"Light Sienna",        QColor(205, 170, 102)},
            {"Light Olivenite",     QColor(205, 205, 102)},
            {"Medium Olivenite",    QColor(171, 205, 102)},
            {"Fern Green",          QColor(137, 205, 102)},
            {"Jadeite",             QColor(102, 205, 171)},
            {"Atlantic Blue",       QColor(102, 153, 205)},
            {"Pacific Blue",        QColor(102, 119, 205)},
            {"Aster Purple",        QColor(170, 102, 205)},
            {"Protea Pink",         QColor(205, 102, 153)}
        },
        {
            {"Black",               QColor(  0,   0,   0)},
            {"Cordovan Brown",      QColor(137,  68,  68)},
            {"Cocoa Brown",         QColor(137,  90,  68)},
            {"Leather Brown",       QColor(137, 112,  68)},
            {"Lichen Green",        QColor(137, 137,  68)},
            {"Moss Green",          QColor(114, 137,  68)},
            {"Lotus Pond Green",    QColor( 92, 137,  68)},
            {"Deep Forest",         QColor( 68, 137, 112)},
            {"Larkspur Blue",       QColor( 68, 101, 137)},
            {"Glacier Blue",        QColor( 38,  79, 137)},
            {"Blackberry",          QColor(112,  68, 137)},
            {"Cabernet",            QColor(137,  68, 101)}
        }
    };

// clang-format on

ColorSelectComboBox::ColorSelectComboBox(QWidget *parent, QColor color)
    : QToolButton(parent) {
    setPopupMode(QToolButton::MenuButtonPopup);
    setMenu(createColorMenu(SLOT(onColorChanged()), SLOT(onShowColorBoard())));
    setColor(std::move(color));
    setFixedSize(QSize(50, 25));
    setButtonColor(color);
}

ColorSelectComboBox::~ColorSelectComboBox() = default;

void ColorSelectComboBox::setColor(QColor color) {
    _currentColor = std::move(color);
}

QColor ColorSelectComboBox::color() const {
    return _currentColor;
}

QMenu *ColorSelectComboBox::createColorMenu(const char *slot, const char *slotColorBoard) {
    // add no color

    QVBoxLayout* verticalLayout = new QVBoxLayout();
    {
        // add no color
        QHBoxLayout* horizontalLayout = new QHBoxLayout();
        ColorBlockWidget* blockWidget = new ColorBlockWidget();
        connect(blockWidget, SIGNAL(clicked()), this, slot);
        blockWidget->setColor(QColor(0,0,0,0));
        blockWidget->setToolTip("No Color");
        blockWidget->setFixedSize(QSize(16, 16));
        horizontalLayout->addWidget(blockWidget);

        QLabel* label = new QLabel("No Color");
        horizontalLayout->addWidget(label);

        QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        verticalLayout->addLayout(horizontalLayout);
    }
    {
        // add line
        QFrame* line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayout->addWidget(line);
    }
    {
        // add default color label
        QLabel* label = new QLabel("Default Color");
        verticalLayout->addWidget(label);
    }
    {
        // add default color widget
        QWidget* widget = new QWidget();
        QVBoxLayout* subVerticalLayout = new QVBoxLayout(widget);
        for(int row = 0; row < 10;++row) {
            QHBoxLayout* horizontalLayout = new QHBoxLayout();
            for(int column =0;column<12;++column){
                ColorBlockWidget* blockWidget = new ColorBlockWidget();
                connect(blockWidget, SIGNAL(clicked()), this, slot);
                blockWidget->setFixedSize(QSize(16,16));
                blockWidget->setColor(colorInfos[row][column].color);
                blockWidget->setToolTip(colorInfos[row][column].color_name);
                horizontalLayout->addWidget(blockWidget);
            }
            subVerticalLayout->addLayout(horizontalLayout);
        }
        verticalLayout->addWidget(widget);
    }
    {
        // add line
        QFrame* line = new QFrame;
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayout->addWidget(line);
    }


    QMenu *colorMenu = new QMenu(this);
    colorMenu->setLayout(verticalLayout);
    colorMenu->addSeparator();
    return colorMenu;
}

QIcon ColorSelectComboBox::createColorToolButtonIcon(QColor color) {
    int nWidth = this->width();
    int nHeight = this->height();
    if (width() > 22 && height() > 8)
    {
        nWidth = this->width() - 22;
        nHeight = this->height() - 8;
    }
    QPixmap pixmap(nWidth, nHeight);

    // no color
    if (color.alpha() == 0)
    {
        QPainter painter(&pixmap);
        // draw mosaic

        QColor lineColor(161, 161, 161);
        QPen pen(lineColor, 1, Qt::SolidLine);
        QColor newColor(225, 225, 225);
        painter.setBrush(newColor);
        painter.setPen(pen);
        painter.drawRect(QRect(0, 0, nWidth - 1, nHeight - 1));

        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawLine(0, nHeight, nWidth, 0);
    }
    else
    {
        pixmap.fill(color);
    }

    QIcon icon(pixmap);
    return icon;
}
QIcon ColorSelectComboBox::createColorIcon(QColor color) {
    QPixmap pixmap(16, 16);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 16, 16), color);
    return QIcon(pixmap);
}

void ColorSelectComboBox::onColorChanged() {
    ColorBlockWidget* blockWidget = qobject_cast<ColorBlockWidget*>(sender());
    if (blockWidget) {
        QColor color = blockWidget->color();
        setButtonColor(color);
    }
}

void ColorSelectComboBox::onShowColorBoard() {
    int i = 0;
}
void ColorSelectComboBox::setButtonColor(QColor color) {
    setIconSize(size());
    setIcon(createColorToolButtonIcon(color));
    if (_currentColor != color)
    {
        _currentColor = color;
        emit selectColorChange(_currentColor);
    }
}
