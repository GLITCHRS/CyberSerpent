from ctypes import windll
from os import name

from modules.CSEngine import CSEngine


def main():

	if name == "nt":
		if windll.shell32.IsUserAnAdmin() == 0:
			print("[CS] Tool requires admin privilages")
			return

		engine = CSEngine()
		engine.run()


if __name__ == '__main__':
	main()
