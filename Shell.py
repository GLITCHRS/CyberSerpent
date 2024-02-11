from sys import exit as sys_exit
from collections import defaultdict
from json import load

from ShellModule import ShellModule

class Shell(ShellModule):

	with open("modules.json") as file:
		_modules = defaultdict(lambda: None, load(file))

	@staticmethod
	def help():
		print("="*50)
		print(". help: display this message")
		print(". clear/cls: clears the console")
		print(". list: displays a list of availble modules to use")
		print(". load N: loads the desired module, n is either the module name/num")
		print(". exit: exits the tool")
		print("="*50)

	@staticmethod
	def list():
		print("="*50)
		for index,module in enumerate(Shell._modules, 1):
			print(f"{index}. {module}")
		print("="*50)

	@staticmethod
	def load_shell(shell):
		
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
		sys_exit(0)

prefix = "CyberSerpent>"
shell_prompts = defaultdict(lambda: lambda *args: None, 
	{"cls":Shell.clear, "clear":Shell.clear,
	"help": Shell.help, "exit": Shell.exit,
	"list": Shell.list, "load": Shell.load_shell}
	)