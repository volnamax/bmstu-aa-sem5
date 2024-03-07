//
// Created by User on 10.12.2023.
//
#include "Document.h"

std::ostream &operator<<(std::ostream &os, const Document &doc) {
    os << "Document " << doc.getNameDoc() << " has terms: ";
    for (const auto &term: doc.getTerms()) {
        os << term << "; ";
    }
    return os;
}

std::vector<double> Document::getTermsVector() const {
    std::vector<double> termsVector;
    for (const auto &term: terms) {
        termsVector.push_back(term.getTfIdf());
    }
    return termsVector;
}

void Document::setTermsVector(const std::vector<double> &new_tf_idf_vector) {
    size_t newSize = new_tf_idf_vector.size();
    if (newSize < terms.size()) {
        terms.resize(newSize);  // Обрезаем вектор terms, если он длиннее нового вектора TF-IDF
    }
    for (size_t i = 0; i < newSize; ++i) {
        if (i < terms.size()) {
            terms[i].setTfIdf(new_tf_idf_vector[i]);  // Обновляем существующие термины
        }
        else {
            terms.push_back(Term("unknown_term", new_tf_idf_vector[i]));
        }
    }
}



void standardizeDocumentLengths(std::vector<Document> &documents) {
    if (documents.empty()) return;

    // Найти максимальную длину вектора
    size_t maxLength = 0;
    for (const auto &doc: documents) {
        maxLength = std::max(maxLength, doc.getTermsVector().size());
    }

    // Дополнить все вектора до максимальной длины нулями
    for (auto &doc: documents) {
        std::vector<double> termsVector = doc.getTermsVector();
        if (termsVector.size() < maxLength) {
            termsVector.resize(maxLength, 0.0); // Дополнение нулями
            // Обновить вектор TF-IDF в документе
            doc.setTermsVector(termsVector);
        }
    }
}
//
//void standardizeDocumentLengths(std::vector<Document> &documents) {
//    if (documents.empty()) return;
//
//    // Найти минимальную длину вектора
//    size_t minLength = std::numeric_limits<size_t>::max();
//    for (const auto &doc: documents) {
//        minLength = std::min(minLength, doc.getTermsVector().size());
//    }
//
//    // Обрезать все вектора до минимальной длины
//    for (auto &doc: documents) {
//        std::vector<double> termsVector = doc.getTermsVector();
//        if (termsVector.size() > minLength) {
//            termsVector.resize(minLength);
//            // Обновите вектор TF-IDF в документе
//            doc.setTermsVector(termsVector);
//        }
//    }
//}
