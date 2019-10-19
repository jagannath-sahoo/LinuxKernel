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

### Makefile: obj-m/obj-y/obj-n
**obj-$(X) += mymodule.o**\
If <X> is set to m , the *obj-m* variable is used, and mymodule.o will be built as a
module.\
If <X> is set to y , the *obj-y* variable is used, and mymodule.o will be built as
part of the kernel. You'd then say foo is a built-in module.\
If <X> is set to n , the *obj-m* variable is used, and mymodule.o will not be built at
all.