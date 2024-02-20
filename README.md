# ObjektinisProgramavimas

This is the fifth subversion of my project v0.2

## Features

1. Has a defined structure of a student, which includes the name, surname, homework grades (the amount of grades per student is defined before the execution of the program), and grade of the exam.
2. Takes an input from the user (or from a file) to fill in the data for all the structure members for a certain amount of students (the amount of students is not necessarily defined before the execution of the program).
3. After taking input from a user it accumulates the average homework grade for every student, and also calculates the final grade for every student, and outputs it to the screen or to another file.
4. At the end of the program it outputs the name, surname and final grade of every single student to the console.
5. Has a feature where the user can choose what method to use to count the final grade - by using average of the homework grades or by using the median of homework grades in the final grade calculation.
6. If any of the inputs done by the user are incorrect, he is informed about a mistake and is prompted to input a value again.
7. Has the feature where a user can enter the amount of students and grades per student at runtime.
8. Has two files, one is using dynamic memory to store student structures and their grades and the other uses vector for the same purpose and lets users input as many grades as they want at runtime.
9. Has a feature where at the very start of the program the user can choose, how does he want to run the program, so far, if the user enter a '1', then he will have to type out everything by hand, if he enters '2' the grades will be generated randomly and he will be able to generate as many grades as he wants, if he enters '3' the grades will be generated randomly and all the names and surnames will be picked randomly from the files that have one thousand names and one thousand surnames, if the user enter a '4', the program will terminate, and if he enters '5', the data will be read from a file.
10. Has all the features added to both of the files, to mainMasyvai.cpp, which only uses C arrays to store data, and to mainVector.cpp, which only uses vectors to store data.
11. Has a feature where a user can choose how he wants to sort the students (in ascending order or in descending order depending on their final grade).
12. Has all the code commented out.
