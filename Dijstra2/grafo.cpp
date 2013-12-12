#include "grafo.h"

using namespace std;

GRAFO::GRAFO(char nombrefichero[30], int &errorapertura){
   unsigned i, j, c; // Nodos inicial y de llegada, respectivamente
   ifstream textfile;
   ElementoLista dummy;

   textfile.open (nombrefichero);
   if (textfile.is_open()) {
      errorapertura = 0;
      textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
      LS.resize (n);
      for (unsigned k = 0; k < m; k++) {
         textfile >> (unsigned &) i >> (unsigned &) j >> (unsigned &) c;;
	 dummy.j = --j;
	 dummy.c = c;
	 LS[--i].push_back(dummy);

	 if (dirigido == 0) {
	    dummy.j = i;
            LS[j].push_back(dummy);
	 }
      }
    }
    else errorapertura = 1;
   textfile.close();
   ListaPredecesores ();
}


void GRAFO::actualizar(char nombrefichero[], int &errorapertura){
   unsigned i, j, c; // Nodos inicial y de llegada, respectivamente
   ifstream textfile;
   ElementoLista dummy;

   LS.clear();
   LP.clear();
   textfile.open (nombrefichero);

   if (textfile.is_open()) {
      errorapertura = 0;
      textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
      LS.resize (n);
      for (unsigned k = 0; k < m; k++) {
         textfile >> (unsigned &) i >> (unsigned &) j >> (unsigned &) c;;
         dummy.j = --j;
		  dummy.c = c;
         LS[--i].push_back(dummy);
            if (dirigido == 0) {
               dummy.j = i;
               LS[j].push_back(dummy);
            }
       }

    textfile.close();
    ListaPredecesores();
    }
    else errorapertura = 1;
 }

void GRAFO::Info_Grafo(){
  if(dirigido==0)
    cout << "Grafo NO dirigido" << '|' << "Nodos " << n << '|' << "Aristas " << m << endl;
  else
    cout << "Grafo dirigido" << '|' << "Nodos " << n << '|' << "Aristas " << m << endl;

}

void GRAFO::Mostrar_Listas(int l){

   if(l==0){
      for(int x=0;x<n;x++){
         cout << "Nodo" << x+1 << " ";
         for (unsigned j=0;j<LS[x].size();j++)
            cout << (LS[x][j].j) + 1 << " ";
      cout << endl;
      }
   }
   if(l==1){
      for(int x=0;x<n;x++){
         cout << "Nodo" << x+1 << " ";
         for (unsigned j=0;j<LP[x].size();j++)
            cout << (LP[x][j].j) + 1 << " ";
      cout << endl;
     }
   }
}

void GRAFO::ListaPredecesores(){
   ElementoLista dummy;
   LP.resize(n);
   for (unsigned i = 0; i < n; i++)
      for (unsigned k = 0; k < LS[i].size(); k++) {
         dummy.j = i;
	 LP[LS[i][k].j].push_back(dummy);
      }
}

void GRAFO::dfs(unsigned i, vector<bool> &visitado){
   visitado[i] = true;
   cout << i+1 << ", ";
   for (unsigned j=0;j<LS[i].size();j++)
      if (visitado[LS[i][j].j] == false)
         dfs(LS[i][j].j, visitado);
}

void GRAFO::ComponentesConexas(){
   unsigned i, cc = 0;
   vector <bool> Vis;

   Vis.resize (n, false);
   for(i=0; i<n; i++) {
      if (Vis[i] == false) {
         cc++;
         cout << "Componente Conexa " << cc << " { " ;
         dfs (i, Vis);
	 cout << "}" << endl;
      }
   }
}

