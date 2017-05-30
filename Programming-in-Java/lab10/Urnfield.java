package lab10;

public class Urnfield implements NumericSystem {
    public String fromArabic(int arabic){
        if(arabic > 29 || arabic < 1)
            throw new IllegalArgumentException();

        StringBuilder out = new StringBuilder();

        for(int i = 0; i < arabic%5; i++)
            out.append("/");
        for(int i = 0; i < arabic/5; i++)
            out.append("\\");

        return out.toString();
    }

    public int toArabic(String urnfield){
        int sum = 0;

        for(char c: urnfield.toCharArray()){
            switch(c){
                case '/':
                    sum++;
                    break;
                case '\\':
                    sum += 5;
                    break;
            }
        }
        return sum;
    }
}
