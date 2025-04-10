import blackbonepy
import const

r = blackbonepy.Process.EnumByName("msedge.exe")

for i in r:
    p = blackbonepy.Process()
    result = p.Attach(i, const.DEFAULT_ACCESS_P)

    modules = p.modules()

    modules.GetAllModules()

    pass

