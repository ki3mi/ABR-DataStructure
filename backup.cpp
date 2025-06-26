#include<iostream>
using namespace std;

struct Nodo
{
    int id;
    string nombre;
    string genero;
    Nodo *right;
    Nodo *left;
};

// Agregar
Nodo *nuevoNodo(int id, string nombre, string genero){
    Nodo *nodo = new Nodo();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->genero = genero;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}


// Asignar ID e Insertar subNodo
void insertarNodo(Nodo *nodo, string nombre, string genero){
    
    int newId = nodo->id * 10;

    // F -> izquierda, M->Derecha
    if(genero == "M" && nodo->right == NULL){
        newId ++;
        nodo->right = nuevoNodo(newId, nombre, genero);
        cout<<"Padre asignado correctamente a "<<nodo->nombre<<"\n"<<endl;
    }else if(genero == "F" && nodo->left == NULL){
        nodo->left = nuevoNodo(newId, nombre, genero);
        cout<<"Madre asignado correctamente a"<<nodo->nombre<<"\n"<<endl;
    }else{
        if(genero != "M" && genero != "F"){
            cout<<"Caracter de genero no admitido \n"<<endl;
        }
        if(nodo->left != NULL || nodo->right !=NULL){
            cout<<"(ERROR) El familiar ya fue asignado previamente"<<endl;
            cout<<"\nMadre: "<<((nodo->left == NULL) ? "Sin asignar" : nodo->left->nombre);
            cout<<"\nPadre: "<<((nodo->right == NULL) ? "Sin asignar" : nodo->right->nombre);
            cout<<"\n"<<endl;
        }       
    }
}

// Buscar / Recorrido en Preorden
Nodo *buscarNombre_Nodo(Nodo *newNodo, string nombre){
    if(newNodo == NULL){
        return NULL;
    }
    if(newNodo->nombre == nombre){
        return newNodo;
    }
    
    Nodo *izq = buscarNombre_Nodo(newNodo->left, nombre);
    if (izq!=NULL){
        return izq;
    }    
    return buscarNombre_Nodo(newNodo->right, nombre);
}

// Conteo de cifras
int contarCifras(int n) {
    int cifras = 0;
    do {
        cifras++;
        n /= 10;
    } while (n != 0);
    return cifras;
}
// Lista de dígitos
void obtenerListaDigitos(int id, int listId[], int cifras) {
    for (int j = 1; j <= cifras; j++) {
        listId[cifras - j] = id % 10;
        id = id / 10;
    }
}
// Buscar por Id
Nodo buscarId_Nodo(Nodo nodo, int id) {
    if (nodo == NULL) return NULL;
    if (nodo->id == id) return nodo;

    int cifras = contarCifras(id);
    int listId[cifras];
    obtenerListaDigitos(id, listId, cifras);

    for (int j = 1; j < cifras; j++) {
        if (listId[j] == 0 && nodo->left != NULL) {
            nodo = nodo->left;
        } else if (listId[j] == 1 && nodo->right != NULL) {
            nodo = nodo->right;
        } else {
            cout << "Nodo no existente\n";
            return NULL;
        }
    }
    return nodo;
}

// Eliminar
bool eliminarPorId(Nodo* raiz, int id) {
    if (raiz == NULL || id == 1) return false;
    Nodo *objetivo = buscarId_Nodo(raiz, id);
    if (objetivo == NULL) return false;
    
    int cifras = contarCifras(id);
    int listId[cifras];
    obtenerListaDigitos(id, listId, cifras);
    
    Nodo* nodo = raiz;
    for (int j = 1; j < cifras - 1; j++) {
        if (listId[j] == 0) nodo = nodo->left;
        else nodo = nodo->right;
        if (nodo == NULL) return false;
    }
    
    if (listId[cifras - 1] == 0 && nodo->left && nodo->left->id == id) {
        delete nodo->left;
        nodo->left = NULL;
        return true;
    } else if (listId[cifras - 1] == 1 && nodo->right && nodo->right->id == id) {
        delete nodo->right;
        nodo->right = NULL;
        return true;
    }
    
    return false;
}

// Eliminar por Nombre
bool eliminarPorNombre(Nodo* nodo, string nombre) {
    if (nodo == NULL) return false;
    
    // Verificar si el hijo izquierdo es el que buscamos
    if (nodo->left != NULL && nodo->left->nombre == nombre) {
        delete nodo->left;
        nodo->left = NULL;
        cout << "Nodo con nombre '" << nombre << "' eliminado.\n";
        return true;
    }
    
    // Verificar si el hijo derecho es el que buscamos
    if (nodo->right != NULL && nodo->right->nombre == nombre) {
        delete nodo->right;
        nodo->right = NULL;
        cout << "Nodo con nombre '" << nombre << "' eliminado.\n";
        return true;
    }
    
    // Buscar recursivamente en los subárboles
    return eliminarPorNombre(nodo->left, nombre) || eliminarPorNombre(nodo->right, nombre);
}

// --- Recorrido preorden ---
void mostrarArbol(Nodo* nodo) {
    if (nodo == NULL) return;

    cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Género: " << nodo->genero << endl;
    mostrarArbol(nodo->left);
    mostrarArbol(nodo->right);
}

int main(){
    
    return 0;
}

