# Unity Hook

Unity il2cpp hook python library, build on minhook and blackbone.

# Example

```python
import blackbonepy
import const

r = blackbonepy.Process.EnumByName("msedge.exe")

for i in r:
    p = blackbonepy.Process()
    result = p.Attach(i, const.DEFAULT_ACCESS_P)
    pass
```

# Dependencies

- Xenos ( blackbone )
- minhook
- pybind11