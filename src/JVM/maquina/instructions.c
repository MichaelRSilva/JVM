#include "maquina.h"

JVM maquina;

static void nop() {
	maquina.current_frame->pc++;
}

static void aconst_null() {
	//TODO
}

static void iconst_m1() {
	//TODO
}

static void iconst_0() {
	//TODO
}

static void iconst_1() {
	//TODO
}

static void iconst_2() {
	//TODO
}

static void iconst_3() {
	//TODO
}

static void iconst_4() {
	//TODO
}

static void iconst_5() {
	//TODO
}

static void lconst_0() {
	//TODO
}

static void lconst_1() {
	//TODO
}
static void fconst_0() {
	//TODO
}

static void fconst_1() {
	//TODO
}

static void fconst_2() {
	//TODO
}

static void dconst_0() {
	//TODO
}

static void dconst_1() {
	//TODO
}

static void bipush() {
	//TODO
}

static void sipush() {
	//TODO
}

static void ldc() {
	//TODO
}

static void ldc_w() {
	//TODO
}

static void ldc2_w() {
	//TODO
}

static void iload() {
	//TODO
}

static void lload() {
	//TODO
}

static void fload() {
	//TODO
}

static void dload() {
	//TODO
}

static void aload() {
	//TODO
}

static void iload_0() {
	//TODO
}

static void iload_1() {
	//TODO
}

static void iload_2() {
	//TODO
}

static void iload_3() {
	//TODO
}

static void lload_0() {
	//TODO
}

static void lload_1() {
	//TODO
}

static void lload_2() {
	//TODO
}

static void lload_3() {
	//TODO
}

static void fload_0() {
	//TODO
}

static void fload_1() {
	//TODO
}

static void fload_2() {
	//TODO
}

static void fload_3() {
	//TODO
}

static void dload_0() {
	//TODO
}

static void dload_1() {
	//TODO
}

static void dload_2() {
	//TODO
}

static void dload_3() {
	//TODO
}

static void aload_0() {
	//TODO
}

static void aload_1() {
	//TODO
}

static void aload_2() {
	//TODO
}

static void aload_3() {
	//TODO
}

static void iaload() {
	//TODO
}

static void laload() {
	//TODO
}

static void faload() {
	//TODO
}

static void daload() {
	//TODO
}

static void aaload() {
	//TODO
}

static void baload() {
	//TODO
}

static void caload() {
	//TODO
}

static void saload() {
	//TODO
}

static void istore() {
	//TODO
}

static void lstore() {
	//TODO
}

static void fstore() {
	//TODO
}

static void dstore() {
	//TODO
}

static void astore() {
	//TODO
}

static void istore_0() {
	//TODO
}

static void istore_1() {
	//TODO
}

static void istore_2() {
	//TODO
}

static void istore_3() {
	//TODO
}

static void lstore_0() {
	//TODO
}

static void lstore_1() {
	//TODO
}

static void lstore_2() {
	//TODO
}

static void lstore_3() {
	//TODO
}

static void fstore_0() {
	//TODO
}

static void fstore_1() {
	//TODO
}

static void fstore_2() {
	//TODO
}

static void fstore_3() {
	//TODO
}

static void dstore_0() {
	//TODO
}

static void dstore_1() {
	//TODO
}

static void dstore_2() {
	//TODO
}

static void dstore_3() {
	//TODO
}

static void astore_0() {
	//TODO
}

static void astore_1() {
	//TODO
}

static void astore_2() {
	//TODO
}

static void astore_3() {
	//TODO
}

static void iastore() {
	//TODO
}

static void lastore() {
	//TODO
}

static void fastore() {
	//TODO
}

static void dastore() {
	//TODO
}

static void aastore() {
	//TODO
}

static void bastore() {
	//TODO
}

static void castore() {
	//TODO
}

static void sastore() {
	//TODO
}

static void _pop() {
	//TODO
}		

static void pop2() {
	//TODO
}	

static void dup() {
	//TODO
}

static void dup_x1() {
	//TODO
}

static void dup_x2() {
	//TODO
}	

static void dup2 () {
	//TODO
}

static void dup2_x1() {
	//TODO
}

static void dup2_x2() {
	//TODO
}

static void swap() {
	//TODO
}	

static void iadd() {
	//TODO
}	

static void ladd() {
	//TODO
}	

static void fadd() {
	//TODO
}	

static void dadd() {
	//TODO
}	

static void isub() {
	//TODO
}	

static void lsub() {
	//TODO
}	

static void fsub() {
	//TODO
}	

static void dsub() {
	//TODO
}	

static void imul() {
	//TODO
}	

static void lmul() {
	//TODO
}	

