#include "../JVM/maquina/instructions.c"

static void printConstantValue(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem, FILE* output) {
	fprintf(output,"%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	fprintf(output,"%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	fprintf(output,"%s\tAttribute length: %d\n", tab,attr.attributeLength);

	fprintf(output,"%s\tConstant value index: %d\n", tab,attr.info.ConstantValueAttribute.constantvalue_index);
}

static void printCode(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem, FILE* output) {
	int k = 0;

	fprintf(output,"%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	fprintf(output,"%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	fprintf(output,"%s\tAttribute length: %d\n", tab,attr.attributeLength);
	fprintf(output,"%s\tBytecode: \n", tab);

	for (int i = 0; i < attr.info.CodeAttribute.code_length; i++)
	{
		fprintf(output,"\t\t\t\t\t%s",instructions[attr.info.CodeAttribute.code[i]].nome);
		for(k = 0; k<instructions[attr.info.CodeAttribute.code[i]].qtd_operandos; k++){
			if(attr.info.CodeAttribute.code[i+k+1] !=0 ){
				fprintf(output," %d",attr.info.CodeAttribute.code[i+k+1]);
			}
		}
		i = i+k;
		fprintf(output,"\n");
	}

	for (int i = 0; i < attr.info.CodeAttribute.attributes_count; i++) {

		fprintf(output, "%s\t[%d]LineNumberTable:\n", tab, i);
		fprintf(output, "%s\t\tAttribute name index:\t%d\n", tab, attr.info.CodeAttribute.attributes[i].attributeNameIndex);
		fprintf(output, "%s\t\tAttribute length:\t%d\n\n", tab, attr.info.CodeAttribute.attributes[i].attributeLength);
		fprintf(output, "%s\t\t\t|Nr.\t|start_pc\t|line_number\t\t|\n", tab);

		for (int j = 0; j < attr.info.CodeAttribute.attributes[i].info.LineNumberTableAttribute.liner_number_table_length; j++) {
			struct _line_number_table* var = attr.info.CodeAttribute.attributes[i].info.LineNumberTableAttribute.line_number_table;
			fprintf(output, "%s\t\t\t|%d\t|%d\t\t|%d\t\t\t|\n", tab, j, var[j].start_pc, var[j].line_number);
		}
	}
	
	fprintf(output,"%s\tMisc: \n", tab);
	fprintf(output,"%s\t\tMaximum stack depth: %d\n", tab,attr.info.CodeAttribute.max_stack);
	fprintf(output,"%s\t\tMaximum local variables: %d\n", tab,attr.info.CodeAttribute.max_locals);
	fprintf(output,"%s\t\tCode length: %d\n", tab,attr.info.CodeAttribute.code_length);


}

static void printExceptions(struct _attribute_info attr, char *tab, FILE* output) {
//TODO: MARCUS
}

static void printInnerClasses(struct _attribute_info attr, char *tab, FILE* output) {
//NOT PRINT IN JCLASSLIB
}

static void printSynthetic(struct _attribute_info attr, char *tab, FILE* output) {
//NOTHING
}

static void printSourceFile(struct _attribute_info attr, char *tab, FILE* output) {
	fprintf(output,"%s\tSource file index: %d\n", tab,attr.info.SourceFileAttribute.sourcefile_index);
}

static void printLineNumberTable(struct _attribute_info attr, char *tab, FILE* output) {
//TODO: MARCUS
}

static void printLocalVariableTable(struct _attribute_info attr, char *tab, FILE* output) {
//NOT PRINT IN JCLASSLIB
}

static void printDeprecated(struct _attribute_info attr, char *tab, FILE* output) {
//NOTHING
}

static void printAttribute(struct _attribute_info attr, CONSTANT_POOL* cp, char* tab, int ordem, FILE* output){
	char* tipoNome = (char*)malloc(cp->constants[attr.attributeNameIndex - 1].type.Utf8.tam * sizeof(char));
	strcpy(tipoNome, (char*)cp->constants[attr.attributeNameIndex - 1].type.Utf8.bytes);

	if (strcmp(tipoNome, "ConstantValue") == 0) {
		printConstantValue(attr, tab,cp,ordem,output);
	} else if (strcmp(tipoNome, "Code") == 0) {
		printCode(attr, tab,cp,ordem,output);
	} else if (strcmp(tipoNome, "Exceptions") == 0) {
		printExceptions(attr, tab, output);
	} else if (strcmp(tipoNome, "InnerClasses") == 0) {
		printInnerClasses(attr, tab, output);
	} else if (strcmp(tipoNome, "Synthetic") == 0) {
		printSynthetic(attr, tab, output);
	} else if (strcmp(tipoNome, "SourceFile") == 0) {
		printSourceFile(attr, tab,output);
	} else if (strcmp(tipoNome, "LineNumberTable") == 0) {
		printLineNumberTable(attr, tab, output);
	} else if (strcmp(tipoNome, "LocalVariableTable") == 0) {
		printLocalVariableTable(attr, tab, output);
	} else { // Deprecated
		
		printDeprecated(attr, tab, output);

	}
}

static int PrintClass(CLASS* this, FILE* output) {
	fprintf(output,"\nINFORMACOES DA CLASSE\n");
	fprintf(output,"-------------------------------------------------------------------\n\n");

	fprintf(output,"Magic Number: \t\t\t0x%x \n",this->magic);
	fprintf(output,"Minor Version: \t\t\t%d \n",this->minor_version);
	fprintf(output,"Major Version: \t\t\t%d ",this->major_version);
	
	if(this->major_version  == 46){
		fprintf(output," [1.2]\n");
	}

	fprintf(output,"Constant pool count: \t\t%d \n",this->constant_pool_count);
	fprintf(output,"Access flags: \t\t\t0x%04x \t\t[%s ] \n", this->access_flags,returnAccessFlagsName(this->access_flags));
	fprintf(output,"This class\t\t\tindice: %d\t<%s> \n", this->this_class, this->constant_pool->constants[this->constant_pool->constants[this->this_class-1].type.Class.nameIndex - 1].type.Utf8.bytes);
	fprintf(output,"Super class\t\t\tindice: %d\t<%s> \n", this->super_class, this->constant_pool->constants[this->constant_pool->constants[this->super_class-1].type.Class.nameIndex - 1].type.Utf8.bytes);
	fprintf(output,"Interfaces count: \t\t%d \n", this->interfaces_count);
	fprintf(output,"Fields count: \t\t\t%d \n", this->fields_count);
	fprintf(output,"Methods count: \t\t\t%d \n", this->methods_count);
	fprintf(output,"Attributes count: \t\t%d \n\n", this->attributes_count);
	
	fprintf(output,"Interfaces: \n");
	for (int i = 0; i < this->interfaces_count; i++) {
		fprintf(output,"\tInterface %d: \n", i);
		fprintf(output,"\t\tInterface index: %d\t\t<%s>\n", this->interfaces[i], this->constant_pool->constants[this->constant_pool->constants[this->interfaces[i]-1].type.Class.nameIndex-1].type.Utf8.bytes);
	}

	fprintf(output,"Constant Pool: \n");
	for (int i = 0; i < this->constant_pool_count - 1; i++) {
		switch (this->constant_pool->constants[i].tag) {
			case tUtf8:
				fprintf(output,"\t[%d]CONSTANT_Utf8_info:\n", i + 1);
				fprintf(output,"\t\tLength of byte array: %d\n", this->constant_pool->constants[i].type.Utf8.tam);
				fprintf(output,"\t\tLength of string: %d\n", this->constant_pool->constants[i].type.Utf8.tam);
				fprintf(output,"\t\tString: %s\n", (char*)this->constant_pool->constants[i].type.Utf8.bytes);
				break;
			case tInteger:
				fprintf(output,"\t[%d]CONSTANT_Integer_info:\n", i + 1);
				fprintf(output,"\t\tBytes: 0x%08x\n", this->constant_pool->constants[i].type.Integer.bytes);
				fprintf(output,"\t\tInteger: %d\n", this->constant_pool->constants[i].type.Integer.bytes);
				break;
			case tFloat:
				fprintf(output,"\t[%d]CONSTANT_Float_info:\n", i + 1);
				fprintf(output,"\t\tBytes: 0x%08x\n", this->constant_pool->constants[i].type.Float.bytes);
				fprintf(output,"\tFloat: %f\n", (float)this->constant_pool->constants[i].type.Float.bytes);
				break;
			case tLong: {
				fprintf(output,"\t[%d]CONSTANT_Long_info:\n", i + 1);
				fprintf(output,"\t\tHigh Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.highBytes);
				fprintf(output,"\t\tLow Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.lowBytes);
				fprintf(output,"\t\tLong: %lu\n", getLong(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes));
				break;
			}
			case tDouble: {
				fprintf(output,"\t[%d]CONSTANT_Double_info:\n", i + 1);
				fprintf(output,"\t\tHigh Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.highBytes);
				fprintf(output,"\t\tLow Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.lowBytes);
				long var = getLong(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes);
				if (var == 0x7ff0000000000000L) {
					fprintf(output,"\t\tDouble: infinito positivo\n");
				} else if (var == 0xfff0000000000000L) {
					fprintf(output,"\t\tDouble: infinito negativo\n");
				} else if ((var >= 0x7ff0000000000001L && var <= 0x7fffffffffffffffL) || (var <= 0xfff0000000000001L && var >= 0xffffffffffffffffL) ) {
					fprintf(output,"\t\tDouble: NaN\n");
				} else {
					fprintf(output,"\t\tDouble: %f\n", getDouble(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes));
				}
				break;
			}
			case tExtended:
				fprintf(output,"\t[%d](large numeric continued)\n", i+1);
				break;
			case tClass:
				fprintf(output,"\t[%1d]CONSTANT_Class_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d \t\t\t <%s>\n", this->constant_pool->constants[i].type.Class.nameIndex,(char*)this->constant_pool->constants[(this->constant_pool->constants[i].type.Class.nameIndex-1)].type.Utf8.bytes);
				break;		
			case tString:
				fprintf(output,"\t[%1d]CONSTANT_String_info:\n", i + 1);
				fprintf(output,"\t\tString: %d \t\t\t <%s>\n", this->constant_pool->constants[i].type.String.stringIndex,(char*)this->constant_pool->constants[(this->constant_pool->constants[i].type.String.stringIndex-1)].type.Utf8.bytes);
				break;		
			case tFieldRef:
				fprintf(output,"\t[%1d]CONSTANT_FieldRef_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d \t\t\t <%s>\n", this->constant_pool->constants[i].type.FieldRef.classIndex,(char*)this->constant_pool->constants[this->constant_pool->constants[this->constant_pool->constants[i].type.FieldRef.classIndex-1].type.Class.nameIndex - 1].type.Utf8.bytes);
				fprintf(output,"\t\tName and type index: %d \t<%s%s>\n", this->constant_pool->constants[i].type.FieldRef.nameTypeIndex,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.FieldRef.nameTypeIndex-1].type.NameType.nameIndex)-1].type.Utf8.bytes,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.FieldRef.nameTypeIndex-1].type.NameType.descriptorIndex)-1].type.Utf8.bytes);
				break;		
			case tMethodRef:
				fprintf(output,"\t[%1d]CONSTANT_Methodref_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d \t\t\t <%s>\n", this->constant_pool->constants[i].type.MethodRef.classIndex,(char*)this->constant_pool->constants[this->constant_pool->constants[this->constant_pool->constants[i].type.MethodRef.classIndex-1].type.Class.nameIndex - 1].type.Utf8.bytes);
				fprintf(output,"\t\tName and type index: %d \t<%s%s>\n", this->constant_pool->constants[i].type.MethodRef.nameTypeIndex,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.MethodRef.nameTypeIndex-1].type.NameType.nameIndex)-1].type.Utf8.bytes,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.MethodRef.nameTypeIndex-1].type.NameType.descriptorIndex)-1].type.Utf8.bytes);
				break;		
			case tInterfaceMethodRef:
				fprintf(output,"\t[%1d]CONSTANT_InterfaceMethodref_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d \t\t\t <%s>\n", this->constant_pool->constants[i].type.InterfaceMethodRef.classIndex,(char*)this->constant_pool->constants[this->constant_pool->constants[this->constant_pool->constants[i].type.InterfaceMethodRef.classIndex-1].type.Class.nameIndex - 1].type.Utf8.bytes);
				fprintf(output,"\t\tName and type index: %d \t<%s%s>\n", this->constant_pool->constants[i].type.InterfaceMethodRef.nameTypeIndex,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.InterfaceMethodRef.nameTypeIndex-1].type.NameType.nameIndex)-1].type.Utf8.bytes,(char*)this->constant_pool->constants[(this->constant_pool->constants[this->constant_pool->constants[i].type.InterfaceMethodRef.nameTypeIndex-1].type.NameType.descriptorIndex)-1].type.Utf8.bytes);
				break;		
			case tNameType:
				fprintf(output,"\t[%1d]CONSTANT_NameAndType_info:\n", i + 1);
				fprintf(output,"\t\tName Index: %d\t\t\t %s\n", this->constant_pool->constants[i].type.NameType.nameIndex,(char*)this->constant_pool->constants[this->constant_pool->constants[i].type.NameType.nameIndex-1].type.Utf8.bytes);
				fprintf(output,"\t\tDescriptor Index: %d\t\t %s\n", this->constant_pool->constants[i].type.NameType.descriptorIndex,(char*)this->constant_pool->constants[this->constant_pool->constants[i].type.NameType.descriptorIndex-1].type.Utf8.bytes);
				break;
			default:
				fprintf(output,"\t[%d]\tERROR: %x\n",(i+1),this->constant_pool->constants[i].tag );
				break;	
		}
	}

	fprintf(output,"Fields: \n");
	for (int i = 0; i < this->fields_count; i++) {
		
		fprintf(output,"\t[%d]%s [%s]\n", i,this->constant_pool->constants[this->fields_pool->fields[i].name_index - 1].type.Utf8.bytes,returnAccessFlagsName(this->fields_pool->fields[i].access_flags));
		fprintf(output,"\t\tDescriptor: %d\n",this->fields_pool->fields[i].descriptor_index);	
		fprintf(output,"\t\tAccess Flags: %d\n",this->fields_pool->fields[i].access_flags);		



		for(int j=0; j < this->fields_pool->fields[i].attributes_count; j++){
			printAttribute(this->fields_pool->fields[i].attributes[j], this->constant_pool, "\t\t", j, output);
		}
	}

	fprintf(output,"Methods: \n");
	for (int i = 0; i < this->methods_count; i++) {
		fprintf(output,"\t[%d]%s\n", i,this->constant_pool->constants[this->methods_pool->methods[i].name_index - 1].type.Utf8.bytes);
		fprintf(output,"\t\tName Index: %d\n", this->methods_pool->methods[i].name_index);
		fprintf(output,"\t\tDescriptor Index: %d\n", this->methods_pool->methods[i].descriptor_index);
		fprintf(output,"\t\tAcess Flags: %x \t\t [%s]\n", this->methods_pool->methods[i].access_flags,returnAccessFlagsName(this->methods_pool->methods[i].access_flags));


		for(int j=0; j < this->methods_pool->methods[i].attributes_count; j++){
			printAttribute(this->methods_pool->methods[i].attributes[j], this->constant_pool, "\t\t\t", j, output);
		}
	}

	fprintf(output,"Attributes: \n");
	for (int i = 0; i < this->attributes_count; i++) {
		fprintf(output,"\t\t%s[%d]\n", this->constant_pool->constants[this->attribute_pool->attributes[i].attributeNameIndex-1].type.Utf8.bytes,i);
		fprintf(output,"\t\t\tAttribute name Index: %d\n", this->attribute_pool->attributes[i].attributeNameIndex);
		fprintf(output,"\t\t\tAttribute length: %d\n", this->attribute_pool->attributes[i].attributeLength);
		fprintf(output,"\t\t\tSource file name index: %d <%s>\n", this->attribute_pool->attributes[i].attributeNameIndex+1,this->constant_pool->constants[this->attribute_pool->attributes[i].attributeNameIndex].type.Utf8.bytes);

	}


	fprintf(output,"\n-------------------------------------------------------------------");
	fprintf(output,"\n\n");

	return 0;
}
