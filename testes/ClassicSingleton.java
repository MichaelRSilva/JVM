public class ClassicSingleton {
	public final static ClassicSingleton instance = getInstance();
	public final static String teste = "Teste";
	public final static double teste2 = 833187342.92312313;
	public final static int teste3 = 123124;

	protected ClassicSingleton() {

	}

	public static ClassicSingleton getInstance() {
		if (instance == null) {
			return new ClassicSingleton();
		}
		return instance;
	}
}