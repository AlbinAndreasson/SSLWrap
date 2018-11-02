# SSLWrap

A simple wrapper for openSSL inet socket communication.
The API is essentially a copy of the [SFML](https://github.com/SFML/SFML)
API.

This still has major flaws like possibly no Windows support (not tested)
and it's very prone to throwing exceptions if *anything* goes wrong.