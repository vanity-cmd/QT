#include "lvbo.h"

LvBo::LvBo()
{

}

//均值滤波
QImage LvBo::avg(QImage image)
{
    int kernel [3][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1}};
        int sizeKernel = 3;
        int sumKernel = 9;
        QColor color;
         for(int x = sizeKernel/2;x<image.width() - sizeKernel/2;x++)
        {
           for(int y= sizeKernel/2;y<image.height() - sizeKernel/2;y++)
            {
                int r = 0;
                int g = 0;
                int b = 0;
                for(int i = -sizeKernel/2;i<=sizeKernel/2;i++)
                {
                   for(int j = -sizeKernel/2;j<=sizeKernel/2;j++)
                    {
                     color = QColor(image.pixel(x+i,y+j));
                     r+=color.red()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                     g+=color.green()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                     b+=color.blue()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                    }
                }
                r = qBound(0,r/sumKernel,255);
                g = qBound(0,g/sumKernel,255);
                b = qBound(0,b/sumKernel,255);
                image.setPixel(x,y,qRgb( r,g,b));
            }
        }
         return image;
}
