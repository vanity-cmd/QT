#include "gamabianhua.h"

GaMabianhua::GaMabianhua()
{

}
//伽马变换
QImage GaMabianhua::Gamma(QImage image,int value){
    QImage GammaImage =image.convertToFormat(QImage::Format_ARGB32);
    QColor oldColor;

    for(int y = 0; y < image.height(); y++)
    {
        for(int x = 0; x < image.width(); x++)
        {
                oldColor = QColor(image.pixel(x,y));
                double red=oldColor.red();
                double green=oldColor.green();
                double blue=oldColor.blue();

                int r=qBound(0,(int)pow(red,value),255);
                int g=qBound(0,(int)pow(green,value),255);
                int b=qBound(0,(int)pow(blue,value),255);
            GammaImage.setPixel(x,y, qRgb(r, g, b));

        }
    }
    return GammaImage;
}
