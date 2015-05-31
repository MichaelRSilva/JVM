#include "class.h"

static int verifyCAFEBABE(uint32_t magic) {
	return (0xCAFEBABE == magic) ? E_SUCCESS : E_CAFEBABE;
}

static int verifyVersion(uint16_t minor_version, uint16_t major_version) {
	return (minor_version <= major_version) ? E_SUCCESS : E_VERSION;
}

static uint32_t getMagicNumber(DADOS* d) {
	return (int)d->le4Bytes(d);
}

static uint16_t getMinorVersion(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getMajorVersion(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getConstantPoolCount(DADOS* d) {
	return d->le2Bytes(d);
}

static void addContinued(CONSTANT_POOL* cp, int ordem) {
    cp->constants[ordem].tag = 0;
    strcpy (cp->constants[ordem].type.Continued.bytes, "(large numeric continued)");
}

static CONSTANT_POOL* populateConstantPool(CLASS* this, DADOS* d){
	CONSTANT_POOL* toReturn = initCONSTANT_POOL((int*)&(this->constant_pool_count));
	int returnContinued = 0;
	
	for (int i = 0; i < this->constant_pool_count - 1; i++) {
		if(toReturn->addConstant(toReturn, i, d) == 1){
			addContinued(toReturn,++i);
		}
	}

	return toReturn;
}
