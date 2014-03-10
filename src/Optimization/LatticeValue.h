#ifndef LATTICEVALUE_H
#define LATTICEVALUE_H


#include <llvm/IR/Constant.h>


namespace C4
{
  namespace Optimize
  {
    struct LatticeValue
    {
      LatticeValue() : type(BOTTOM) {}

      /* Return true if status changes */
      bool setTop();
      bool setConstant( llvm::Constant * const constant );
      bool join( llvm::Constant * const constant );

      inline bool isConstant() { return type == VT::CONSTANT; }
      inline bool isTop() { return type == VT::TOP; }
      inline bool isBottom() { return type == VT::BOTTOM; }
      inline llvm::Constant * getConstant() { return constant; }

      private:
      enum class VT
      {
        TOP,
        CONSTANT,
        BOTTOM
      };

      VT type;
      /* The constant * if this is a constant */
      llvm::Constant *constant = NULL;
    };

  }
}


#endif
