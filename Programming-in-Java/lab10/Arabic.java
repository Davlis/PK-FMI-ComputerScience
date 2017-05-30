package lab10;

public class Arabic implements NumericSystem {
    public int toArabic(String number) {
        for(int i = 0; i < number.length(); i++)
            if(number.charAt(i) < '0' || number.charAt(i) > '9')
                throw new IllegalArgumentException();

        return Integer.parseInt(number);
    }

    public String fromArabic(int number) {
        return Integer.toString(number);
    }
}
