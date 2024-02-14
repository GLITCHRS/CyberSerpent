from os import name, system
from string import hexdigits
from re import findall, compile as regex_compile
from random import choice, sample
from subprocess import check_output

from ..ImpersonationModel import Impersonation


class Spoofer(Impersonation):

	r"""
=======================================
Author: GLITCH
	The following command to spoof mac:

			reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002BE10318}\{adapter_key} /v NetworkAddress /t REG_SZ /d 002622D90EFC /f

	To identify the choosen network adapter by user, consider comparing the (Description) from the adapter he chose, with the (DriverDesc) key in registery for that adapter.
	"""

	# MAC addresses are always 12 digit hexadecimal numbers (48 bits)
	# They consist of six pairs of two hexadecimal digits {0-9, A-F}
	# Windows uses XX-XX-XX-XX-XX-XX
	# MAC addresses are case-insensitive
	# Leading zeros are optional (02-0A-1B-00-00-FF is the same as 02-0A-1B-0-0-FF)
	# The 2nd character is significant in a MAC address, if it's one of these letters (26AE) it's an LAA, otherwise it's UAA
	# follow the rules, setting a custom MAC without using these letters as the second letter could cause conflicts/issues with the network
	# LAA stands for (Locally Administrated Addresses)
	# UAA stands for (Universally Administrated Addresses)

	def enable_interface_windows(interface_reg):
		enabling_interface_result = check_output(f"wmic path win32_networkadapter where index={interface_reg} call enable")
		return enable_interface_windows

	def disable_interface_windows(interface_reg):
		disabling_interface_result = check_output(f"wmic path win32_networkadapter where index={interface_reg} call disable")
		return disabling_interface_result

	def get_random_mac_address_windows():
		# uppercase hexdigits (used set() for eliminating duplicates)
		uppercased_hexdigits = "".join(set(hexdigits.upper()))

		# generating a random MAC with following the LAA rule
		return f"{choice(uppercased_hexdigits)}{choice("24AE")}{''.join(sample(uppercased_hexdigits, k=10))}"

	def get_interfaces_windows():
		mac_regex = regex_compile(r"([A-Z0-9]{2}[:-]){5}([A-Z0-9]{2})")
		transport_name_regex = regex_compile("{.+}")

		interfaces_mac = []

		for line in check_output("getmac").decode().splitlines():
			mac = mac_regex.search(line)
			transport_name = transport_name_regex.search(line)

			if transport_name is not None and mac is not None:
				interfaces_mac.append((mac.group(), transport_name.group()))

		return interfaces_mac

	def spoof_mac_windows(transport_name, mac):
		network_interface_reg_path = "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}"

		# using reg QUERY to get available adapters from regsitery
		output = check_output(f"reg QUERY {network_interface_reg_path.replace("\\\\", "\\")}").decode()

		# looping through all interfaces from registery
		for interface in findall(rf"{network_interface_reg_path}\\\d+", output):

			# finding the interface path from registery
			interface_reg = int(interface.split("\\")[-1])

			# getting the content of the interface from registery
			interface_content = check_output(f"reg QUERY {interface_reg.strip()}").decode()

			# if transport name is found inside the interface we queried from registery, this is the interface we'd like to spoof its MAC
			if transport_name in interface_content:
				mac_spoofing_result = check_output(f"reg ADD {interface} /v NetworkAddress /d {mac} /f").decode()
				print(f"Spoofing Result: {mac_spoofing_result}")
				return interface_reg

	def clear_mac(mac):
		# returns a clear MAC (removing all '-' and ':' or other possible characters)
		return "".join(c for c in mac if c in hexdigits).upper()

	def select_interface(interfaces):

		# print available options
		for index, interface in enumerate(interfaces):
			print(f"#{index}: {interface[0]}, {interface[1]}")

		# if only one adapter exists, choose it automatically
		if len(interfaces) == 1:
			return interfaces[0]

		while True:
			try:
				choice = int(input("Please choose the interface you'd like to spoof its MAC by entering it's #N (e to exit): "))

				if choice == 'e':
					return

				return interfaces[choice]

			except:
				print("Not a valid answer!")

	def spoof_windows(self, *args):

		while True:
			system("cls")
			print("="*50)
			choice = input("you want to spoof it to a random MAC or a specific MAC? (R for random or S for specific): ")[0].upper()
			print("="*50)

			if choice in ('R', 'S'):
				break

		if choice == 'S':
			print("="*50)
			mac = input("Please enter the MAC address you'd like to spoof to: ")
			print("="*50)

			new_mac = clear_mac(mac)

		else:
			new_mac = get_random_mac_address_windows()
			interfaces = get_interfaces_windows()


		old_mac, target_transport_name = select_interface(interfaces)
		# to be continued