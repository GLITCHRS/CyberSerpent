from importlib import import_module
from os import listdir
from collections import defaultdict
from json import load

from ...BasicShell import BasicShell
from ...DynamicShellPrompts import DynamicShellPrompts


class Shell(BasicShell):

	current_script_name = None
	current_script = None
	current_script_instance = None
	scripts_info = \
	{
		"Category": "Impersonation",
		"Tags": ["Network manipulation", "Deception and impersonation", "Intrusive"]
	}

	def __init__(self):
		super().__init__()
		self.shell_prompts = DynamicShellPrompts(Shell)
		self.prefix = "CyberSerpent(Impersonation/Mac-Spoofer)>"
		self.modules = [x.replace(".py", "") for x in listdir("./modules/impersonation/mac") if x not in ("Shell.py", "__pycache__")]
		self.prev_shell_rel_path = "modules.impersonation.Shell"

	@property
	def available_scripts(self):
		return self.modules

	def use(self, script):
		"""uses the desired script
	syntax: use <script name/num>"""
		try:
			script_index = int(script) - 1

			if script_index > len(self.available_scripts):
				print("Script doesn't exist")
				return

			self.current_script_name = self.available_scripts[script_index]
			self.current_script = import_module(f"modules.impersonation.mac.{self.current_script_name}")

		except:
			try:
				self.current_script_name = self.available_scripts[self.available_scripts.index(script)]
				self.current_script = import_module(f"modules.impersonation.mac.{self.current_script_name}")
			except:
				print("Script doesn't exist")
				return

		self.current_script_instance = self.current_script.Spoofer()

	def script(self):
		"""displays the current selected script to use"""
		print(self.current_script_name)

	def run(self):
		"""runs the current selected script"""

		if self.current_script_instance is None:
			return

		self.current_script_instance.spoof_windows()

	def info(self, script=None):
		"""displays info about the current selected script, if used with a script (info <script name/num>) it displays info about that script"""
		if script is None:
			if self.current_script_instance is None:
				print("Please select a script to display by either using the (use) command or by providing a script like (info <script name/num>)")
			else:
				print(f"{self.current_script_name}: {self.current_script_instance.get_info()}")
		else:
			try:
				script_index = int(script) - 1

				if script_index > len(self.available_scripts):
					print(script_index)
					print(self.available_scripts)
					print("Script doesn't exist")
					return

				temp_script_name = self.available_scripts[script_index]
				temp_script = import_module(f"modules.impersonation.mac.{temp_script_name}")
				temp_script_instance = temp_script.Spoofer()

			except:
				try:
					temp_script_name = self.available_scripts[self.available_scripts.index(script)]
					temp_script = import_module(f"modules.impersonation.mac.{temp_script_name}")
					temp_script_instance = temp_script.Spoofer()
				except:
					print("Script doesn't exist")
					return

			print(f"{temp_script_name}: {temp_script_instance.get_info()}")

	def set(self, attribute, value):
		"""sets the desired attribute value, usage (set <attrib name> <value>)"""
		if self.current_script_instance is None:
			print(f"Please select a script to set the {attribute}'s value")
			return

		try:
			getattr(self.current_script_instance, attribute)

			self.current_script_instance.__setattr__(attribute, value)
			print(f"Attrib {attribute} is set to {value}")

		except:
			print(f"Attrib {attribute} not found!")