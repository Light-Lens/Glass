# Linker
import argparse
import sys
import os

# Initialize Command-line arguments.
Description = "Compile Glass from source."
Parser = argparse.ArgumentParser(description=Description)

Parser.add_argument("-o", action="store_true", help="Open in Glass Build Directory.")
Parser.add_argument("-f", action="store_true", help="Force Compile Glass.")
Parser.add_argument("-e", help="Execute the Program without Compiling.")
Parser.add_argument("-r", help="Execute the Program.")

Args = Parser.parse_args()

# Check for modifications in any file.
print("> Checking files")

ModifiedFiles = []
LastModified = []
DoesFileExist = False

# Check if any files were modified or not.
if os.path.isfile("LastModified.log") and not Args.f:
    File = open("LastModified.log", "r", encoding="utf-8").readlines()
    LastModified = [float(i) for i in File]
    DoesFileExist = True

for Path, SubDirs, Files in os.walk(".."):
    for Name in Files:
        SourceFiles = os.path.join(Path, Name)
        if (Path == "..\\src" or Path == "..\\includes") and os.path.isfile(SourceFiles):
            if not DoesFileExist:
                open("LastModified.log", "a", encoding="utf-8").write(f"{str(os.path.getmtime(SourceFiles))}\n")
                File = open("LastModified.log", "r", encoding="utf-8").readlines()
                LastModified = [float(i) for i in File]
                ModifiedFiles.append(Name)

            elif os.path.getmtime(SourceFiles) not in LastModified: ModifiedFiles.append(Name)

if not ModifiedFiles or Args.e:
    if Args.e: Args.r = Args.e
    print(f"No modifications found.\n")
    print("> Build info")

else:
    open("LastModified.log", "w", encoding="utf-8").write("")
    for Path, SubDirs, Files in os.walk(".."):
        for Name in Files:
            SourceFiles = os.path.join(Path, Name)
            if (Path == "..\\src" or Path == "..\\includes") and os.path.isfile(SourceFiles):
                open("LastModified.log", "a", encoding="utf-8").write(f"{str(os.path.getmtime(SourceFiles))}\n")

    # Compile Glass.
    print(f"Modifications found in {', '.join(ModifiedFiles)}\n")
    print("> Force Compile Glass") if Args.f else print("> Compiling Glass")

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

    # Generate the new build number for Glass.
    if not os.path.isfile("Build.log"): open("Build.log", "w", encoding="utf-8").write("0")

    # Increment the build number by 1
    BuildNum = int(open("Build.log", "r", encoding="utf-8").read()) + 1
    open("Build.log", "w", encoding="utf-8").write(str(BuildNum))

# Move to Bin folder.
os.chdir("..\\bin")

# Exit the progarm successfully.
BuildNum = open("..\\scripts\\Build.log", "r", encoding="utf-8").read()
print(f"Glass executable exists at '{os.path.join(os.getcwd(), 'Glass.exe')}'")
if Args.o:
    print("Opening build directory")
    os.startfile(".")

print(f"Glass build {BuildNum}")
print("Done.\n")

# Check for command-line arguments.
if Args.r:
    print(f"> Executing '{Args.r}'")
    os.system(f"Glass {Args.r}")

sys.exit()
