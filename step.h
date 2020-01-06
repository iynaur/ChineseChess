#ifndef STEP_H
#define STEP_H


#include <QObject>

class Step
{
public:
    explicit Step();
    ~Step();

    int _moveid;
    int _killid;
    int _rowFrom;
    int _colFrom;
    int _rowTo;
    int _colTo;

};

#endif // STEP_H
