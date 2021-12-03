package co.wordbe.level1;

public class NewIdRecommend {
    public String solution(String new_id) {
        String step = new_id;
        String step1 = step.toLowerCase();
        String step2 = step1.replaceAll("[^a-z0-9-_.]", "");
        String step3 = step2.replaceAll("[.]{2,}", ".");
        String step4 = step3.replaceAll("^[.]", "").replaceAll("[.]$", "");
        String step5 = step4.isEmpty() ? "a" : step4;
        String step5_1 = step5.length() >= 16 ? step5.substring(0, 15) : step5;
        String step6 = step5_1.replaceAll("[.]$", "");
        String step7 = step6;
        if (step6.length() <= 2) {
            char last = step6.charAt(step6.length() - 1);
            String result = step6;
            while (result.length() < 3) {
                result += last;
            }
            step7 = result;
        }

        return step7;
    }
}
