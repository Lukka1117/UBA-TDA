def transformar(x, y):
    camino = [y]
    while y > x:
        if y % 10 == 1:
            y = (y - 1) // 10
        elif y % 2 == 0:
            y = y // 2
        else:
            print("NO")
            return
        camino.append(y)
    
    if y == x:
        print("YES")
        print(len(camino))
        print(" ".join(map(str, reversed(camino))))
    else:
        print("NO")


print(transformar(1,82))