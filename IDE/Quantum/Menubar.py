# All these modules need to be imported in Menubar
from tkinter import *
from tkinter.simpledialog import *
from tkinter import filedialog
from tkinter import messagebox
from tkinter.colorchooser import askcolor
from tkinter.font import Font, families
from tkinter.scrolledtext import *
import time
import sys

# These are custom classes that will be used to add features to Quantum
from Statusbar import Statusbar

# This class will be used to make the menu for Quantum
class Menubar:
	def __init__(self, parent):
		Font_data = ("calibri", 9) # This Font data will be used to add font to menubar

		# Create a new menu object
		Menu_options = Menu(parent.root, font = Font_data)
		parent.root.config(menu = Menu_options)
		self.parent = parent

		# Make a File menu in Menubar
		File_drop = Menu(Menu_options, font = Font_data, tearoff = 0, background = "white", foreground = "black")
		File_drop.add_command(label = "New File", command = parent.new_file, accelerator = "Ctrl+N")
		File_drop.add_command(label = "Open File", command = parent.open_file, accelerator = "Ctrl+O")
		File_drop.add_command(label = "Save", command = parent.save_file, accelerator = "Ctrl+S")
		File_drop.add_command(label = "Save As", command = parent.save_file_as, accelerator = "Ctrl+Shift+S")
		File_drop.add_separator()
		File_drop.add_command(label = "Exit", command = parent.root.destroy)

		Edit_drop = Menu(Menu_options, font = Font_data, tearoff = 0, background = "white", foreground = "black")
		Edit_drop.add_command(label = "Undo", command = self.undo, accelerator = "Ctrl+Z")
		Edit_drop.add_command(label = "Redo", command = self.redo, accelerator = "Ctrl+Y")
		Edit_drop.add_separator()
		Edit_drop.add_command(label = "Cut", command = self.cut, accelerator = "Ctrl+X")
		Edit_drop.add_command(label = "Copy", command = self.copy, accelerator = "Ctrl+C")
		Edit_drop.add_command(label = "Paste", command = self.paste, accelerator = "Ctrl+V")
		Edit_drop.add_separator()
		Edit_drop.add_command(label = "Find", command = self.find, accelerator = "Ctrl+F")
		Edit_drop.add_separator()
		Edit_drop.add_command(label = "Select All", command = self.selectAll, accelerator = "Ctrl+A")

		Project_drop = Menu(Menu_options, font = Font_data, tearoff = 0, background = "white", foreground = "black")
		Project_drop.add_command(label = "Run Project", command = parent.Run_Project)

		About_drop = Menu(Menu_options, font = Font_data, tearoff = 0, background = "white", foreground = "black")
		About_drop.add_command(label = "Release Note", command = self.show_release_note)
		About_drop.add_separator()
		About_drop.add_command(label = "About", command = self.show_about_option)

		Menu_options.add_cascade(label = "File", menu = File_drop)
		Menu_options.add_cascade(label = "Edit", menu = Edit_drop)
		Menu_options.add_cascade(label = "Project", menu = Project_drop)
		Menu_options.add_cascade(label = "Help", menu = About_drop)

	# Help menu functions
	def show_about_option(self):
		note_title = "About Quantum"
		note_message = "Quantum is an IDE which can be used to code in Glass programming language."
		messagebox.showinfo(note_title, note_message)

	def show_release_note(self):
		note_title = "Release Notes"
		note_message = "\t  Light-Lens\nQuantum 2021 [Version 0.5.1-alpha]"
		messagebox.showinfo(note_title, note_message)

	# Edit menu functions
	def copy(self, *args):
		sel = self.parent.Text_area.selection_get()
		self.clipboard = sel

	def cut(self, *args):
		sel = self.parent.Text_area.selection_get()
		self.clipboard = sel
		self.parent.Text_area.delete(SEL_FIRST, SEL_LAST)

	def paste(self, *args):
		self.parent.Text_area.insert(INSERT, self.clipboard)

	def selectAll(self, *args):
		self.parent.Text_area.tag_add(SEL, "1.0", END)
		self.parent.Text_area.mark_set(0.0, END)
		self.parent.Text_area.see(INSERT)

	def undo(self, *args):
		self.parent.Text_area.edit_undo()

	def redo(self, *args):
		self.parent.Text_area.edit_redo()

	def find(self, *args):
		self.parent.Text_area.tag_remove('found', '1.0', END)
		target = askstring('Find', 'Find what:')
		if target:
			idx = '1.0'
			while 1:
				idx = self.parent.Text_area.search(target, idx, nocase = 1, stopindex=END)
				if not idx: break
				lastidx = '%s+%dc' % (idx, len(target))
				self.parent.Text_area.tag_add('found', idx, lastidx)
				idx = lastidx

			self.parent.Text_area.tag_config('found', foreground = '#f9f9f9', background = '#1054de')