void GRAFO::MostrarCamino(unsigned s, unsigned i, vector<unsigned> pred){
   if (i != s){
      MostrarCamino(s,pred[i],pred);
      cout << pred[i]+1 << " -> ";
   }
}
void GRAFO::Dijkstra(){

   vector<bool> PermanentementeEtiquetado;
   vector<int> d;
   vector<unsigned> pred;
   unsigned i=0,j,k=0,m;

unsigned s, candidato, min;
int aux = 0;

   PermanentementeEtiquetado.resize(n,false);
   d.resize(n,maxint);
   pred.resize(n,UERROR);
   cout <<"Introduzca el nodo por el que desea empezar (" << n << ") nodos es el max:" <<endl; //Pedir el nodo de partida s (0-n-1) por pantalla;
   cin >> s ;
   s--; //Decremento el valor de s, para que coincida con el valor del vector.
   d[s]=0; //Incializamos la distancia
   pred[s] = s;
   do{
      i=0;
	  candidato = UERROR; //Inicializamos el valor de candidato a UERROR.
	  min = maxint;
	      for(i=0; i < n; i++){
               if (PermanentementeEtiquetado[i] == false && d[i] < min){ // La etiqueta permanente es falsa.
                     min = d[i];
                              candidato = i; //Candidato coje el valor de i y se sale del bucle
            }
      }
      if (candidato != UERROR) {
	     PermanentementeEtiquetado[candidato] = true;
         for (unsigned k = 0; k < LS[candidato].size(); k++){ //Recorremos los sucesores.
            if (( d[LS[candidato][k].j]) > (d[candidato] + LS[candidato][k].c)){   //Si la distancia de los sucesores, es mayor que la distancia del candidato mÃƒÆ’Ã‚Â¡s el coste.
			   d[LS[candidato][k].j] = (d[candidato] + LS[candidato][k].c); //Sustituimos la nueva distancia por el valor que nos dio la suma anterior.
               pred[LS[candidato][k].j] = candidato; //El predecesor es el nuevo candidato.*/
            }
         }
     }
    }while (min < maxint);
	  cout << "Soluciones:" << endl;
      for (unsigned i = 0; i < n; i++){
	     if (i != s){
	        if(PermanentementeEtiquetado[i] == true){
               cout << "El camino  " << s+ 1 << " a " << i +1 << " es: ";
			   MostrarCamino(s,i,pred);
			   cout << i + 1 << " con coste " << d[i] << endl;
			   }
            else
               cout <<"No hay camino desde: " << s + 1 <<" a " << i + 1 <<endl;
         }
	  }
   }


void GRAFO::BellmanFordMoore(){
  vector<int> d;
   vector<unsigned> pred;
   unsigned s, numeromejoras = 0;
   bool mejora;
   //Idem que en el algoritmo de Dijkstra
   d.resize(n,maxint);
   pred.resize(n,UERROR);
   cout << endl;
   cout << "Caminos minimos: Bellman ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â€šÂ¬Ã…â€œ Ford - Moore" << endl;
   cout << "Nodo de partida? [1-"<< n << "]: ";
   cin >> (unsigned &) s;
   s--;
   d[s]=0; pred[s]=s;
   do{
      mejora = false;
       for (unsigned i = 0; i < n; i++){
          for (unsigned k = 0; k < LS[i].size(); k++){ //Recorremos los sucesores.
            if (( d[LS[i][k].j]) > (d[i] + LS[i][k].c)){   //Si la distancia de los sucesores, es mayor que la distancia del candidato mÃƒÆ’Ã‚Â¡s el coste.
	       d[LS[i][k].j] = (d[i] + LS[i][k].c); //Sustituimos la nueva distancia por el valor que nos dio la suma anterior.
               pred[LS[i][k].j] = i; //El predecesor es el nuevo candidato.*/
               numeromejoras++;
               mejora = true;
               }
         }
    }

   }while ((numeromejoras <= n + 1) && (mejora == true));
       cout << numeromejoras << endl;
	   for (unsigned i = 0; i < n; i++)
	    cout << pred[i] << endl;
   if (mejora == true)
        cout << "Ciclo negativo" << endl;
    else {
        cout << "Solucion" << endl;
      for (unsigned i = 0; i < n; i++){
	     if (i!=s){
		    if (pred[i]!= UERROR){
               cout << "El camino  " << s+ 1 << " a " << i +1 << " es: ";
	           MostrarCamino(s,i,pred);
		       cout << i + 1 << endl;
	        }
            else
               cout <<"No hay camino desde: " << s + 1 <<" a " << i + 1 <<endl;
        }
	}
   }
}
   //para salir del bucle, si mejora es true, pues hay un ciclo, pues hemos realizado n+1 veces la relajacion con mejora; si mejora es false, pues tenemos solucion
   //Mostramos los caminos mÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â­nimos que se puedan haber encontrado, o advertimos de la existencia de un ciclo de coste negativo.


GRAFO::~GRAFO(){


}
