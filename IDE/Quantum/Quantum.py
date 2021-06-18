# Quantum
# All these modules need to be imported in Quantum
from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
import sys, os

# These are custom classes that will be used to add features to Quantum
from Menubar import Menubar
from Statusbar import Statusbar
from Intellisense import Intellisense

# Creating the main class for Quantum
class Quantum:
	def __init__(self, root):
		Logo = PhotoImage(file = 'Logo.png') # This will load logo for Quantum IDE
		Font_data = ("calibri", 11) # This Font data will be used to add font to this IDE

		# This will add Title and give Quantum a resolution
		root.title("Quantum")
		root.geometry("1000x675")
		root.iconphoto(False, Logo)

		# These are the global variables
		self.root = root
		self.filename = None

		# This is Text widget in which you can type anything
		self.Text_area = Text(root,
							font = Font_data,
							selectbackground = "#474747",
							insertbackground = "#ff1269",
							foreground = "#f9f9f9",
							background = "#222222",
							undo = True,
							wrap = WORD)

		# This is Scrollbar widget to add a scrollbar in Text widget
		self.scroll = Scrollbar(root, command = self.Text_area.yview)

		# This will configure and pack Text_area and scroll objects
		self.Text_area.configure(yscrollcommand = self.scroll.set)
		self.Text_area.pack(side = LEFT, fill = BOTH, expand = True)
		self.scroll.pack(side = RIGHT, fill = Y)

		# This is a Custom Menu Class in which New and more items are there.
		self.menu = Menubar(self)
		self.status = Statusbar(self)
		self.intellisense = Intellisense(self)
		self.binding_keys()

	def Run_Project(self, *args):
		self.status.running_status(True)
		self.Code = self.Text_area.get(1.0, END)
		if self.filename.endswith(".py"): os.system(f"start python \"{self.filename}\"")
		if self.filename.endswith(".cpp"): os.system(f"start g++ \"{self.filename}\"")
		if self.filename.endswith(".c"): os.system(f"start gcc \"{self.filename}\"")
		if self.filename.endswith(".java"): os.system(f"start javac \"{self.filename}\"")
		if self.filename.endswith(".glass"): os.system(f"start glass \"{self.filename}\"")
		if self.filename.endswith(".html"): os.system(f"start \"{self.filename}\"")
		if self.filename.endswith(".cs"): os.system(f"start dotnet run \"{self.filename}\"")

	# This will update title of the window
	def update_title(self, name = None):
		if name: self.root.title(f"{name} - Quantum")
		else: self.root.title("Untitled - Quantum")
		self.intellisense.Colorcode()

	# This will create a new file in our IDE
	def new_file(self, *args):
		self.Text_area.delete(1.0, END)
		self.filename = None
		self.update_title()

	# This will open a file in our IDE
	def open_file(self, *args):
		self.filename = filedialog.askopenfilename(
			defaultextension = "*.*",
			filetypes = [("All Files", "*.*"),
						("Markdown", ".md"),
						("Text Files", ".txt"),
						("Glass", ".glass"),
						("C", ".c"),
						("C#", ".cs"),
						("C++", ".cpp"),
						("Java", ".java"),
						("Python", ".py"),
						("Css", ".css"),
						("HTML", ".html"),
						("JavaScript", ".js")])

		self.Text_area.delete(1.0, END)
		with open(self.filename, "r") as Data: self.Text_area.insert(1.0, Data.read())
		self.update_title(self.filename)

	# This will save a file in our IDE
	def save_file(self, *args):
		if self.filename:
			try:
				textarea_content = self.Text_area.get(1.0, END)
				with open(self.filename, "w") as Data: Data.write(textarea_content)
				self.status.update_status(True)

			except Exception: pass

		else: self.save_file_as()

	# This will save a file with giving more control to the user in our IDE
	def save_file_as(self, *args):
		try:
			new_file = filedialog.asksaveasfilename(
				initialfile = "Untitled.txt",
				defaultextension = ".txt",
				filetypes = [("All Files", "*.*"),
							("Markdown", ".md"),
							("Text Files", ".txt"),
							("Glass", ".glass"),
							("C", ".c"),
							("C#", ".cs"),
							("C++", ".cpp"),
							("Java", ".java"),
							("Python", ".py"),
							("Css", ".css"),
							("HTML", ".html"),
							("JavaScript", ".js")])

			textarea_content = self.Text_area.get(1.0, END)
			with open(new_file, "w") as Data: Data.write(textarea_content)
			self.status.update_status(True)
			self.filename = new_file
			self.update_title(self.filename)

		except Exception: pass

	def do_ctrl_backspace(self, *args): self.Text_area.delete("insert -7 chars", "insert")
	def binding_keys(self):
		self.Text_area.bind('<Control-n>', self.new_file)
		self.Text_area.bind('<Control-o>', self.open_file)
		self.Text_area.bind('<Control-s>', self.save_file)
		self.Text_area.bind('<Control-S>', self.save_file_as)
		self.Text_area.bind('<Control-f>', self.menu.find)
		self.Text_area.bind('<Control-BackSpace>', self.do_ctrl_backspace)
		self.Text_area.bind('<Key>', self.status.update_status)
		self.Text_area.bind('<Alt-i>', self.intellisense.Colorcode)

# Creating Tkinter root
if __name__ == '__main__':
	root = Tk()
	root.configure(background = "white")
	Editor = Quantum(root)
	root.mainloop()
