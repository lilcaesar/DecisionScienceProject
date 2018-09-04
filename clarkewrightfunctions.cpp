#include "clarkewrightfunctions.h"

#include<math.h>
#include<bits/stdc++.h>

//Funzione per definire l'ordine inverso utilizzato nella sort dei savings
bool sortinrev(const std::pair<float,std::pair<int,int>> &a,
               const std::pair<float,std::pair<int,int>> &b)
{
    return (a.first > b.first);
}

//Funzione per eliminare il primo valore del vettore
template<typename T>
void pop_front(std::vector<T>& vec)
{
    //assert(!vec.empty());
    vec.erase(vec.begin());
}

void computeDistanceTable(const std::vector<std::pair<int, int> > &coordinates, std::vector<std::vector<float>> &distances){
    //Dichiaro un vettore delle distanze della stessa dimensione del vettore delle coordinate
    unsigned long dimension = coordinates.size();
    distances.resize(dimension);
    for(unsigned long i=0; i<dimension;i++){
        //Per ogni riga definisco la sua lunghezza come dimensione del vettore delle coordinate
        //Ottengo così un vettore bidimensionale n*n
        distances[i].resize(dimension);
        //Per ogni elemento j della riga i calcolo la distanza tra i e j nel vettore delle coordinate
        for(unsigned long j=0; j<dimension;j++){
            //Utilizzo questo if per evitare eccezzioni e risparmiare operazioni
            if(i == j){
                distances[i][j]=0;
            }else{
                distances[i][j]=sqrtf(static_cast<float> (pow((coordinates[i].first)-(coordinates[j].first),2.0) +
                                                          pow((coordinates[i].second)-(coordinates[j].second),2.0)));
            }
        }
    }
}

void computeSavingsTable(const std::vector<std::vector<float>> &distances, std::vector<std::vector<float>> &savings, std::vector<std::pair<float,std::pair<int,int>>> &list){
    //Dichiaro un vettore dei savings della stessa dimensione del vettore delle distanze
    unsigned long dimension = distances.size();
    savings.resize(dimension-1);
    for(unsigned long i=0; i<dimension-1;i++){
        //Per ogni riga definisco la sua lunghezza come dimensione del vettore delle distanze
        //Ottengo così un vettore bidimensionale n*n
        savings[i].resize(dimension);        
        //Per ogni elemento j della riga i calcolo il saving tra i e j nel vettore delle distanze
        for(unsigned long j=0; j<dimension;j++){
            //La prima riga è formata da 0 e la matrice è triangolare superiore
            if((i==0)||(j<=i)){
                savings[i][j]=0;
            }else{
                //Per i valori diversi da 0 calcoliamo per la riga i colonna j il risultato dell'operazione
                // (d(0,i)*2 + d(0,j)*2) -(d(0,i) + d(0,j) + d(i,j))
                savings[i][j]= (distances[0][i]*2 + distances[0][j]*2)-(distances[0][i]+distances[0][j]+distances[i][j]);
            }
        }
    }

    //Lista temporanea di savings da ordinare
    std::vector<std::pair<float,std::pair<int,int>>> temporaryList;

    for(unsigned long i = 1; i<savings.size(); i++){
        for(unsigned long j= i+1; j<savings.size()+1; j++){
            temporaryList.push_back(std::make_pair(savings[i][j],std::make_pair(i,j)));
        }
    }

    //Ordinamento descrescente
    sort(temporaryList.begin(), temporaryList.end(), sortinrev);

    //Assegnamento della lista aggiungendo le copie speculari per ottenere:
    //Es. 1-5, 5-1, 4-2, 2-4 ecc...
    for(unsigned long i=0; i<temporaryList.size(); i++){
        list.push_back(temporaryList[i]);
        list.push_back(std::make_pair(temporaryList[i].first, std::make_pair(temporaryList[i].second.second, temporaryList[i].second.first)));
    }
}

//Creazione di un vettore iniziale 010, 020, 030,...,0(n-1)0
//Da notare che dimension deve essere già assegnato come n-1
void createInitialRoutes(std::vector<std::vector<int> > &routes, unsigned long dimension){
    for(unsigned long i = 0; i < dimension; i++){
        std::vector<int> row;
        row.push_back(0);
        row.push_back(i+1);
        row.push_back(0);
        routes.push_back(row);
    }
}

