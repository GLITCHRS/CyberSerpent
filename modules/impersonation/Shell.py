from collections import defaultdict
from json import load

from ..BasicShell import BasicShell
from ..DynamicShellPrompts import DynamicShellPrompts


class Shell(BasicShell):

	def __init__(self):
		super().__init__()

		self.shell_prompts = DynamicShellPrompts(Shell)
		self.prefix = "CyberSerpent(Impersonation)>"
		self.prev_shell_rel_path = "modules.Shell"

		with open("modules/impersonation/modules.json") as file:
			self.modules = defaultdict(lambda: None, load(file))

	def enable(self, mode):
		"""enables the desired mode
	syntax: enable <mode name/num>"""
		try:
			shell_index = int(mode) - 1
			values = tuple(self.modules.values())

			if shell_index > len(values):
				return

			return values[shell_index]

		except:
			return self.modules[mode]
