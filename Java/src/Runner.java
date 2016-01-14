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
		PrintWriter writer_access = null;
		PrintWriter writer_rank = null;
		PrintWriter writer_select = null;
		try {
			writer_read = new PrintWriter("read.out", "UTF-8");
			writer_build = new PrintWriter("build.out", "UTF-8");
			writer_access = new PrintWriter("access.out", "UTF-8");
			writer_rank = new PrintWriter("rank.out", "UTF-8");
			writer_select = new PrintWriter("select.out", "UTF-8");
		} catch (FileNotFoundException e) {
			System.out.println("Result filepath is not valid.");
			System.exit(1);
		} catch (UnsupportedEncodingException e) {
			System.out.println("Result file encoding is unsupported.");
			System.exit(1);
		}

		String filepath = args[0];

		/////////// PARSE //////////////
		double readElapsedTime = System.nanoTime();
		// parse FASTA file
		String fileData = Parser.parseFASTA(filepath);
		readElapsedTime = (System.nanoTime() - readElapsedTime) / 1000000;
		
		writer_read.write(Double.toString(readElapsedTime));
		writer_read.close();
		
		/////////// OPS PARAMS /////////
		char letter = fileData.charAt(0); 
		int accessIndex = fileData.length() / 2;
		int rankIndex = fileData.length() / 2;
		int selectIndex = (int) Math.floor(Math.sqrt(fileData.length()));
		int iter = 1000;
		
		////////// BUILD ///////////////
		double buildElapsedTime = System.nanoTime();
		// build tree
		WaveletTree wt = new WaveletTree(fileData.getBytes());
		buildElapsedTime = (System.nanoTime() - buildElapsedTime) / 1000000;
		
		writer_build.write(Double.toString(buildElapsedTime));
		writer_build.close();
		
		/////////// ACCESS ////////////
		double accessTime = 0;
		for (int i = 0; i < iter; i++) {
			double accessElapsedTime = System.nanoTime();
			wt.access(accessIndex);
			accessElapsedTime = (System.nanoTime() - accessElapsedTime) / 1000000;
			accessTime += accessElapsedTime;
		}
		writer_access.write(Double.toString(accessTime / iter));
		writer_access.close();
		
		/////////// RANK ////////////
		double rankTime = 0;
		for (int i = 0; i < iter; i++) {
			double rankElapsedTime = System.nanoTime();
			wt.rank((byte)letter, rankIndex);
			rankElapsedTime = (System.nanoTime() - rankElapsedTime) / 1000000;
			rankTime += rankElapsedTime;
		}
		writer_rank.write(Double.toString(rankTime / iter));
		writer_rank.close();
		
		/////////// SELECT ////////////
		double selectTime = 0;
		for (int i = 0; i < iter; i++) {
			double selectElapsedTime = System.nanoTime();
			wt.select((byte)letter, selectIndex);
			selectElapsedTime = (System.nanoTime() - selectElapsedTime) / 1000000;
			selectTime += selectElapsedTime;
		}
		writer_select.write(Double.toString(selectTime / iter));
		writer_select.close();
	}

}
