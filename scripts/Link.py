# Linker
from colorama import init, Fore, Style
import argparse, datetime, hashlib, sys, os

# Initialize Command-line arguments.
Parser = argparse.ArgumentParser(description="Compile Glass from source")

Parser.add_argument("-o", action="store_true", help="Open Build Directory")
Parser.add_argument("-c", action="store_true", help="Compile Glass")
Parser.add_argument("-e", help="Run a File")

Args = Parser.parse_args()

# Initialize Compiler.
init(autoreset = True)

def CheckFiles():
    with open("Test.txt", "rb") as f: print(hashlib.md5(f.read()).hexdigest())

def Compile():
    # Change the Current Working Directory to Source folder of Glass
    print(f"{Fore.YELLOW}{Style.BRIGHT}> Compiling Glass")
    os.chdir("..\\src")

    # Create the Bin folder
    # Compile and save the executable in the Bin folder.
    if not os.path.exists("..\\bin"): os.makedirs("..\\bin")
    os.system(f"g++ *.cpp -o \"..\\bin\\Glass\"")

    # Open Glass in explorer.
    if os.path.isfile("..\\bin\\Glass.exe"): print(f"Glass executable exists at {Fore.CYAN}{Style.BRIGHT}'bin\\Glass.exe'")
    else: print(f"{Fore.RED}{Style.BRIGHT}Cannot compile Glass.")

def OpenInFolder():
    print("Opening build directory")
    os.startfile(".")

def Execute():
    # Run the program,
    # Check for command-line arguments.
    print(f"\n{Fore.YELLOW}{Style.BRIGHT}> Executing '{Args.e}'")
    if os.path.isfile("..\\bin\\Glass.exe"):
        os.chdir("..\\bin") # Move to Bin folder.
        os.system(f"Glass {Args.e}")

    else: print(f"{Fore.RED}{Style.BRIGHT}Cannot find Glass.exe")

# Compile glass
if Args.c: Compile()
if Args.o: OpenInFolder()
if Args.e: Execute()
