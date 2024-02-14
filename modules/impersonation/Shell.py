from os import system, name
from collections import defaultdict
from json import load

from ..DynamicShellPrompts import DynamicShellPrompts


class Shell:

	with open("modules/impersonation/modules.json") as file:
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
		"""lists the available modes to use"""
		print("="*50)
		for index,module in enumerate(Shell._modules, 1):
			print(f"{index}. {module}")
		print("="*50)

	@staticmethod
	def enable(mode):
		"""enables the desired mode
	syntax: enable <mode name/num>"""
		try:
			shell_index = int(mode) - 1
			values = tuple(Shell._modules.values())

			if shell_index > len(values):
				return

			return values[shell_index]

		except:
			return Shell._modules[mode]

	@staticmethod
	def exit():
		"""goes back to the main shell"""
		return "Shell"

prefix = "CyberSerpent(Impersonation)>"
shell_prompts = shell_prompts = DynamicShellPrompts(Shell)
