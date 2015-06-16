#include "maquina.h"

JVM maquina;

uint8_t WIDE = 0;

static void _nop() {
	maquina.current_frame->pc++;
}

static void _aconst_null() {
    maquina.current_frame->push(0);
    maquina.current_frame->pc++;
}

static void _iconst_m1() {
	maquina.current_frame->push(-1);
	maquina.current_frame->pc++;
}

static void _iconst_0() {
    maquina.current_frame->push(0);
    maquina.current_frame->pc++;
}

static void _iconst_1() {
	maquina.current_frame->push(1);
	maquina.current_frame->pc++;
}

static void _iconst_2() {
    maquina.current_frame->push(2);
    maquina.current_frame->pc++;
}


static void _iconst_3() {
	maquina.current_frame->push(3);
	maquina.current_frame->pc++;
}

static void _iconst_4() {
    maquina.current_frame->push(4);
    maquina.current_frame->pc++;
}

static void _iconst_5() {
	maquina.current_frame->push(5);
	maquina.current_frame->pc++;
}

static void _lconst_0() {
    maquina.current_frame->push(0);
    maquina.current_frame->push(0);
    maquina.current_frame->pc++;
}

static void _lconst_1() {
	maquina.current_frame->push(0);
	maquina.current_frame->push(1);
	maquina.current_frame->pc++;
}

static void _fconst_0() {
    float float_number = 0.0;
    maquina.current_frame->push(*((uint32_t*)&float_number));
    maquina.current_frame->pc++;
}

static void _fconst_1() {
    float float_number = 1.0;
    maquina.current_frame->push(*((uint32_t*)&float_number));
    maquina.current_frame->pc++;
}

static void _fconst_2() {
    float float_number = 2.0;
    maquina.current_frame->push(*((uint32_t*)&float_number));
    maquina.current_frame->pc++;
}
static void _dconst_0() {
	//testar
	uint32_t auxiliar_32;
	uint64_t auxiliar_64;
	double double_number = 0.0;

	auxiliar_32 = *(uint64_t*)double_number >> 32;
	maquina.current_frame->push(auxiliar_32);
	auxiliar_32 = *(uint64_t*)double_number;
	maquina.current_frame->push(auxiliar_32);

}

static void _dconst_1() {
	uint32_t auxiliar_32;
	uint64_t auxiliar_64;
	double double_number = 1.0;

	auxiliar_32 = *(uint64_t*)double_number >> 32;
	maquina.current_frame->push(auxiliar_32);
	auxiliar_32 = *(uint64_t*)double_number;
	maquina.current_frame->push(auxiliar_32);
}

static void _bipush() {
    //Pula os 8 bits codigo da instrucao contida no array de codes
    maquina.current_frame->pc++;
    maquina.current_frame->push(maquina.current_frame->code_attr->code[maquina.current_frame->pc]);
    maquina.current_frame->pc++;
}

static void _sipush() {
	uint8_t high,low;
	int16_t auxiliar_16;
	
	maquina.current_frame->pc++;	
	high = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
	maquina.current_frame->pc++;
	low = maquina.current_frame->code_attr->code[maquina.current_frame->pc];

	auxiliar_16 = high;
	auxiliar_16 <<= 8;
	auxiliar_16 |= low;
	
	maquina.current_frame->push((int32_t)auxiliar_16);
	maquina.current_frame->pc++;
}

static void _ldc() {
    uint8_t indice, type;
    
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;
    
    if(type == tInteger){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Integer.bytes);
    }else if(type == tFloat){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Float.bytes);
    }else if(type == tString){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.String.stringIndex);
    }
    
}

static void _ldc_w() {
	uint32_t indice;
	uint8_t type;
	uint32_t high, low, completeValue;
	
	maquina.current_frame->pc++;

	high = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
	maquina.current_frame->pc++;
	low = maquina.current_frame->code_attr->code[maquina.current_frame->pc];

	completeValue = high;
	completeValue = completeValue << 8;
	completeValue = completeValue | low;

	type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;

	if(type == tInteger){
		maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Integer.bytes);
	}
	if(type == tFloat){
		maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Float.bytes);
	}
	else if(type == tString){
		maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.String.stringIndex);
	}

	maquina.current_frame->pc++;
}

