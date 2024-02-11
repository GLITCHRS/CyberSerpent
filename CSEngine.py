from importlib import import_module

class CSEngine:

	current_shell_module = import_module("Shell")
	current_prompts = current_shell_module.shell_prompts

	def __init__(self):
		...

	def run(self):
		CSEngine.current_prompts["clear"]()

		while True:

			input_text = input(CSEngine.current_shell_module.prefix)
			command, *params = input_text.split() if input_text != "" else "not a command"
			result = CSEngine.current_prompts[command](*params)

			if result is not None:

				module = import_module(result)
				if module is None:
					continue

				CSEngine.current_shell_module = module
				CSEngine.current_prompts = module.shell_prompts