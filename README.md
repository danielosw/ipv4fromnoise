Hello, here is the repository for the ipv4 from noise project.  
the AI usage disclaimer is in [GIA.md](GIA.md) and I generally tried to also comment in main.cpp.  
Testing is done using python. On linux if you have python3 installed as just "python" you can run "make test", and it should build the project and test it.  
tests are stored in [tests.txt](test/tests.txt) in the text folder, in the format  
```
program input
correct output
```
example:  
```
192.168.1.1
Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)
END
Program terminated.
```
This testing infistructure is mostly based off how some previus classes did grading.  
But much more fleshed out, I kinda of got a little caried away and completly changed it to not actually ever output files, only use python subproccesses.   
