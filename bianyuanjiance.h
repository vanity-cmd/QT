#ifndef BIANYUANJIANCE_H
#define BIANYUANJIANCE_H

#include <QMainWindow>
#include <cmath>


class BianYuanjiance
{
public:
    BianYuanjiance();
    QImage guass(QImage grayimg);
    QImage calculate(QImage img,QImage img_gray,QImage img_guass);
};

#endif // BIANYUANJIANCE_H
