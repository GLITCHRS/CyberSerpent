class DynamicShellPrompts:

	def __init__(self, class_obj):

		# these comments needs to be edited
		# inner dict comprehension: getting all methods from class (using callable() to check if method or attribute)
		# outer dict comprehension: removing all special methods (that __smth__ ones)

		self.__methods_dict = {func_name:func for func_name in dir(class_obj) if callable((func := getattr(class_obj, func_name))) and "__" not in func_name}
		self.__methods_help = {func_name:func.__doc__ for func_name, func in self.__methods_dict.items()}

	def __getitem__(self, attrib):
		
		if attrib in self.__methods_dict:
			return self.__methods_dict[attrib]

		return None

	def help(self, command=None):

		print("="*50)

		if command is None:
			for command, help_message in self.__methods_help.items():
				print(f". {command}: {help_message}")

		elif command in self.__methods_help:
				print(f". {command}: {self.__methods_help[command]}")
		
		else:
			print("Command doesn't exist")

		print("="*50)
