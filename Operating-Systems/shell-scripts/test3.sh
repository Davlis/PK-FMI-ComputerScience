echo "Podaj opcje:"
read zm
case $zm in
	"l") ls -l;;
	"s") ls -s;;
	"c") ls *.c;;
	*) echo "Błędna opcja";;
esac
exit 0