static void fmul() {
	//TODO
}	

static void dmul() {
	//TODO
}	

static void idiv() {
	//TODO
}	

static void _ldiv() {
	//TODO
}	

static void fdiv() {
	//TODO
}	

static void ddiv() {
	//TODO
}	

static void irem() {
	//TODO
}	

static void lrem() {
	//TODO
}	

static void frem() {
	//TODO
}	

static void _drem() {
	//TODO
}	

static void ineg() {
	//TODO
}	

static void lneg() {
	//TODO
}	

static void fneg() {
	//TODO
}	

static void dneg() {
	//TODO
}	

static void ishl() {
	//TODO
}	

static void lshl() {
	//TODO
}	

static void ishr() {
	//TODO
}	

static void lshr() {
	//TODO
}	

static void iushr() {
	//TODO
}

static void lushr() {
	//TODO
}

static void iand() {
	//TODO
}

static void land() {
	//TODO
}

static void ior	() {
	//TODO
}

static void lor	() {
	//TODO
}

static void ixor() {
	//TODO
}

static void lxor() {
	//TODO
}

static void iinc() {
	//TODO
}

static void i2l	() {
	//TODO
}

static void i2f	() {
	//TODO
}

static void i2d	() {
	//TODO
}

static void l2i	() {
	//TODO
}

static void l2f	() {
	//TODO
}

static void l2d	() {
	//TODO
}

static void f2i	() {
	//TODO
}

static void f2l	() {
	//TODO
}

static void f2d	() {
	//TODO
}

static void d2i	() {
	//TODO
}

static void d2l	() {
	//TODO
}

static void d2f	() {
	//TODO
}

static void i2b	() {
	//TODO
}

static void i2c	() {
	//TODO
}

static void i2s	() {
	//TODO
}

static void lcmp() {
	//TODO
}

static void fcmpl() {
	//TODO
}

static void fcmpg() {
	//TODO
}

static void dcmpl() {
	//TODO
}

static void dcmpg() {
	//TODO
}

static void ifeq() {
	//TODO
}

static void ifne() {
	//TODO
}

static void iflt() {
	//TODO
}

static void ifge() {
	//TODO
}

static void ifgt() {
	//TODO
}

static void ifle() {
	//TODO
}

static void if_icmpeq() {
	//TODO
}

static void if_icmpne() {
	//TODO
}

static void if_icmplt() {
	//TODO
}

static void if_icmpge() {
	//TODO
}

static void if_icmpgt() {
	//TODO
}

static void if_icmple() {
	//TODO
}

static void if_acmpeg() {
	//TODO
}

static void if_acmpne() {
	//TODO
}

static void _goto() {
	//TODO
}

static void jsr	() {
	//TODO
}

static void ret	() {
	//TODO
}

static void tableswitch() {
	//TODO
}

static void lookupswitch() {
	//TODO
}

static void ireturn() {
	//TODO
}

static void lreturn() {
	//TODO
}

static void freturn() {
	//TODO
}

static void dreturn() {
	//TODO
}

static void areturn() {
	//TODO
}

static void _return() {
	//TODO
}

static void getstatic() {
	//TODO
}

static void putstatic() {
	//TODO
}

static void getfield() {
	//TODO
}

static void putfield() {
	//TODO
}

static void invokevirtual() {
	//TODO
}

static void invokespecial() {
	//TODO
}

static void invokestatic() {
	//TODO
}

static void invokeinterface() {
	//TODO
}

static void new() {
	//TODO
}

static void newarray() {
	//TODO
}

static void anewarray() {
	//TODO
}

static void arraylength() {
	//TODO
}

static void athrow() {
	//TODO
}

static void checkcast() {
	//TODO
}

static void instanceof() {
	//TODO
}

static void monitorenter() {
	//TODO
}

static void monitorexit() {
	//TODO
}

static void wide() {
	//TODO
}

static void multianewarray() {
	//TODO
}

static void ifnull() {
	//TODO
}

static void ifnonnull() {
	//TODO
}

static void goto_w() {
	//TODO
}

static void jsr_w() {
	//TODO
}

