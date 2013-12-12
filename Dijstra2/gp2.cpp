#include "grafo.cpp"

using namespace std;




main(){
   char opcion;
   char nombrefichero[30];
   int errorapertura;
   int l;


   cout << "Introduce el nombre del fichero de datos " << endl;
   cin >> nombrefichero;
   GRAFO a (nombrefichero, errorapertura);

   if(errorapertura==1)
      cout << "Error en la apertura del fichero" << endl;
   else if(errorapertura==0)
      cout <<  "Fichero cargado correctamente" << endl;


   do{
      cout << endl << "=====================================================";
      cout << "Actividad II,Optimizacion: caminos minimos\n";
      cout << "c. [c]argar grafo desde un fichero\n";
      cout << "i. Mostrar [i]nformacion basica del grafo\n";
      if (a.dirigido == 1) {
         cout << "s. Mostrar la lista de [s]ucesores del grafo\n";
         cout << "p. Mostrar la lista de [p]redecesores del grafo\n";
		 cout << "d. Caminos minimos: [d]ijkstra\n";
		 cout << "b. Caminos minimos: [b]ellman-ford-moore\n";
         cout << "q. [Q]uit\n";
         cout << "Introduce la letra de la accion a ejecutar :";
      }
      else {
         cout << "a. Mostrar la lista de [a]dyacencia del grafo\n";
         cout << "o. Mostrar componentes c[o]nexas del grafo\n";
         cout << "q. [Q]uit\n";
         cout << "Introduce la letra de la accion a ejecutar :";
      }

   cin >> opcion;
   switch (opcion){
      case 'c':
         cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
         cout << "Introduce el nombre del fichero de datos " << endl;
         cin >> nombrefichero;
         a.actualizar(nombrefichero, errorapertura);
         if(errorapertura==1){
            cout << "Error en la apertura del fichero" << endl;
            opcion = 'q';}
         else if(errorapertura==0)
            cout <<  "Fichero cargado correctamente" << endl;
         break;
      case 'i':
         cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
         a.Info_Grafo();
         break;
      if (a.dirigido == 1) {
         case 's':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.Mostrar_Listas(0);
            break;
         case 'p':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.Mostrar_Listas(1);
            break;
		case 'd':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.Dijkstra();
            break;
		case 'b':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.BellmanFordMoore();
            break;
       }
      else{
         case 'a':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.Mostrar_Listas(0);
            break;
         case 'o':
            cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
            a.ComponentesConexas();
            break;
      }
   }
   }while(opcion!='q');
   cout << "Salimos" << endl;
  // return 0;
}
