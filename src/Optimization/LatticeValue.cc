#include "LatticeValue.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


std::ostream & Optimize::operator<<( std::ostream &out, LatticeValue &LV )
{
  if ( LV.isTop() )
    out << "TOP";
  else if ( LV.isBottom() )
    out << "BOTTOM";
  else
    out << "CONSTANT: " << LV.getConstant();

  return out;
}

std::ostream & Optimize::operator<<( std::ostream &out,
    LatticeValue * const LV )
{
  return out << *LV;
}

bool LatticeValue::setTop()
{
  if ( isTop() )
    return false;
  this->constant = NULL;
  type = VT::TOP;
  return true;
}

bool LatticeValue::join( llvm::Constant * const constant )
{
  /* TOP stays TOP. */
  if ( isTop() )
    return false;

  if ( isBottom() )
  {
    this->type = VT::CONSTANT;
    this->constant = constant;
    return true;
  }

  /* We now have to join two constants. */
  if ( this->constant == constant )
    return false;

  /* The constants are not equal, therefore this will become TOP. */
  setTop();
  return true;
}

bool LatticeValue::join( LatticeValue const &Other )
{
  /* TOP stays TOP. */
  if ( isTop() )
    return false;

  /* Join with TOP yields TOP. */
  if ( Other.isTop() )
    return setTop();

  /* Join with BOTTOM is a NOP. */
  if ( Other.isBottom() )
    return false;

  /* If this is BOTTOM, it will become Other. */
  if ( isBottom() )
  {
    this->type = Other.type;
    this->constant = Other.constant;
    return true;
  }

  /* We now have to join two constants. */
  if ( Other.getConstant() == this->constant )
    return false;

  /* The constants are not equal, therefore this will become TOP. */
  return setTop();
}

void LatticeValue::dump() const
{
  if ( isTop() )
    std::cerr << "TOP";
  else if ( isBottom() )
    std::cerr << "BOTTOM";
  else
    std::cerr << "CONSTANT: " << getConstant();
  std::cerr << std::endl;
}