const JVM_INSTRUCTION instructions[] = {
	{0, 	"nop", 				nop				},
	{0, 	"aconst_null", 		aconst_null		},
	{0, 	"iconst_m1", 		iconst_m1		},
	{0, 	"iconst_0", 		iconst_0		},
	{0, 	"iconst_1",			iconst_1		},
	{0, 	"iconst_2",			iconst_2		},
	{0, 	"iconst_3",			iconst_3		},
	{0, 	"iconst_4",			iconst_4		},
	{0, 	"iconst_5",			iconst_5		},
	{0, 	"lconst_0",			lconst_0		},
	{0, 	"lconst_1",			lconst_1		},
	{0, 	"fconst_0",			fconst_0		},
	{0, 	"fconst_1",			fconst_1		},
	{0, 	"fconst_2",			fconst_2		},
	{0, 	"dconst_0",			dconst_0		},
	{0, 	"dconst_1",			dconst_1		},
	{1, 	"bipush",			bipush			},
	{2, 	"sipush",			sipush			},
	{1, 	"ldc",				ldc				},
	{2, 	"ldc_w",			ldc_w			},
	{2, 	"ldc2_w",			ldc2_w			},
	{1, 	"iload",			iload			},
	{1, 	"lload",			lload			},
	{1, 	"fload",			fload			},
	{1, 	"dload",			dload			},
	{1, 	"aload",			aload			},
	{0, 	"iload_0",			iload_0			},
	{0, 	"iload_1",			iload_1			},
	{0, 	"iload_2",			iload_2			},
	{0, 	"iload_3",			iload_3			},
	{0, 	"lload_0",			lload_0			},
	{0, 	"lload_1",			lload_1			},
	{0, 	"lload_2",			lload_2			},
	{0, 	"lload_3",			lload_3			},
	{0, 	"fload_0",			fload_0			},
	{0, 	"fload_1",			fload_1			},
	{0, 	"fload_2",			fload_2			},
	{0, 	"fload_3",			fload_3			},
	{0, 	"dload_0",			dload_0			},
	{0, 	"dload_1",			dload_1			},
	{0, 	"dload_2",			dload_2			},
	{0, 	"dload_3",			dload_3			},
	{0, 	"aload_0",			aload_0			},
	{0, 	"aload_1",			aload_1			},
	{0, 	"aload_2",			aload_2			},
	{0, 	"aload_3",			aload_3			},
	{0, 	"iaload",			iaload			},
	{0, 	"laload",			laload			},
	{0, 	"faload",			faload			},
	{0, 	"daload",			daload			},
	{0, 	"aaload",			aaload			},
	{0, 	"baload",			baload			},
	{0, 	"caload",			caload			},
	{0, 	"saload",			saload			},
	{1, 	"istore",			istore			},
	{1, 	"lstore",			lstore			},
	{1, 	"fstore",			fstore			},
	{1, 	"dstore",			dstore			},
	{1, 	"astore",			astore			},
	{0, 	"istore_0",			istore_0		},
	{0, 	"istore_1",			istore_1		},
	{0, 	"istore_2",			istore_2		},
	{0, 	"istore_3",			istore_3		},
	{0, 	"lstore_0",			lstore_0		},
	{0, 	"lstore_1",			lstore_1		},
	{0, 	"lstore_2",			lstore_2		},
	{0, 	"lstore_3",			lstore_3		},
	{0, 	"fstore_0",			fstore_0		},
	{0, 	"fstore_1",			fstore_1		},
	{0, 	"fstore_2",			fstore_2		},
	{0, 	"fstore_3",			fstore_3		},
	{0, 	"dstore_0",			dstore_0		},
	{0, 	"dstore_1",			dstore_1		},
	{0, 	"dstore_2",			dstore_2		},
	{0, 	"dstore_3",			dstore_3		},
	{0, 	"astore_0",			astore_0		},
	{0, 	"astore_1",			astore_1		},
	{0, 	"astore_2",			astore_2		},
	{0, 	"astore_3",			astore_3		},
	{0, 	"iastore",			iastore			},
	{0, 	"lastore",			lastore			},
	{0, 	"fastore",			fastore			},
	{0, 	"dastore",			dastore			},
	{0, 	"aastore",			aastore			},
	{0, 	"bastore",			bastore			},
	{0, 	"castore",			castore			},
	{0, 	"sastore",			sastore			},
	{0, 	"pop",				_pop			},
	{0, 	"pop2",				pop2			},
	{0, 	"dup",				dup				},
	{0, 	"dup_x1",			dup_x1			},
	{0, 	"dup_x2",			dup_x2			},
	{0, 	"dup2",				dup2			},
	{0, 	"dup2_x1",			dup2_x1			},
	{0, 	"dup2_x2",			dup2_x2			},
	{0, 	"swap",				swap			},
	{0, 	"iadd",				iadd			},
	{0, 	"ladd",				ladd			},
	{0, 	"fadd",				fadd			},
	{0, 	"dadd",				dadd			},
	{0, 	"isub",				isub			},
	{0, 	"lsub",				lsub			},
	{0, 	"fsub",				fsub			},
	{0, 	"dsub",				dsub			},
	{0, 	"imul",				imul			},
	{0, 	"lmul",				lmul			},
	{0, 	"fmul",				fmul			},
	{0, 	"dmul",				dmul			},
	{0, 	"idiv",				idiv			},
	{0, 	"ldiv",				_ldiv			},
	{0, 	"fdiv",				fdiv			},
	{0, 	"ddiv",				ddiv			},
	{0, 	"irem",				irem			},
	{0, 	"lrem",				lrem			},
	{0, 	"frem",				frem			},
	{0, 	"drem",				_drem			},
	{0, 	"ineg",				ineg			},
	{0, 	"lneg",				lneg			},
	{0, 	"fneg",				fneg			},
	{0, 	"dneg",				dneg			},
	{0, 	"ishl",				ishl			},
	{0, 	"lshl",				lshl			},
	{0, 	"ishr",				ishr			},
	{0, 	"lshr",				lshr			},
	{0, 	"iushr",			iushr			},
	{0, 	"lushr",			lushr			},
	{0, 	"iand",				iand			},
	{0, 	"land",				land			},
	{0, 	"ior",				ior				},
	{0, 	"lor",				lor				},
	{0, 	"ixor",				ixor			},
	{0, 	"lxor",				lxor			},
	{2, 	"iinc",				iinc			},
	{0, 	"i2l",				i2l				},
	{0, 	"i2f",				i2f				},
	{0, 	"i2d",				i2d				},
	{0, 	"l2i",				l2i				},
	{0, 	"l2f",				l2f				},
	{0, 	"l2d",				l2d				},
	{0, 	"f2i",				f2i				},
	{0, 	"f2l",				f2l				},
	{0, 	"f2d",				f2d				},
	{0, 	"d2i",				d2i				},
	{0, 	"d2l",				d2l				},
	{0, 	"d2f",				d2f				},
	{0, 	"i2b",				i2b				},
	{0, 	"i2c",				i2c				},
	{0, 	"i2s",				i2s				},
	{0, 	"lcmp",				lcmp			},
	{0, 	"fcmpl",			fcmpl			},
	{0, 	"fcmpg",			fcmpg			},
	{0, 	"dcmpl",			dcmpl			},
	{0, 	"dcmpg",			dcmpg			},
	{2, 	"ifeq",				ifeq			},
	{2, 	"ifne",				ifne			},
	{2, 	"iflt",				iflt			},
	{2, 	"ifge",				ifge			},
	{2, 	"ifgt",				ifgt			},
	{2, 	"ifle",				ifle			},
	{2, 	"if_icmpeq",		if_icmpeq		},
	{2, 	"if_icmpne",		if_icmpne		},
	{2, 	"if_icmplt",		if_icmplt		},
	{2, 	"if_icmpge",		if_icmpge		},
	{2, 	"if_icmpgt",		if_icmpgt		},
	{2, 	"if_icmple",		if_icmple		},
	{2, 	"if_acmpeg",		if_acmpeg		},
	{2, 	"if_acmpne",		if_acmpne		},
	{2, 	"goto",				_goto			},
	{2, 	"jsr",				jsr				},
	{1, 	"ret",				ret				},
	{14, 	"tableswitch",		tableswitch		},
	{10,	"lookupswitch",		lookupswitch	},
	{0, 	"ireturn",			ireturn			},
	{0, 	"lreturn",			lreturn			},
	{0, 	"freturn",			freturn			},
	{0, 	"dreturn",			dreturn			},
	{0, 	"areturn",			areturn			},
	{0, 	"return",			_return			},
	{2, 	"getstatic",		getstatic		},
	{2, 	"putstatic",		putstatic		},
	{2, 	"getfield",			getfield		},
	{2, 	"putfield",			putfield		},
	{2, 	"invokevirtual",	invokevirtual	},
	{2, 	"invokespecial",	invokespecial	},
	{2, 	"invokestatic",		invokestatic	},
	{4, 	"invokeinterface",	invokeinterface	},
	{0, 	NULL,				NULL			},
	{2, 	"new",				new				},
	{1, 	"newarray",			newarray		},
	{2, 	"anewarray",		anewarray		},
	{0, 	"arraylength",		arraylength		},
	{0, 	"athrow",			athrow			},
	{0, 	"checkcast",		checkcast		},
	{0, 	"instanceof",		instanceof		},
	{0, 	"monitorenter",		monitorenter	},
	{0, 	"monitorexit",		monitorexit		},
	{7, 	"wide",				wide			},
	{3, 	"multianewarray",	multianewarray	},
	{2, 	"ifnull",			ifnull			},
	{2, 	"ifnonnull",		ifnonnull		},
	{4, 	"goto_w",			goto_w			},
	{4, 	"jsr_w",			jsr_w			}
};
