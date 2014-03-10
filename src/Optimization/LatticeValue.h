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
      bool setConstant( llvm::Constant * );
      bool setTop();

      inline bool isConstant() { return type == CONSTANT; }
      inline bool isTop() { return type == TOP; }
      inline bool isBottom() { return type == BOTTOM; }
      inline llvm::Constant * getConstant() { return constant; }

      private:
      enum ValueType
      {
        TOP,
        CONSTANT,
        BOTTOM
      };
      
      ValueType type;
      /* The constant * if this is a constant */
      llvm::Constant * constant;
    };

  }
}
#endif
