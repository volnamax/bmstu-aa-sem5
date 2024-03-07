//
// Created by User on 10.12.2023.
//

#include "io.h"

std::vector<Document> readDocumentsFromCSV(const std::string &filename) {
    std::vector<Document> documents;
    std::unordered_map<std::string, Document> documentsMap;
    std::ifstream file(filename);
    std::string line;
    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cerr << "Err open file: " << filename << std::endl;
        return documents; // Возвращаем пустой вектор
    }
    std::getline(file, line); // Пропустить заголовок

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string name_doc, term;
        double tf_idf;

        std::getline(lineStream, name_doc, ',');
        std::getline(lineStream, term, ',');
        lineStream >> tf_idf;

        // Создать новый документ или получить существующий
        auto &doc = documentsMap[name_doc];
        doc.setNameDoc(name_doc);
        doc.addTerm(Term(term, tf_idf));
    }

    // Копирование документов из map в вектор
    for (auto &pair: documentsMap) {
        documents.push_back(pair.second);
    }

    return documents;
}

bool areVectorsEqual(const std::vector<double> &vec1, const std::vector<double> &vec2, double epsilon = 1e-6) {
    if (vec1.size() != vec2.size()) {
        return false;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        if (std::abs(vec1[i] - vec2[i]) > epsilon) {
            return false;
        }
    }

    return true;
}


using json = nlohmann::json;

// Функция для записи результатов кластеризации в файл JSON
void saveClustersToJson(const std::vector<Cluster> &clusters,
                        const std::vector<Document> &documents,
                        const std::string &filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl;
        return;
    }

    double epsilon = 0.0001; // Погрешность для сравнения векторов

    json j;

    for (size_t i = 0; i < clusters.size(); ++i) {
        json clusterJson;
        for (const auto &clusterPoint: clusters[i].points) {
            for (const auto &doc: documents) {
                if (areVectorsEqual(doc.getTermsVector(), clusterPoint, epsilon)) {
                    clusterJson.push_back(doc.getNameDoc());
                    break;
                }
            }
        }
        j["Кластер " + std::to_string(i + 1)] = clusterJson;
    }

    outFile << j.dump(4); // Запись с отступами для лучшей читаемости
    outFile.close();
}
