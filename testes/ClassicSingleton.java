public class ClassicSingleton {
	public final static ClassicSingleton instance = getInstance();
	public final static String teste = "Teste";
	public final static long valLong= 544213139;
	public final static int valInt = 123124;
	public final static double valDouble= 54.0224;

	protected ClassicSingleton() {

	}

	public static ClassicSingleton getInstance() {
		if (instance == null) {
			return new ClassicSingleton();
		}
		return instance;
	}


	private int soma(int a, int b){

		int resultado = 0;
		resultado = a+b;

		return resultado;
	}

}