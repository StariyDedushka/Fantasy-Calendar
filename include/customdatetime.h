#ifndef CUSTOMDATETIME_H
#define CUSTOMDATETIME_H

#include <QObject>

class CustomDateTime
{
    // Q_OBJECT
private:

    int h, m, s, ms;
public:
    CustomDateTime(int h, int m, int s = 0, int ms = 0);
    CustomDateTime();
    bool setHMS(int h, int m, int s, int ms = 0);
};

#endif // CUSTOMDATETIME_H
