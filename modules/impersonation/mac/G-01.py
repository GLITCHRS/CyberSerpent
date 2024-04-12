from os import name, system
from string import hexdigits
from re import findall, compile as regex_compile
from random import choice, sample
from subprocess import check_output


class Spoofer:

	# MAC addresses are always 12 digit hexadecimal numbers (48 bits)
	# They consist of six pairs of two hexadecimal digits {0-9, A-F}
	# Windows uses XX-XX-XX-XX-XX-XX
	# MAC addresses are case-insensitive
	# Leading zeros are optional (02-0A-1B-00-00-FF is the same as 02-0A-1B-0-0-FF)
	# The 2nd character is significant in a MAC address, if it's one of these letters (26AE) it's an LAA, otherwise it's UAA
	# follow the rules, setting a custom MAC without using these letters as the second letter could cause conflicts/issues with the network
	# LAA stands for (Locally Administrated Addresses)
	# UAA stands for (Universally Administrated Addresses)

	MAC = "00:00:00:00:00:00"

	def get_info(self):
		return f"""
{'='*69}
Author: GLITCH
Supported Platforms: Windows
{'-'*69}
{'VARIALBE':12}{'VALUE':23}{'DESCRIPTION':23}{'REQUIRED':12}{'NOTE'}
{'MAC':12}{self.MAC:23}{'The MAC to spoof to':23}{'No':12}{'If not set, will spoof to a random MAC address'}
{'='*69}
"""

	def __setattr__(self, attrib, value):
		if attrib != "MAC":
			raise ValueError

		else:
			# validate MAC first (later)
			Spoofer.MAC = value 


	def enable_interface_windows(self, interface_reg):
		check_output(f"wmic path win32_networkadapter where index={interface_reg} call enable")

	def disable_interface_windows(self, interface_reg):
		check_output(f"wmic path win32_networkadapter where index={interface_reg} call disable")

	def get_random_mac_address_windows(self):
		# uppercase hexdigits (used set() for eliminating duplicates)
		uppercased_hexdigits = "".join(set(hexdigits.upper()))

		# generating a random MAC with following the LAA rule
		return f"{choice(uppercased_hexdigits)}{choice('26AE')}{''.join(sample(uppercased_hexdigits, k=10))}"

	def get_interfaces_windows(self):
		mac_regex = regex_compile(r"([A-Z0-9]{2}[:-]){5}([A-Z0-9]{2})")
		transport_name_regex = regex_compile("{.+}")

		interfaces_mac = []

		for line in check_output("getmac").decode().splitlines():
			mac = mac_regex.search(line)
			transport_name = transport_name_regex.search(line)

			if transport_name is not None and mac is not None:
				interfaces_mac.append((mac.group(), transport_name.group()))

		return interfaces_mac

	def spoof_mac_windows(self, transport_name, mac):
		network_interface_reg_path = r"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}"

		# using reg QUERY to get available adapters from regsitery
		path_to_query = network_interface_reg_path.replace("\\\\", "\\")
		output = check_output(f"reg QUERY \"{path_to_query}\"").decode()

		# looping through all interfaces from registery
		for interface in findall(rf"{network_interface_reg_path}\\\d+", output):

			# finding the interface path from registery
			interface_reg = int(interface.split("\\")[-1])

			# getting the content of the interface from registery
			interface_content = check_output(f"reg QUERY {interface.strip()}").decode()

			# if transport name is found inside the interface we queried from registery, this is the interface we'd like to spoof its MAC
			if transport_name in interface_content:
				mac_spoofing_result = check_output(f"reg ADD \"{interface}\" /v NetworkAddress /d {mac} /f").decode()
				print(f"Spoofing Result: {mac_spoofing_result}")
				return interface_reg

	def unspoof_mac_windows(self, transport_name):
		network_interface_reg_path = r"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}"

		# using reg QUERY to get available adapters from regsitery
		path_to_query = network_interface_reg_path.replace("\\\\", "\\")
		output = check_output(f"reg QUERY \"{path_to_query}\"").decode()

		# looping through all interfaces from registery
		for interface in findall(rf"{network_interface_reg_path}\\\d+", output):

			# finding the interface path from registery
			interface_reg = int(interface.split("\\")[-1])

			# getting the content of the interface from registery
			interface_content = check_output(f"reg QUERY {interface.strip()}").decode()

			# if transport name is found inside the interface we queried from registery, this is the interface we'd like to spoof its MAC
			if transport_name in interface_content:
				mac_unspoofing_result = check_output(f"reg DELETE {interface} /v NetworkAddress /f").decode()
				print(f"[CS]UnSpoofing Result: {mac_unspoofing_result}")
				return interface_reg

	def clear_mac(self, mac):
		# returns a clear MAC (removing all '-' and ':' or other possible characters)
		return "".join(c for c in mac if c in hexdigits).upper()

	def select_interface(self, interfaces):

		# print available options
		for index, interface in enumerate(interfaces):
			print(f"[CS] #{index}: {interface[0]}, {interface[1]}")

		# if only one adapter exists, choose it automatically
		if len(interfaces) == 1:
			return interfaces[0]

		while True:
			try:
				choice = int(input("Please choose the interface you'd like to spoof its MAC by entering it's #N: "))
				return interfaces[choice]

			except:
				print("[CS] Not a valid answer!")

	def spoof_windows(self):

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
