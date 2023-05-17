#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    bool disponible;

public:
    Libro(const string& titulo, const string& autor)
        : titulo(titulo), autor(autor), disponible(true) {}

    const string& getTitulo() const {
        return titulo;
    }

    const string& getAutor() const {
        return autor;
    }

    bool estaDisponible() const {
        return disponible;
    }

    void prestar() {
        disponible = false;
    }

    void devolver() {
        disponible = true;
    }
};

class Biblioteca 
{
private:
    vector<Libro> libros;
    vector<Libro> librosPrestados;
public:
    void agregarLibro(Libro& libro) 
    {
        libros.push_back(libro);
    }

    void eliminarLibro(Libro& libro) 
    {
        libros.erase(remove_if(libros.begin(), libros.end(), [&libro](const Libro& l) 
        {
            return l.getTitulo() == libro.getTitulo() && l.getAutor() == libro.getAutor();
        }),
        libros.end());
    }

    void mostrarLibros() const 
    {
    for (const auto& libro : libros) 
    {
        if (libro.estaDisponible()) {
            cout <<endl<< "Titulo: "<< libro.getTitulo() <<endl <<"Autor: "<< libro.getAutor();
            cout << " (Disponible)"<<endl;
        }
    }
}
void prestarLibro(const string& titulo, const string& autor) {
    for (size_t i = 0; i < libros.size(); ++i) {
        if (libros[i].getTitulo() == titulo && libros[i].getAutor() == autor) {
            if (libros[i].estaDisponible()) {
                libros[i].prestar();
                librosPrestados.push_back(libros[i]);
                libros.erase(libros.begin() + i);
                cout << "El libro ha sido prestado." << endl;
            } else {
                cout << "El libro ya está prestado." << endl;
            }
            return;
        }
    }
    cout << "El libro no está disponible en la biblioteca." << endl;
}
void devolverLibro(const string& titulo, const string& autor) {
    for (size_t i = 0; i < librosPrestados.size(); ++i) {
        if (librosPrestados[i].getTitulo() == titulo && librosPrestados[i].getAutor() == autor) {
            librosPrestados[i].devolver();
            libros.push_back(librosPrestados[i]);
            librosPrestados.erase(librosPrestados.begin() + i);
            cout << "El libro ha sido devuelto." << endl;
            return;
        }
    }
    cout << "El libro no ha sido prestado." << endl;
}
    vector<Libro> buscarLibrosPorTitulo(string& titulo) const 
    {
        vector<Libro> resultados;

        for (const auto& libro : libros) {
            if (libro.getTitulo() == titulo) {
                resultados.push_back(libro);
            }
        }

        return resultados;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    Biblioteca biblioteca;
    Libro libro1("La ciudad y los perros", "Mario Vargas Llosa");
    Libro libro2("La palabra del mudo", "Julio Ramón Ribeyro");
    Libro libro3("Trilce", "César Vallejo");
    Libro libro4("1984", "George Orwell");

    biblioteca.agregarLibro(libro1);
    biblioteca.agregarLibro(libro2);
    biblioteca.agregarLibro(libro3);
    biblioteca.agregarLibro(libro4);

    int opcion = 0;

    while (opcion != 5) {
        cout << "----- MENU PRINCIPAL -----" << endl;
        cout << "1. Ver libros disponibles" << endl;
        cout << "2. Prestar un libro" << endl;
        cout << "3. Devolver un libro" << endl;
        cout << "4. Eliminar un libro" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su numero: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << endl << "Libros disponibles:" << endl << "=======================" << endl;
                biblioteca.mostrarLibros();
                cout << endl;
                break;
            }
            case 2: {
                string titulo, autor;
                cin.ignore(); // Se usa el cin para ignorar el salto de linea que hace el getline, debido al caracter enter
                cout << endl << "Prestar un libro:" << endl;
                cout << "Ingrese el título del libro: ";
                getline(cin, titulo); // Se usa el getline y no el cin>> tradicional ya que el cin solo recoge la primera palabra, con el getline nos aseguramos se que se lean los nombre completos
                cout << "Ingrese el autor del libro: ";
                getline(cin, autor);
                biblioteca.prestarLibro(titulo, autor);
                break;
            }
            case 3: {
                string titulo, autor;
                cin.ignore();
                cout << endl << "Devolver un libro de la biblioteca:" << endl;
                cout << "Ingrese el título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese el autor del libro: ";
                getline(cin, autor);
                biblioteca.devolverLibro(titulo, autor);
                break;
            }
            case 4: {
                string titulo, autor;
                cin.ignore();
                cout << endl << "Eliminar un libro de la biblioteca:" << endl;
                cout << "Ingrese el título del libro: ";
                getline(cin, titulo);
                cout << "Ingrese el autor del libro: ";
                getline(cin, autor);
                Libro libroEliminar(titulo, autor);
                biblioteca.eliminarLibro(libroEliminar);

            }
            case 5: {
                cout << "ADI0S" << endl;
                break;
            }
            default:
                cout << "ERR0R , Seleccione una opcion valida" << endl << endl;
        }
    }

    return 0;
}