class DynamicShellPrompts:

	def __init__(self, class_obj):

		# these comments needs to be edited
		# inner dict comprehension: getting all methods from class (using callable() to check if method or attribute)
		# outer dict comprehension: removing all special methods (that __smth__ ones)
		unfiltered_methods_dict = {t:x for t in dir(class_obj) if callable((x := getattr(class_obj, t)))}
		self.__methods_dict = {k:v for k, v in unfiltered_methods_dict.items() if "__" not in k}
		self.__methods_help = {k:f"{v.__doc__}" for k, v in self.__methods_dict.items()}

	def __getitem__(self, attrib):
		
		if attrib in self.__methods_dict:
			return self.__methods_dict[attrib]

		return None

	def help(self, command=None):

		print("="*50)

		if command is None:
			for command, help_message in self.__methods_help.items():
				print(f". {command}: {help_message}")

		else:
			if command in self.__methods_help:
				print(f". {command}: {self.__methods_help[command]}")
			else:
				print("Command doesn't exist")

		print("="*50)
