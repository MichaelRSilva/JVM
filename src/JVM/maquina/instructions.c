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
	
	uint32_t auxiliar_32;
	double double_number = 0.0;
	int64_t *auxiliar_64 = malloc(sizeof(uint64_t));

	memcpy(auxiliar_64, &double_number, sizeof(uint64_t));
	auxiliar_32 = *auxiliar_64 >> 32;
	maquina.current_frame->push(auxiliar_32);
	auxiliar_32 = *auxiliar_64 & 0xffffffff;
	maquina.current_frame->push(auxiliar_32);
	maquina.current_frame->pc++;
        

}

static void _dconst_1() {
	uint32_t auxiliar_32;
	double double_number = 1.0;
	int64_t *auxiliar_64 = malloc(2 * sizeof(uint32_t));

	memcpy(auxiliar_64, &double_number, 2 * sizeof(uint32_t));
	auxiliar_32 = *auxiliar_64 >> 32;
	maquina.current_frame->push(auxiliar_32);
	auxiliar_32 = *auxiliar_64 & 0xffffffff;
	maquina.current_frame->push(auxiliar_32);
	maquina.current_frame->pc++;
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

    maquina.current_frame->pc++;
    
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
    uint32_t indice, aux;
    uint32_t* arrayRef;

    indice 	 = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint32_t));
    maquina.current_frame->push(arrayRef[indice]);
    maquina.current_frame->pc++;
}

static void _laload() {
	uint32_t indice,aux;
	uint64_t* arrayRef;

	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint32_t));
	maquina.current_frame->push2(arrayRef[indice]);
	maquina.current_frame->pc++;
}

static void _faload() {
    uint32_t indice, aux, aux2;
    uint32_t* arrayRef;

    indice 	 = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint32_t));
    memcpy(&aux2, &((float *)arrayRef)[indice], sizeof(uint32_t));
    maquina.current_frame->push(aux2);
    maquina.current_frame->pc++;
}

static void _daload() {
	_laload();
}

static void _aaload() {
    _iaload();
}

static void _baload() {
	uint32_t indice,aux;
	uint8_t* arrayRef;

	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint8_t));
	maquina.current_frame->push(arrayRef[indice]);
	maquina.current_frame->pc++;

}

static void _caload() {
    uint32_t indice,aux;
	uint16_t* arrayRef;

	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint16_t));
	maquina.current_frame->push(arrayRef[indice]);
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
	value = maquina.current_frame->pop();
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
    uint32_t indice, low, high,aux;
    uint16_t value;
    uint64_t auxValue;
    int32_t* arrayRef;


    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    auxValue = high;
    auxValue = auxValue << 32;
    value = auxValue + low;

    aux = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint32_t));
    arrayRef[indice] = value;
    maquina.current_frame->pc++;
}

static void _fastore() {
	uint32_t indice,aux,valor;
	uint16_t* arrayRef;

	valor = maquina.current_frame->pop();
	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint16_t));

	arrayRef[indice] = valor;

	maquina.current_frame->pc++;
}

static void _dastore() {
	uint32_t indice, low, high,aux;
    uint16_t value;
    uint64_t auxValue;
    int32_t* arrayRef;


    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    auxValue = high;
    auxValue = auxValue << 32;
    value = auxValue + low;

    aux = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint32_t));
    arrayRef[indice] = value;
    maquina.current_frame->pc++;
}

static void _aastore() {
	uint32_t indice,aux,value;
	uint32_t* arrayRef;

	value = maquina.current_frame->pop();
	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint32_t));

	arrayRef[indice] = (uint32_t)value;

	maquina.current_frame->pc++;
}

static void _bastore() {
	uint32_t indice,aux,value;
	uint8_t* arrayRef;

	value = maquina.current_frame->pop();
	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint8_t));

	arrayRef[indice] = (uint8_t)value;

	maquina.current_frame->pc++;
}

static void _castore() {
	uint32_t indice,aux,value;
	uint16_t* arrayRef;

	value = maquina.current_frame->pop();
	indice = maquina.current_frame->pop();
	aux = maquina.current_frame->pop();
	memcpy(&arrayRef, &aux, sizeof(uint16_t));

	arrayRef[indice] = (uint16_t)value;

	maquina.current_frame->pc++;
}

static void _sastore() {
	_castore();
}

static void _pop() {
	maquina.current_frame->pop();
	maquina.current_frame->pc++;
}		

static void _pop2() {
	maquina.current_frame->pop();
	maquina.current_frame->pop();
	maquina.current_frame->pc++;
}	

static void _dup() {
	uint32_t data;
	data = maquina.current_frame->pop();
	maquina.current_frame->push(data);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}

static void _dup_x1() {
	uint32_t data,other;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	maquina.current_frame->push(data);
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}

static void _dup_x2() {
	uint32_t data,other,last;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	last = maquina.current_frame->pop();
	maquina.current_frame->push(data);
	maquina.current_frame->push(last);
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}	

static void _dup2 () {
	uint32_t data,other;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}

static void _dup2_x1() {
	uint32_t data,other,last;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	last = maquina.current_frame->pop();
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->push(last);
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}

