#include "net_protected.h"
#include "print_funcs.h"

#include "pickle.h"
#include "op_split.h"

//-------------------------------------------------
//----- descriptor
static const char* op_split_instring = "VAL     ";
static const char* op_split_outstring = "OUT1    OUT2    ";
static const char* op_split_opstring = "SPLIT";

//-------------------------------------------------
//----- static function declaration


// UI increment
static void op_split_inc(op_split_t* split, const s16 idx, const io_t inc);
// set inputs
static void op_split_in_val(op_split_t* split, const io_t v);
// pickle / unpickle
static u8* op_split_pickle(op_split_t* split, u8* dst);
static u8* op_split_unpickle(op_split_t* split, const u8* src);

// array of input functions 
static op_in_fn op_split_in[1] = {
  (op_in_fn)&op_split_in_val,
};

//----- external function definition

/// initialize
void op_split_init(void* op) {
  op_split_t* split = (op_split_t*)op;

  // superclass functions
  split->super.inc_fn = (op_inc_fn)&op_split_inc;
  split->super.in_fn = op_split_in;
  split->super.pickle = (op_pickle_fn) (&op_split_pickle);
  split->super.unpickle = (op_unpickle_fn) (&op_split_unpickle);
  
  // superclass state
  split->super.numInputs = 1;
  split->super.numOutputs = 2;
  split->outs[0] = -1;
  split->outs[1] = -1;
 
  split->super.in_val = split->in_val;
  split->in_val[0] = &(split->val);

  split->super.out = split->outs;
  split->super.opString = op_split_opstring;
  split->super.inString = op_split_instring;
  split->super.outString = op_split_outstring;
  split->super.type = eOpSplit;

  // class state
  split->val = 0;
}

//-------------------------------------------------
//----- static function definition

//===== operator input

// input state
static void op_split_in_val(op_split_t* split, const io_t v) {
  split->val = v;
  net_activate(split->outs[0], split->val, split);
  net_activate(split->outs[1], split->val, split);
}

//===== UI input

// increment
static void op_split_inc(op_split_t* split, const s16 idx, const io_t inc) {
  // no UI
  ;;
}

// serialization
u8* op_split_pickle(op_split_t* split, u8* dst) {
  // no state
  return dst;
}

u8* op_split_unpickle(op_split_t* split, const u8* src) {
  // no state
  return (u8*)src;
}
