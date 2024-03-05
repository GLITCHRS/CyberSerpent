from os import system, name
from sys import exit as sys_exit


class BasicShell:

	def __init__(self):
		self.prefix = None
		self.shell_prompts = None
		self.modules = None
		self.prev_shell_rel_path = None

	def clear(self):
		"""clears the console"""
		system("cls" if name == "nt" else "clear")

	def cls(self):
		"""clears the console"""
		system("cls" if name == "nt" else "clear")

	def help(self, command=None):
		"""displays this help message, if used with a command (help <command>) it only displays the help message for that command"""
		self.shell_prompts.help(command)

	def list(self):
		"""lists the available scripts to use"""
		print("="*50)
		for index,module in enumerate(self.modules, 1):
			print(f"{index}. {module}")
		print("="*50)

	def back(self):
		"""goes back to the previous shell"""
		return self.prev_shell_rel_path

	def exit(self):
		"""exits to tool"""
		sys_exit(0)