static void _dup2_x2() {
	uint32_t data,other,middle,last;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	middle = maquina.current_frame->pop();
	last = maquina.current_frame->pop();
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->push(last);
	maquina.current_frame->push(middle);
	maquina.current_frame->push(other);
	maquina.current_frame->push(data);
	maquina.current_frame->pc++;
}

static void _swap() {
	uint32_t data,other;
	data = maquina.current_frame->pop();
	other = maquina.current_frame->pop();
	maquina.current_frame->push(data);
	maquina.current_frame->push(other);
	maquina.current_frame->pc++;
}	

static void _iadd() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op+opp);
	maquina.current_frame->pc++;
}	

static void _ladd() {
	
	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op+opp);
	maquina.current_frame->pc++;

}	

static void _fadd() {
	
	float op, opp, sum;
	uint32_t value, other,result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	other = maquina.current_frame->pop();
	memcpy(&opp, &other, sizeof(uint32_t));

	sum = op + opp;

	memcpy(&result, &sum, sizeof(uint32_t));
	maquina.current_frame->push(result);

	maquina.current_frame->pc++;
}	

static void _dadd() {
	double op, opp, sum;
	uint64_t result;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	op = getDouble(high,low);

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	opp = getDouble(high,low);

	sum = op + opp;

	memcpy(&result, &sum, sizeof(uint64_t));
	maquina.current_frame->push2(result);
	
	maquina.current_frame->pc++;
}	

static void _isub() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op-opp);
	maquina.current_frame->pc++;
}	

static void _lsub() {
	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op-opp);
	maquina.current_frame->pc++;
}	

static void _fsub() {
	float op, opp, sum;
	uint32_t value, other,result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	other = maquina.current_frame->pop();
	memcpy(&opp, &other, sizeof(uint32_t));

	sum = op - opp;

	memcpy(&result, &sum, sizeof(uint32_t));
	maquina.current_frame->push(result);

	maquina.current_frame->pc++;
}	

static void _dsub() {
	double op, opp, sum;
	uint64_t result;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	op = getDouble(high,low);

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	opp = getDouble(high,low);

	sum = op - opp;

	memcpy(&result, &sum, sizeof(uint64_t));
	maquina.current_frame->push2(result);
	
	maquina.current_frame->pc++;
}	

static void _imul() {
	uint32_t op,opp;
	op  = (int32_t)maquina.current_frame->pop();
	opp = (int32_t)maquina.current_frame->pop();
	maquina.current_frame->push(op*opp);
	maquina.current_frame->pc++;
}	

static void _lmul() {

	int32_t hop, lop, hopp, lopp;
	int64_t op, opp;

	lop  = maquina.current_frame->pop();
	hop  = maquina.current_frame->pop();
	lopp = maquina.current_frame->pop();
	hopp = maquina.current_frame->pop();

	op  = hop;
	op  = op << 32;
	op  = op + lop;

	opp  = hopp;
	opp  = opp << 32;
	opp  = opp + lopp;

	maquina.current_frame->push2((int64_t)(op*opp));
	maquina.current_frame->pc++;

}	

static void _fmul() {
	float op, opp, mult;
	uint32_t value, other,result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	other = maquina.current_frame->pop();
	memcpy(&opp, &other, sizeof(uint32_t));

	mult = op * opp;

	memcpy(&result, &mult, sizeof(uint32_t));
	maquina.current_frame->push((uint32_t)(result));

	maquina.current_frame->pc++;
}	

static void _dmul() {
	int32_t hop, lop, hopp, lopp;
	double op, opp, mult,final;

	lop  = maquina.current_frame->pop();
	hop  = maquina.current_frame->pop();
	lopp = maquina.current_frame->pop();
	hopp = maquina.current_frame->pop();

	op  = getDouble(lop,hop);
	opp  = getDouble(lopp,hopp);
	mult = op*opp;

	memcpy(&final, &mult, sizeof(int64_t));
	maquina.current_frame->push2((int64_t)(final));

	maquina.current_frame->pc++;
}	

static void _idiv() {
	uint32_t op,opp;
	op  = (int32_t)maquina.current_frame->pop();
	opp = (int32_t)maquina.current_frame->pop();
	maquina.current_frame->push(op/opp);
	maquina.current_frame->pc++;
}	

static void _ldiv() {
	
	int32_t hop, lop, hopp, lopp;
	int64_t op, opp;

	lop  = maquina.current_frame->pop();
	hop  = maquina.current_frame->pop();
	lopp = maquina.current_frame->pop();
	hopp = maquina.current_frame->pop();

	op  = hop;
	op  = op << 32;
	op  = op + lop;

	opp  = hopp;
	opp  = opp << 32;
	opp  = opp + lopp;

	maquina.current_frame->push2((int64_t)(op/opp));

	maquina.current_frame->pc++;
}	

static void _fdiv() {
	float op, opp, mult;
	uint32_t value, other,result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	other = maquina.current_frame->pop();
	memcpy(&opp, &other, sizeof(uint32_t));

	mult = op / opp;

	memcpy(&result, &mult, sizeof(uint32_t));
	maquina.current_frame->push((uint32_t)(result));

	maquina.current_frame->pc++;
}	