static void _ldc2_w() {
    
    uint32_t indice;
    uint8_t type;
    uint32_t high, low, completeValue;
    
    maquina.current_frame->pc++;
    
    high = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    maquina.current_frame->pc++;
    low = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    completeValue = high;
    completeValue = completeValue << 8;
    completeValue = completeValue | low;
    
    type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;
    
    if(type == tLong){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Long.highBytes);
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Long.lowBytes);
    }else if(type == tDouble){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Double.highBytes);
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Double.lowBytes);
    }
    
    maquina.current_frame->pc++;
}

static void _iload() {
	
	uint16_t indice;
	maquina.current_frame->pc++;
	indice =  maquina.current_frame->code_attr->code[maquina.current_frame->pc];

	if(WIDE == 1){
		indice = indice << 8;
		maquina.current_frame->pc++;
		indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
		WIDE = 0;
	}
	maquina.current_frame->push(maquina.current_frame->local_variables[indice]);
	maquina.current_frame->pc++;
}

static void _lload() {
    uint16_t indice;
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    if(WIDE == 1){
        indice = indice << 8;
        maquina.current_frame->pc++;
        indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
        WIDE = 0;
    }
    
    maquina.current_frame->push(maquina.current_frame->local_variables[indice]);
    maquina.current_frame->push(maquina.current_frame->local_variables[indice+1]);
    maquina.current_frame->pc++;
    
}
static void _fload() {
	_iload();
}

static void _dload() {
    _lload();
}

static void _aload() {
	_iload();
}

static void _iload_0() {
    maquina.current_frame->push(maquina.current_frame->local_variables[0]);
    maquina.current_frame->pc++;
}

static void _iload_1() {
	maquina.current_frame->push(maquina.current_frame->local_variables[1]);
	maquina.current_frame->pc++;
}

static void _iload_2() {
    maquina.current_frame->push(maquina.current_frame->local_variables[2]);
    maquina.current_frame->pc++;
}

static void _iload_3() {
	maquina.current_frame->push(maquina.current_frame->local_variables[3]);
	maquina.current_frame->pc++;
}

static void _lload_0() {
    maquina.current_frame->push(maquina.current_frame->local_variables[0]);
    maquina.current_frame->push(maquina.current_frame->local_variables[1]);
    maquina.current_frame->pc++;
}

static void _lload_1() {
	maquina.current_frame->push(maquina.current_frame->local_variables[1]);
	maquina.current_frame->push(maquina.current_frame->local_variables[2]);
	maquina.current_frame->pc++;
}

static void _lload_2() {
    maquina.current_frame->push(maquina.current_frame->local_variables[2]);
    maquina.current_frame->push(maquina.current_frame->local_variables[3]);
    maquina.current_frame->pc++;
}

static void _lload_3() {
	maquina.current_frame->push(maquina.current_frame->local_variables[3]);
	maquina.current_frame->push(maquina.current_frame->local_variables[4]);
	maquina.current_frame->pc++;
}

static void _fload_0() {
    _iload_0();
}

static void _fload_1() {
	_iload_1();
}

static void _fload_2() {
    _iload_2();
}


static void _fload_3() {
	_iload_3();
}

static void _dload_0() {
    _lload_0();
}

static void _dload_1() {
	_lload_1();
}

static void _dload_2() {
    _lload_2();
}

static void _dload_3() {
	_lload_3();;
}

static void _aload_0() {
    _iload_0();
}

static void _aload_1() {
	_iload_1();
}

static void _aload_2() {
    _iload_2();
}

static void _aload_3() {
	_iload_3();
}

static void _iaload() {
    uint32_t indice;
    void *point;
    indice = maquina.current_frame->pop();
    point = (void *)(maquina.current_frame->pop());
    maquina.current_frame->push(((uint32_t *)point)[indice]);
    maquina.current_frame->pc++;
}

static void _laload() {
	uint32_t indice;
	void *point;
	indice = maquina.current_frame->pop();
	point = (void *) maquina.current_frame->pop();
	maquina.current_frame->push2(((uint64_t *)point)[indice]);
	maquina.current_frame->pc++;
}

