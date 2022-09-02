for((i = 1; ; ++i)); do
    echo $i
    ./gen $i> input.in
    ./teczow <input.in> 1.out
    ./brut <input.in> 2.out
    diff -w 1.out 2.out || break
done