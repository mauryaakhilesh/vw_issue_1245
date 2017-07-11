
#cd predict && autoreconf -i && ./configure &&  make 
cd predict &&  make 
cd -

valgrind --tool=memcheck --log-file=memory_leak_proc_`date +%s`.txt --leak-check=full --show-reachable=yes  --run-libc-freeres=no  predict/predictTest  predict/model/vwModel
