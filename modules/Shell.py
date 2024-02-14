from os import system, name
from sys import exit as sys_exit
from collections import defaultdict
from json import load

from modules.DynamicShellPrompts import DynamicShellPrompts


class Shell:

	with open("modules//modules.json") as file:
		_modules = defaultdict(lambda: None, load(file))

	@staticmethod
	def clear():
		"""clears the console"""
		system("cls" if name == "nt" else "clear")

	@staticmethod
	def cls():
		"""clears the console"""
		system("cls" if name == "nt" else "clear")

	@staticmethod
	def help(command=None):
		"""displays this help message, if used with a command (help <command>) it only displays the help message for that command"""
		shell_prompts.help(command)

	@staticmethod
	def list():
		"""lists the available modules to use"""
		print("="*50)
		for index,module in enumerate(Shell._modules, 1):
			print(f"{index}. {module}")
		print("="*50)

	@staticmethod
	def load(shell):
		"""loads the desired module
	syntax: load <module name/num>"""
		try:
			shell_index = int(shell) - 1
			values = tuple(Shell._modules.values())

			if shell_index > len(values):
				return

			return values[shell_index]

		except:
			return Shell._modules[shell]

	@staticmethod
	def exit():
		"""exits the app"""
		sys_exit(0)

prefix = "CyberSerpent>"
shell_prompts = DynamicShellPrompts(Shell)
