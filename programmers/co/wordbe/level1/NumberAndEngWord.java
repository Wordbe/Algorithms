package co.wordbe.level1;

public class NumberAndEngWord {
    public int solution(String s) {
        String[] digits = {"0","1","2","3","4","5","6","7","8","9"};
        String[] alphabets = {"zero","one","two","three","four","five","six","seven","eight","nine"};

        for(int i=0; i<10; i++){
            s = s.replaceAll(alphabets[i],digits[i]);
        }

        return Integer.parseInt(s);
    }

//    public int solution(String s) {
//        String string = s;
//        while (containsDigitWord(string)) {
//            string = convert(string);
//        }
//
//        return Integer.parseInt(convert(string));
//    }
//
//    private String convert(String s) {
//        if (s.contains("zero")) {
//            return s.replaceAll("zero", "0");
//        } else if (s.contains("one")) {
//            return s.replaceAll("one", "1");
//        } else if (s.contains("two")) {
//            return s.replaceAll("two", "2");
//        } else if (s.contains("three")) {
//            return s.replaceAll("three", "3");
//        } else if (s.contains("four")) {
//            return s.replaceAll("four", "4");
//        } else if (s.contains("five")) {
//            return s.replaceAll("five", "5");
//        } else if (s.contains("six")) {
//            return s.replaceAll("six", "6");
//        } else if (s.contains("seven")) {
//            return s.replaceAll("seven", "7");
//        } else if (s.contains("eight")) {
//            return s.replaceAll("eight", "8");
//        } else if (s.contains("nine")) {
//            return s.replaceAll("nine", "9");
//        }
//        return s;
//    }
//
//    private boolean containsDigitWord(String s) {
//        if (s.contains("zero")) {
//            return true;
//        } else if (s.contains("one")) {
//            return true;
//        } else if (s.contains("two")) {
//            return true;
//        } else if (s.contains("three")) {
//            return true;
//        } else if (s.contains("four")) {
//            return true;
//        } else if (s.contains("five")) {
//            return true;
//        } else if (s.contains("six")) {
//            return true;
//        } else if (s.contains("seven")) {
//            return true;
//        } else if (s.contains("eight")) {
//            return true;
//        } else if (s.contains("nine")) {
//            return true;
//        }
//        return false;
//    }
}
