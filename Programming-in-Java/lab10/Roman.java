package lab10;

public class Roman implements NumericSystem {
    private static final int[] romanCharacters = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    private static final int[] valuesOfRomanCharacters = {1000, 500, 100, 50, 10, 5, 1};
    private static final char[] wholes = {'I', 'X', 'C', 'M'};
    private static final char[] halves = {'V', 'L', 'D'};


    public String fromArabic(int arabic){
        if(arabic > 3000 || arabic < 1)
            throw new IllegalArgumentException();

        String num = new StringBuilder(Integer.toString(arabic)).reverse().toString();
        StringBuilder out = new StringBuilder();

        for(int i = num.length()-1; i >= 0; i--){
            int temp = Integer.parseInt(num.substring(i, i+1));
            switch(temp){

                case 5:case 6:case 7:case 8:
                    out.append(halves[i]);
                case 1:case 2:case 3:
                    for(int j = 0; j < temp%5; j++)
                        out.append(wholes[i]);
                    break;

                case 4:
                    out.append(wholes[i]);
                    out.append(halves[i]);
                    break;

                case 9:
                    out.append(wholes[i]);
                    out.append(wholes[i+1]);
                    break;
            }
        }
        return out.toString();
    }

    public int toArabic(String roman){
        int sum = 0;

        char prevChar = roman.charAt(0);
        for(char c: roman.toCharArray()){
            int i = 0;
            for(; i < romanCharacters.length; i++)
                if(c == romanCharacters[i])
                    break;

            if(prevChar != c){
                int j = 0;
                for(; j < romanCharacters.length; j++)
                    if(prevChar == romanCharacters[j])
                        break;

                prevChar = c;

                if(j > i){
                    sum += 0.6 * valuesOfRomanCharacters[i];
                    continue;
                }
            }
            sum += valuesOfRomanCharacters[i];
        }
        return sum;
    }
}
