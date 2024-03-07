// иерархическая кластеризации с использованием k-средних

#include <vector>
#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>
#include <iomanip> // Для std::setw и std::setfill


#include "in_out_file/Document.h"
#include "in_out_file/io.h"
#include "klasters/Claster.h"
#include "thread/ThreadSafeQueue.h"
#include "klasters/Klastering.h"

#define ITER 1
#define ITER_MIN 1

#define COUNT_FILE 50

#include <string>

#include "thread/Atomic.h"

int menu() {
    int choice;
    while (true) {
        std::cout << "\n\t\tMenu\n"
                     "1. Run the sequential version of document clustering.\n"
                     "2. Run the conveyor version of document clustering.\n"
                     "3. Perform timing measurements of implemented algorithms.\n"
                     "4. Display the tf-idf of documents.\n"
                     "0. Exit.\n\n"
                     "Select an option (0-4): ";

        // Reading the user input
        std::cin >> choice;

        // Check if input is an integer and within the valid range
        if (std::cin.fail() || choice < 0 || choice > 4) {
            std::cout << "Invalid input. Please enter a number between 0 and 4.\n";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        }
        else {
            break; // Valid input
        }
    }

    std::cout << std::endl;
    return choice;
}

void
sequentialVersionDocumentClustering(int count_f, const std::vector<std::string> filenames,
                                    const std::vector<std::string> filenames_out) {
    std::vector<Document> documents;
    std::vector<Cluster> clusters;
    for (int i = 0; i < count_f; ++i) {

        documents = readDocumentsFromCSV(filenames[i]);
        standardizeDocumentLengths(documents);

        // Выполнение иерархической кластеризации
        clusters = hierarchicalClustering(documents, MAX_DEPTH);

        // Сохранение результатов кластеризации в файл
        saveClustersToJson(clusters, documents, filenames_out[i]);
        documents.clear();
        clusters.clear();
    }

}

std::vector<std::string>
generateFileNames(const std::string &base_path, const std::string &base_name, const std::string &file_extension,
                  int count) {
    std::vector<std::string> file_names;
    file_names.reserve(count);

    for (int i = 0; i < count; ++i) {
        file_names.push_back(base_path + base_name + std::to_string(i) + file_extension);
    }

    return file_names;
}

int main() {
    const std::string base_path_in = "D:\\\\sem_5\\\\bmstu_aa\\\\lab_05\\\\tmp\\\\vm21u004\\\\src\\\\data\\\\in\\\\";
    const std::string base_name_in = "tf-idf";
    const std::string file_extension_in = ".csv";
    const std::string file_extension_out = ".json";
    const std::vector<std::string> file_names = generateFileNames(base_path_in, base_name_in, file_extension_in,
                                                                  COUNT_FILE);

    const std::string base_path_out = "D:\\\\sem_5\\\\bmstu_aa\\\\lab_05\\\\tmp\\\\vm21u004\\\\src\\\\data\\\\out\\\\";
    const std::string base_name_out = "clustering-doc";
    const std::vector<std::string> files_out = generateFileNames(base_path_out, base_name_out, file_extension_out,
                                                                 COUNT_FILE);


    int choice = 0;

    while ((choice = menu())) {
        if (choice == 1) {
            sequentialVersionDocumentClustering(COUNT_FILE, file_names, files_out);
            std::cout << "\n\tSequential hierarchical clustering done\t\n";
        }
        else if (choice == 2) {
            AtomicQueue<Request> completedRequests;
            run_pipeline(file_names, files_out, COUNT_FILE, completedRequests);
            createReport(completedRequests);
            std::cout << "\n\tConveyor hierarchical clustering done\t\n";
        }
        else if (choice == 3) {

            // Заголовки столбцов
            std::vector<std::string> headers = {"Count File (request)", "Sequential version (ms)                ",
                                                "Conveyor version (ms)                 "};

            // Вывод заголовков
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
            for (const auto &header: headers) {
                std::cout << "| " << std::left << std::setw(21) << header;
            }
            std::cout << "|\n";
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
            AtomicQueue<Request> completedRequests;

            for (int count_f_i = 1; count_f_i <= COUNT_FILE; ++count_f_i) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < ITER; ++i) {
                    sequentialVersionDocumentClustering(count_f_i, file_names, files_out);
                }
                auto end = std::chrono::high_resolution_clock::now();
                long long seqDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < ITER; ++i) {
                    run_pipeline(file_names, files_out, count_f_i, completedRequests);
                }
                end = std::chrono::high_resolution_clock::now();
                long long convDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                std::cout << "| " << std::left << std::setw(21) << count_f_i << "| "
                          << std::setw(39) << seqDuration / ITER << "| "
                          << std::setw(38) << convDuration / ITER << "|\n";
            }
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";

        }
        else if (choice == 4) {
            std::vector<Document> documents = readDocumentsFromCSV(file_names[0]);
            for (const auto &doc: documents) {
                std::cout << doc << std::endl;
            }
        }
        else if (choice == 0)
            return 0;
        else
            std::cout << "Incorect choise menu";
    }
    return 0;

}
