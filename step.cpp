#include "step.h"
#include <stdio.h>
#include <string.h>

Step::Step()
{

}

Step::~Step()
{

}

bool Step::operator==(const Step &step) const
{
  return !memcmp(this, &step, sizeof(Step));
}