void sequentialClarkeAndWright(const std::vector<int> &demand, std::vector<std::pair<float, std::pair<int, int> > > &sequentialList, std::vector<std::vector<int>> &routes){
    //Indice della route su cui stiamo operando
    unsigned long routeIndex=0;
    //Capienza rimanente per la route corrente
    int capacity;
    //Finchè la lista dei savings non e vuota e l'indice della route non supera il numero di routes
    while ((!sequentialList.empty())&&(routeIndex<routes.size())) {
        bool found = false;
        bool isFirst = false;
        //Inizializzo la capienza della route
        capacity=100 - demand[routes[routeIndex][1]];
        //Indice del saving su cui stiamo operando
        unsigned long savingIndex=0;
        //Finchè c'è ancora capienza disponibile
        while(capacity > 0){
            //Se abbiamo trovato un saving compatibile aggiorno la route
            if(found){
                //Salvo le informazioni riguardo al valore in comune e a quello da aggiungere alla route
                int foundValue;
                int addedValue;
                //Elimino lo 0 finale
                routes[routeIndex].pop_back();
                //A seconda di dove si trova il nuovo valore da aggiungere lo inserisco nella route
                if(isFirst){
                    foundValue=sequentialList[savingIndex].second.first;
                    addedValue=sequentialList[savingIndex].second.second;
                    routes[routeIndex].push_back(addedValue);
                }else{
                    foundValue=sequentialList[savingIndex].second.second;
                    addedValue=sequentialList[savingIndex].second.first;
                    routes[routeIndex].push_back(addedValue);
                }
                //Riaggiungo lo 0 finale
                routes[routeIndex].push_back(0);

                //Elimino tutti i saving che contengono il terzultimo valore della route
                //Es. se la route ha 01230 elimino tutti i saving con 2
                for(unsigned long i=0; i<sequentialList.size(); i++){
                    if((sequentialList[i].second.first == foundValue)||(sequentialList[i].second.second == foundValue)){
                        sequentialList.erase(sequentialList.begin() + i);
                        i--; //perchè se eliminiamo una riga e poi incrementiamo saltiamo quella
                        //successiva che potrebbe avere un valore non valido
                    }
                }

                //Cancello la route in cui era presente il valore appena aggiunto
                for(unsigned long i = routeIndex+1; i<routes.size(); i++){
                    if(routes[i][1]==addedValue){
                        routes.erase(routes.begin()+i);
                        i=routes.size();
                    }
                }

                //Aggiorno la capienza rimanente e le variabili di stato
                capacity -= demand[addedValue];
                savingIndex=0;
                found=false;

            }else{//Ricerca del saving compatibile con la rute attuale
                //Se l'indice del saving attuale supera il numero di saving
                if(savingIndex>=sequentialList.size()){
                    //Forziamo il cambiamento di route
                    capacity=-1;

                    //Eliminiamo tutti i saving che contengono l'ultimo valore prima dello zero contenuto nella route attuale
                    for(unsigned long i=0; i<sequentialList.size(); i++){
                        if((sequentialList[i].second.first == routes[routeIndex][routes[routeIndex].size()-2])
                                ||(sequentialList[i].second.second == routes[routeIndex][routes[routeIndex].size()-2])){
                            sequentialList.erase(sequentialList.begin() + i);
                            i--;
                        }
                    }

                }else{//Se invece l'indice del saving risulta valido
                    //Controllo se il l'ultimo valore (escluso lo 0) della route attuale coincide con
                    //il primo o il secondo valore del saving attuale. Nel caso aggiorniamo le variabili di stato relative
                    if((sequentialList[savingIndex].second.first == routes[routeIndex][routes[routeIndex].size()-2])
                            && (capacity-demand[sequentialList[savingIndex].second.second] >= 0)){
                        found=true;
                        isFirst = true;
                    }else if((sequentialList[savingIndex].second.second == routes[routeIndex][routes[routeIndex].size()-2])
                             && (capacity-demand[sequentialList[savingIndex].second.first] >= 0)){
                        found=true;
                        isFirst=false;
                    }else{//Altrimenti aggiorniamo l'indice del saving
                        savingIndex++;
                    }
                }
            }
        }
        //Eliminiamo tutti i saving che contengono l'ultimo valore prima dello zero contenuto nella route attuale
        for(unsigned long i=0; i<sequentialList.size(); i++){
            if((sequentialList[i].second.first == routes[routeIndex][routes[routeIndex].size()-2])
                    ||(sequentialList[i].second.second == routes[routeIndex][routes[routeIndex].size()-2])){
                sequentialList.erase(sequentialList.begin() + i);
                i--;
            }
        }
        //Aggiorniamo l'indice della route
        routeIndex++;
    }
}

