//
// Created by User on 10.12.2023.
//
#ifndef CPP_DOCUMENT_H
#define CPP_DOCUMENT_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>


#include "Term.h"

class Document {
public:
    std::string name_doc;
    std::vector<Term> terms;

    Document() {}

    Document(std::string name_doc_) : name_doc(name_doc_) {}

    void addTerm(const Term &term) {
        terms.push_back(term);
    }

    std::string getNameDoc() const { return name_doc; }

    void setNameDoc(const std::string &newName) {
        name_doc = newName;  // Правильное присваивание значения
    }

    const std::vector<Term> &getTerms() const { return terms; }

    friend std::ostream &operator<<(std::ostream &os, const Document &doc);

    std::vector<double> getTermsVector() const;


    void setTermsVector(const std::vector<double> &new_tf_idf_vector);


};

void standardizeDocumentLengths(std::vector<Document> &documents);

#endif //CPP_DOCUMENT_H
