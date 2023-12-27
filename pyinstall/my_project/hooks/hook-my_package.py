# my_project/hooks/hook-my_package.py

from PyInstaller.utils.hooks import collect_all

datas, binaries, hiddenimports = collect_all('my_package')