void parallelClarkeAndWright(const std::vector<int> &demand, std::vector<std::pair<float, std::pair<int, int> > > &parallelList, std::vector<std::vector<int> > &routes){
    //Creo una lista di routes aggiungendo la capacità relativa ad ognuna di loro
    std::vector<std::pair<std::vector<int>, int>> routesWithCapacity;

    //Assegno la capacità iniziale legata alla domanda della stazione centrale della route
    for(unsigned long i=0; i< routes.size(); i++){
        routesWithCapacity.push_back(std::make_pair(routes[i], demand[i+1]));
    }

    //Indici delle due route che dovremo unire
    unsigned long route1=0;
    unsigned long route2=0;

    //Per ogni elemento ij nella lista ordinata dei savings
    for(unsigned long savingIndex=0; savingIndex< parallelList.size(); savingIndex++){
        bool found = false;

        //Per ogni route presente
        for(unsigned long i=0; i<routesWithCapacity.size(); i++){
            //Cerco la route 0i
            if(parallelList[savingIndex].second.first == routesWithCapacity[i].first[routesWithCapacity[i].first.size()-2]){
                route1=i;
                //Cerco la route j0
                for(unsigned long j=0; j<routesWithCapacity.size(); j++){
                    if(parallelList[savingIndex].second.second == routesWithCapacity[j].first[1]){
                        route2=j;
                        //Se le ho trovate entrambe e non corrispondono alla stessa route
                        if(route1!=route2){
                            //Esco dai for loops
                            found = true;
                            j=routesWithCapacity.size();
                            i=routesWithCapacity.size();
                        }
                    }
                }
            }
        }

        //Se ho trovato le route e la somma delle capacità di esse è inferiore alla capacità massima
        if(((routesWithCapacity[route1].second + routesWithCapacity[route2].second) <=100)&&(found)){
            //effettuo il merge delle due route
            routesWithCapacity[route1].first.pop_back();
            pop_front(routesWithCapacity[route2].first);
            routesWithCapacity[route1].first.insert(routesWithCapacity[route1].first.end(), routesWithCapacity[route2].first.begin(), routesWithCapacity[route2].first.end());
            routesWithCapacity[route1].second+=routesWithCapacity[route2].second;
            routesWithCapacity.erase(routesWithCapacity.begin()+route2);
        }
    }

    //Aggiorno la versione senza capacità delle route
    routes.clear();
    for(unsigned long i = 0; i < routesWithCapacity.size(); i++){
        routes.push_back(routesWithCapacity[i].first);
    }
}

//Data una route restituisce il costo totale basandosi sulla matrice delle distanze
float computeCost(const std::vector<std::vector<float>> &distances, const std::vector<int> &route){
    float cost=0;
    for(unsigned long j=0; j<route.size()-1; j++){
        float c = distances[route[j]][route[j+1]];;
        cost+= c;
    }
    return cost;
}

//Salvo i risultati delle operazioni nei due file
void saveResults(const std::vector<std::vector<float> > &distances, const std::vector<std::vector<int> > &routes, std::ofstream &outputFile, double duration, std::ofstream &finalTableFile, int optimalValue, std::string inputFileName){
    float totalCost=0;
    for(unsigned long i=0; i<routes.size(); i++){
        float cost= computeCost(distances,routes[i]);
        totalCost += cost;
        std::string line = "Route #" + std::to_string(i+1) + " Cost: " + std::to_string(cost) + ",   ";
        for(unsigned long j=0; j<routes[i].size(); j++){
            line += " " + std::to_string(routes[i][j]);
        }
        line+="\n";
        outputFile << line;
    }
    outputFile << "\n" << "Total cost: " + std::to_string(totalCost);
    outputFile << "\n" << "Duration: " + std::to_string(duration) + "s";

    finalTableFile << inputFileName + "   "<< distances.size()-1 << "         " + std::to_string(totalCost) +  "    " << duration << "s" << "     " + std::to_string((totalCost - optimalValue)/optimalValue*100) + "\n";
}
