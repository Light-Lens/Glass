# All these modules need to be imported in Menubar
from tkinter import *

# This class will be used to make the menu for Quantum
class Statusbar:
	def __init__(self, parent):
		Font_data = ("calibri", 9)

		self.status = StringVar()
		self.status.set("Quantum")
		bar_data = Label(parent.Text_area,
						textvariable = self.status,
						fg = "#f9f9f9",
						bg = "#1c1c1c",
						font = Font_data)

		bar_data.pack(side = BOTTOM, fill = BOTH)

	def update_status(self, *args):
		if isinstance(args[0], bool): self.status.set("Your File Has Been Saved!")
		else: self.status.set("Quantum")