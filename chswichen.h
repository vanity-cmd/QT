#ifndef CHSWICHEN_H
#define CHSWICHEN_H

#include <QMainWindow>

class ChSwichEn
{
public:
    ChSwichEn();
};

typedef enum{
    UI_ZH,
    UI_EN
}LANGUAGE;
Q_DECLARE_METATYPE(LANGUAGE)

#endif // CHSWICHEN_H
