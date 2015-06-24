class HelloWorld{
	public static void main(String args[]){
		long a=0xEFFFFFFF;
		/*l2d*/
		double b=(double)a;
		/*l2f*/
		float c=(float)a;
		/*l2i*/
		int d=(int)a;
		
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		
		a = -a;
		b=(double)a;
		/*l2f*/
		c=(float)a;
		/*l2i*/
		d=(int)a;
		
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
	}	
}
