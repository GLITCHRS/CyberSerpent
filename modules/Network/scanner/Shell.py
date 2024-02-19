from importlib import import_module
from os import listdir, system, name
from collections import defaultdict
from json import load

from ...DynamicShellPrompts import DynamicShellPrompts


class Shell:

	current_script_name = None
	current_script = None
	available_scripts = [x.replace(".py", "") for x in listdir("./modules/impersonation/mac") if x not in {"Shell.py", "__pycache__"}]
	scripts_info = \
	{
		"Category": "Impersonation",
		"Tags": ["Network manipulation", "Deception and impersonation", "Intrusive"]
	}

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
		"""lists the available scripts to use"""
		print("="*50)
		for index,module in enumerate(Shell.available_scripts, 1):
			print(f"{index}. {module}")
		print("="*50)

	@staticmethod
	def use(script):
		"""uses the desired script
	syntax: use <script name/num>"""
		try:
			script_index = int(script) - 1

			if script_index > len(Shell.available_scripts):
				print("Script doesn't exist")
				return

			Shell.current_script_name = Shell.available_scripts[script_index]
			Shell.current_script = import_module(f"modules.impersonation.mac.{Shell.current_script_name}")

		except:
			try:
				Shell.current_script_name = Shell.available_scripts[Shell.available_scripts.index(script)]
				Shell.current_script = import_module(f"modules.impersonation.mac.{Shell.current_script_name}")
			except:
				print("Script doesn't exist")

	@staticmethod
	def script():
		"""displays the current selected script to use"""
		print(Shell.current_script_name)

	@staticmethod
	def run():
		"""runs the current selected script"""

		if Shell.current_script is None:
			return

		_shell = Shell.current_script.Spoofer()
		_shell.spoof_windows()

	@staticmethod
	def info(script=None):
		"""displays info about the current selected script, if used with a script (info <script name/num>) it displays info about that script"""
		if script is None:
			if Shell.current_script is None:
				print("Please select a script to display by either using the (use) command or by providing a script like (info <script name/num>)")
			else:
				print(f"{Shell.current_script_name}: {Shell.current_script.Spoofer.info}")
		else:
			try:
				script_index = int(script) - 1

				if script_index > len(Shell.available_scripts):
					print(script_index)
					print(Shell.available_scripts)
					print("Script doesn't exist")
					return

				temp_script_name = Shell.available_scripts[script_index]
				temp_script = import_module(f"modules.impersonation.mac.{temp_script_name}")

			except:
				try:
					temp_script_name = Shell.available_scripts[Shell.available_scripts.index(script)]
					temp_script = import_module(f"modules.impersonation.mac.{temp_script_name}")
				except:
					print("Script doesn't exist")
					return

			print(f"{temp_script_name}: {temp_script.Spoofer.info}")

	@staticmethod
	def exit():
		"""goes back to the previous shell"""
		return "modules.impersonation.Shell"

prefix = "CyberSerpent(Impersonation/Mac-Spoofer)>"
shell_prompts = DynamicShellPrompts(Shell)
