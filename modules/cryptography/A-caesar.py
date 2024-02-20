from typing import Any, Generator


def encrypt(text: str, key: int) -> str:
    """Encrypts text with key"""
    return "".join(chr((ord(letter) + key) % 0x10ffff) for letter in text)

def decrypt(text: str, key: int) -> str:
    """Decrypts text with key"""
    return "".join(chr((ord(letter) - key) % 0x10ffff) for letter in text)

def brute_force_decrypt(text: str, start: int, end: int) -> Generator[str, Any, None]:
    """Decrypts text using a range of keys"""
    return (decrypt(text, i) for i in range(start, end+1))

def brute_force_encrypt(text: str, start: int, end: int) -> Generator[str, Any, None]:
    """Encrypts text using a range of keys"""
    return (encrypt(text, i) for i in range(start, end+1))