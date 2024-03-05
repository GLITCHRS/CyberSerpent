from importlib import import_module
from inspect import signature, Parameter


class CSEngine:

	current_shell_module = import_module("modules.Shell")
	current_shell_class = current_shell_module.Shell()
	current_prompts = current_shell_class.shell_prompts
	print(current_prompts)

	def __init__(self):
		...

	def run(self):
		CSEngine.current_prompts["clear"](CSEngine.current_shell_class)

		while True:

			input_text = input(CSEngine.current_shell_class.prefix)
			command, *params = input_text.split() if input_text != "" else "not a command"

			func = CSEngine.current_prompts[command]

			if func is None:
				print("Command doesn't exist")
				continue

			# if all parameters are provided
			if func.__code__.co_argcount == len(params) + 1:
				result = func(CSEngine.current_shell_class, *params)

			# check, maybe some are left to defaults...
			else:
				_signature = signature(func)
				default_params = [v.default for v in _signature.parameters.values() if v.default != Parameter.empty]

				# substituting the default parameters count from the total arguments count to get the total required arguments count
				required_arg_count = func.__code__.co_argcount - len(default_params)

				# if all required are proivded then run, otherwise not
				if required_arg_count == len(params) + 1:
					result = func(CSEngine.current_shell_class, *params)

				else:
					print("Wrong number of parameters")
					continue

			if result is not None:

				module = import_module(result)
				if module is None:
					continue

				CSEngine.current_shell_module = module
				CSEngine.current_shell_class = CSEngine.current_shell_module.Shell()
				CSEngine.current_prompts = CSEngine.current_shell_class.shell_prompts
