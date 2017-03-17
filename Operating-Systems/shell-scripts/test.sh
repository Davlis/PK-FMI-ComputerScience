if [ $# -ne 1 ]
	then
		echo "Zła liczba argumentów"
		exit 1
fi

if [ ! -f $1 ]
	then
		echo "Nie istnieje plik $1"
	else
		echo "Istnieje $1"
fi

exit 0