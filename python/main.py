import blackbonepy
import pefile
import time
import sys

dll_path = "d:/steam/steamapps/common/luckyhunter/luckyhunterwindows/gameassembly.dll"

# f = open('./log.txt', 'w+', encoding='utf8')
# sys.stdout = f

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

def handle(p):
    pass
    modules = p.modules()

    # mainThread = p.threads().getMain()

    # mainThread.Suspend()

    # export = modules.GetExport("GameAssembly.dll", "il2cpp_domain_get")
    
    # blackbonepy.il2cpp_stop_gc_world(p)

    # time.sleep(1)

    # r = blackbonepy.il2cpp_get_corlib(p)

    r = blackbonepy.il2cpp_domain_get(p)

    # r = blackbonepy.il2cpp_stats_dump_to_file(p, "D:/Users/LP/Desktop/unityhook/dump.txt")

    # time.sleep(1)
    
    # blackbonepy.il2cpp_start_gc_world(p)

    pass


def attach():
    # game = blackbonepy.Process.EnumByName("LuckyHunter.exe")

    # game = blackbonepy.Process.EnumByName("Discord.exe")

    game = blackbonepy.Process.EnumByName("Tariff.exe")

    # game = blackbonepy.Process.EnumByName("powershell.exe")

    for i in game:
        p = blackbonepy.Process()

        p.Attach(i)

        handle(p)

        return

def create_and_attach():
    p = blackbonepy.Process()

    p.CreateAndAttach('D:/Steam/steamapps/common/LuckyHunter/LuckyHunterWindows/LuckyHunter.exe')

    handle(p)

    pass

attach()
# create_and_attach()