# ScreenFiddler
A small, useless, and pretty fun program which was made for learning the basics of C++

![A full screen image of the program in effect](https://i.imgur.com/cHuBszy.png)
A full screen image of the program in effect

### What is it?
I have for a long time worked in all sorts of high-level programming languages, primarily Java and C#.
I wanted to learn something new and expirement with C++, a lower-level language which I am not expierenced or familiar in.

I can't take all the credit for this program. I took a lot of inspiration from [the MemZ virus](https://github.com/Leurak/MEMZ), and the header file of this program is virtually entirely copied from the one used in the MemZ virus.

### Usage
Open a command prompt and launch the exe with `-h` or `-help` to get some arguements on what you can launch the program with. You may use multiple effect arguements, however you must remember to remove the help menu arguement for the program to work.

### How does it work?
By simply getting the desktop window, and then it's handle, we are able to manipulate the desktop window of the computer, which essentially gets drawn on top of every other window.

This allows us to have some fun by drawing pretty much whatever we want over any part of the screen without being limited to first creating a gui window and drawing on that.

### Is it destructive?
It could certainly be modified to be destructive, but in it's current form **no**, it's designed to be more of a short-term fun prank. At any moment during the programs execution, the program can be closed and stopped by literally pressing any alphabetical key on the keyboard, and thus having no long-term effects on the victim computer.

All the left-over graphical glitches can be removed by simply refreshing the screen, by for example moving a window over the screen.
