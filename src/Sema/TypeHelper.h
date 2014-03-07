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

#define isFunctionType(t) \
  (dynamic_cast<FuncType const*>(t) != NULL)

// Integer + real floating. Same as integer in our case.
#define isRealType(t) \
  (dynamic_cast<BasicType const*>(t) != NULL)

#define isStructType(t) \
  (dynamic_cast<StructType const*>(t) != NULL)

//Cast functions
#define toPointerType(t) \
  (dynamic_cast<PtrType const*>(t))

#define toFunctionType(t) \
  (dynamic_cast<FuncType const*>(t))

#define toObjType(t) \
  (dynamic_cast<ObjType const*>(t))

#define toStructType(t) \
  (dynamic_cast<StructType const*>(t))

//Note: these take an Expr object
#define isNullPointerConstant(e) \
  (e->getEntity() != NULL && \
    e->getEntity()->type == TypeFactory::getInt() && \
    e->tok.sym == Symbol("0"))

#define isUnaryOperation(e) \
  (dynamic_cast<UnaryOperation const*>(e) != NULL)

#define toExprList(e) \
  (dynamic_cast<ExprList const*>(e))
#endif
