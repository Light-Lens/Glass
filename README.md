# Glass
![Glass](https://github.com/Light-Lens/Glass/blob/In-Dev/res/branding/Icons/Transparent.png?raw=true)

Glass is an early-stage programming language written in C++ which will be a **Powerful** yet **Easy to Learn** language as it's inspirations are Python and C#, however it's primary goal is to create games and game engines from scratch.

The plan for Glass is to create a Powerful, General Purpose, OOP (Object Oriented Programming) Language which will be capable of handling massive GUI and Game rendering applications using the SDL2 game library.

### ***Note: This branch contains the In-Dev version of Glass, some features may not functions properly.***

---

## Getting Started
Visual Studio Code is recommended, Glass is officially untested on other development environments whilst we focus on a Windows build.

<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone https://github.com/Light-Lens/Glass`.

<ins>**2. Configuring the dependencies:**</ins>
1. Install [Mingw-w64](http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download), [Python 3](https://www.python.org/downloads/windows), and [Visual Studio Code](https://code.visualstudio.com/download) on your machine.
2. Run the [Build.bat](https://github.com/Light-Lens/Glass/blob/In-Dev/scripts/Build.bat) file found in `scripts` folder via Command Prompt with `-c` parameter to compile Glass.

<ins>**3. Setting up project:**</ins>
1. Create a file with `.glass` extension and write some code in it. You will find some sample code in [`res\sample projects`](https://github.com/Light-Lens/Glass/tree/In-Dev/res/sample%20projects) folder.
2. As soon as Glass compiles, start Command Prompt in `bin` folder and type `Glass.exe [path of your file]` to run the program.

## Short Term Goals
By the end of 2022, we want to make Glass capable of handling massive console applications, not like a test/sample program, but this time with proper Loops, Functions, Variables, Conditional statements making the application fun to use.

---

## License and Contributions
All code is licensed under an MIT license. This allows you to re-use the code freely, remixed in both commercial and non-commercial projects. The only requirement is to include the same license when distributing.

We welcome any contributions to Glass Programming Language development through pull requests on GitHub. Most of our active development is in the In-Dev branch, so we prefer to take pull requests there (particularly for new features).