static void _ddiv() {
	int32_t hop, lop, hopp, lopp;
	double op, opp, mult,final;

	lop  = maquina.current_frame->pop();
	hop  = maquina.current_frame->pop();
	lopp = maquina.current_frame->pop();
	hopp = maquina.current_frame->pop();

	op  = getDouble(lop,hop);
	opp  = getDouble(lopp,hopp);
	mult = op/opp;

	memcpy(&final, &mult, sizeof(int64_t));
	maquina.current_frame->push2((int64_t)(final));

	maquina.current_frame->pc++;
}	

static void _irem() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op%opp);
	maquina.current_frame->pc++;
}	

static void _lrem() {
	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op%opp);
	maquina.current_frame->pc++;
}	

static void _frem() {
	float op, opp, mod;
	uint32_t value, other, result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	other = maquina.current_frame->pop();
	memcpy(&opp, &other, sizeof(uint32_t));

	mod = fmodf(op , opp);
	memcpy(&result, &mod, sizeof(uint32_t));

	maquina.current_frame->push(result);
	maquina.current_frame->pc++;

}	

static void _drem() {
	int32_t hop, lop, hopp, lopp;
	double op, opp, mod;
	int64_t final;

	lop  = maquina.current_frame->pop();
	hop  = maquina.current_frame->pop();
	lopp = maquina.current_frame->pop();
	hopp = maquina.current_frame->pop();

	op  = getDouble(lop,hop);
	opp  = getDouble(lopp,hopp);
	mod = fmod(op,opp);

	memcpy(&final, &mod, sizeof(int64_t));

	maquina.current_frame->push2((int64_t)(final));
	maquina.current_frame->pc++;
}	

static void _ineg() {
	uint32_t op;
	op  = maquina.current_frame->pop();
	maquina.current_frame->push((uint32_t)(-op));
	maquina.current_frame->pc++;
}	

static void _lneg() {
	uint64_t op;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	op = -(op);

	maquina.current_frame->push2(op);
	maquina.current_frame->pc++;
}	

static void _fneg() {
	float op, negative;
	uint32_t value, other,result;

	value = maquina.current_frame->pop();
	memcpy(&op, &value, sizeof(uint32_t));

	negative = -op;

	memcpy(&result, &negative, sizeof(uint32_t));
	maquina.current_frame->push(result);

	maquina.current_frame->pc++;
}	

static void _dneg() {
	double op, negative;
	uint64_t result;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	op = getDouble(high,low);

	negative = -op;

	memcpy(&result, &negative, sizeof(uint64_t));
	maquina.current_frame->push2(result);
	
	maquina.current_frame->pc++;
}	

static void _ishl() {
	uint32_t lowsFive = 0x1f;
	uint32_t value1, value2;
	
	value2 = maquina.current_frame->pop();
	value2 = value2 & lowsFive;

	value1 = maquina.current_frame->pop();
	value1 = value1 << value2;

	maquina.current_frame->push(value1);

	maquina.current_frame->pc++;
}	

static void _lshl() {
	int64_t bigBits;
	uint32_t lowSeven = 0x3f;
	uint32_t low, high, result;

	result = maquina.current_frame->pop();
	result = result & lowSeven;
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	bigBits = high;
	bigBits = bigBits << 32;
	bigBits = (signed)(bigBits + low);


	bigBits = bigBits << result;
	maquina.current_frame->push((uint64_t)bigBits);

	maquina.current_frame->pc++;
}	

static void _ishr() {
	uint32_t value1, value2,lowFive = 0x1f;
	value1 = maquina.current_frame->pop();
	value1 = value1 & lowFive;
	value2 = (int32_t)maquina.current_frame->pop();
	
	for(int j = 0; j < value1; j++) {
		value2 = value2 / 2;
	}

	maquina.current_frame->push((int32_t)value2);
	maquina.current_frame->pc++;
}	

static void _lshr() {
	
	uint64_t allOne = 0xffffffffffffffff, firstOne = 0x8000000000000000, var;	
	uint32_t low, high, vartwo, lowSeven = 0x3f;;

	vartwo = maquina.current_frame->pop();
	vartwo = vartwo & lowSeven;

	allOne = allOne << (64-vartwo);
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();


	var = high;
	var = var << 32;
	var = (signed)(var + low);

	firstOne = var & firstOne;
	var = var >> vartwo;
	
	if(firstOne == 1) {
		var = var | allOne;
	}

	maquina.current_frame->push((uint64_t)var);

	maquina.current_frame->pc++;
}	

static void _iushr() {
	uint32_t lowFive = 0x1f;
	uint32_t value, other;

	other = maquina.current_frame->pop();
	other = other & lowFive;
	value = maquina.current_frame->pop();
	value = value >> other;
	maquina.current_frame->push(value);
	maquina.current_frame->pc++;
}

static void _lushr() {
	int64_t bigBits;
	uint32_t var, low, high, lowFive = 0x3f;

	var = maquina.current_frame->pop();
	var = var & lowFive;

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	
	bigBits = high;
	bigBits = bigBits << 32;
	bigBits = (signed)(bigBits + low);

	bigBits = bigBits >> var;
	maquina.current_frame->push2((uint64_t)bigBits);

	maquina.current_frame->pc++;
}

