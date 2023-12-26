# -*- mode: python ; coding: utf-8 -*-


a = Analysis(
    ['SmartCalcWeb/manage.py'],
    pathex=['SmartCalcWeb/calculator'],
    binaries=[],
    datas=[
        ('SmartCalcWeb/logs', 'logs' ), 
        ('SmartCalcWeb/assets', 'assets'),
        ('SmartCalcWeb/calculator/configs', 'calculator/configs'), 
        ('SmartCalcWeb/calculator/templates', 'calculator/templates'), 
    ],
    hiddenimports=['calculator.apps' , 'calculator.urls'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
)
pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name='manage',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
coll = COLLECT(
    exe,
    a.binaries,
    a.datas,
    strip=False,
    upx=True,
    upx_exclude=[],
    name='manage',
)
