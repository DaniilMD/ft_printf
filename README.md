# ft_printf
## Project objective
  Recoding libc printf.  
## Skills to acquire and use
•	Fundamentals of C  
•	Algorithm elaboration  
•	Imperative programming  
•	Unix  
•	Rigor  
•	Discovering variadic functions in C and learning to use them  
## How to run it? (works on Linux and MacOS)
•	git clone https://github.com/DaniilMD/ft_printf.git «Folder name»  
•	cd «Folder name»  
•	make  
•	Create a .c file that uses ft_printf function (using #include "way/to/ft_printf.h/printf.h" ofc)  
•	Compile this file:  
```
gcc file_using_libft_funcs.c -L "way/to/libft.a" -lftprintf
```
•	Run executable
```
./a.out
```
  
Or use the presented main.c or even the sh script called "fast" after cloning and entering the folder.  
  
![Screenshot from 2020-08-12 19-08-40](https://user-images.githubusercontent.com/48802453/90039689-a7d02b00-dccf-11ea-8d61-68d0951c13df.png)  
  
You will see something like this:  
  
![Screenshot from 2020-08-12 19-08-42](https://user-images.githubusercontent.com/48802453/90125220-51fc9100-dd6a-11ea-9f0b-bbae55147019.png)
  
Of course, main.c can be changed to test ft_printf() even more.  
## What does it do?
ft_printf() imitates part of libc printf's behaviour.  
  
It must:  
• manage the following conversions: csp  
• manage the following conversions: diouxX with the following flags: hh, h, l and ll  
• manage the following conversion: f with the following flags: l and L  
• manage %%  
• manage the flags #0-+ and space  
• manage the minimum field-width  
• manage the precision  
## How it works
1) Needless to say, ft_printf() is variadic function and has an indefinite number of arguments.  
  
![Screenshot from 2020-08-13 14-23-02](https://user-images.githubusercontent.com/48802453/90129044-9be87580-dd70-11ea-8688-02af026a68d3.png)
  
2) It uses a buffer where all characters are saved. This buffer is printed later in order to hasten the program run.
3) First of all, if a '%' character is met, ft_printf() uses function called options_handler() to gather all needed info about flags, conversions, precision, e.t.c. to print everything correct.
  
![Screenshot from 2020-08-13 14-05-25](https://user-images.githubusercontent.com/48802453/90128870-490ebe00-dd70-11ea-9874-04e29f5320db.png)  
  
4) Depending on the output type, a suitable type handler is chosen. For example, to print a char, c_handler() is used:  
  
![Screenshot from 2020-08-13 14-19-37](https://user-images.githubusercontent.com/48802453/90128873-49a75480-dd70-11ea-8aa0-18d98af24a2f.png)
  
5) Finally, the whole buffer is printed ("printed" is a number of characters which is calculated during the function run)
```
write(1, printf_buf, printed);
```
and deleted.
```
ft_strdel(&printf_buf);
```
Then, the function run finishes.
## Project evaluation result  
### Score 101/100  
Mandatory part  
100/100  
  
Bonus part  
1/25
