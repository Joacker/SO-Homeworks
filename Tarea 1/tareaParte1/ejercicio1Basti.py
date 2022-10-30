#-*- coding: utf-8 -*-
import os, sys


def arbol_rec(n):
    print("Soy:", os.getpid(),"hijo de",os.getppid())
    n -= 1
    if(n >= 2):
        n2 = n//2 
        r = n%2 

        if(os.fork() == 0):
            arbol_rec(n2+r)
        else:
            if(os.fork() == 0):
                arbol_rec(n2)
            else:
                pass
                
    elif(n == 1):
        os.fork() 
        return
    else:
        return

if __name__ == '__main__':
    n = int(input("Número de procesos: "))

    arbol_rec(n)