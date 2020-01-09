#ifndef STEP_H
#define STEP_H


#include <memory>

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

    bool operator==(Step const&) const;

};

#endif // STEP_H
