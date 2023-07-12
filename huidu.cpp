#include "huidu.h"

Huidu::Huidu()
{

}

//灰度化
QImage Huidu::gray(QImage image){
    QImage newImage =image.convertToFormat(QImage::Format_ARGB32);
    QColor oldColor;

        for(int y = 0; y < newImage.height(); y++)
        {
            for(int x = 0; x < newImage.width(); x++)
            {
                oldColor = QColor(image.pixel(x,y));
                int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
                newImage.setPixel(x, y, qRgb(average, average, average));
            }
        }
        return newImage;
}