static void _iand() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op&opp);
	maquina.current_frame->pc++;
}

static void _land() {

	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op&opp);
	maquina.current_frame->pc++;
}

static void _ior() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op|opp);
	maquina.current_frame->pc++;
}

static void _lor() {
	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op|opp);
	maquina.current_frame->pc++;
}

static void _ixor() {
	uint32_t op,opp;
	op  = maquina.current_frame->pop();
	opp = maquina.current_frame->pop();
	maquina.current_frame->push(op^opp);
	maquina.current_frame->pc++;
}

static void _lxor() {
	uint64_t op,opp;
	uint32_t high,low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	op = high;
	op = op << 32;
	op = op + low;

	low  = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	opp = high;
	opp = opp << 32;
	opp = opp + low;

	maquina.current_frame->push2(op^opp);
	maquina.current_frame->pc++;
}

static void _iinc() {
	uint8_t field_index = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	uint32_t auxiliar = maquina.current_frame->local_variables[field_index];
	uint8_t auxiliar2 = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	int8_t index = (int8_t) auxiliar;
	int8_t constant = (int8_t) auxiliar2;


	index += constant;
	maquina.current_frame->local_variables[field_index] = (uint32_t) index;
	maquina.current_frame->pc++;
}

static void _i2l() {
	uint32_t value1, value3, oneOne = 0x80000000;
	uint64_t bigBits,getHigh = 0xffffffff00000000;

	value1 = maquina.current_frame->pop();
	value3 = value1 & oneOne;
	bigBits = (int64_t) value1;
	
	if(value3 == 1) {
		bigBits = bigBits | getHigh;
	}

	maquina.current_frame->push2(bigBits);
	maquina.current_frame->pc++;
}

static void _i2f() {
	int32_t value;
	uint32_t value2;
	
	float number;
	value = (int32_t)maquina.current_frame->pop();
	
	number = (float)value;

	memcpy(&value, &number, sizeof(int32_t));
	maquina.current_frame->push(value2);

	maquina.current_frame->pc++;
}

static void _i2d() {
	int32_t value1;
	double value2;
	uint64_t bigBits;
	
	value1 = (int32_t)maquina.current_frame->pop();
	value2 = (double)value1;

	memcpy(&value2, &value2, sizeof(uint64_t));

	maquina.current_frame->pc++;
}

static void _l2i() {
	uint32_t low, high;
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	maquina.current_frame->push(low);
	maquina.current_frame->pc++;

	maquina.current_frame->pc++;
}

static void _l2f() {
	uint32_t low, high, *parse;
	float number;
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	number = (float)getDouble(low, high);

	parse = (uint32_t*) malloc(sizeof(uint32_t));
	memcpy(parse, &number, sizeof(uint32_t));
	maquina.current_frame->push(*parse); 
	maquina.current_frame->pc++;
}


static void _l2d() {

	uint32_t low, high, value;
	uint64_t *other;

	double double_number;

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	double_number =  getDouble(low, high);
	other = (uint64_t*) malloc(sizeof(uint64_t));
	memcpy(other, &double_number, sizeof(uint64_t));

	value = *other >> 32;
	maquina.current_frame->push(value);

	value = *other;
	maquina.current_frame->push(value);

	maquina.current_frame->pc++;
}

static void _f2i() {
	uint32_t value;
	float number;

	value = maquina.current_frame->pop();
	memcpy(&number, &value, sizeof(uint32_t));
	value = (uint32_t) number;

	maquina.current_frame->push(value);

	maquina.current_frame->pc++;
}

static void _f2l() {

	uint32_t value;
	uint64_t other;
	float number;

	value = maquina.current_frame->pop();
	memcpy(&number, &value, sizeof(uint32_t));

	other = (uint64_t) number;
	maquina.current_frame->push2(other);
	
	maquina.current_frame->pc++;
}

static void _f2d() {

	uint32_t value;
	uint64_t other;

	double double_number;
	float float_number;

	value = maquina.current_frame->pop();
	memcpy(&float_number, &value, sizeof(uint32_t));

	double_number = (double) float_number;
	memcpy(&other, &double_number, sizeof(uint64_t));

	maquina.current_frame->push2(other);

	maquina.current_frame->pc++;
}

static void _d2i() {

	uint32_t low, high;
	int32_t resp;
	uint64_t auxiliar;
	double double_number;

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	auxiliar = getDouble(low, high);
	memcpy(&double_number, &auxiliar, sizeof(uint64_t));

	resp = (int32_t) double_number;
	maquina.current_frame->push((uint32_t)resp);

	maquina.current_frame->pc++;
}

static void _d2l() {

	uint32_t low, high;
	uint64_t aux;
	double value;
	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	aux = getDouble(low, high);
	memcpy(&value, &aux, sizeof(uint64_t));
	aux = (uint64_t) value;
	maquina.current_frame->push(aux);

	maquina.current_frame->pc++;

}

