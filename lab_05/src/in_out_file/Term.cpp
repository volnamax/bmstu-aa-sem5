//
// Created by User on 10.12.2023.
//

#include "Term.h"

std::ostream &operator<<(std::ostream &os, const Term &term) {
    os << term.getTerm() << ": " << term.getTfIdf();
    return os;
}
