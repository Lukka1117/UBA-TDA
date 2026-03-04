def esLlinda(cadenea, long, l):
    if cadenea.isalpha():
        if long == 1 and cadenea == l:
            return True

        medio = long//2
        cadenaI = cadenea[:medio]
        cadenaD = cadenea[medio:]

        siguiente_char = chr(ord(l) + 1)

        if cadenea[0] == l and todosCharIguales(cadenaI):
            return esLlinda(cadenaD, medio, siguiente_char)
        if cadenea[long-1] == l and todosCharIguales(cadenaD):
            return esLlinda(cadenaI, medio, siguiente_char)

    return False

def todosCharIguales(cadena):
    if len(cadena) <= 1:
        return True
    
    primer_char = cadena[0]
    for i in range(1, len(cadena)):
        if cadena[i] != primer_char:
            return False
    return True