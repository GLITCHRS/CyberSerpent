from .CSImpersonationModel import CSImpersonationModel

class Spoofer(CSImpersonationModel):

	author = "GLITCH"

	def spoof(self, *args):
		print("Hello World")