public class String {
	private char[] value;
	private int count;

	public String() {
		value = new char[0];
	}

	public String(char[] newValue) {
		count = newValue.length;
		value = newValue;
	}
}