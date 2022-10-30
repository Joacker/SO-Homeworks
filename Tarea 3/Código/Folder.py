import os, errno, shutil
import File as F

mode = 0o777

class Folder(object):
    def __init__(self, nombre, path, parent = None):
        self.parent = None
        if(parent):
            self.parent = parent
        self.path_parent = path
        self.path = path+"/"+nombre
        if not os.path.exists(self.path):
            try:
                os.mkdir(self.path, mode)    
            except:
                raise OSError("no podí crear archivos existentes chuchetumare")
        self.child = {} #carpetas 
        self.files = {} #archivos

    def busqueda(self, dst):
        pasos = dst.split("/")
        #arr = pasos[:1]
        aux = self
        while(aux.parent):
            aux = aux.parent
        
        pasos = pasos[6:]
        for i in pasos:
            if(i in aux.child):
                aux = aux.child[i]
            else:
                return None
        return aux

    def ls(self):
        return os.listdir(self.path)
    
    def mkdir(self, nombre):
        nuevo = Folder(nombre, self.path, self)
        self.child[nombre] = nuevo
        if not os.path.exists(self.path):
            try:
                os.mkdir(self.path+'/'+nombre, mode)  
            except:
                raise OSError("no podí crear archivos existentes chuchetumare")
        
    
    def touch(self, name):
        if os.path.exists(name):
            os.utime(self.path+"/"+name, None)
        else:
            open(self.path+"/"+name, 'a').close()
        
        nuevo = F.File(name,self.path)
        self.files[name] = nuevo
        #open(self.path+'/'+name, 'a').close()
        #os.mknod(self.path+'/'+name,mode)

    def move(self,src,dst):
        archivo = None 
        if(src in self.files):
            archivo = self.files[src]
        else:
            return False
        dest = self.busqueda(dst)
        if(dest):
            dest.files[src] = archivo
        else:
            return False
        
        self.files.pop(src)
        shutil.move(self.path+"/"+src,dst)
        archivo.update_path(dst)
        return True

    def delete_all(self):
        while(len(self.child) > 0):
            nom_a = list(self.child.keys())[0]
            aux = self.child[nom_a]
            if(len(aux.child) > 0 or len(aux.files) > 0):
                aux.delete_all()
            os.rmdir(aux.path)
            self.child.pop(nom_a)
            aux = None

        while(len(self.files) > 0):
            nom_a = list(self.files.keys())[0]
            aux = self.files[nom_a]
            os.remove(aux.path)
            self.files.pop(nom_a)
            aux = None

    def rmdir(self,key): #key = nombre del archivo que se desea eliminar
        print(self.child)
        if(key in self.child):
            aux = self.child[key]
            aux.delete_all()
            os.rmdir(aux.path)
            self.child.pop(key)
            aux = None
        else:
            print("El directorio no existe")

    
    def rm(self,key):
        self.files.pop(key)
        os.remove(self.path+"/"+str(key))
        
