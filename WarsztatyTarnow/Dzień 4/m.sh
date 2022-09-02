./brut <tec3ocen.in> 3.out
if diff -b 3.out tec3ocen.out > /dev/null
then
    echo "$i OK!"
else
    echo "$i ZLE!"
fi