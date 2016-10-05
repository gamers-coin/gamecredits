from distutils.core import setup
setup(name='gamespendfrom',
      version='1.0',
      description='Command-line utility for Gamecredits "coin control"',
      author='Gamecredits Developer',
      author_email='info@gamecredits.net',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
