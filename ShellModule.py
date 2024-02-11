from os import system, name


class ShellModule:

	@staticmethod
	def clear():
		system("cls" if name == "nt" else "clear")