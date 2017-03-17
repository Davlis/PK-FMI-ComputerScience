if [ $# -ne 1 ]
	then
	echo "Zła liczba argumentów"
	exit 1
fi

until [ "`who | grep $1`" ]
	do
		sleep 2
	done
echo "JEST $1 "`date`>x

mail kosinskypl@gmail.com<x