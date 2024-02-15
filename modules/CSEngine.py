from importlib import import_module
from inspect import signature, Parameter


class CSEngine:

	current_shell_module = import_module("modules.Shell")
	current_prompts = current_shell_module.shell_prompts

	def __init__(self):
		...

	def run(self):
		CSEngine.current_prompts["clear"]()

		while True:

			input_text = input(CSEngine.current_shell_module.prefix)
			command, *params = input_text.split() if input_text != "" else "not a command"

			func = CSEngine.current_prompts[command]

			if func is None:
				print("Command doesn't exist")
				continue

			_signature = signature(func)
			default_params = [v.default for v in _signature.parameters.values() if v.default != Parameter.empty]

			# if all parameters are provided
			if func.__code__.co_argcount == len(params):
				result = func(*params)

			# check, maybe some are left to defaults...
			else:
				# substituting the default parameters count from the total arguments count to get the total required arguments count
				required_arg_count = func.__code__.co_argcount - len(default_params)

				# if all required are proivded then run, otherwise not
				if required_arg_count == len(params):
					result = func(*params)

				else:
					print("Wrong number of parameters")
					continue

			if result is not None:

				module = import_module(result)
				if module is None:
					continue

				CSEngine.current_shell_module = module
				CSEngine.current_prompts = module.shell_prompts
