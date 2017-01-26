#pragma once
#include <string>
#include <iostream>
#include <vector>

class Range
{
public:
    int getLower() {
        return lower;
    }
    int getUpper() {
        return upper;
    }
    Range() {
        lower = 0;
        upper = 0;
    }
    Range(int lower, int upper) {
        setRange(lower, upper);
    }
    void setRange(int lower, int upper) {
        if (upper >= lower) {
            this->upper = upper;
            this->lower = lower;
        }
        else {
            this->upper = lower;
            this->lower = upper;
        }
    }
    int getElementsNum() {
        return upper - lower;
    }
private:
    int upper;
    int lower;
};

struct Term {
    std::string name;
    std::vector<float> nodes;
    
    float value;
    Term() {}
    Term(std::string name, float node1, float node2, float node3, float node4) {
        this->name = name;
        nodes = { node1, node2, node3, node4 };
    }

    float getPct(float xValue) {
        for (int i = 0; i < nodes.size(); ++i) 
            if(nodes[i] <= xValue && nodes[i+1] >= xValue)
                return getCrossPointX(i, i + 1, xValue);
        return 0;
    }

    float getCrossPointX(int nodeNumber1, int nodeNumber2, float xValue) {
        float a = (nodesY[nodeNumber2] - nodesY[nodeNumber1]) /
            (nodes[nodeNumber2] - nodes[nodeNumber1]);
        float b = nodesY[nodeNumber2] - a*nodes[nodeNumber2];
        return a*xValue + b;
    }

    float getCrossPointY(int nodeNumber1, int nodeNumber2, float yValue) {
        float a = (nodesY[nodeNumber2] - nodesY[nodeNumber1]) /
            (nodes[nodeNumber2] - nodes[nodeNumber1]);
        float b = nodesY[nodeNumber2] - a*nodes[nodeNumber2];
        return (yValue-b)/a;
    }
private:
    float nodesY[4] = { 0, 1, 1, 0 };
};

class FuzzyVariable
{
    std::string _name;
    Range _range;
    std::vector<Term> _terms;
    int _value;

public:
    FuzzyVariable();
    FuzzyVariable(std::string name, Range range);

    size_t getTermsSize();
    Term& getTerm(size_t index);
    Term& getTerm(std::string termName);
    float getTermPct(std::string termName);
    void addTerm(std::string name, float node1, float node2, float node3, float node4);
    void addTerm(Term term);

    std::string getName();
    Range getRange();
    int getValue();
    void setRange(Range range);
    void setName(std::string name);
    void setValue(int value);
};

