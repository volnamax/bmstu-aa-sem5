//
// Created by User on 10.12.2023.
//

#ifndef CPP_TERM_H
#define CPP_TERM_H

#include <vector>
#include <string>
#include <iostream>

class Term {
public:
    Term(std::string term_, double tf_idf_) : term(term_), tf_idf(tf_idf_) {}

    Term() : term(""), tf_idf(0.0) {}  // Конструктор по умолчанию
    void setTfIdf(double new_tf_idf) { tf_idf = new_tf_idf; }

    std::string getTerm() const { return term; }

    double getTfIdf() const { return tf_idf; }

    friend std::ostream &operator<<(std::ostream &os, const Term &term);

private:
    std::string term;
    double tf_idf;
};

#endif //CPP_TERM_H
