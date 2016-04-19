from distutils.core import setup
setup(name='gmcspendfrom',
      version='1.0',
      description='Command-line utility for Gamecredits "coin control"',
      author='Gavin Andresen',
      author_email='gavin@bitcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
