#include "FuzzyLogic.h"


FuzzyLogic::FuzzyLogic() 
{
    _axis = Axis({ 1000, 200 }, { 0, 300 }, { -50, 100 });
}

void FuzzyLogic::setOutputVariable(FuzzyVariable& variable) 
{
    _outputVar = &variable;
    _axis.setRange(_outputVar->getRange());
    setTermOnAxis();
}

void FuzzyLogic::setInputVariables(std::vector<FuzzyVariable> inputVars)
{
    //_inputVars->swap(inputVars);
}

void FuzzyLogic::setInputVariables(FuzzyVariable& variabe1, FuzzyVariable& variabe2)
{
    _inputVar1 = &variabe1;
    _inputVar2 = &variabe2;
}

void FuzzyLogic::setTermOnAxis() 
{
    float pointsY[6] = { 300, 100, 100, 100, 100, 300 };
    float nodes[6] = { 0, 1, 1, 2, 2, 3 };
    for (int i = 0; i < _outputVar->getTermsSize(); ++i) {
        for (int j = 0; j < 6; ++j){
            _shapes.push_back(Shape());
            float pointX = _axis.getX(_outputVar->getTerm(i).nodes[nodes[j]]);
            _shapes[i].points[j] = sf::Vertex({ pointX, pointsY[j] });
        }
        for (auto &x : _shapes[i].points) {
            x.color = sf::Color::Black;
        }
    }
}

void FuzzyLogic::addRule(std::string inputArg1, std::string inputArg2, std::string outputArg)
{
    for (int i = 0; i < _inputVar1->getTermsSize(); ++i) {
        if (_inputVar1->getTerm(i).name == inputArg1) {
            for (int j = 0; j < _inputVar2->getTermsSize(); ++j) {
                if (_inputVar2->getTerm(j).name == inputArg2) {
                    for (int k = 0; k < _outputVar->getTermsSize(); ++k) {
                        if (_outputVar->getTerm(k).name == outputArg) {
                            _rules.push_back(Rules(inputArg1, inputArg2, outputArg));
                            return;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Some or all arguments doesn't exist\n";
}

void FuzzyLogic::draw(sf::RenderWindow& window)
{
    for (auto& x : outDiagram)
        window.draw(x);
    _axis.draw(window);
    for (auto& x : _shapes)
        window.draw(x.points, 6, sf::Lines);
}

void FuzzyLogic::setConclusionMIN()
{
    for (int i = 0; i < _outputVar->getTermsSize(); ++i) {
        std::string outputTerm = _outputVar->getTerm(i).name;
        int index = getRuleIndex(outputTerm);
        float outcome = _inputVar1->getTermPct(_rules[index]._inputValue1)*
            _inputVar2->getTermPct(_rules[index]._inputValue2);
        _outputVar->getTerm(outputTerm).value = outcome;
    }
    setConclusionMinOnAxis();
}

int FuzzyLogic::getRuleIndex(std::string outputValue)
{
    for (int i = 0; i < _rules.size(); ++i) 
        if (_rules[i]._outputValue == outputValue)
            return i;
    std::cout <<"Rule: "<< outputValue << " doesn't exist\n";
    return 0;
}

void FuzzyLogic::setConclusionMinOnAxis()
{
    for (int i = 0; i < _outputVar->getTermsSize(); ++i) {
        if (_outputVar->getTerm(i).value > 0) {
            setOutputDiagram(i);
        }
    }
}

void FuzzyLogic::setOutputDiagram(size_t index)
{
    outDiagram.push_back(sf::ConvexShape());
    outDiagram.back().setPointCount(4);
    outDiagram.back().setFillColor(sf::Color::Red);
    setOutputDiagramPoints(index);
}

void FuzzyLogic::setOutputDiagramPoints(size_t index)
{
    float x = _axis.getX(_outputVar->getTerm(index).nodes[0]);
    float y = _axis.getY(0);
    outDiagram.back().setPoint(0, { x, y });

    x = _axis.getX(_outputVar->getTerm(index).getCrossPointY(1, 0));
    y = _axis.getY(_outputVar->getTerm(index).value);
    outDiagram.back().setPoint(1, { x, y });

    x = _axis.getX(_outputVar->getTerm(index).getCrossPointY(2, 3));
    outDiagram.back().setPoint(2, { x, y });

    x = _axis.getX(_outputVar->getTerm(index).nodes[3]);
    y = _axis.getY(0);
    outDiagram.back().setPoint(3, { x, y });
}

float FuzzyLogic::getLOMValue()
{
    LOM_Value = 0;
    for (auto& x : outDiagram) {
        float checkLOM = x.getPoint(2).x;;
        if (checkLOM > LOM_Value)
            LOM_Value = checkLOM;
    }
    LOM_Value -= _axis.getZeroX();
    return LOM_Value/_axis.getPixelSpace();
}