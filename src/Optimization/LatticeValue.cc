#include "LatticeValue.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


bool LatticeValue::setTop()
{
  if ( type == VT::TOP )
    return false;
  type = VT::TOP;
  return true;
}

bool LatticeValue::setConstant( Constant * const constant )
{
  if ( type == VT::TOP )
    return false;

  if ( type == VT::CONSTANT )
  {
    assert( getConstant() == constant &&
        "Value already set to another constant");
    return false;
  }

  type = VT::CONSTANT;
  this->constant = constant;
  return true;
}

bool LatticeValue::join( llvm::Constant * const constant )
{
  /* TOP stays TOP. */
  if ( VT::TOP == type )
    return false;

  /* If we join two constants.  If the values differ, we get TOP, otherwise
   * nothing changes.
   */
  if ( VT::CONSTANT == type )
  {
    if ( this->constant == constant )
      return false;

    this->type = VT::TOP;
    return true;
  }

  this->type = VT::CONSTANT;
  this->constant = constant;
  return true;
}
