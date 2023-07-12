#ifndef GAMABIANHUA_H
#define GAMABIANHUA_H

#include <QMainWindow>
#include <cmath>

class GaMabianhua
{
public:
    GaMabianhua();
    QImage Gamma(QImage image,int value);
};

#endif // GAMABIANHUA_H
