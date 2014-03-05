#ifndef TYPE_HELPER_H
#define TYPE_HELPER_H

#define isArithmeticType(t) \
  (dynamic_cast<ArithmeticType const *>(t) != NULL)

#define isCompleteObjType(t) \
  (dynamic_cast<ObjType const *>(t) != NULL &&	\
   (dynamic_cast<ObjType const *>(t))->isComplete())

#define isPointerType(t) \
  (dynamic_cast<PtrType const *>(t) != NULL)

#define pointerType(t) \
  (dynamic_cast<PtrType const*>(t))

#define isConstantType(t) \
  (dynamic_cast<Constant const*>(t) != NULL)

#define isIntegerType(t) \
  (dynamic_cast<BasicType const*>(t) != NULL)

#endif
