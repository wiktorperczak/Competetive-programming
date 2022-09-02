./brutsz < sza3ocen.in >  1.out
if diff -b 1.out sza3ocen.out > /dev/null
then
    echo "$i OK!"
else
    echo "$i ZLE!"
    break
fi