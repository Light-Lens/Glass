# Glass
Glass is primarily an early-stage Programming Language written in C++ almost from scratch. It is inspired by Python and C#, so programmer coming from these languages may find some similarities. It is going to be a Powerful yet Easy to Learn Programming Language. Currently not much is implemented, however the progress for Glass is on a pretty good track.

### ***Note: The In-Dev branch contains the new version of Glass.***

## Getting Started
Visual Studio Code is recommended, Glass is officially untested on other development environments whilst we focus on a Windows build.

Start by cloning the repository with `git clone https://github.com/Light-Lens/Glass`.

## The Plan
The plan for Glass is two-fold: to create a Powerful, General Purpose, OOP (Object Oriented Programming) Language. It will be capable to handle massive GUI and Game rendering, yet it will be Easy enough so any application could be written as quick as possible. We may use OpenGL for Game rendering, but that's just what we expect to happen in future. It's totally possible for us to use DirectX, Vulkan or something else.

## Major Features to Come
- Classes
- Functions
- Graphics rendering
- Loops (For loops, While loops)
- GUI application development support
- Conditional statements (If else statements, Switch statements)
- Custom Library building support (By this feature you can make a Glass Library using ".glass" files only, this means you don't need to access the source code everytime you want to create a new Library for Glass)

---

## About [CGlass][CGlassReadme].
## Check out [Glass's Devlog][GlassOnTrello].

---

## Instructions
### Requirments
You need to install the following on your machine.
- Mingw-w64
- Python 3
- Visual Studio Code (or any other IDE)

### How To Use
- Create a Glass program by creating a new file with the extention `.glass`
- If you don't have a Glass program yet try running some from `res\sample projects`
- As soon as Glass compiles start Command Prompt in `bin` folder and type `Glass [path of your file]`
- To compile Glass from source, start Command Prompt and run `scripts\Build.bat`

## Short Term Goals
By the end of 2022, we want to make Glass capable of handling massive console applications, not like a test program, but this time with proper Loops, Functions, Variables, Conditional statements and a bit more.

## License and Contributions
All code is licensed under a MIT license. This allows you to re-use the code freely, remixed in both commercial and non-commercial projects. The only requirement is to include the same license when distributing.

We welcome any contributions to Glass's development through pull requests on GitHub. Most of our active development is in the In-Dev branch, so we prefer to take pull requests there (particularly for new features).

[CGlassReadme]: https://github.com/Light-Lens/Glass/blob/master/IDE/CGlass/CGlass.md#cglass
[GlassOnTrello]: https://trello.com/b/xZ02JY5g/glass
