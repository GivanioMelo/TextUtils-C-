Text Utils for C++

You know it's realy boring to use std::cin and std::cout
even if you don't admit it, here is a simple Console class
to make your days of c++ programming happier.

You can use it as simple as that...
```cpp
#include "Console.hpp"
int main() 
{
	Console console = Console();
	console.printTitleBox("Eita", Console::Color::White, Console::Color::Red, Console::BoxStyle::Single);
```
![image](https://github.com/user-attachments/assets/1f3bad29-9874-4df0-abf5-d23abd2968c2)

You can use C++ autocast of boolean types in your favor

```cpp
	console.print("Bool: ").printBool(true).print("\n");
	console.print("Bool from string: ").printBool("A").print("\n");
	console.print("Bool from int: ").printBool(10).print("\n");
	console.print("Bool float: ").printBool(45.5f).print("\n");

```
![image](https://github.com/user-attachments/assets/5a837f23-3aa8-47fa-a377-010e2712168f)


You can print numeric values using decimal precision easy bizzy

```cpp
	console.setColor(Console::Color::Yellow);
	console.setStyle(Console::Style::Bold);
	console.print("Int: ").print(123).print("\n");
	console.print("Float: ").print(3.14159f).print("\n");
	console.print("Double: ").print(2.718281828459, 5).print("\n");
```
![image](https://github.com/user-attachments/assets/48e7c78a-5426-4762-ad33-254eb541e8e6)


You can draw boxes with simple x,y,w,h parameters...
and in different styles...

```cpp
	console.setColor(Console::Color::Magenta);
	console.drawBox(2, 15, 20, 10, Console::BoxStyle::Single);
	console.setColor(Console::Color::Blue);
	console.drawBox(22, 15, 20, 10, Console::BoxStyle::Double);
	console.setColor(Console::Color::Yellow);
	console.drawBox(42, 15, 20, 10, Console::BoxStyle::Broad);
	console.setColor(Console::Color::Cyan);
	console.drawBox(62, 15, 20, 10, Console::BoxStyle::Dashed);
	console.setColor(Console::Color::White);
	console.drawBox(82, 15, 20, 10, Console::BoxStyle::Rounded);

```
![image](https://github.com/user-attachments/assets/7f9608b4-d4e2-44d4-a3a6-f131e531a362)

and you can use the input function as close holder (i love doing this MacGyver)

```cpp
	console.input();
	console.reset();
}
```

The class methods return the Console instance, so you can chain the methods for multiple configuration and printing...
```cpp
	console.moveCursor(7,30)
		.setColor(Console::Color::Magenta)
		.setStyle(Console::Style::Underline)
		.print("chained configurations...");
```
![image](https://github.com/user-attachments/assets/3ea527ee-7bea-4ca8-b9b0-077637bf7410)

I added some default threat level outputs ready for action...
```cpp
	console.info("This is a totaly fine message, nothing to warry about...");
	console.warning("Better look at this, bro...");
	console.error("Oh shit, this ain't look good...");
```
![image](https://github.com/user-attachments/assets/e510e5b1-4656-4265-a7fd-f6f173eab10a)

