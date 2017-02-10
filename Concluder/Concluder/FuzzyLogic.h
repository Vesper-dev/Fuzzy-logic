#pragma once
#include "FuzzyVariable.h"
#include "Axis.h"


struct Shape{
    sf::Vertex points[6];
    int size() {
        return 6;
    }
};

struct Rules {
    std::string _inputValue1, _inputValue2, _outputValue;
    Rules(std::string inputValue1, std::string inputValue2, std::string outputValue) {
        _inputValue1 = inputValue1;
        _inputValue2 = inputValue2;
        _outputValue = outputValue;
    }
    std::string isActive(std::string inputValue1, std::string inputValue2) {
        if (_inputValue1 == inputValue1 && _inputValue2 == inputValue2)
            return _outputValue;
    }
};

class FuzzyLogic
{
    Axis _axis;
    float LOM_Value;
    FuzzyVariable* _outputVar, *_inputVar1, *_inputVar2;
    //std::vector<FuzzyVariable> *_inputVars;

    std::vector<Shape> _shapes;
    std::vector<Rules> _rules;
    std::vector<sf::ConvexShape> outDiagram;
    void setTermOnAxis();
    int getRuleIndex(std::string outputValue);
    void setConclusionMinOnAxis();
    void setOutputDiagram(size_t index);
    void setOutputDiagramPoints(size_t index);

public:
    FuzzyLogic();
    void setOutputVariable(FuzzyVariable& variabe);
    void setInputVariables(std::vector<FuzzyVariable> inputVars);
    void setInputVariables(FuzzyVariable& variabe1, FuzzyVariable& variabe2);
    void addRule(std::string inputArg1, std::string inputArg2, std::string outputArg);
    void setConclusionMIN();
    void draw(sf::RenderWindow& window);

    float getLOMValue();
};

