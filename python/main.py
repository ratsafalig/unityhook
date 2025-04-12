import blackbonepy
import const
import pefile
import time

# r = blackbonepy.Process.EnumByName("powershell.exe")
r = blackbonepy.Process.EnumByName("LuckyHunter.exe")

dll_path = "d:/steam/steamapps/common/luckyhunter/luckyhunterwindows/gameassembly.dll"

def get_all_exports(dll_path):
    pe = pefile.PE(dll_path)
    if hasattr(pe, 'DIRECTORY_ENTRY_EXPORT'):
        exports = pe.DIRECTORY_ENTRY_EXPORT.symbols
        for export in exports:
            name = export.name.decode('utf-8')
            export.address
            export.ordinal
            print(name)

# get_all_exports(dll_path)

def get_export():
    for i in r:
        p = blackbonepy.Process()

        result = p.Attach(i, const.DEFAULT_ACCESS_P)

        modules = p.modules()

        rr = modules.GetExport("GameAssembly.dll", "il2cpp_stop_gc_world")

        blackbonepy.il2cpp_stop_gc_world(p)
        
        time.sleep(10)

        blackbonepy.il2cpp_start_gc_world(p)

        pass


get_export()