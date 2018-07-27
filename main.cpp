#include <experimental/filesystem>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

#include <genericfunctions.h>
#include <clarkewrightfunctions.h>

int main()
{
    //Vettore delle coordinate (l'indice del vettore indica la stazione, 0 è il magazzino)
    std::vector<std::pair<int,int>> coordinates;
    //Vettore delle domande (anche qui indice indica stazione e il magazzino ha 0 come valore)
    std::vector<int> demand;
    /*Vettore bidimensionale n*n delle distanze tra le stazioni (riga i e colonna j hanno
     * lo stesso valore di riga j e colonna i)
     */
    std::vector<std::vector<float>> distances;
    /*Vettore bidimensionale n*n dei savings (è una triangolare superiore con 0 nella prima riga e
     * per gli altri valori abbiamo il valore del saving calcolato sulla matrice delle distanze
    */
    std::vector<std::vector<float>> savings;

    //Path in cui è presente la cartella dei file di input
    std::string path = "/root/Scrivania/DecisionScienceProjectData";

    //File della tabella complessiva
    std::string finalTableFileName = "output/FINAL_TABLE.txt";
    std::ofstream finalTableFile(finalTableFileName);

    //Prima riga della tabella complessiva
    finalTableFile << "Name       Clients    O.F.    Duration     Gap\n\n";

    //Scorriamo ogni file presente nella cartella di input
    for(const std::experimental::filesystem::directory_entry & p : std::experimental::filesystem::directory_iterator(path)){
        //valore ottimale previsto nel file
        int optimalValue;
        //Parsing delle coordinate, delle domande e dell'optimal value dal file di input
        parseInitialFile(p, coordinates, demand, optimalValue);

        //Calcolo della tabella delle distanze basata sul vettore delle distanze
        computeDistanceTable(coordinates,distances);

        /*Dichiaro e popolo le liste ordinate dei savings (per effettuare una sola volta
         * il calcolo richiamo il costruttore per copia nella lista parallela)
         */
        std::vector<std::pair<float,std::pair<int,int>>> sequentialList;
        computeSavingsTable(distances, savings, sequentialList);
        std::vector<std::pair<float,std::pair<int,int>>> parallelList(sequentialList);

        //Dichiaro il file di output relativo al file attuale
        boost::filesystem::path temporaryFilePath(p.path().string());
        std::string outputFileName = "output/solution-" + temporaryFilePath.stem().string() + ".txt";
        std::ofstream outputFile(outputFileName);

        //Creazione delle route iniziali (010, 020,..., 0(n-1)0)
        std::vector<std::vector<int>> routes;
        createInitialRoutes(routes, distances.size()-1);

        //Dichiaro un clock per la misurazione del tempo impiegato nelle fasi di calcolo
        std::clock_t start;
        double duration;

        start = std::clock();

        //Calcolo le route relative al Clarke and Wright sequenziale
        sequentialClarkeAndWright(demand, sequentialList, routes);

        duration = ( std::clock() - start ) / static_cast<double>(CLOCKS_PER_SEC);

        outputFile << "Sequential\n";
        finalTableFile << "Sequential\n";

        //Salvo i valori ottenuti nei file
        saveResults(distances, routes, outputFile, duration, finalTableFile, optimalValue, temporaryFilePath.stem().string());

        //Ricreo le route iniziali per utilizzarle nell'algoritmo parallelo
        routes.clear();
        createInitialRoutes(routes, distances.size()-1);
        start = std::clock();


        //Calcolo le route relative al Clarke and Wright sequenziale
        parallelClarkeAndWright(demand, parallelList, routes);

        duration = ( std::clock() - start ) / static_cast<double>(CLOCKS_PER_SEC);


        finalTableFile << "\nParallel\n";

        outputFile << "\n\nParallel\n";

        //Salvo i valori del parallelo nel file
        saveResults(distances, routes, outputFile, duration, finalTableFile, optimalValue, temporaryFilePath.stem().string());

        finalTableFile << "\n\n";

        outputFile.close();

        //Svuoto i vettori per l'utilizzo nella successiva iterazione
        coordinates.clear();
        demand.clear();
        distances.clear();
        savings.clear();
    }

    finalTableFile.close();
    return 0;
}
