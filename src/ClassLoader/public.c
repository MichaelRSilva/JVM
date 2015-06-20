#include "private.c"

// funcoes somente visiveis a struct classloader
static CLASS* load(CLASS_LOADER* this, char* fileName) {
	DADOS d = getUTILInstance().LeArquivo(fileName);
	int flag = 0, contador = 0, cp_size = 0;
	uint8_t* base_pointer = d.bytes;

	this->class->magic = getMagicNumber(&d);
	if (!(flag = verifyCAFEBABE(this->class->magic))) {
		this->class->minor_version = getMinorVersion(&d);
		this->class->major_version = getMajorVersion(&d);
		if (!(flag = verifyVersion(this->class->minor_version, this->class->major_version))) {
			this->class->constant_pool_count = getConstantPoolCount(&d);
			this->class->constant_pool = populateConstantPool(this->class, &d);
			this->class->access_flags = getAccessFlags(&d);
			this->class->this_class = getThisClass(&d);
			this->class->super_class = getSuperClass(&d);
			this->class->interfaces_count = getInterfacesCount(&d);
			if (!(flag = populateInterfaces(this->class, &d))) {
				this->class->fields_count = getFieldsCount(&d);
				this->class->fields_pool = populateFieldPool(this->class,&d);
				this->class->methods_count = getMethodsCount(&d);
				this->class->methods_pool = populateMethodsPool(this->class, &d);
				this->class->attributes_count = getAttributesCount(&d);
				this->class->attribute_pool = populateAttributePool(this->class, &d);
			}
		}
	}

	return ((int)(d.bytes - base_pointer) != d.tamanho)?NULL:this->class;
}
