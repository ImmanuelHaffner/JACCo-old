#include "LatticeValue.h"

using namespace C4;
using namespace llvm;
using namespace Optimize;

bool LatticeValue::setTop()
{
  if ( type == TOP )
    return false;
  type = TOP;
  return true;
}

bool LatticeValue::setConstant( Constant * constant )
{
  if ( type == TOP )
    return false;

  if ( type == CONSTANT )
  {
    assert( getConstant() == constant &&
        "Value already set to another constant");
    return false;
  }

  type = CONSTANT;
  this->constant = constant;
  return true;
}
