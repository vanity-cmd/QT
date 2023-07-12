#include "erzhihua.h"

ErZhiHua::ErZhiHua()
{

}

//二值化
QImage ErZhiHua::TwoSide(QImage grayimage,int value){
    QImage TwoSideImage =grayimage.convertToFormat(QImage::Format_ARGB32);
    QColor oldColor;
    int ts;
    for(int y = 0; y < grayimage.height(); y++)
    {
        for(int x = 0; x < grayimage.width(); x++)
        {
                oldColor = QColor(grayimage.pixel(x,y));
                ts = oldColor.red();
            if(ts<value){
                ts=0;
            }else{
                ts=255;
            }
            TwoSideImage.setPixel(x,y, qRgb(ts, ts, ts));

        }
    }
    return TwoSideImage;
}
