COMP 3004 - 2019 Fall
Team Do-while

Runhe Zhong     101016659
Jie Ji          101022463
Xinting Wang    101055027
Tiancheng Zhao  100988646

RUN PROCESS:
1. locate at the folder in terminal
2. bash run


ALTERNATIVE PROCESS:
1. open terminal
2. locate at the interface folder
3. type /home/student/Qt/5.13.0/gcc_64/bin/qmake
4. type make
5. type ./SCAPES

Description:
This SCAPES software allowed the user to create, load, save, compile, and run a program that was written by SCAPES language. The strategy pattern is used for handling different kinds of statements. This pattern allows choosing a specific algorithm during the runtime. It is included context class, strategy class, and different concrete strategy classes. The context class will refer to the strategy API for performing a certain algorithm. The strategy class will have some virtual functions that different concrete strategy classes that are inherited from it could assign their functions. In our program, the program class is context class, the statement class is the strategy class, and different statement classes are different concrete strategy classes. When the user tried to compile or run a SCAPES program, the statement could be determined during the software run time. Apart from it, each statement's behavior could be modified easily. It means that only one class needs to be edit. It is not necessary to understand other's statement in this situation.

Test-Program:
largeNumberPrint - allow user to input two numbers, and the program will print the large number.

secretNumberGues - allow one user to input a secret number, and then second user to input a number to guess the secret number, the loop will keep going on until the second user's number is larger than the first user's.


Be Aware!
Your program must have an ‘end’ to indicate the end of the program. Otherwise, it won’t compile.




Resource Credits:
1. icons:{compile_icon.png, new_icon.png, open_icon.png, run_icon.png, save_icon.png}, all icons credited to LogoMakr.com, "Created my free logo at LogoMakr.com"
