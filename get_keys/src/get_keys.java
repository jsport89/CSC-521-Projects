import java.io.*;
import java.math.BigInteger;
import java.util.Base64;

public class get_keys{
    public static void main(String [] args) throws IOException{
        File file = new File("/Users/Sam/Desktop/moduli.txt");
        File fout = new File("out.txt");
        FileOutputStream fos = new FileOutputStream(fout);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line, substring;
            while ((line = br.readLine()) != null) {
                if(!line.equals("null")) {
                    substring = line.substring(1, line.length() - 1);
                    byte[] asBytes = Base64.getDecoder().decode(substring.getBytes());
                    BigInteger bigInteger = new BigInteger(1, asBytes);
                    bw.write(bigInteger.toString());
                    bw.newLine();
                }
            }
            bw.close();
        }
    }
}
