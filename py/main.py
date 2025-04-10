import blackbonepy

r = blackbonepy.EnumByName("msedge.exe")

for i in r:
    print(i)

print("hello world")