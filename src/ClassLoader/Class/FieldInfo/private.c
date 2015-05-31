#include "fieldinfo.h"


static uint16_t getAccessFlags(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getNameIndex(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getDescriptorIndex(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getAttributesCount(DADOS* d) {
	return d->le2Bytes(d);
}
