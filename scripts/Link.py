# Linker
from colorama import init, Fore, Style
import argparse, datetime, sys, os

# Initialize Command-line arguments.
Parser = argparse.ArgumentParser(description="Compile Glass from source")

Parser.add_argument("-o", action="store_true", help="Open Build Directory")
Parser.add_argument("-c", action="store_true", help="Compile Glass")
Parser.add_argument("-e", help="Run a File")

Args = Parser.parse_args()

# Initialize Compiler.
init(autoreset = True)

# Compile glass
if Args.c:
    # Change the Current Working Directory to Source folder of Glass,
    # List all the files in it, and remove Glass.cpp
    print(f"{Fore.YELLOW}{Style.BRIGHT}> Compiling Glass")
    os.chdir("..\\src")
    Files = os.listdir()
    Files.remove("main.cpp")

    # Exclude folders and files who's extention isn't '.cpp'.
    for Filename in Files:
        if not os.path.isfile(Filename) or os.path.splitext(Filename)[1].lower() != ".cpp":
            Files.remove(Filename)

    FilesToCompile = " ".join(Files[:len(Files)])

    # Create the Bin folder,
    # Compile and save the executable in the Bin folder.
    if not os.path.exists("..\\bin"): os.makedirs("..\\bin")
    os.system(f"g++ main.cpp {FilesToCompile} -o \"..\\bin\\Glass\"")

# Open Glass in explorer.
if os.path.isfile("..\\bin\\Glass.exe"): print(f"Glass executable exists at {Fore.CYAN}{Style.BRIGHT}'..\\bin\\Glass.exe'")
else:
    print(f"{Fore.RED}{Style.BRIGHT}Cannot find Glass.exe")

if Args.o:
    print("Opening build directory")
    os.startfile(".")

# Run the program,
# Check for command-line arguments.
if Args.e:
    print(f"\n{Fore.YELLOW}{Style.BRIGHT}> Executing '{Args.e}'")
    if os.path.isfile("..\\bin\\Glass.exe"):
        os.chdir("..\\bin") # Move to Bin folder.
        os.system(f"Glass {Args.r}")

    else: print(f"{Fore.RED}{Style.BRIGHT}Cannot find Glass.exe")

# Exit the progarm successfully.
sys.exit()
