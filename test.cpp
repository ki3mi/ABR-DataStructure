#include <iostream>
using namespace std;

// --- Estructura del nodo ---
struct Nodo {
    int id;
    string nombre;
    string genero;
    Nodo* right;
    Nodo* left;
};

// --- Crear nuevo nodo ---
Nodo* nuevoNodo(int id, string nombre, string genero) {
    Nodo* nodo = new Nodo();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->genero = genero;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}

// --- Insertar subnodo en base a género ---
void insertarNodo(Nodo* nodo, string nombre, string genero) {
    int newId = nodo->id * 10;

    if (genero == "M" && nodo->right == NULL) {
        newId++;
        nodo->right = nuevoNodo(newId, nombre, genero);
        cout << "Padre asignado correctamente a " << nodo->nombre << "\n" << endl;
    } else if (genero == "F" && nodo->left == NULL) {
        nodo->left = nuevoNodo(newId, nombre, genero);
        cout << "Madre asignada correctamente a " << nodo->nombre << "\n" << endl;
    } else {
        if (genero != "M" && genero != "F") {
            cout << "Caracter de género no admitido\n";
        }
        if (nodo->left != NULL || nodo->right != NULL) {
            cout << "(ERROR) El familiar ya fue asignado previamente\n";
            cout << "Madre: " << ((nodo->left == NULL) ? "Sin asignar" : nodo->left->nombre) << endl;
            cout << "Padre: " << ((nodo->right == NULL) ? "Sin asignar" : nodo->right->nombre) << endl;
        }
    }
}

// --- Buscar por nombre (recorrido preorden) ---
Nodo* buscarNombre_Nodo(Nodo* nodo, string nombre) {
    if (nodo == NULL) return NULL;
    if (nodo->nombre == nombre) return nodo;

    Nodo* izq = buscarNombre_Nodo(nodo->left, nombre);
    if (izq != NULL) return izq;

    return buscarNombre_Nodo(nodo->right, nombre);
}

// --- Funciones auxiliares ---
int contarCifras(int n) {
    int cifras = 0;
    do {
        cifras++;
        n /= 10;
    } while (n != 0);
    return cifras;
}

void obtenerListaDigitos(int id, int listId[], int cifras) {
    for (int j = 1; j <= cifras; j++) {
        listId[cifras - j] = id % 10;
        id = id / 10;
    }
}

// --- Buscar por ID ---
Nodo* buscarId_Nodo(Nodo* nodo, int id) {
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

// --- Eliminar por ID ---
bool eliminarPorId(Nodo* raiz, int id) {
    if (raiz == NULL || id == 1) return false;

    Nodo* objetivo = buscarId_Nodo(raiz, id);
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

// --- Eliminar por nombre ---
bool eliminarPorNombre(Nodo* nodo, string nombre) {
    if (nodo == NULL) return false;

    if (nodo->left != NULL && nodo->left->nombre == nombre) {
        delete nodo->left;
        nodo->left = NULL;
        cout << "Nodo con nombre '" << nombre << "' eliminado.\n";
        return true;
    }

    if (nodo->right != NULL && nodo->right->nombre == nombre) {
        delete nodo->right;
        nodo->right = NULL;
        cout << "Nodo con nombre '" << nombre << "' eliminado.\n";
        return true;
    }

    return eliminarPorNombre(nodo->left, nombre) || eliminarPorNombre(nodo->right, nombre);
}

// --- Recorrido preorden ---
void mostrarArbol_preorden(Nodo* nodo) {
    if (nodo == NULL) return;

    cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Género: " << nodo->genero << endl;
    mostrarArbol_preorden(nodo->left);
    mostrarArbol_preorden(nodo->right);
}

// Vista Gerarquica
void mostrarArbolVisual(Nodo* nodo, string prefijo = "", bool esIzquierdo = true) {
    if (nodo == NULL) return;

    cout << prefijo;
    cout << (esIzquierdo ? "├── " : "└── ");
    cout << nodo->nombre << " (ID: " << nodo->id << ", " << nodo->genero << ")" << endl;

    // Si hay hijos, aumentar el prefijo con formato adecuado
    if (nodo->left != NULL || nodo->right != NULL) {
        if (nodo->left) {
            mostrarArbolVisual(nodo->left, prefijo + (esIzquierdo ? "│   " : "    "), true);
        }
        if (nodo->right) {
            mostrarArbolVisual(nodo->right, prefijo + (esIzquierdo ? "│   " : "    "), false);
        }
    }
}
// --- Menú principal ---
int main() {
    system("chcp 65001 > nul");
    Nodo* raiz = nuevoNodo(1, "Raiz", "Raiz");

    int opcion;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Insertar familiar\n";
        cout << "2. Buscar por nombre\n";
        cout << "3. Buscar por ID\n";
        cout << "4. Eliminar por nombre\n";
        cout << "5. Eliminar por ID\n";
        cout << "6. Mostrar árbol (Gerarquías)\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // limpiar el buffer

        string nombre, genero;
        int id;

        switch (opcion) {
            case 1:
                cout << "Nombre del nodo de referencia: ";
                getline(cin, nombre);
                {
                    Nodo* nodoRef = buscarNombre_Nodo(raiz, nombre);
                    if (nodoRef == NULL) {
                        cout << "Nodo no encontrado.\n";
                        break;
                    }
                    cout << "Nombre del familiar a agregar: ";
                    getline(cin, nombre);
                    cout << "Género (M/F): ";
                    getline(cin, genero);
                    insertarNodo(nodoRef, nombre, genero);
                }
                break;

            case 2:
                cout << "Nombre a buscar: ";
                getline(cin, nombre);
                {
                    Nodo* resultado = buscarNombre_Nodo(raiz, nombre);
                    if (resultado) {
                        cout << "ID: " << resultado->id << ", Género: " << resultado->genero << endl;
                    } else {
                        cout << "No se encontró el nodo.\n";
                    }
                }
                break;

            case 3:
                cout << "ID a buscar: ";
                cin >> id;
                {
                    Nodo* resultado = buscarId_Nodo(raiz, id);
                    if (resultado) {
                        cout << "Nombre: " << resultado->nombre << ", Género: " << resultado->genero << endl;
                    } else {
                        cout << "No se encontró el nodo.\n";
                    }
                }
                break;

            case 4:
                cout << "Nombre a eliminar: ";
                getline(cin, nombre);
                if (!eliminarPorNombre(raiz, nombre)) {
                    cout << "No se encontró el nodo con ese nombre.\n";
                }
                break;

            case 5:
                cout << "ID a eliminar: ";
                cin >> id;
                if (!eliminarPorId(raiz, id)) {
                    cout << "No se pudo eliminar el nodo.\n";
                } else {
                    cout << "Nodo eliminado con éxito.\n";
                }
                break;

            // case 6:
            //     cout << "\n-- Árbol familiar (preorden) --\n";
            //     mostrarArbol_preorden(raiz);
            //     break;

            case 6:
                cout << "\n-- Árbol familiar (vista jerárquica) --\n";
                cout << raiz->nombre << " (ID: " << raiz->id << ", " << raiz->genero << ")" << endl;
                if (raiz->left) mostrarArbolVisual(raiz->left, "", true);
                if (raiz->right) mostrarArbolVisual(raiz->right, "", false);
                break;

            case 0:
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opción inválidaa.\n";
                break;
        }
        if(opcion != 0){
            system("pause");
        }
        system("cls");
    } while (opcion != 0);

    return 0;
}