static void _faload() {
    uint32_t retorno, indice;
    void *point;
    indice = maquina.current_frame->pop();
    point = (void *)(maquina.current_frame->pop());
    memcpy(&retorno, &((float *)point)[indice], sizeof(retorno));
    maquina.current_frame->push(retorno);
    maquina.current_frame->pc++;
}

static void _daload() {
	_laload();
}

static void _aaload() {
    uint32_t indice;
    void *point;
    indice = maquina.current_frame->pop();
    point = (void *)maquina.current_frame->pop();
    maquina.current_frame->push(((uint32_t *)point)[indice]);
    maquina.current_frame->pc++;
}

static void _baload() {
	uint32_t indice;
	void *point;
	indice = maquina.current_frame->pop();
	point = (void *) maquina.current_frame->pop();
	maquina.current_frame->push((uint32_t)(((uint8_t *)point)[indice]));
	maquina.current_frame->pc++;

}

static void _caload() {
    uint32_t indice;
    void *point;
    indice = maquina.current_frame->pop();
    point = (void *)maquina.current_frame->pop();
    maquina.current_frame->push((uint32_t)(((uint16_t*)point)[indice]));
    maquina.current_frame->pc++;
}

static void _saload() {
	_caload();
}

static void _istore() {
    uint16_t indice;
    uint32_t value;
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    value = maquina.current_frame->pop();
    maquina.current_frame->local_variables[indice] = value;
    maquina.current_frame->pc++;
}

static void _lstore() {
	uint16_t indice;
	uint32_t high, low;
	maquina.current_frame->pc++;
	
	indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	maquina.current_frame->local_variables[indice] = high;
	maquina.current_frame->local_variables[indice+1] = low;

	maquina.current_frame->pc++;
}

static void _fstore() {
    _istore();
}

static void _dstore() {
	uint16_t indice;
	uint32_t high, low;
	maquina.current_frame->pc++;
	
	indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	maquina.current_frame->local_variables[indice] = low;
	maquina.current_frame->local_variables[indice+1] = high;

	maquina.current_frame->pc++;
}

static void _astore() {
    _istore();
}

static void _istore_0() {
	uint32_t value;
	value = maquina.current_frame->pop();
	maquina.current_frame->local_variables[0] = value;
	maquina.current_frame->pc++;
}

static void _istore_1() {
    uint32_t value;
    value = maquina.current_frame->pop();
    maquina.current_frame->local_variables[1] = value;
    maquina.current_frame->pc++;
}

static void _istore_2() {
	uint32_t value;
	value = maquina.current_frame->pop();
	maquina.current_frame->local_variables[2] = value;
	maquina.current_frame->pc++;
}

static void _istore_3() {
    uint32_t value;
    value = maquina.current_frame->pop();
    maquina.current_frame->local_variables[3] = value;
    maquina.current_frame->pc++;
}

static void _lstore_0() {
	uint32_t high, low;
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	maquina.current_frame->local_variables[0] = high;
	maquina.current_frame->local_variables[1] = low;
	maquina.current_frame->pc++;
}

static void _lstore_1() {
    uint32_t high, low;
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    maquina.current_frame->local_variables[1]= high;
    maquina.current_frame->local_variables[2] = low;
    maquina.current_frame->pc++;
}

static void _lstore_2() {
	uint32_t high, low;
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	maquina.current_frame->local_variables[2] = high;
	maquina.current_frame->local_variables[3] = low;
	maquina.current_frame->pc++;
}

static void _lstore_3() {
    uint32_t high, low;
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    maquina.current_frame->local_variables[3]= high;
    maquina.current_frame->local_variables[4] = low;
    maquina.current_frame->pc++;
}

static void _fstore_0() {
	uint32_t  value;
	valor = maquina.current_frame->pop();
	maquina.current_frame->local_variables[0] = value;
	maquina.current_frame->pc++;
}

static void _fstore_1() {
    _istore_1();
}


static void _fstore_2() {
	//TODO
}

static void _fstore_3() {
    _istore_3();
}

static void _dstore_0() {
	//TODO
}

static void _dstore_1() {
    _lstore_1();
}

static void _dstore_2() {
	//TODO
}

static void _dstore_3() {
    _lstore_3();
}

