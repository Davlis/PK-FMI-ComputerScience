package lab10;

public class Converter {
    public String convert(NumericSystem source, NumericSystem destination, String str){
        return destination.fromArabic(source.toArabic(str));
    }
}
