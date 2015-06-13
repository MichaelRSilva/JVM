#include "../Common/common.h"
#include "../Util/util.h"
#include "maquina/maquina.h"

int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();
	CLASS_LOADER* cl = initCLASS_LOADER();

	if(!(flag = util.VerificaLeitorExibidorCMDArgs(argc, argv))) {
		if (!(flag = cl->load(cl, util.LeArquivo(argv[1])))) {
			JVM maquina = initJVM();

			maquina.classes[maquina.classes_size++] = cl->class;
			flag = maquina.loadParentClasses(&maquina, cl->class, &util);
			
			if(!flag){
				flag = maquina.loadInterfaces(&maquina, cl->class, &util);
			}
			
		}
	}
	
	printf("%s", errordesc[abs(flag)].message);
	return 0;
}