static void _astore_0() {
	//TODO
}

static void _astore_1() {
    uint32_t value;
    value = maquina.current_frame->pop();
    maquina.current_frame->local_variables[1] = value;
    maquina.current_frame->pc++;
}

static void _astore_2() {
	//TODO
}

static void _astore_3() {
    uint32_t value;
    value = maquina.current_frame->pop();
    maquina.current_frame->local_variables[3] = value;
    maquina.current_frame->pc++;
}

static void _iastore() {
	//TODO
}


static void _lastore() {
    uint32_t indice, low, high;
    uint16_t value;
    uint64_t auxValue;
    void *point;
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    auxValue = high;
    auxValue = auxValue << 32;
    value = auxValue + low;
    indice = maquina.current_frame->pop();
    point = (void *)maquina.current_frame->pop();
    ((uint16_t *)point)[indice] = value;
    maquina.current_frame->pc++;
}

static void _fastore() {
	//TODO
}

static void _dastore() {
	//TODO
}

static void _aastore() {
	//TODO
}

static void _bastore() {
	//TODO
}

static void _castore() {
	//TODO
}

static void _sastore() {
	//TODO
}

static void _pop() {
	//TODO
}		

static void _pop2() {
	//TODO
}	

static void _dup() {
	//TODO
}

static void _dup_x1() {
	//TODO
}

static void _dup_x2() {
	//TODO
}	

static void _dup2 () {
	//TODO
}

static void _dup2_x1() {
	//TODO
}

static void _dup2_x2() {
	//TODO
}

static void _swap() {
	//TODO
}	

static void _iadd() {
	//TODO
}	

static void _ladd() {
	//TODO
}	

static void _fadd() {
	//TODO
}	

static void _dadd() {
	//TODO
}	

static void _isub() {
	//TODO
}	

static void _lsub() {
	//TODO
}	

static void _fsub() {
	//TODO
}	

static void _dsub() {
	//TODO
}	

static void _imul() {
	//TODO
}	

static void _lmul() {
	//TODO
}	

static void _fmul() {
	//TODO
}	

static void _dmul() {
	//TODO
}	

static void _idiv() {
	//TODO
}	

static void _ldiv() {
	//TODO
}	

static void _fdiv() {
	//TODO
}	

static void _ddiv() {
	//TODO
}	

static void _irem() {
	//TODO
}	

static void _lrem() {
	//TODO
}	

static void _frem() {
	//TODO
}	

static void _drem() {
	//TODO
}	

static void _ineg() {
	//TODO
}	

static void _lneg() {
	//TODO
}	

static void _fneg() {
	//TODO
}	

static void _dneg() {
	//TODO
}	

static void _ishl() {
	//TODO
}	

static void _lshl() {
	//TODO
}	

static void _ishr() {
	//TODO
}	

static void _lshr() {
	//TODO
}	

static void _iushr() {
	//TODO
}

static void _lushr() {
	//TODO
}

static void _iand() {
	//TODO
}

static void _land() {
	//TODO
}

static void _ior	() {
	//TODO
}

static void _lor	() {
	//TODO
}

static void _ixor() {
	//TODO
}

static void _lxor() {
	//TODO
}

static void _iinc() {
	//TODO
}

static void _i2l	() {
	//TODO
}

static void _i2f	() {
	//TODO
}

static void _i2d	() {
	//TODO
}

static void _l2i	() {
	//TODO
}

static void _l2f	() {
	//TODO
}

static void _l2d	() {
	//TODO
}

static void _f2i	() {
	//TODO
}

static void _f2l	() {
	//TODO
}

static void _f2d	() {
	//TODO
}

static void _d2i	() {
	//TODO
}

static void _d2l	() {
	//TODO
}

static void _d2f	() {
	//TODO
}

static void _i2b	() {
	//TODO
}

static void _i2c	() {
	//TODO
}

static void _i2s	() {
	//TODO
}

static void _lcmp() {
	//TODO
}

static void _fcmpl() {
	//TODO
}

static void _fcmpg() {
	//TODO
}

static void _dcmpl() {
	//TODO
}

static void _dcmpg() {
	//TODO
}

static void _ifeq() {
	//TODO
}

static void _ifne() {
	//TODO
}