static void _d2f() {

	uint32_t low, high, result;
	uint64_t value;
	double double_number;
	float float_number;

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	value = getDouble(low, high);

	memcpy(&double_number, &value, sizeof(uint64_t));
	float_number = (float) double_number;

	memcpy(&result, &float_number, sizeof(uint32_t));

	maquina.current_frame->push(result);

	maquina.current_frame->pc++;
}

static void _i2b() {
	
	int8_t value;
	int32_t other;

	value = (int8_t) maquina.current_frame->pop();
	other = (int32_t)value;
	maquina.current_frame->push((int32_t)other);

	maquina.current_frame->pc++;
}

static void _i2c() {

	int16_t value;
	int32_t other;

	value = (int16_t) maquina.current_frame->pop();
	other = (int32_t)value;
	maquina.current_frame->push((int32_t)other);

	maquina.current_frame->pc++;
}

static void _i2s() {

	int16_t value;
	int32_t other;

	value = (int16_t) maquina.current_frame->pop();
	other = (int32_t)value;

	maquina.current_frame->push((uint32_t)other);
	
	maquina.current_frame->pc++;
}

static void _lcmp() {

	int32_t result;
	int32_t low, high;
	int64_t value, other;
	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	other = getDouble(low, high);

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	value = high;
	value = value << 32;
	value = value + low;


	if(value == other) {
		result = 0;
	} else{
		if(value > other) {
			result = 1;
		} else {
			result = -1;
		}
	} 
	
	maquina.current_frame->push((int32_t) result);
	maquina.current_frame->pc++;
}

static void _fcmpl() {

	int32_t empilha;
	uint32_t value;
	float op, opp;

	value = maquina.current_frame->pop();
	
	memcpy(&opp, &value, sizeof(uint32_t));
	value = maquina.current_frame->pop();

	memcpy(&op, &value, sizeof(uint32_t));
	
	if(op == opp) {
		empilha = 0;
	}else{

		if(op > opp) {
			empilha = 1;
		}else {
			empilha = -1;
		}
	} 

	maquina.current_frame->push((uint32_t) empilha);
	maquina.current_frame->pc++;
}

static void _fcmpg() {

	float value, other;
	uint32_t auxiliar;

	int32_t resultado;

	auxiliar = maquina.current_frame->pop();
	memcpy(&other, &auxiliar, sizeof(uint32_t));
	
	auxiliar = maquina.current_frame->pop();
	memcpy(&value, &auxiliar, sizeof(uint32_t));

	if(value == other) {
		resultado = 0;
	} else{ 
		if(value > other) {
			resultado = 1;
		}else {
			resultado = -1;
		}
	}

	maquina.current_frame->push((uint32_t) resultado);
	maquina.current_frame->pc++;
}

static void _dcmpl() {
	
	double double_number, double_number2;
	uint32_t low, high;
	uint64_t bigBits;
	int32_t empilha;
	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	bigBits = getDouble(low, high);
	memcpy(&double_number2, &bigBits, sizeof(uint64_t));

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	bigBits = high;
	bigBits = bigBits << 32;
	bigBits = bigBits + low;


	memcpy(&double_number, &bigBits, sizeof(uint64_t));
	if(double_number == double_number2) {
		empilha = 0;
	} else{
		if(double_number > double_number2) {
			empilha = 1;
		}else {
			empilha = -1;
		}
	}

	maquina.current_frame->push((uint64_t) empilha);
	maquina.current_frame->pc++;
}

static void _dcmpg() {
	double double_number, double_number2;
	uint32_t low, high;
	uint64_t auxiliar;
	int32_t empilha;

	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();
	

	auxiliar = high;
	auxiliar = auxiliar << 32;
	auxiliar = auxiliar + low;

	memcpy(&double_number2, &auxiliar, sizeof(uint64_t));
	
	low = maquina.current_frame->pop();
	high = maquina.current_frame->pop();

	auxiliar = high;
	auxiliar = auxiliar << 32;
	auxiliar = auxiliar + low;

	memcpy(&double_number, &auxiliar, sizeof(uint32_t));

	if(double_number == double_number2) {
		empilha = 0;
	} else{
		if(double_number > double_number2) {
			empilha = 1;
		}else {
			empilha = -1;
		}
	}

	maquina.current_frame->push((uint32_t) empilha);
	maquina.current_frame->pc++;

}

static void _ifeq() {

	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value == 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}
}


static void _ifne() {

	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value != 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}
}

static void _iflt() {
	
	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value < 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}
}

