Compare() {
   File=$1
   if ! cmp -s ${File} test/${File}; then
      echo diff -d ${File} test/${File} >> Log
      diff -d ${File} test/${File} >>Log
   else
      rm ${File}
   fi
}

./fca -c -f <test/fclSW.in >& fcaf.ex; Compare fcaf.ex;
./fca -v <test/fclSW.in > fcai.ex; Compare fcai.ex
./fca -n -c -f <test/data0.in >& fcafs0.ex; Compare fcafs0.ex;
./fca -v -n <test/data0.in > fcas0.ex; Compare fcas0.ex
./fca -n -c -f <test/data.in >& fcafs.ex; Compare fcafs.ex;
./fca -v -n <test/data.in > fcas.ex; Compare fcas.ex

if test -f Log; then
   echo "Tests failed."
   echo "The results are saved in Log."
else
   echo "Tests passed."
fi
