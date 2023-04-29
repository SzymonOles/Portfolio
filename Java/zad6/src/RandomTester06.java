import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Random;

public class RandomTester06 {
  static Random rand = new Random(21372137l);

  // imputs words separated with spaces
  public static void inputSequence(String sequence, Compression comp) {
    for (var word : sequence.split(" "))
      comp.addWord(word);
  }

  // joins output words into single string
  public static String outputSequence(Compression comp, int size) {
    List<String> ls = new ArrayList<String>(size);
    for (int i = 0; i < size; i++) {
      ls.add(comp.getWord());
    }
    return String.join(" ", ls);
  }

  // calculates header bit length
  public static int getHeaderLength(Map<String, String> header) {
    var entry1 = header.entrySet().iterator().next();
    return (entry1.getKey().length() + entry1.getValue().length()) * header.size();
  }

  // calculates sequence length
  public static int getSequenceLenght(String sequence) {
    return List.of(sequence.split(" ")).stream().mapToInt(String::length).sum();
  }

  public static void main(String[] args) {
    int testCount = 10000;

    List<Integer> results = new ArrayList<Integer>(testCount);
    for (int i = 1; i <= testCount; i++) {
      var comp = new Compression();

      // random size list 10-31
      int testSize = 10 + rand.nextInt(21);
      List<String> wordList = new ArrayList<String>(testSize);
      // random word size 2-8
      int wordSize = 2 + rand.nextInt(7);

      for (int j = 0; j < testSize; j++) {
        int limit = (int) Math.pow(2, wordSize);
        // weighted random numbers to make it more likely that compression is possible
        int randInt = (int) Math.floor(Math.pow(rand.nextDouble() * Math.pow(limit, 5), 1.0 / 5));
        String word = Integer.toBinaryString(limit | randInt).substring(1);
        wordList.add(word);
        comp.addWord(word);
      }

      // System.out.println(wordList);

      comp.compress();
      var header = comp.getHeader();

      // compression failed - skip
      if (header.size() == 0) {
        continue;
      }

      String sequence = outputSequence(comp, testSize);

      results.add(getSequenceLenght(sequence) + getHeaderLength(header));
    }

    System.out.println(results);

    List<Integer> expectedArray = List.of(155, 41, 32, 63, 130, 124, 47, 38, 49, 86, 34, 103, 49, 105, 100, 25, 37, 40, 65, 24, 24, 69, 115, 60, 96, 142, 42, 47, 69, 97, 35, 35,
        87, 36, 111, 69, 36, 50, 106, 26, 31, 46, 57, 22, 90, 32, 52, 88, 55, 56, 70, 20, 128, 62, 205, 34, 39, 34, 59, 57, 29, 36, 28, 22, 43, 41, 52, 70, 60, 65, 38, 70, 83, 69,
        82, 62, 39, 53, 17, 43, 72, 85, 35, 22, 44, 104, 29, 88, 22, 40, 29, 99, 48, 107, 17, 38, 167, 115, 64, 35, 71, 164, 56, 92, 105, 37, 58, 72, 25, 35, 107, 51, 31, 43, 109,
        35, 125, 53, 102, 112, 69, 60, 60, 21, 105, 40, 26, 16, 54, 36, 57, 18, 116, 22, 56, 72, 30, 29, 25, 75, 118, 75, 48, 50, 53, 78, 50, 43, 85, 17, 39, 49, 40, 29, 109, 44,
        49, 49, 39, 48, 94, 30, 112, 33, 58, 54, 102, 85, 84, 50, 27, 73, 46, 97, 59, 101, 32, 124, 25, 104, 29, 25, 51, 38, 35, 124, 26, 57, 27, 51, 132, 85, 88, 36, 50, 39, 70,
        75, 31, 93, 107, 40, 47, 53, 24, 66, 34, 18, 55, 83, 20, 72, 88, 57, 98, 133, 56, 34, 55, 79, 104, 74, 76, 29, 25, 39, 30, 106, 42, 176, 33, 25, 88, 58, 27, 81, 32, 15, 57,
        71, 45, 73, 28, 23, 23, 36, 72, 34, 91, 72, 132, 40, 56, 34, 83, 57, 142, 167, 167, 22, 88, 31, 39, 43, 59, 68, 68, 30, 63, 82, 53, 138, 85, 78, 24, 40, 75, 52, 74, 19, 32,
        28, 39, 124, 116, 70, 42, 67, 33, 55, 67, 72, 111, 47, 30, 66, 29, 56, 75, 29, 65, 52, 35, 128, 40, 52, 86, 51, 118, 72, 62, 43, 16, 35, 43, 80, 36, 41, 104, 28, 67, 95,
        92, 88, 24, 80, 66, 23, 67, 28, 70, 28, 85, 67, 82, 37, 70, 89, 45, 58, 104, 41, 65, 55, 20, 88, 74, 39, 27, 146, 74, 43, 39, 58, 51, 17, 29, 76, 37, 34, 95, 71, 41, 38,
        47, 124, 34, 64, 112, 44, 67, 43, 39, 31, 28, 69, 124, 35, 55, 38, 28, 83, 126, 46, 47, 63, 124, 33, 86, 50, 76, 43, 128, 89, 112, 58, 119, 146, 58, 48, 86, 50, 75, 95, 58,
        43, 28, 57, 23, 47, 79, 94, 39, 39, 32, 35, 140, 27, 26, 50, 141, 34, 55, 43, 52, 72, 119, 30, 88, 64, 76, 41, 29, 202, 59, 26, 146, 32, 61, 27, 86, 19, 103, 124, 47, 37,
        42, 64, 33, 103, 31, 69, 23, 34, 21, 56, 46, 109, 128, 64, 66, 83, 47, 39, 66, 123, 45, 60, 36, 62, 23, 50, 56, 30, 65, 64, 27, 30, 50, 168, 20, 83, 67, 94, 52, 84, 32, 86,
        53, 20, 28, 99, 55, 30, 23, 24, 79, 62, 50, 117, 95, 27, 24, 48, 38, 41, 97, 35, 29, 93, 45, 72, 25, 45, 35, 45, 73, 34, 42, 30, 45, 37, 28, 72, 107, 25, 35, 160, 56, 49,
        73, 53, 19, 39, 64, 70, 30, 57, 97, 29, 97, 67, 38, 35, 38, 45, 53, 23, 136, 70, 79, 19, 54, 39, 115, 26, 38, 38, 100, 66, 60, 47, 78, 55, 84, 25, 79, 112, 134, 139, 29,
        70, 29, 69, 47, 44, 41, 92, 56, 74, 87, 51, 123, 114, 29, 100, 46, 18, 23, 19, 18, 42, 57, 51, 36, 30, 146, 102, 234, 96, 43, 25, 71, 33, 57, 40, 55, 112, 55, 36, 32, 41,
        86, 53, 70, 50, 23, 77, 24, 31, 44, 39, 57, 40, 27, 46, 31, 35, 41, 57, 112, 35, 30, 49, 30, 23, 126, 35, 59, 77, 20, 39, 122, 132, 98, 78, 44, 29, 63, 50, 20, 56, 68, 28,
        28, 26, 41, 67, 25, 73, 136, 30, 55, 78, 47, 78, 34, 73, 45, 19, 54, 30, 54, 86, 40, 33, 86, 19, 97, 17, 71, 26, 102, 76, 103, 43, 47, 34, 41, 29, 29, 32, 32, 102, 27, 48,
        47, 33, 46, 76, 114, 87, 167, 53, 133, 86, 108, 74, 126, 52, 53, 47, 85, 30, 33, 64, 31, 19, 103, 81, 40, 20, 111, 25, 43, 86, 169, 61, 20, 62, 110, 33, 91, 38, 21, 27, 39,
        48, 82, 91, 31, 25, 51, 31, 50, 32, 44, 72, 126, 84, 56, 25, 34, 57, 66, 38, 72, 51, 78, 72, 115, 82, 68, 34, 40, 40, 63, 35, 33, 29, 43, 35, 27, 37, 59, 70, 77, 34, 15,
        58, 69, 27, 47, 132, 58, 21, 39, 22, 86, 48, 95, 72, 70, 34, 93, 46, 34, 87, 42, 21, 29, 40, 31, 64, 51, 39, 92, 41, 66, 146, 40, 86, 65, 31, 31, 105, 100, 134, 39, 35, 33,
        45, 194, 86, 96, 36, 38, 104, 82, 60, 62, 28, 18, 25, 18, 114, 103, 83, 44, 52, 50, 104, 18, 38, 60, 71, 146, 21, 78, 74, 33, 52, 32, 21, 73, 98, 108, 19, 91, 31, 66, 58,
        47, 61, 139, 71, 18, 146, 74, 83, 103, 62, 36, 40, 59, 100, 37, 52, 29, 72, 46, 93, 54, 107, 39, 38, 28, 24, 103, 37, 76, 47, 39, 36, 29, 23, 54, 60, 63, 32, 73, 47, 26,
        61, 44, 48, 29, 26, 42, 38, 33, 41, 110, 30, 41, 29, 88, 83, 29, 34, 58, 42, 55, 70, 23, 72, 72, 31, 28, 40, 60, 123, 146, 32, 30, 84, 83, 43, 47, 19, 42, 98, 38, 40, 72,
        66, 23, 36, 78, 92, 39, 39, 66, 25, 56, 99, 53, 20, 41, 50, 54, 38, 62, 34, 52, 47, 100, 76, 55, 44, 39, 110, 38, 23, 144, 42, 111, 46, 62, 48, 39, 62, 29, 67, 105, 36, 44,
        26, 44, 118, 92, 116, 34, 27, 103, 27, 51, 34, 28, 34, 89, 81, 38, 47, 100, 138, 67, 96, 89, 107, 47, 76, 38, 74, 14, 78, 62, 83, 36, 84, 88, 53, 138, 47, 79, 38, 28, 67,
        93, 36, 102, 26, 124, 100, 81, 114, 86, 98, 104, 40, 63, 93, 50, 50, 21, 23, 73, 69, 43, 138, 57, 71, 89, 34, 135, 118, 45, 51, 76, 57, 103, 37, 27, 58, 59, 63, 71, 62, 42,
        70, 44, 63, 51, 103, 46, 46, 26, 37, 80, 83, 41, 86, 45, 20, 108, 33, 80, 107, 71, 76, 44, 71, 67, 27, 19, 31, 68, 44, 71, 47, 32, 106, 74, 76, 79, 44, 92, 94, 36, 23, 36,
        32, 115, 103, 46, 65, 112, 58, 127, 103, 160, 45, 88, 23, 32, 37, 44, 26, 98, 39, 114, 43, 19, 81, 95, 105, 20, 58, 69, 27, 26, 26, 138, 117, 37, 45, 29, 36, 130, 45, 110,
        64, 50, 63, 106, 74, 111, 31, 35, 110, 32, 52, 37, 35, 112, 79, 39, 31, 36, 59, 35, 40, 15, 106, 20, 99, 102, 107, 71, 19, 31, 35, 71, 120, 48, 40, 76, 21, 43, 119, 81, 55,
        37, 45, 36, 57, 40, 33, 19, 32, 78, 78, 110, 60, 26, 49, 23, 28, 73, 80, 103, 32, 19, 36, 112, 83, 118, 63, 50, 62, 62, 46, 40, 94, 108, 39, 33, 32, 134, 78, 47, 20, 24,
        40, 51, 18, 44, 32, 19, 38, 78, 76, 41, 67, 28, 66, 82, 31, 30, 153, 78, 78, 56, 26, 29, 92, 68, 153, 117, 84, 48, 56, 28, 24, 91, 104, 70, 59, 39, 55, 50, 72, 36, 23, 31,
        36, 44, 65, 39, 53, 39, 100, 41, 42, 33, 82, 131, 86, 112, 43, 127, 28, 112, 38, 33, 79, 29, 23, 24, 114, 37, 31, 24, 52, 54, 29, 37, 19, 35, 41, 48, 61, 27, 69, 100, 25,
        15, 41, 93, 40, 81, 56, 84, 25, 36, 102, 93, 51, 24, 15, 61, 53, 26, 103, 162, 58, 103, 46, 34, 58, 80, 76, 69, 90, 50, 95, 21, 61, 75, 28, 27, 49, 44, 32, 24, 52, 24, 120,
        108, 52, 27, 110, 40, 21, 29, 63, 36, 17, 104, 40, 69, 124, 63, 152, 45, 59, 92, 37, 55, 123, 59, 20, 68, 89, 68, 68, 100, 70, 77, 66, 80, 29, 82, 26, 20, 50, 41, 70, 38,
        162, 68, 15, 39, 29, 113, 110, 64, 37, 32, 39, 68, 50, 41, 96, 36, 89, 13, 27, 66, 38, 109, 34, 62, 19, 56, 124, 37, 82, 104, 54, 39, 67, 59, 130, 19, 37, 52, 96, 39, 74,
        91, 37, 36, 34, 86, 93, 44, 64, 73, 25, 50, 25, 43, 34, 44, 35, 45, 35, 19, 120, 82, 44, 38, 89, 50, 100, 26, 33, 48, 21, 34, 60, 37, 27, 52, 83, 35, 29, 30, 41, 60, 31,
        76, 34, 23, 46, 41, 84, 29, 36, 33, 20, 51, 71, 85, 27, 37, 62, 94, 58, 44, 67, 28, 29, 88, 104, 69, 79, 39, 64, 38, 81, 26, 37, 21, 138, 42, 33, 49, 30, 81, 84, 81, 37,
        29, 32, 25, 111, 124, 17, 48, 111, 29, 28, 86, 30, 66, 81, 45, 40, 32, 95, 28, 76, 27, 89, 17, 67, 112, 19, 126, 118, 102, 37, 47, 55, 99, 61, 40, 114, 105, 98, 43, 74, 21,
        34, 31, 70, 98, 106, 52, 42, 38, 41, 22, 61, 37, 64, 95, 111, 31, 86, 106, 138, 59, 93, 144, 67, 71, 99, 64, 13, 106, 56, 33, 31, 90, 117, 42, 59, 111, 137, 53, 49, 46, 88,
        28, 139, 32, 87, 33, 49, 36, 58, 35, 144, 20, 67, 59, 31, 86, 52, 36, 43, 55, 77, 97, 68, 74, 66, 107, 27, 60, 43, 25, 95, 66, 48, 84, 54, 103, 39, 27, 28, 33, 27, 26, 34,
        137, 144, 57, 47, 36, 27, 50, 22, 19, 101, 15, 86, 30, 46, 97, 39, 140, 126, 60, 43, 54, 102, 136, 71, 91, 65, 80, 58, 95, 93, 30, 39, 15, 142, 30, 66, 47, 37, 36, 73, 44,
        43, 37, 77, 99, 59, 22, 23, 104, 34, 106, 45, 34, 38, 34, 45, 47, 39, 39, 53, 38, 72, 73, 81, 72, 59, 47, 33, 18, 52, 59, 37, 169, 111, 37, 30, 78, 65, 42, 58, 35, 75, 76,
        38, 23, 38, 28, 104, 38, 62, 24, 62, 55, 27, 40, 69, 19, 22, 23, 42, 22, 83, 40, 126, 28, 23, 35, 21, 100, 32, 40, 48, 104, 52, 70, 36, 52, 27, 167, 17, 73, 25, 139, 20,
        124, 100, 23, 32, 30, 78, 103, 77, 102, 103, 37, 124, 61, 37, 64, 23, 100, 94, 105, 25, 82, 17, 144, 36, 63, 45, 80, 76, 67, 64, 110, 37, 32, 104, 26, 45, 24, 56, 50, 42,
        70, 41, 48, 112, 33, 28, 94, 98, 34, 35, 124, 21, 24, 34, 31, 45, 43, 80, 50, 117, 55, 86, 41, 104, 35, 43, 71, 29, 77, 28, 56, 103, 21, 59, 19, 35, 39, 14, 68, 51, 111,
        115, 138, 38, 102, 83, 77, 38, 111, 64, 69, 48, 29, 58, 91, 38, 88, 73, 102, 34, 25, 41, 36, 39, 79, 77, 91, 55, 102, 63, 22, 56, 55, 51, 97, 82, 93, 68, 16, 72, 23, 84,
        72, 53, 31, 39, 38, 98, 75, 62, 72, 65, 37, 43, 46, 44, 45, 17, 30, 72, 43, 52, 36, 84, 52, 68, 30, 39, 66, 68, 142, 66, 160, 29, 33, 55, 47, 25, 60, 60, 39, 20, 26, 39,
        26, 35, 59, 98, 38, 38, 38, 33, 164, 26, 33, 70, 44, 41, 47, 19, 43, 46, 32, 13, 96, 48, 52, 31, 71, 31, 70, 78, 47, 67, 28, 57, 203, 41, 29, 41, 65, 34, 50, 111, 26, 104,
        94, 36, 55, 110, 79, 98, 74, 71, 63, 36, 169, 48, 57, 91, 76, 38, 100, 169, 39, 18, 37, 35, 67, 80, 68, 29, 45, 74, 25, 31, 55, 144, 85, 107, 47, 57, 46, 37, 73, 104, 73,
        39, 20, 37, 33, 96, 75, 17, 71, 42, 79, 42, 20, 49, 114, 43, 57, 53, 25, 75, 20, 90, 54, 73, 109, 83, 70, 42, 39, 26, 51, 33, 71, 17, 132, 39, 52, 63, 26, 63, 49, 68, 71,
        44, 64, 61, 68, 39, 97, 65, 120, 108, 84, 26, 51, 41, 70, 76, 24, 19, 73, 104, 112, 50, 148, 72, 32, 36, 54, 89, 36, 38, 63, 109, 86, 85, 65, 34, 38, 49, 84, 69, 31, 66,
        95, 31, 52, 60, 57, 37, 64, 119, 137, 66, 71, 59, 70, 82, 72, 95, 38, 55, 32, 37, 50, 31, 17, 58, 91, 23, 46, 53, 29, 17, 56, 71, 44, 78, 45, 146, 37, 49, 73, 28, 100, 76,
        62, 19, 117, 28, 49, 19, 38, 162, 34, 84, 35, 53, 115, 50, 44, 37, 82, 26, 114, 32, 61, 21, 109, 32, 37, 38, 45, 47, 105, 39, 48, 70, 32, 98, 42, 20, 61, 44, 38, 42, 33,
        106, 18, 43, 77, 54, 85, 35, 68, 117, 48, 42, 88, 44, 40, 16, 34, 43, 79, 40, 22, 74, 96, 25, 111, 38, 25, 22, 34, 105, 146, 53, 109, 61, 53, 97, 112, 38, 16, 71, 73, 91,
        36, 39, 56, 56, 137, 29, 48, 72, 22, 32, 61, 28, 162, 68, 86, 50, 40, 21, 52, 79, 75, 31, 40, 79, 25, 55, 48, 74, 71, 76, 41, 52, 22, 39, 51, 43, 35, 37, 32, 40, 110, 112,
        55, 19, 22, 24, 35, 66, 34, 93, 64, 95, 24, 82, 20, 39, 31, 42, 22, 33, 17, 60, 123, 104, 55, 75, 34, 19, 59, 62, 186, 47, 44, 83, 33, 38, 51, 94, 104, 26, 54, 86, 35, 106,
        35, 59, 43, 98, 41, 63, 116, 22, 29, 41, 134, 36, 48, 105, 29, 30, 47, 38, 24, 21, 65, 26, 109, 66, 94, 75, 87, 27, 105, 20, 61, 114, 69, 73, 140, 105, 89, 47, 47, 66, 62,
        37, 64, 94, 115, 21, 77, 108, 43, 54, 39, 43, 35, 44, 26, 63, 83, 43, 51, 34, 39, 42, 38, 39, 43, 93, 19, 27, 72, 34, 21, 25, 28, 30, 38, 70, 84, 62, 39, 78, 41, 43, 36,
        33, 84, 20, 92, 78, 43, 76, 20, 36, 22, 112, 44, 67, 24, 130, 80, 79, 44, 53, 35, 39, 62, 43, 27, 83, 65, 51, 109, 46, 59, 69, 59, 82, 46, 19, 59, 84, 52, 90, 39, 131, 76,
        53, 86, 67, 139, 39, 66, 69, 64, 62, 31, 98, 74, 38, 88, 39, 118, 35, 56, 32, 30, 53, 62, 82, 82, 100, 35, 65, 64, 74, 146, 82, 18, 71, 43, 26, 55, 29, 50, 78, 17, 129, 38,
        33, 91, 22, 112, 92, 49, 52, 86, 33, 92, 39, 32, 61, 75, 108, 83, 70, 72, 79, 24, 30, 153, 72, 16, 36, 101, 28, 137, 34, 124, 28, 77, 27, 61, 38, 18, 35, 19, 81, 41, 26,
        15, 146, 35, 72, 78, 35, 65, 64, 42, 38, 15, 66, 115, 42, 24, 46, 59, 21, 49, 33, 41, 56, 24, 114, 71, 20, 17, 39, 43, 27, 138, 29, 61, 59, 74, 28, 93, 149, 41, 42, 20, 60,
        99, 81, 25, 35, 73, 58, 48, 89, 30, 38, 33, 33, 109, 93, 31, 28, 102, 47, 34, 72, 34, 65, 71, 40, 38, 43, 42, 75, 20, 66, 72, 40, 65, 17, 27, 22, 61, 18, 46, 42, 136, 91,
        31, 20, 40, 65, 114, 80, 73, 50, 37, 79, 29, 45, 40, 19, 120, 49, 35, 70, 66, 21, 44, 71, 44, 31, 72, 138, 71, 18, 20, 56, 34, 60, 45, 49, 31, 65, 19, 59, 47, 27, 33, 38,
        23, 74, 64, 65, 54, 70, 20, 26, 81, 74, 93, 100, 31, 25, 56, 30, 25, 30, 83, 15, 78, 20, 17, 61, 90, 103, 36, 76, 62, 36, 45, 28, 76, 60, 44, 31, 45, 45, 38, 21, 57, 124,
        24, 118, 42, 103, 28, 34, 37, 21, 49, 74, 22, 71, 112, 87, 76, 54, 17, 31, 108, 122, 84, 88, 39, 27, 79, 52, 76, 36, 26, 181, 43, 78, 144, 82, 45, 71, 51, 32, 157, 166, 54,
        80, 68, 91, 57, 58, 30, 95, 27, 36, 91, 102, 50, 68, 16, 44, 49, 32, 117, 50, 40, 76, 63, 117, 74, 38, 55, 91, 95, 140, 66, 55, 31, 68, 39, 83, 46, 17, 101, 91, 34, 21, 48,
        62, 48, 55, 44, 114, 138, 18, 66, 19, 77, 66, 95, 37, 78, 38, 93, 62, 106, 49, 115, 54, 53, 72, 53, 63, 34, 146, 68, 32, 122, 68, 70, 58, 42, 26, 49, 20, 75, 120, 39, 42,
        42, 74, 37, 114, 98, 30, 38, 63, 62, 26, 160, 36, 73, 112, 66, 78, 49, 55, 73, 43, 16, 62, 33, 54, 70, 82, 123, 29, 17, 31, 40, 24, 56, 44, 88, 75, 28, 32, 22, 84, 43, 23,
        57, 47, 34, 146, 31, 43, 68, 88, 60, 44, 112, 107, 29, 88, 32, 54, 25, 40, 44, 21, 30, 39, 122, 53, 139, 24, 93, 66, 20, 72, 84, 118, 41, 117, 40, 107, 41, 83, 58, 39, 28,
        40, 46, 47, 74, 93, 40, 99, 101, 149, 40, 30, 59, 70, 85, 69, 36, 62, 39, 98, 34, 65, 35, 44, 85, 34, 81, 71, 59, 84, 41, 31, 70, 42, 45, 50, 31, 52, 56, 61, 24, 23, 93,
        68, 42, 103, 114, 41, 54, 27, 30, 30, 18, 34, 43, 139, 59, 29, 64, 41, 21, 52, 41, 42, 19, 35, 138, 24, 102, 29, 40, 38, 75, 118, 102, 36, 126, 34, 33, 198, 30, 71, 65, 42,
        30, 39, 42, 79, 68, 138, 36, 35, 72, 61, 31, 52, 58, 31, 51, 66, 83, 37, 82, 29, 37, 29, 40, 112, 23, 39, 160, 48, 19, 123, 34, 23, 28, 38, 81, 79, 34, 115, 171, 24, 68,
        43, 64, 35, 67, 117, 140, 34, 81, 62, 40, 26, 67, 109, 34, 17, 93, 175, 44, 71, 118, 97, 40, 124, 28, 132, 81, 32, 59, 60, 107, 59, 39, 72, 138, 24, 108, 68, 103, 39, 58,
        101, 35, 42, 37, 101, 40, 41, 26, 37, 65, 39, 41, 29, 23, 24, 47, 33, 81, 23, 72, 38, 42, 23, 29, 32, 64, 29, 48, 30, 117, 72, 49, 102, 28, 39, 46, 44, 25, 49, 91, 31, 74,
        47, 70, 71, 38, 62, 56, 99, 29, 93, 59, 30, 38, 117, 15, 37, 35, 66, 46, 83, 39, 37, 107, 50, 19, 15, 23, 41, 33, 72, 63, 40, 74, 31, 39, 25, 35, 39, 89, 49, 136, 120, 74,
        64, 65, 31, 40, 90, 34, 31, 25, 111, 28, 26, 24, 32, 23, 30, 29, 33, 39, 34, 41, 67, 38, 53, 44, 30, 100, 34, 39, 33, 121, 43, 37, 79, 43, 78, 194, 25, 73, 38, 96, 53, 43,
        132, 28, 106, 57, 89, 20, 98, 98, 39, 34, 34, 56, 46, 33, 43, 75, 15, 88, 61, 79, 20, 98, 16, 35, 71, 43, 68, 109, 39, 40, 105, 48, 44, 91, 28, 35, 83, 32, 40, 50, 98, 95,
        64, 30, 74, 39, 40, 40, 40, 38, 26, 83, 86, 47, 78, 17, 105, 155, 56, 114, 89, 56, 19, 80, 35, 112, 48, 57, 64, 85, 43, 37, 39, 45, 45, 83, 59, 71, 37, 27, 40, 33, 61, 68,
        38, 36, 95, 40, 91, 64, 50, 68, 23, 137, 20, 91, 35, 16, 118, 50, 24, 82, 109, 29, 24, 43, 31, 94, 78, 93, 30, 142, 25, 83, 33, 34, 73, 96, 45, 74, 39, 84, 64, 34, 39, 104,
        57, 24, 19, 28, 100, 136, 54, 54, 39, 40, 64, 68, 47, 27, 26, 64, 34, 64, 20, 34, 76, 15, 41, 98, 128, 65, 36, 32, 94, 48, 79, 44, 64, 83, 35, 18, 54, 69, 47, 98, 17, 51,
        99, 38, 107, 59, 41, 38, 47, 35, 70, 22, 66, 72, 100, 102, 138, 82, 34, 50, 80, 48, 62, 26, 77, 26, 55, 78, 35, 118, 41, 37, 59, 22, 66, 25, 71, 70, 68, 82, 34, 39, 90, 83,
        29, 103, 42, 33, 86, 97, 32, 47, 27, 42, 93, 17, 41, 167, 107, 118, 115, 38, 97, 132, 35, 86, 167, 97, 64, 105, 62, 23, 105, 46, 83, 99, 53, 63, 115, 48, 71, 114, 51, 29,
        46, 41, 124, 64, 32, 42, 54, 41, 96, 162, 46, 27, 43, 48, 186, 49, 70, 43, 54, 49, 56, 58, 50, 78, 51, 17, 19, 28, 146, 47, 39, 107, 41, 31, 34, 45, 53, 66, 32, 84, 64, 40,
        91, 35, 146, 72, 58, 71, 78, 66, 37, 21, 26, 66, 107, 36, 58, 43, 56, 27, 22, 38, 83, 39, 47, 82, 28, 31, 28, 56, 50, 51, 39, 108, 26, 45, 71, 109, 92, 41, 47, 54, 70, 107,
        20, 32, 138, 61, 69, 28, 40, 36, 52, 63, 146, 70, 39, 29, 25, 98, 20, 40, 42, 47, 36, 129, 39, 110, 87, 55, 26, 97, 115, 68, 45, 17, 47, 29, 147, 38, 42, 78, 45, 33, 64,
        32, 160, 31, 74, 46, 29, 52, 72, 36, 52, 37, 52, 46, 120, 19, 31, 77, 32, 22, 28, 91, 35, 41, 43, 42, 67, 83, 41, 83, 72, 88, 102, 103, 72, 126, 74, 61, 39, 36, 24, 56, 31,
        35, 35, 35, 19, 41, 41, 194, 43, 48, 45, 46, 44, 31, 35, 23, 45, 20, 99, 15, 162, 36, 38, 29, 112, 46, 36, 49, 43, 62, 39, 133, 124, 37, 44, 28, 43, 47, 107, 29, 28, 44,
        18, 116, 45, 146, 194, 120, 61, 47, 83, 57, 102, 166, 69, 130, 68, 116, 75, 23, 50, 39, 39, 102, 54, 101, 18, 110, 37, 112, 53, 68, 72, 105, 71, 76, 45, 27, 86, 104, 48,
        38, 30, 24, 27, 29, 98, 18, 33, 114, 93, 117, 75, 26, 83, 68, 47, 72, 23, 48, 107, 52, 39, 28, 71, 94, 85, 98, 73, 48, 35, 43, 115, 36, 85, 61, 25, 107, 25, 91, 52, 37, 37,
        83, 28, 94, 98, 70, 29, 149, 74, 86, 69, 15, 51, 35, 70, 22, 29, 27, 36, 72, 72, 103, 45, 31, 55, 68, 70, 29, 89, 21, 45, 27, 20, 45, 39, 88, 55, 36, 31, 104, 57, 43, 30,
        45, 37, 46, 19, 51, 58, 124, 22, 144, 47, 16, 36, 82, 71, 56, 23, 34, 30, 109, 146, 48, 104, 79, 16, 57, 98, 65, 31, 82, 47, 120, 66, 49, 40, 20, 33, 42, 57, 47, 53, 100,
        27, 160, 70, 81, 53, 24, 52, 110, 31, 40, 83, 16, 49, 34, 39, 96, 44, 102, 74, 29, 40, 18, 133, 47, 35, 65, 48, 40, 48, 41, 43, 78, 108, 48, 26, 37, 31, 30, 92, 26, 79, 68,
        68, 32, 77, 31, 39, 116, 72, 78, 62, 42, 15, 24, 68, 34, 47, 65, 39, 40, 93, 124, 56, 38, 53, 146, 68, 36, 79, 36, 104, 46, 30);

    System.out.println("Results " + (expectedArray.equals(results) ? "" : "do not") + "match expected values");
  }

}