static void _iflt() {
	//TODO
}

static void _ifge() {
	//TODO
}

static void _ifgt() {
	//TODO
}

static void _ifle() {
	//TODO
}

static void _if_icmpeq() {
	//TODO
}

static void _if_icmpne() {
	//TODO
}

static void _if_icmplt() {
	//TODO
}

static void _if_icmpge() {
	//TODO
}

static void _if_icmpgt() {
	//TODO
}

static void _if_icmple() {
	//TODO
}

static void _if_acmpeg() {
	//TODO
}

static void _if_acmpne() {
	//TODO
}

static void _goto() {
	//TODO
}

static void _jsr	() {
	//TODO
}

static void _ret	() {
	//TODO
}

static void _tableswitch() {
	//TODO
}

static void _lookupswitch() {
	//TODO
}

static void _ireturn() {
	//TODO
}

static void _lreturn() {
	//TODO
}

static void _freturn() {
	//TODO
}

static void _dreturn() {
	//TODO
}

static void _areturn() {
	//TODO
}

static void _return() {
	//TODO
}

static void _getstatic() {
	//TODO
}

static void _putstatic() {
	//TODO
}

static void _getfield() {
	//TODO
}

static void _putfield() {
	//TODO
}

static void _invokevirtual() {
	//TODO
}

static void _invokespecial() {
	//TODO
}

static void _invokestatic() {
	//TODO
}

static void _invokeinterface() {
	//TODO
}

static void _new() {
	//TODO
}

static void _newarray() {
	//TODO
}

static void _anewarray() {
	//TODO
}

static void _arraylength() {
	//TODO
}

static void _athrow() {
	//TODO
}

static void _checkcast() {
	//TODO
}

static void _instanceof() {
	//TODO
}

static void _monitorenter() {
	//TODO
}

static void _monitorexit() {
	//TODO
}

static void _wide() {
	WIDE = 1;
	maquina.current_frame->pc++;
}

static void _multianewarray() {
	//TODO
}

static void _ifnull() {
	//TODO
}

static void _ifnonnull() {
	//TODO
}

static void _goto_w() {
	//TODO
}

static void _jsr_w() {
	//TODO
}