static void _ifge() {
	
	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value >= 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _ifgt() {
	
	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value > 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _ifle() {
	
	uint8_t pathOne, pathTwo;
	int16_t desloc;
	int32_t value;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value = (signed) maquina.current_frame->pop();
	if(value <= 0) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}
}

static void _if_icmpeq() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 == value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_icmpne() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 != value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_icmplt() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 < value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_icmpge() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 >= value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_icmpgt() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 > value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_icmple() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 <= value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_acmpeg() {
	
	int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 == value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _if_acmpne() {
	
int8_t pathOne, pathTwo;
	int32_t value1, value2;
	int16_t desloc;

	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	value1 = (signed) maquina.current_frame->pop();
	value2 = (signed) maquina.current_frame->pop();
	
	if(value1 != value2) {
		
		desloc = pathTwo;
		desloc = desloc << 8;
		desloc = desloc | pathOne;

		maquina.current_frame->pc = maquina.current_frame->pc + desloc;

	} else {
		maquina.current_frame->pc = maquina.current_frame->pc + 3;
	}

}

static void _goto() {
	uint8_t pathOne, pathTwo;
	int16_t desloc;
	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
	
	desloc = pathTwo;
	desloc = desloc << 8;
	desloc = desloc | pathOne;

	maquina.current_frame->pc += desloc;
}

static void _jsr() {
	
	uint8_t pathOne, pathTwo;
	int16_t desloc;

	maquina.current_frame->push((maquina.current_frame->pc) + 3);
	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
	pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];

	desloc = pathTwo;
	desloc = desloc << 8;
	desloc = desloc | pathOne;
	
	maquina.current_frame->pc = maquina.current_frame->pc + desloc;

}

static void _ret() {
	
	int16_t indice;
	maquina.current_frame->pc++;
	indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
	
	if(WIDE == 1){
		indice = indice << 8;
		maquina.current_frame->pc++;
		indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
		WIDE = 0;
	}
	maquina.current_frame->pc = maquina.current_frame->local_variables[indice];
}

static void _tableswitch() {
	
	int32_t *tabela;
	int32_t defaultSwitch, min, max, indice;
	uint32_t byte[12], genericByte[5],stopped,desloc;

	indice = (int32_t)maquina.current_frame->pop();
	stopped = maquina.current_frame->pc;

	while((maquina.current_frame->pc + 1) % 4 != 0) {
		maquina.current_frame->pc++;
	}
	
	maquina.current_frame->pc++;

	for(int i=0; i<12; i++){
		byte[i] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
	}
	
	defaultSwitch = (byte[0] & 0xFF) << 24;
	defaultSwitch = defaultSwitch | (byte[1] & 0xFF) << 16;
	defaultSwitch = defaultSwitch | (byte[2] & 0xFF) << 8;
	defaultSwitch = defaultSwitch | (byte[3] & 0xFF);


	min = (byte[4] & 0xFF) << 24;
	min = min | (byte[5] & 0xFF) << 16;
	min = min | (byte[6] & 0xFF) << 8;
	min = min | (byte[7] & 0xFF);

	max = (byte[8] & 0xFF) << 24;
	max = max | (byte[9] & 0xFF) << 16;
	max = max | (byte[10] & 0xFF) << 8;
	max = max | (byte[11] & 0xFF);

	if(indice < min || indice > max) {
		
		maquina.current_frame->pc = defaultSwitch+stopped;

	} else {

		tabela = calloc(sizeof(uint32_t), (max-min+1));

		for(int i = 0; i < (max-min+1); i++) 	{
			
			genericByte[0] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
			genericByte[1] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
			genericByte[2] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
			genericByte[3] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
			
			tabela[i]  = (genericByte[0] & 0xFF) << 24;
			tabela[i]  = tabela[i]  | (genericByte[1] & 0xFF) << 16;
			tabela[i]  = tabela[i]  | (genericByte[2] & 0xFF) << 8;
			tabela[i]  = tabela[i]  | (genericByte[3] & 0xFF);

		}

		maquina.current_frame->pc = tabela[indice-min]+stopped;
	}

}

static void _lookupswitch() {
	
	int32_t defaultSwitch, key, count;
	int32_t *list, *offset;
	int k, find,i;
	uint32_t stopped, byte[12];

	key = (int32_t)maquina.current_frame->pop();
	stopped = maquina.current_frame->pc;

	while((maquina.current_frame->pc + 1) % 4 != 0) {
		maquina.current_frame->pc++;
	}
	
	maquina.current_frame->pc++;

	for(int i=0; i<8; i++){
		byte[i] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
	}
	
	defaultSwitch = (byte[0] & 0xFF) << 24;
	defaultSwitch = defaultSwitch | (byte[1] & 0xFF) << 16;
	defaultSwitch = defaultSwitch | (byte[2] & 0xFF) << 8;
	defaultSwitch = defaultSwitch | (byte[3] & 0xFF);

	count = (byte[4] & 0xFF) << 24;
	count = count | (byte[5] & 0xFF) << 16;
	count = count | (byte[6] & 0xFF) << 8;
	count = count | (byte[7] & 0xFF);

	list = calloc(sizeof(int32_t), count);
	offset = calloc(sizeof(int32_t), count);

	for(i = 0; i < count; i++) {

		byte[0] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[1] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[2] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[3] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[4] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[5] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[6] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
		byte[7] = maquina.current_frame->code_attr->code[maquina.current_frame->pc++];

		list[i]  = (byte[0] & 0xFF) << 24;
		list[i]  = list[i]  | (byte[1] & 0xFF) << 16;
		list[i]  = list[i]  | (byte[2] & 0xFF) << 8;
		list[i]  = list[i]  | (byte[3] & 0xFF);

		offset[i]  = (byte[4] & 0xFF) << 24;
		offset[i]  = offset[i]  | (byte[5] & 0xFF) << 16;
		offset[i]  = offset[i]  | (byte[6] & 0xFF) << 8;
		offset[i]  = offset[i]  | (byte[7] & 0xFF);		

	}

	k = 0;
	find = 0;

	while((k < count) &&( !find)) {

		if(list[k] == key)
			find = 1;
		k++;
	}

	k--;

	if(find == 1) {
		maquina.current_frame->pc = offset[i] + stopped;
	} else {
		maquina.current_frame->pc = defaultSwitch + stopped;
	}

}


static void _ireturn() {
	
	uint32_t aux = maquina.current_frame->pop();
	maquina.stack->popFrame();
	maquina.current_frame->push(aux);

}

static void _lreturn() {

	uint32_t low = maquina.current_frame->pop();
	uint32_t high = maquina.current_frame->pop();
	maquina.stack->popFrame();
	maquina.current_frame->push2(getLong(high,low));
}

static void _freturn() {
	_ireturn();
}

static void _dreturn() {
	_dreturn();
}

static void _areturn() {
	_ireturn();
}

static void _return() {
	maquina.stack->popFrame();
}

static void _getstatic() {
	
	uint8_t index_1, index_2;
	uint16_t indice, nameTypeIndex;
	uint32_t classIndexTemp;
	int32_t classIndex, field_index;
	uint64_t valor;
	char *className, *name, *type;

	index_1 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	index_2 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	indice = ((uint16_t)index_1 << 8) |(uint16_t)index_2;
	
	classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);


	nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
	name = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
	type = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
		className = maquina.current_frame->current_class->getParentName(maquina.getClassByName(className));
	}

	classIndex = maquina.loadClass(className);


	valor = maquina.getStaticFieldVal(classIndex , field_index);

	if(type[0] == 'J' || type[0] == 'D') {
		maquina.current_frame->push2(valor);
	} else {
		maquina.current_frame->push(valor);
	}


	maquina.current_frame->pc++;

}

