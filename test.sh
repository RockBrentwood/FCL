Mode=$1

Compare() {
   File=$1
   if ! cmp -s ${File} test/${File}; then
      echo diff -d ${File} test/${File} >> Log
      diff -d ${File} test/${File} >>Log
   else
      rm ${File}
   fi
}

TestCompare() {
   App=$1; Test=$2; File=${App}${Test}.ex
   ./${App}${Mode} < test/fcl${Test}.in > ${File}
   Compare ${File}
}

for App in fcbo iteress pcbo; do for Test in 0 1 2 3 4 SW; do
   TestCompare ${App} ${Test}
done done

if test -f Log; then
   echo "Tests failed."
   echo "The results are saved in Log."
else
   echo "Tests passed."
fi
