import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;


public class Runner {
	
	public static String usageInfo = "usage: java Runner <filepath>";

	public static void main(String[] args) {
		if (args.length != 1) {
			System.out.println("Number of arguments is not valid.\n"
					+ usageInfo);
			System.exit(1);
		}
		
		PrintWriter writer_read = null;
		PrintWriter writer_build = null;
		try {
			writer_read = new PrintWriter("read.out", "UTF-8");
			writer_build = new PrintWriter("build.out", "UTF-8");
		} catch (FileNotFoundException e) {
			System.out.println("Result filepath is not valid.");
			System.exit(1);
		} catch (UnsupportedEncodingException e) {
			System.out.println("Result file encoding is unsupported.");
			System.exit(1);
		}

		String filepath = args[0];

		long readElapsedTime = System.currentTimeMillis();
		// parse FASTA file
		String fileData = Parser.parseFASTA(filepath);
		readElapsedTime = System.currentTimeMillis() - readElapsedTime;
		
		writer_read.write(Long.toString(readElapsedTime));
		writer_read.close();
		
		long buildElapsedTime = System.currentTimeMillis();
		// build tree
		WaveletTree wt = new WaveletTree(fileData.getBytes());
		buildElapsedTime = System.currentTimeMillis() - buildElapsedTime;
		
		writer_build.write(Long.toString(buildElapsedTime));
		writer_build.close();
	}

}
