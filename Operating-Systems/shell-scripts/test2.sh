if [ $# -ne 2 ]
	then
		echo "Zła liczba argumentów"
		exit 1
fi

if [ ! -f $1 -o ! -f $2 ]
	then
		echo "Nie ma takich plików"
		exit 1
fi

d1=`cat $1 | wc -c`
d2=`cat $2 | wc -c`

if [ $d1 -gt $d2 ]
	then
		echo "Plik $1 jest dłuższy od pliku $2 o $(($d1-$d2)) znaków."
fi

if [ $d1 -eq $d2 ]
	then
		echo "Plik $1 ma długośc równą plikowi $2."
fi

if [ $d2 -gt $d1 ]
	then
		echo "Plik $2 jest dłuższy od pliku $1 o $(($d2-$d1)) znaków."
fi

exit 0