from abc import ABC, abstractmethod


class Impersonation(ABC):

	author = None

	@abstractmethod
	def spoof(self, *args):
		# Spoofing logic goes here
		...