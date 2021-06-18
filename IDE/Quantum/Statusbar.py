# All these modules need to be imported in Statusbar
from tkinter import *

# This class will be used to make the menu for Quantum
class Statusbar:
	def __init__(self, parent):
		Font_data = ("calibri", 9)

		self.status = StringVar()
		self.status.set("Quantum")
		self.bar_data = Label(parent.Text_area,
						textvariable = self.status,
						fg = "#f9f9f9",
						bg = "#111111",
						font = Font_data)

		self.bar_data.pack(side = BOTTOM, fill = BOTH)

	def update_status(self, *args):
		if isinstance(args[0], bool): self.status.set("Your File Has Been Saved!")
		else: self.status.set("Quantum")

	def running_status(self, *args):
		if isinstance(args[0], bool): self.status.set("Your File Has Been Compiled!")
		else: self.status.set("Quantum")