const JVM_INSTRUCTION instructions[] = {
	{0, 	"nop", 				_nop			},
	{0, 	"aconst_null", 		_aconst_null	},
	{0, 	"iconst_m1", 		_iconst_m1		},
	{0, 	"iconst_0", 		_iconst_0		},
	{0, 	"iconst_1",			_iconst_1		},
	{0, 	"iconst_2",			_iconst_2		},
	{0, 	"iconst_3",			_iconst_3		},
	{0, 	"iconst_4",			_iconst_4		},
	{0, 	"iconst_5",			_iconst_5		},
	{0, 	"lconst_0",			_lconst_0		},
	{0, 	"lconst_1",			_lconst_1		},
	{0, 	"fconst_0",			_fconst_0		},
	{0, 	"fconst_1",			_fconst_1		},
	{0, 	"fconst_2",			_fconst_2		},
	{0, 	"dconst_0",			_dconst_0		},
	{0, 	"dconst_1",			_dconst_1		},
	{1, 	"bipush",			_bipush			},
	{2, 	"sipush",			_sipush			},
	{1, 	"ldc",				_ldc			},
	{2, 	"ldc_w",			_ldc_w			},
	{2, 	"ldc2_w",			_ldc2_w			},
	{1, 	"iload",			_iload			},
	{1, 	"lload",			_lload			},
	{1, 	"fload",			_fload			},
	{1, 	"dload",			_dload			},
	{1, 	"aload",			_aload			},
	{0, 	"iload_0",			_iload_0		},
	{0, 	"iload_1",			_iload_1		},
	{0, 	"iload_2",			_iload_2		},
	{0, 	"iload_3",			_iload_3		},
	{0, 	"lload_0",			_lload_0		},
	{0, 	"lload_1",			_lload_1		},
	{0, 	"lload_2",			_lload_2		},
	{0, 	"lload_3",			_lload_3		},
	{0, 	"fload_0",			_fload_0		},
	{0, 	"fload_1",			_fload_1		},
	{0, 	"fload_2",			_fload_2		},
	{0, 	"fload_3",			_fload_3		},
	{0, 	"dload_0",			_dload_0		},
	{0, 	"dload_1",			_dload_1		},
	{0, 	"dload_2",			_dload_2		},
	{0, 	"dload_3",			_dload_3		},
	{0, 	"aload_0",			_aload_0		},
	{0, 	"aload_1",			_aload_1		},
	{0, 	"aload_2",			_aload_2		},
	{0, 	"aload_3",			_aload_3		},
	{0, 	"iaload",			_iaload			},
	{0, 	"laload",			_laload			},
	{0, 	"faload",			_faload			},
	{0, 	"daload",			_daload			},
	{0, 	"aaload",			_aaload			},
	{0, 	"baload",			_baload			},
	{0, 	"caload",			_caload			},
	{0, 	"saload",			_saload			},
	{1, 	"istore",			_istore			},
	{1, 	"lstore",			_lstore			},
	{1, 	"fstore",			_fstore			},
	{1, 	"dstore",			_dstore			},
	{1, 	"astore",			_astore			},
	{0, 	"istore_0",			_istore_0		},
	{0, 	"istore_1",			_istore_1		},
	{0, 	"istore_2",			_istore_2		},
	{0, 	"istore_3",			_istore_3		},
	{0, 	"lstore_0",			_lstore_0		},
	{0, 	"lstore_1",			_lstore_1		},
	{0, 	"lstore_2",			_lstore_2		},
	{0, 	"lstore_3",			_lstore_3		},
	{0, 	"fstore_0",			_fstore_0		},
	{0, 	"fstore_1",			_fstore_1		},
	{0, 	"fstore_2",			_fstore_2		},
	{0, 	"fstore_3",			_fstore_3		},
	{0, 	"dstore_0",			_dstore_0		},
	{0, 	"dstore_1",			_dstore_1		},
	{0, 	"dstore_2",			_dstore_2		},
	{0, 	"dstore_3",			_dstore_3		},
	{0, 	"astore_0",			_astore_0		},
	{0, 	"astore_1",			_astore_1		},
	{0, 	"astore_2",			_astore_2		},
	{0, 	"astore_3",			_astore_3		},
	{0, 	"iastore",			_iastore		},
	{0, 	"lastore",			_lastore		},
	{0, 	"fastore",			_fastore		},
	{0, 	"dastore",			_dastore		},
	{0, 	"aastore",			_aastore		},
	{0, 	"bastore",			_bastore		},
	{0, 	"castore",			_castore		},
	{0, 	"sastore",			_sastore		},
	{0, 	"pop",				_pop			},
	{0, 	"pop2",				_pop2			},
	{0, 	"dup",				_dup			},
	{0, 	"dup_x1",			_dup_x1			},
	{0, 	"dup_x2",			_dup_x2			},
	{0, 	"dup2",				_dup2			},
	{0, 	"dup2_x1",			_dup2_x1		},
	{0, 	"dup2_x2",			_dup2_x2		},
	{0, 	"swap",				_swap			},
	{0, 	"iadd",				_iadd			},
	{0, 	"ladd",				_ladd			},
	{0, 	"fadd",				_fadd			},
	{0, 	"dadd",				_dadd			},
	{0, 	"isub",				_isub			},
	{0, 	"lsub",				_lsub			},
	{0, 	"fsub",				_fsub			},
	{0, 	"dsub",				_dsub			},
	{0, 	"imul",				_imul			},
	{0, 	"lmul",				_lmul			},
	{0, 	"fmul",				_fmul			},
	{0, 	"dmul",				_dmul			},
	{0, 	"idiv",				_idiv			},
	{0, 	"ldiv",				_ldiv			},
	{0, 	"fdiv",				_fdiv			},
	{0, 	"ddiv",				_ddiv			},
	{0, 	"irem",				_irem			},
	{0, 	"lrem",				_lrem			},
	{0, 	"frem",				_frem			},
	{0, 	"drem",				_drem			},
	{0, 	"ineg",				_ineg			},
	{0, 	"lneg",				_lneg			},
	{0, 	"fneg",				_fneg			},
	{0, 	"dneg",				_dneg			},
	{0, 	"ishl",				_ishl			},
	{0, 	"lshl",				_lshl			},
	{0, 	"ishr",				_ishr			},
	{0, 	"lshr",				_lshr			},
	{0, 	"iushr",			_iushr			},
	{0, 	"lushr",			_lushr			},
	{0, 	"iand",				_iand			},
	{0, 	"land",				_land			},
	{0, 	"ior",				_ior			},
	{0, 	"lor",				_lor			},
	{0, 	"ixor",				_ixor			},
	{0, 	"lxor",				_lxor			},
	{2, 	"iinc",				_iinc			},
	{0, 	"i2l",				_i2l			},
	{0, 	"i2f",				_i2f			},
	{0, 	"i2d",				_i2d			},
	{0, 	"l2i",				_l2i			},
	{0, 	"l2f",				_l2f			},
	{0, 	"l2d",				_l2d			},
	{0, 	"f2i",				_f2i			},
	{0, 	"f2l",				_f2l			},
	{0, 	"f2d",				_f2d			},
	{0, 	"d2i",				_d2i			},
	{0, 	"d2l",				_d2l			},
	{0, 	"d2f",				_d2f			},
	{0, 	"i2b",				_i2b			},
	{0, 	"i2c",				_i2c			},
	{0, 	"i2s",				_i2s			},
	{0, 	"lcmp",				_lcmp			},
	{0, 	"fcmpl",			_fcmpl			},
	{0, 	"fcmpg",			_fcmpg			},
	{0, 	"dcmpl",			_dcmpl			},
	{0, 	"dcmpg",			_dcmpg			},
	{2, 	"ifeq",				_ifeq			},
	{2, 	"ifne",				_ifne			},
	{2, 	"iflt",				_iflt			},
	{2, 	"ifge",				_ifge			},
	{2, 	"ifgt",				_ifgt			},
	{2, 	"ifle",				_ifle			},
	{2, 	"if_icmpeq",		_if_icmpeq		},
	{2, 	"if_icmpne",		_if_icmpne		},
	{2, 	"if_icmplt",		_if_icmplt		},
	{2, 	"if_icmpge",		_if_icmpge		},
	{2, 	"if_icmpgt",		_if_icmpgt		},
	{2, 	"if_icmple",		_if_icmple		},
	{2, 	"if_acmpeg",		_if_acmpeg		},
	{2, 	"if_acmpne",		_if_acmpne		},
	{2, 	"goto",				_goto			},
	{2, 	"jsr",				_jsr			},
	{1, 	"ret",				_ret			},
	{14, 	"tableswitch",		_tableswitch	},
	{10,	"lookupswitch",		_lookupswitch	},
	{0, 	"ireturn",			_ireturn		},
	{0, 	"lreturn",			_lreturn		},
	{0, 	"freturn",			_freturn		},
	{0, 	"dreturn",			_dreturn		},
	{0, 	"areturn",			_areturn		},
	{0, 	"return",			_return			},
	{2, 	"getstatic",		_getstatic		},
	{2, 	"putstatic",		_putstatic		},
	{2, 	"getfield",			_getfield		},
	{2, 	"putfield",			_putfield		},
	{2, 	"invokevirtual",	_invokevirtual	},
	{2, 	"invokespecial",	_invokespecial	},
	{2, 	"invokestatic",		_invokestatic	},
	{4, 	"invokeinterface",	_invokeinterface},
	{0, 	NULL,				NULL			},
	{2, 	"new",				_new			},
	{1, 	"newarray",			_newarray		},
	{2, 	"anewarray",		_anewarray		},
	{0, 	"arraylength",		_arraylength	},
	{0, 	"athrow",			_athrow			},
	{0, 	"checkcast",		_checkcast		},
	{0, 	"instanceof",		_instanceof		},
	{0, 	"monitorenter",		_monitorenter	},
	{0, 	"monitorexit",		_monitorexit	},
	{7, 	"wide",				_wide			},
	{3, 	"multianewarray",	_multianewarray	},
	{2, 	"ifnull",			_ifnull			},
	{2, 	"ifnonnull",		_ifnonnull		},
	{4, 	"goto_w",			_goto_w			},
	{4, 	"jsr_w",			_jsr_w			}
};
