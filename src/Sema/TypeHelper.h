#ifndef TYPE_HELPER_H
#define TYPE_HELPER_H

#define isArithmeticType(t) \
  (dynamic_cast<ArithmeticType const *>(t) != NULL)

#define isCompleteObjType(t) \
  (dynamic_cast<ObjType const *>(t) != NULL &&	\
   (dynamic_cast<ObjType const *>(t))->isComplete())

#define isObjType(t) \
  (dynamic_cast<ObjType const *>(t) != NULL)

#define isPointerType(t) \
  (dynamic_cast<PtrType const *>(t) != NULL)

// 'char' or 'int'
#define isIntegerType(t) \
  (dynamic_cast<BasicType const*>(t) != NULL)

#define isVoidType(t) \
  (dynamic_cast<VoidType const*>(t) != NULL)

#define isScalarType(t) \
  (dynamic_cast<ScalarType const*>(t) != NULL)

//Cast functions
#define toPointerType(t) \
  (dynamic_cast<PtrType const*>(t))

//Note: this takes an Expr object
#define isNullPointerConstant(e) \
  (e->getEntity() != NULL && \
    e->getEntity()->type == TypeFactory::getInt() && \
    e->tok.sym == Symbol("0"))

#endif
