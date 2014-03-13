#ifndef LATTICEVALUE_H
#define LATTICEVALUE_H


#include <iostream>
#include "llvm/IR/Constant.h"


namespace C4
{
  namespace Optimize
  {
    struct LatticeValue
    {
      LatticeValue() : type( VT::BOTTOM ) {}
      ~LatticeValue() {}

      friend std::ostream & operator<<( std::ostream &out, LatticeValue &LV );
      friend std::ostream & operator<<( std::ostream &out,
          LatticeValue * const LV );

      /// Sets this LatticeValue to TOP.
      ///
      /// \return true iff the LatticeValue was not TOP already, false otherwise
      bool setTop();

      bool join( llvm::Constant * const constant );
      bool join( LatticeValue const &Other );

      inline bool isTop() const { return type == VT::TOP; }
      inline bool isConstant() const { return type == VT::CONSTANT; }
      inline bool isBottom() const { return type == VT::BOTTOM; }

      inline llvm::Constant * getConstant() const { return constant; }

      void dump() const;

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

    std::ostream & operator<<( std::ostream &out, LatticeValue &LV );
    std::ostream & operator<<( std::ostream &out,
        LatticeValue * const LV );
  }
}


#endif
