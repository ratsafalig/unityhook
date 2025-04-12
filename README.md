# Unity Hook

# Example

```python
import blackbonepy
import const
import time

# r = blackbonepy.Process.EnumByName("powershell.exe")
r = blackbonepy.Process.EnumByName("LuckyHunter.exe")

def example():
    for i in r:
        p = blackbonepy.Process()

        result = p.Attach(i, const.DEFAULT_ACCESS_P)

        modules = p.modules()

        rr = modules.GetExport("GameAssembly.dll", "il2cpp_stop_gc_world")

        blackbonepy.il2cpp_stop_gc_world(p)
        
        time.sleep(10)

        blackbonepy.il2cpp_start_gc_world(p)

        return


example()
```

# Dependencies

- blackbone
- minhook
- pybind11