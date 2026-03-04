def movimientos_para_obtener_aLinda(cadena, long): 
    return movimientos_para_llinda(cadena, long, "a")

def movimientos_para_llinda(cadena, long, l):
    #el caso base cuando el string es de 1 caracter, si es l no hace movimientos, si no, necesita 1 movimiento
    if long == 1 and cadena == l:
            return 0
    if long == 1 and cadena != l:
            return 1
    
    #divido la longitud del string para encarar por el lado de D&C, necesito verificar de a mitades
    medio = long//2
    cadenaI = cadena[:medio]    #lado izquierdo del string
    cadenaD = cadena[medio:]    #lado derecho del string

    siguiente_char = chr(ord(l) + 1) #mi l+1

    #caso donde la primera mitad es todo l
    #cuento cuantos caracteres son distintos a l en la primera mitad (suma un mov cada uno), y recursivamente
    #verifico cuantos  necesito en la otra mitad, con el char siguiente a l
    movimientos1 = cantidad_char_distintos(cadenaI, l) + movimientos_para_llinda(cadenaD, medio, siguiente_char) 
    #caso donde la segunda mitad es todo a
    #hago llo mismo pero contanod que todos los caracteres de la segunda mitad sean l
    movimientos2 = cantidad_char_distintos(cadenaD, l) + movimientos_para_llinda(cadenaI, medio, siguiente_char)

    return min(movimientos1, movimientos2)  #devuelve la opcion de cambios que haya necesitado menos movimientos

def cantidad_char_distintos(cadena, l):
    res = 0

    for i in range(0, len(cadena)):
        if cadena[i] != l:
            res += 1
    return res

def main():
    t = int(input())

    for _ in range(t):
        long = int(input())
        cadena = input().strip()

        movimientos_necesarios = movimientos_para_obtener_aLinda(cadena, long)
        print(movimientos_necesarios)

if __name__ == "__main__":
    main()



