import os
import Folder as Fo
import File as Fi

def commands(puntero, comando):
    comando = comando.split(" ")
    try:
        if(comando[0]=="ls"):
            for i in puntero.ls():
                print(i)
        elif(comando[0] == "touch"):
            nombre = comando[1]
            puntero.touch(nombre)
            
        elif(comando[0] == "mkdir"):
            nombre = comando[1]
            puntero.mkdir(nombre)
            
        elif(comando[0] == "mv"):
            src = comando[1]
            #print("\n")
            dst = comando[2]
            print(puntero.move(src,dst))
        elif(comando[0] == "rm"):
            src = comando[1]
            #print("\n")
            print(puntero.rm(src))
        elif(comando[0] == "rmdir"):
            src = comando[1]
            #print("\n")
            print(puntero.rmdir(src))
    except:
        pass


if __name__ == "__main__":
    ## first file in current dir (with full path)
    origen = os.path.join(os.getcwd(), os.listdir(os.getcwd())[0])
    #print(os.path.dirname(origen)) ## directory of file

    carpetita = Fo.Folder("Carpetita",os.path.dirname(origen))

    puntero = carpetita
    
    com = str(input(puntero.path+"# "))
    while(1):
        comand = com.split(" ")
        if(com == "exit"):
            break
        elif(comand[0]=="cd"):
            nombre = comand[1]
            if(nombre == ".."):
                if(puntero.parent):
                    puntero = puntero.parent
            elif(nombre in puntero.child):
                puntero = puntero.child[nombre]
        else:
            commands(puntero, com)
        com = str(input(puntero.path + "# "))
    
    carpetita.delete_all()