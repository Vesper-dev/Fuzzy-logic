#include "FuzzyVariable.h"


FuzzyVariable::FuzzyVariable(){}

FuzzyVariable::FuzzyVariable(std::string name, Range range)
{
    _range = range;
    _name = name;
}

size_t FuzzyVariable::getTermsSize() {
    return _terms.size();
}

Range FuzzyVariable::getRange() {
    return _range;
}

void FuzzyVariable::setRange(Range range) {
    _range = range;
}

std::string FuzzyVariable::getName() {
    return _name;
}

void FuzzyVariable::setName(std::string name) {
    _name = name;
}

void FuzzyVariable::addTerm(std::string name, float node1, float node2, float node3, float node4) {
    _terms.push_back(Term(name, node1, node2, node3, node4));
}

void FuzzyVariable::addTerm(Term term) {
    _terms.push_back(term);
}

Term& FuzzyVariable::getTerm(size_t index) {
    return _terms[index];
}

Term& FuzzyVariable::getTerm(std::string termName) {
    for (auto& x : _terms)
        if (x.name == termName)
            return x;

    std::cout << "Term does not exist\n";
    return _terms[0];
}

void FuzzyVariable::setValue(int value) {
    _value = value;
}

int FuzzyVariable::getValue() {
    return _value;
}

float FuzzyVariable::getTermPct(std::string termName)
{
    return getTerm(termName).getPct(_value);
}
