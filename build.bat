g++ -c -DBUILD_MY_DLL atm.cpp
g++ -shared -o atm.dll atm.o -Wl,--out-implib,libatm.a
