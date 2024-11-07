#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <iomanip>

struct Posting {
    std::string filename;
    int frequency;
};

struct DictionaryEntry {
    int docCount;
    int postingStartPos;
};

void generateDictionaryAndPostingFiles(const std::map<std::string, std::vector<Posting>>& tokenData) {
    std::ofstream dictFile("diccionario.txt");
    std::ofstream postFile("posting.txt");

    if (!dictFile.is_open() || !postFile.is_open()) {
        std::cerr << "Error al abrir los archivos de salida." << std::endl;
        return;
    }

    int postingPosition = 0;

    dictFile << "Token\tNumDocs\tPostingStartPos" << std::endl;

    for (const auto& [token, postings] : tokenData) {
        dictFile << token << "\t" << postings.size() << "\t" << postingPosition << std::endl;

        for (const auto& posting : postings) {
            postFile << posting.filename << "\t" << posting.frequency << std::endl;
        }

        postingPosition += postings.size();
    }

    dictFile.close();
    postFile.close();
}

void logProcessingTime(const std::string& fileName, std::chrono::duration<double> duration) {
    std::ofstream logFile("a7_matricula.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Archivo: " << fileName << "\tTiempo: " << std::fixed << std::setprecision(5) << duration.count() << " segundos" << std::endl;
        logFile.close();
    } else {
        std::cerr << "Error al abrir el archivo de log." << std::endl;
    }
}

int main() {
    std::map<std::string, std::vector<Posting>> tokenData = {
        {"perro", {{"108.html", 2}, {"005.html", 2}, {"444.html", 4}, {"321.html", 8}}},
        {"gato", {{"049.html", 1}, {"102.html", 1}}},
        {"pato", {{"108.html", 3}, {"444.html", 2}, {"321.html", 6}}}
    };

    auto start = std::chrono::high_resolution_clock::now();
    generateDictionaryAndPostingFiles(tokenData);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    logProcessingTime("Generación de diccionario y posting", duration);

    std::cout << "Archivos generados exitosamente." << std::endl;

    return 0;
}
