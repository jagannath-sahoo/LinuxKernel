# Notes SimpleKernelHelloWorld
## Difference between := and +=
##
### := 
(Simply Expanded Variable ) The value is scanned for once and for all expanding any
references to other variables and functions, when variable is defined.
e.g.  x:=foo
y:=$(x) bar
x:=later
so above is equivalent to 
y:=foo bar
x:=later

### +=
Used for appending more text to variables e.g.
objects=main.o foo.o bar.o
objects+=new.o
which will set objects to 'main.o foo.o bar.o new.o'