static void _putstatic() {
	
	uint8_t index_1, index_2;
	uint16_t indice, nameTypeIndex;
	uint32_t classIndexTemp;
	int32_t classIndex, field_index;
	uint64_t valor,valor2;
	char *className, *name, *type;

	index_1 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	index_2 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	indice = ((uint16_t)index_1 << 8) |(uint16_t)index_2;
	
	classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);


	nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
	name = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
	type = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
		className = maquina.current_frame->current_class->getParentName(maquina.getClassByName(className));
	}

	classIndex = maquina.loadClass(className);

	if(type[0] == 'J' || type[0] == 'D') {

		valor  = maquina.current_frame->pop();
		valor2 = maquina.current_frame->pop();
		valor = valor | (valor2 << 32);
 
	} else {
		valor = maquina.current_frame->pop();
	}

	maquina.setStaticFieldVal(classIndex , field_index, valor);
	maquina.current_frame->pc++;
}

static void _getfield() {
	
	uint8_t low, high;
	uint32_t indice;
	int32_t classIndex, field_index, nameIndex, aux;
	uint16_t nameTypeIndex;
	char *className, *name, *type;
	struct _object *objeto;
	struct _field_info* aux2;
	uint64_t valor;

	high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];

	indice = high;
	indice <<= 8;
	indice = indice | low;


	classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);


	nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
	name = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
	type = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);


	while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
		className = maquina.current_frame->current_class->getParentName(maquina.getClassByName(className));
	}

	aux = maquina.current_frame->pop();
	memcpy(objeto, &aux, sizeof(uint32_t));

	nameIndex = maquina.current_frame->current_class->fields_pool->fields[field_index].name_index;
	aux2 = maquina.getObjectField(objeto, nameIndex);


	if(type[0] == 'J' || type[0] == 'D') {
		maquina.current_frame->push2(aux2->value);
	} else {
		maquina.current_frame->push(aux2->value);
	}

	maquina.current_frame->pc++;
}

static void _putfield() {
	
	uint8_t low, high;
	uint32_t indice;
	int32_t classIndex, field_index, nameIndex, aux, val_1,val_2;
	uint16_t nameTypeIndex;
	char *className, *name, *type;
	struct _object *objeto;
	struct _field_info* aux2;
	uint64_t valor,valor2;

	high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];

	indice = high;
	indice <<= 8;
	indice = indice | low;


	classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);


	nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
	name = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
	type = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);


	while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
		className = maquina.current_frame->current_class->getParentName(maquina.getClassByName(className));
	}
	
	nameIndex = maquina.current_frame->current_class->fields_pool->fields[field_index].name_index;

	if(type[0] == 'J' || type[0] == 'D') {
		

		valor  = maquina.current_frame->pop();
		valor2 = maquina.current_frame->pop();

		valor = valor | (valor2 << 32);
		maquina.setObjectField(objeto, nameIndex, valor);

	} else {
		
		val_1 = maquina.current_frame->pop();
		
		aux = maquina.current_frame->pop();
		memcpy(objeto, &aux, sizeof(uint32_t));

		maquina.setObjectField(objeto, nameIndex, val_1);

	}

	maquina.current_frame->pc++;
}

