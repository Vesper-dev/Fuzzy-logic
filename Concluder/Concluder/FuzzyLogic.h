#pragma once
#include <SFML/Graphics.hpp>
#include "FuzzyVariable.h"


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
    struct Axis {
        sf::RectangleShape horizontal;
        sf::RectangleShape vertical;
        std::vector<sf::RectangleShape> graduations;
        float width, height;
        sf::Vector2f position;

        Axis() {
            position = { 0, 200 };
            width = 1000;
            height = 200;
            horizontal = sf::RectangleShape({ width, 1 });
            horizontal.setPosition(0, 300);
            horizontal.setFillColor(sf::Color::Black);
            vertical = sf::RectangleShape({ 1, height });
            vertical.setFillColor(sf::Color::Black);
        }
    } _axis;
    float _pixelSpace;
    float _realSpace;
    float LOM_Value;
    FuzzyVariable* _outputVar;
    FuzzyVariable* _inputVar1;
    FuzzyVariable* _inputVar2;

    std::vector<Shape> _shapes;
    std::vector<Rules> _rules;
    std::vector<sf::ConvexShape> outDiagram;
    void setGraduation();
    void setVerticalAxis();
    void setTermOnAxis();
    float getPixelXPosition(int index, int node);
    float getPixelXPosition(float value);
    int getRuleIndex(std::string outputValue);
    void setConclusionMinOnAxis();
public:
    FuzzyLogic(FuzzyVariable& variable);
    FuzzyLogic();
    void setOutputVariable(FuzzyVariable& variabe);
    void setInputVariables(FuzzyVariable& variabe1, FuzzyVariable& variabe2);
    void addRule(std::string inputArg1, std::string inputArg2, std::string outputArg);
    void setConclusionMIN();
    void draw(sf::RenderWindow& window);

    float getLOMValue();
};

