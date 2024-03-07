// иерархическая кластеризации с использованием k-средних

#include <vector>
#include <iostream>
#include <ctime>
#include <mutex>
#include <iomanip> // Для std::setw и std::setfill


#include "in_out_file/Document.h"
#include "in_out_file/io.h"
#include "klasters/Claster.h"
#include "klasters/Klastering.h"

#define ITER 10
#define COUNT_FILE 96


int menu() {
    int choice;
    while (true) {
        std::cout << "\n\t\tMenu\n"
                     "1) Run the sequential version of document clustering.\n"
                     "2) Run the parallel version of document clustering.\n"
                     "3) Perform timing measurements of implemented algorithms.\n"
                     "4) Perform timing measurements of implemented algorithms with one additional thread.\n"
                     "0) Exit.\n\n"
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
    const std::string base_path_in = "D:\\\\sem_5\\\\bmstu_aa\\\\lab_04\\\\vm21u004\\\\src\\\\src_new\\\\data\\\\in\\\\";
    const std::string base_name_in = "tf-idf";
    const std::string file_extension_in = ".csv";
    const std::string file_extension_out = ".json";
    const std::vector<std::string> file_names = generateFileNames(base_path_in, base_name_in, file_extension_in,
                                                                  COUNT_FILE);

    const std::string base_path_out = "D:\\\\sem_5\\\\bmstu_aa\\\\lab_04\\\\vm21u004\\\\src\\\\src_new\\\\data\\\\out\\\\";
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
            parallelDocClustering(file_names, files_out, 8, COUNT_FILE);
            std::cout << "\n\tParallel hierarchical clustering done\t\n";
        }
        else if (choice == 3) {
            // Заголовки столбцов
            std::vector<std::string> headers = {"Number of threads ", "Sequential version (ms)                ",
                                                "Parallel version (ms)                  "};

            // Вывод заголовков
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
            for (const auto &header: headers) {
                std::cout << "| " << std::left << std::setw(19) << header;
            }
            std::cout << "|\n";
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";

            for (int num_threads = 1; num_threads <= COUNT_FILE; ++num_threads) {
                std::chrono::nanoseconds start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch());

                for (int i = 0; i < ITER; ++i) {
                    sequentialVersionDocumentClustering(COUNT_FILE, file_names, files_out);
                }
                std::chrono::nanoseconds end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch());
                long long seqDuration = (end - start).count();

                auto start_ = std::clock();
                for (int i = 0; i < ITER; ++i) {
                    parallelDocClustering(file_names, files_out, num_threads, COUNT_FILE);
                }
                auto stop = std::clock();
                double res_time_without_mt = (double) (stop - start_) / (CLOCKS_PER_SEC) / ITER * 1e3;


                std::cout << "| " << std::left << std::setw(19) << num_threads << "| "
                          << std::setw(39) << seqDuration / ITER / 1000000 << "| "
                          << std::setw(38) << res_time_without_mt / ITER << "|\n";
            }
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
        }
        else if (choice == 4) {
            // Заголовки столбцов
            std::vector<std::string> headers = {"Count file ", "Sequential version (ms)                ",
                                                "Parallel version with one additional thread (ms)"};

            // Вывод заголовков
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
            for (const auto &header: headers) {
                std::cout << "| " << std::left << std::setw(19) << header;
            }
            std::cout << "|\n";
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";

            for (int count_f = 1; count_f <= COUNT_FILE; ++count_f) {
                std::chrono::nanoseconds start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch());

                for (int i = 0; i < ITER; ++i) {
                    sequentialVersionDocumentClustering(count_f, file_names, files_out);
                }
                std::chrono::nanoseconds end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch());
                long long seqDuration = (end - start).count();

                auto start_ = std::clock();
                for (int i = 0; i < ITER; ++i) {
                    parallelDocClustering(file_names, files_out, 2, count_f);
                }
                auto stop = std::clock();
                double res_time_without_mt = (double) (stop - start_) / (CLOCKS_PER_SEC) / ITER * 1e3;


                std::cout << "| " << std::left << std::setw(19) << count_f << "| "
                          << std::setw(39) << seqDuration / ITER / 1000000 << "| "
                          << std::setw(38) << res_time_without_mt  << "|\n";
            }
            std::cout
                    << "+--------------------+----------------------------------------+----------------------------------------+\n";
        }
        else if (choice == 0)
            return 0;
        else
            std::cout << "Incorect choise menu";
    }
    return 0;

}
