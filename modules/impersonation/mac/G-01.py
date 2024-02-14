from ..ImpersonationModel import Impersonation


class Spoofer(Impersonation):

	r"""
	The following command to spoof mac:

			reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4D36E972-E325-11CE-BFC1-08002BE10318}\{adapter_key} /v NetworkAddress /t REG_SZ /d 002622D90EFC /f

	To identify the choosen network adapter by user, consider comparing the (Description) from the adapter he chose, with the (DriverDesc) key in registery for that adapter.
	"""

	author = "GLITCH"

	def spoof(self, *args):
		print("Hello World")
