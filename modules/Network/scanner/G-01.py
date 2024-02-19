from os import name, system
from string import hexdigits
from re import findall, compile as regex_compile
from random import choice, sample
from subprocess import check_output


class Scanner:

	info = f"""

	"""

	MAC = None

	def scan(self):

		while True:
			choice = input("Would you like to spoof or unspoof ? (e to exit): ").upper()

			if choice == 'E':
				return

			elif choice in ("SPOOF", "UNSPOOF"):
				break

			print("[CS] Not a valid answer!")

		interfaces = self.get_interfaces_windows()
		old_mac, target_transport_name = self.select_interface(interfaces)
		print(f"[CS] Old MAC: {old_mac}")

		if choice == "SPOOF":
			if Spoofer.MAC is None:
				new_mac = self.get_random_mac_address_windows()

			else:
				new_mac = Spoofer.MAC
				# add MAC validation

			interface_reg = self.spoof_mac_windows(target_transport_name, new_mac)
			print(f"[CS] New MAC: {new_mac}")

		else:
			interface_reg = self.unspoof_mac_windows(target_transport_name)
			print("MAC restored")

		self.disable_interface_windows(interface_reg)
		print("[CS] Interface is disabled")
		self.enable_interface_windows(interface_reg)
		print("[CS] Interface is enabled")
