#ifndef _EVAL_LETREC
#define _EVAL_LETREC

Value *eval_letrec(Value *args, Value *expr, Frame *parent_frame);

#endif
