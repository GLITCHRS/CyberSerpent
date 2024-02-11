from collections import defaultdict
from json import load

from ShellModule import ShellModule

class Shell(ShellModule):

	with open("modules/impersonation/modules.json") as file:
		_modules = defaultdict(lambda: None, load(file))

	@staticmethod
	def help():
		print("="*50)
		print(". help: display this message")
		print(". clear/cls: clears the console")
		print(". list: displays a list of availble modes to use")
		print(". enable N: enables the desired mode, n is either the mode name/num")
		print(". exit: exits the module")
		print("="*50)

	@staticmethod
	def list():
		print("="*50)
		for index,module in enumerate(Shell._modules, 1):
			print(f"{index}. {module}")
		print("="*50)

	@staticmethod
	def enable_mode(mode):
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
		return "Shell"

prefix = "CyberSerpent(Impersonation)>"
shell_prompts = defaultdict(lambda: lambda *args: None, 
	{"cls":Shell.clear, "clear":Shell.clear,
	"help": Shell.help, "exit": Shell.exit,
	"list": Shell.list, "enable": Shell.enable_mode}
	)