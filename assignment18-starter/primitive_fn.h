#ifndef _PRIMITIVE_FN
#define _PRIMITIVE_FN

Value *prim_add(Value *args);

Value *prim_null(Value *arg);

Value *prim_car(Value *arg);

Value *prim_cdr(Value *arg);

Value *prim_cons(Value *args);

Value *prim_subtract(Value *args);

Value *prim_equal(Value *args);

#endif
