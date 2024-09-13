    /*
    * Ejercicio: Act 1.2 - Algoritmos de Búsqueda y Ordenamiento
    * Archivo: act1.2.cpp
    * Autor: Joanna Nicole Uriostegui Magaña
    * Matricula: A01711853
    * Fecha: 29/08/24
    * 
    * El código determina el orden de los equipos en un concurso
    * de a cuerdo al que más problemas haya resuelto, con menor
    * tiempo de penalización y en el orden de los equipos
    * 
    * Complejidad: O(m log n + n log n)
    * 
    * Copyright (c) 2024 by Tecnologico de Monterrey.
    * All Rights Reserved. May be reproduced for any non-commercial
    * purpose.
    */

    //Librerias
    #include <iostream>
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>// Para sort


    using namespace std;

    /*
    * * * * * * * * * * * * * Clase: Intento * * * * * * * * * * * * *
    * 
    * Guarda el tiempo de penalización que se lleva en un problema y
    * la cantidad de intentos en el mismo.
    * 
    * Atributos: Tiempo, Cantidad de Intentos
    * Métodos: Incrementar intento
    */
    class Intento {
        private:
            //Atributos
            int tiempo;
            int cant_intentos;

        public:
            //Constructores
            Intento() : tiempo(0), cant_intentos(0) {}
            Intento(int t, int c) : tiempo(t), cant_intentos(c) {}

            //Getters y Setters
            void setTiempo(int t){ tiempo = t; }
            int getTiempo(){ return tiempo; }
            void setCant(int c){ cant_intentos = c; }
            int getCant(){ return cant_intentos; }

            //Metodo
                //Suma uno al atributo de cantidad de intentos
            void incrementarIntento(){ cant_intentos++; }
    };

    /*
    * * * * * * * * * * * * * Clase: Equipo * * * * * * * * * * * * *
    * 
    * Guarda el el total de penalización que lleva un equipo, la cantidad de
    * problemas resueltos que tienen y en un mapa de enteros y de objetos tipo
    * intento los intentos incorrectos del equipo según el problema.
    * 
    * Atributos: n, penalización, resueltos, mapa de problema e objeto Intento
    * Métodos: Agregar Intento
    */
    class Equipo {
        private:
            //Atributos
            int n;
            int penalizacion;
            int resueltos;
            map<int, Intento> incorrectos; //Mapa que guarda intentos incorrectos
        
        public:
            //Contructores
            Equipo() : n(0), penalizacion(0), resueltos(0) {}
            Equipo(int id) : n(id), penalizacion(0), resueltos(0) {}

            //Getters
            int getId(){ return n; }
            int getPenalizacion(){ return penalizacion; }
            int getResueltos(){ return resueltos; }

            /*
            * * * * * * * * * * * * * Agregar Intento * * * * * * * * * * * * *
            * 
            * Verifica si el problema ya existe, si no lo crea y de a cuerdo a
            * si es C o I, incrementa e tiempo de penalización y cuando es correcto
            * incrementa la cantidad de problemas resueltos.
            * 
            * Complejidad: O(log n)
            * Param: int del problema, tiempo y char del estatus
            * Return: -
            */
            void agregarIntento(int problema, int tiempo, char estatus) {
                if (estatus == 'C') {
                    //Verificamos si hay más intentos del mismo problema
                    if (incorrectos.find(problema) == incorrectos.end()) {
                        incorrectos[problema] = Intento(tiempo, 0);
                    }
                    //Cálculo de la penalización, de acuerdo a la cantidad de intentos
                    //realizados y el tiempo de penalización que ya tenía c/u.
                    penalizacion += tiempo + (incorrectos[problema].getCant() * 20);
                    resueltos++;
                } else if (estatus == 'I') {
                    //Agregamos el intento del problema si no existe
                    if (incorrectos.find(problema) == incorrectos.end()) {
                        incorrectos[problema] = Intento(0, 1);
                    } else {
                        //Incrementar contador de intentos incorrectos
                        incorrectos[problema].incrementarIntento();
                    }
                }
            }
    };

    int main() {
        //Variables
        int casos, equipo, problema, tiempo;
        char estatus;

        //Leer la cantidad de casos
        cin >> casos;

        //Iterar la cantidad de casos indicados
        for (int i = 0; i < casos; i++) {
            // Mapa para almacenar los equipos
            //Complejidad del while: O(m log n)
            map<int, Equipo> concurso;
            while (cin >> equipo >> problema >> tiempo >> estatus) {
                // Verificamos la existencia del equipo, si no. se crea
                if (concurso.find(equipo) == concurso.end()) {
                    concurso[equipo] = Equipo(equipo);
                }

                //Agregar el intento al equipo
                concurso[equipo].agregarIntento(problema, tiempo, estatus);

                //Para que al detectar dos saltos de línea se salga del ciclo
                //y termine el caso
                if (cin.peek() == '\n') {
                    cin.ignore();
                    if (cin.peek() == '\n') {
                        cin.ignore();
                        break;
                    }
                }
            }

            //Complejidad: O(n)
            vector<vector<int>> elements;

            //Imprimimos los resultados de cada equipo
            for (auto& key : concurso) {
                int equipo_id = key.first;  //clave
                Equipo& equipo = key.second;  //objeto
                
                //Vector para guardar info de equipo
                vector<int> info_equipo;
                info_equipo.push_back(equipo_id);               
                info_equipo.push_back(equipo.getResueltos());   
                info_equipo.push_back(equipo.getPenalizacion());

                // Añadir el vector
                elements.push_back(info_equipo);
            }
            
            //Ordenar el vector
            //Complejidad: O(n log n)
            sort(elements.begin(), elements.end(), [](const vector<int>& a, const vector<int>& b) {
                if (a[1] != b[1])  //Del mayor numero de problemas resueltos al menor
                    return a[1] > b[1];
                if (a[2] != b[2])  //Si no, del menor al mayor tiempo de penalizacion
                    return a[2] < b[2];
                return a[0] < b[0]; //Al fina, del menor al mayor número de equipo
            });

            //Complejidad O(n)
            // Imprimir los resultados
            for (const auto& equipo_info : elements) {
                cout << equipo_info[0] << " " << equipo_info[1] << " " << equipo_info[2] << endl;
            }
            cout << endl;

            // Eliminar todos los elementos del mapa
            concurso.clear();
        }

        return 0;
    }
