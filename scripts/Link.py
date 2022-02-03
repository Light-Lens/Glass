# Linker
from colorama import init, Fore, Style
import argparse, datetime, sys, os

# Initialize Command-line arguments.
Parser = argparse.ArgumentParser(description="Compile Glass from source")

Parser.add_argument("-o", action="store_true", help="Open in Glass Build Directory")
Parser.add_argument("-f", action="store_true", help="Force Compile Glass")
Parser.add_argument("-e", help="Execute the Program without Compiling")
Parser.add_argument("-r", help="Execute the Program")

Args = Parser.parse_args()

# Initialize Compiler.
init(autoreset = True)

ModifiedFiles = []
LastBuildTime = 0
if os.path.isfile("Build.log"): LastBuildTime = os.path.getmtime("..\\scripts\\Build.log")

# Check for modified files.
print(f"{Fore.YELLOW}{Style.BRIGHT}> Checking files")
for Path, SubDirs, Files in os.walk(".."):
    for Name in Files:
        SourceFiles = os.path.join(Path, Name)
        if ((Path == "..\\src" or Path == "..\\includes") and os.path.isfile(SourceFiles)) and (os.path.getmtime(SourceFiles) > LastBuildTime or Args.f):
            ModifiedFiles.append(Name)

# Compile Glass.
if not ModifiedFiles or Args.e:
    if Args.e: Args.r = Args.e
    print(f"{Fore.RED}{Style.BRIGHT}No modifications found\n")
    print(f"{Fore.YELLOW}{Style.BRIGHT}> Build info")

else:
    JoinFiles = ", ".join(ModifiedFiles)
    print(f"{Fore.GREEN}{Style.BRIGHT}Modifications found in: {Style.RESET_ALL}{JoinFiles}\n")
    print(f"{Fore.YELLOW}{Style.BRIGHT}> Force Compile Glass") if Args.f else print(f"{Fore.YELLOW}{Style.BRIGHT}> Compiling Glass")

    # Change the Current Working Directory to Source folder of Glass,
    # List all the files in it, and remove Glass.cpp
    os.chdir("..\\src")
    Files = os.listdir()
    Files.remove("Glass.cpp")

    # Exclude folders and files who's extention isn't '.cpp'.
    for Filename in Files:
        if not os.path.isfile(Filename) or os.path.splitext(Filename)[1].lower() != ".cpp":
            Files.remove(Filename)

    FilesToCompile = " ".join(Files[:len(Files)])

    # Create the Bin folder,
    # Compile and save the executable in the Bin folder.
    if not os.path.exists("..\\bin"): os.makedirs("..\\bin")
    os.system(f"g++ Glass.cpp {FilesToCompile} -o \"..\\bin\\Glass\"")
    os.chdir("..\\scripts")

    # Increment the build number by 1
    if os.path.isfile("Build.log"):
        BuildNum = int(open("Build.log", "r", encoding="utf-8").read())
        open("Build.log", "w", encoding="utf-8").write(str(BuildNum + 1))

    else: open("Build.log", "w", encoding="utf-8").write("1")

# Exit the progarm successfully.
BuildNum = open("..\\scripts\\Build.log", "r", encoding="utf-8").read()
CTime = datetime.time(datetime.datetime.now().hour, datetime.datetime.now().minute, datetime.datetime.now().second)
if os.path.isfile("..\\bin\\Glass.exe"): print(f"Glass executable exists at {Fore.CYAN}{Style.BRIGHT}'..\\bin\\Glass.exe'")
else: print(f"{Fore.RED}{Style.BRIGHT}Cannot find Glass.exe")
if Args.o:
    print("Opening build directory")
    os.startfile(".")

print(f"Glass build time {Fore.BLUE}{Style.BRIGHT}{CTime}")
print(f"Glass build {Fore.BLUE}{Style.BRIGHT}{BuildNum}")
print("Done.")

# Check for command-line arguments.
if Args.r:
    # Run the program.
    print(f"\n{Fore.YELLOW}{Style.BRIGHT}> Executing '{Args.r}'")
    if os.path.isfile("..\\bin\\Glass.exe"):
        # Move to Bin folder.
        os.chdir("..\\bin")
        os.system(f"Glass {Args.r}")

    else: print(f"{Fore.RED}{Style.BRIGHT}Cannot find Glass.exe")
sys.exit()
