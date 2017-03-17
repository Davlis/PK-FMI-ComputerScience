n=0
for zm in $(ls *.c)
	do
		echo "$zm"
		n=$(($n+1))
	done

echo "Liczba plików: $n"

if [ $# -ne 1 ]
	then
		echo "Zła liczba argumentów"
		exit 1
fi

n=0
while [ $1 -gt $n ]
	do
		echo "Systemy operacyjne"
		n=$(($n+1))
	done