import ctypes, os
from modules.CSEngine import CSEngine


def main():

	try:
		is_root = os.getuid() == 0

	except:
		is_root = ctypes.windll.shell32.IsUserAnAdmin() != 0


	if not is_root:
		print("[CS] Tool requires root privilages")
		return

	engine = CSEngine()
	engine.run()


if __name__ == '__main__':
	main()
