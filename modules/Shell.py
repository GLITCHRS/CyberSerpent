from collections import defaultdict
from json import load

from modules.BasicShell import BasicShell
from modules.DynamicShellPrompts import DynamicShellPrompts


class Shell(BasicShell):

	def __init__(self):
		super().__init__()

		self.shell_prompts = DynamicShellPrompts(Shell)
		self.prefix = "CyberSerpent>"

		with open("modules//modules.json") as file:
			self.modules = defaultdict(lambda: None, load(file))

	def load(self, shell):
		"""loads the desired module
	syntax: load <module name/num>"""
		try:
			shell_index = int(shell) - 1
			values = tuple(self.modules.values())

			if shell_index > len(values):
				return

			return values[shell_index]

		except:
			return Shell._modules[shell]
