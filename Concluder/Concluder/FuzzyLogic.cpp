#include "FuzzyLogic.h"


FuzzyLogic::FuzzyLogic(){}

FuzzyLogic::FuzzyLogic(FuzzyVariable& variable)
{
    setOutputVariable(variable);
}

void FuzzyLogic::setGraduation()
{
    float width = _axis.horizontal.getSize().x;
    float ratio = width / _outputVar->getRange().getElementsNum();
    if (ratio >= 5) {
        _pixelSpace = ratio;
        _realSpace = _pixelSpace;
    }
    int j = 0;
    for (float i = 0; i <= width; i += _pixelSpace, ++j) {
        _axis.graduations.push_back(sf::RectangleShape({ 1, 10 }));
        _axis.graduations[j].setPosition(i, 295);
        _axis.graduations[j].setFillColor(sf::Color(185, 185, 185, 255));
    }
}

void FuzzyLogic::setVerticalAxis() 
{
    if(_outputVar->getRange().getUpper() >= 0){
        int lowerRange = _outputVar->getRange().getLower();
        int upperRange = _outputVar->getRange().getUpper();
    for (int i = lowerRange, j = 0; i < upperRange; ++i, ++j) 
        if (i == 0) 
            _axis.vertical.setPosition(_axis.graduations[j].getPosition().x, 100);
        
    }
}

void FuzzyLogic::setOutputVariable(FuzzyVariable& variable) 
{
    _outputVar = &variable;
    setGraduation();
    setVerticalAxis();
    setTermOnAxis();
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
            _shapes[i].points[j] = sf::Vertex({ getPixelXPosition(i, nodes[j]), pointsY[j] });
        }
        for (auto &x : _shapes[i].points) {
            x.color = sf::Color::Black;
        }
    }
}

float FuzzyLogic::getPixelXPosition(int index, int node)
{
    float x = _outputVar->getTerm(index).nodes[node] * _pixelSpace;
    return x + _axis.vertical.getPosition().x;
}

float FuzzyLogic::getPixelXPosition(float value)
{
    float x = value * _pixelSpace;
    return x + _axis.vertical.getPosition().x;
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
    for (auto &x : _axis.graduations) {
        window.draw(x);
    }
    window.draw(_axis.horizontal);
    window.draw(_axis.vertical);
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
            outDiagram.push_back(sf::ConvexShape());
            outDiagram.back().setPointCount(4);
            outDiagram.back().setFillColor(sf::Color::Red);
            outDiagram.back().setPoint(0, { getPixelXPosition(i, 0), 300 });
            float y = (_outputVar->getTerm(i).value);
            float crossPoint = _outputVar->getTerm(i).getCrossPointY(1, 0, y);
            outDiagram.back().setPoint(1, { getPixelXPosition(crossPoint), 300-(y*200) });
            crossPoint = _outputVar->getTerm(i).getCrossPointY(2, 3, y);
            outDiagram.back().setPoint(2, { getPixelXPosition(crossPoint), 300- (y * 200) });
            outDiagram.back().setPoint(3, { getPixelXPosition(i, 3), 300 });
        }
    }
}

float FuzzyLogic::getLOMValue()
{
    LOM_Value = 0;
    for (auto& x : outDiagram) {
        float checkLOM = x.getPoint(2).x;;
        if (checkLOM > LOM_Value)
            LOM_Value = checkLOM;
    }
    LOM_Value -= _axis.vertical.getPosition().x;
    return LOM_Value/_pixelSpace;
}