static void _invokevirtual() {
	
	uint32_t indice, valorHigh, valorLow, vU4, array_ref;
	uint64_t valor;
	uint8_t low, high;
	int32_t numParams, i, j;
	int32_t classIndex, classIndexTemp;
	uint16_t nameTypeIndex, methodNameIndex, methodDescriptorIndex;
	char *className, *methodName, *methodDesc;
	uint32_t *fieldsTemp;
	float vfloat;
	uint8_t *bytes;
	uint8_t length;
	CLASS *class;
	struct _method_info  *method;

	high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
	low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];

	indice = high;
	indice <<= 8;
	indice = indice | low;


	classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);

	

	classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
	className = maquina.current_frame->runtime_constant_pool->getClassName(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);

	methodNameIndex = maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex;
	methodDescriptorIndex = maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex;
	
	methodDesc = maquina.getNameConstants(maquina.current_frame->current_class, methodDescriptorIndex);
	methodName = maquina.getNameConstants(maquina.current_frame->current_class, methodNameIndex);


	if((strcmp(className, "java/io/PrintStream") == 0) && ((strcmp(methodName,"println") == 0) ||(strcmp(methodName,"print") == 0))){

		//Quando tem que imprimir long
		if(strstr(methodDesc, "J") != NULL){
			valorLow = maquina.current_frame->pop();
			valorHigh = maquina.current_frame->pop();

			printf("%lu",getLong(valorHigh,valorLow));

		//Quando tem que imprimir double
		} else if(strstr(methodDesc, "D") != NULL) {
			valorLow = maquina.current_frame->pop();
			valorHigh = maquina.current_frame->pop();
			
			printf("%f", getDouble(valorHigh,valorLow));

		//Quando tem que imprimir boolean
		} else if(strstr(methodDesc, "Z") != NULL) {
			
			if(!maquina.current_frame->pop()) {
				printf("false");
			} else {
				printf("true");
			}

		//Quando tem que imprimir char
		} else if(strstr(methodDesc, "C") != NULL) {
			
			//array
			if(strstr(methodDesc, "[C") != NULL){
				array_ref = maquina.current_frame->pop();
				for(i = 0; i < maquina.heap->array_count; i++){
					if(!memcmp(&maquina.heap->arrays[i], &array_ref, sizeof(uint32_t)))
						break;
				}
				for(j = 0; j < maquina.heap->array_count; j++){
					printf("%c",(int16_t)array_ref +i);
				}
				//CHAR
			} else {
				printf("%c",(int16_t)maquina.current_frame->pop());
			}

		//Quando tem que imprimir inteiro
		}else if(strstr(methodDesc, "I") != NULL) {
			printf("%"PRIi32,(int32_t)maquina.current_frame->pop());
		
		//Quando tem que imprimir float
		}else if(strstr(methodDesc, "F") != NULL) {
			vU4 = maquina.current_frame->pop();
			memcpy(&vfloat, &vU4, sizeof(uint32_t));
			printf("%f", vfloat);

		//Quando tem que imprimir string
		}else if(strstr(methodDesc, "Ljava/lang/String") != NULL) {
			char* aux; 
			vU4 = maquina.current_frame->pop();
			memcpy(&aux, &vU4, sizeof(uint32_t));

			printf("%s",aux);

		//OBJECT
		}else if(strstr(methodDesc, "Ljava/lang/Object") != NULL) {

			void* aux; 
			vU4 = maquina.current_frame->pop();
			memcpy(&aux, &vU4, sizeof(uint32_t));

			printf("%p",aux);
		}

		if(strcmp(methodName,"println") == 0) {
			printf("\n");
		}
	} else {

		classIndex = maquina.loadClass(className);
		class = maquina.method_area->classes[classIndex];


		while(class != NULL && (method = maquina.getMethodByNameDesc(class, maquina.current_frame->current_class, nameTypeIndex)) == NULL) {
			
			className = class->getParentName(class);
			classIndex = maquina.loadClass(className);

			class = maquina.method_area->classes[classIndex];
		}

		if(class == NULL) {
			printf(" Erro: Metodo nao encontrando.\n");
			exit(1);
		}

		numParams = maquina.getNumParameters(class , method);
		fieldsTemp = calloc(sizeof(uint32_t),numParams+1);
		for(i = numParams; i >= 0; i--) {
			fieldsTemp[i] = maquina.current_frame->pop();
		}

		if(((method->access_flags) & mask_native) || strcmp("println", maquina.getNameConstants(class, method->name_index)) == 0) {
			bytes = class->constant_pool->constants[(method->descriptor_index-1)].type.Utf8.bytes;
			length = class->constant_pool->constants[(method->descriptor_index-1)].type.Utf8.tam;

			if(bytes[length-1] == 'D' || bytes[length-1] == 'J') {
				maquina.current_frame->push2(0);
			} else if(bytes[length-1] != 'V') {
				maquina.current_frame->push(0);
			}

		} else {
			maquina.construirFrame(class, method);
			for(i = numParams; i >= 0; i--) {
				maquina.current_frame->local_variables[i] = fieldsTemp[i];
			}
			maquina.execute();
		}
	}

	maquina.current_frame->pc++;

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
