#include <SFML/Graphics.hpp>
#include "FuzzyLogic.h"
#include "Parser.h"

using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 400), "SFML works!");
    Parser parser("Plik.txt");
    Range range1(-50, 100);
    Range range2(-10, 200);
    Range range3(0, 50);
    FuzzyLogic fuzzy;
    FuzzyVariable outputVar("Power", range1);
    outputVar.addTerm("LOW", -20, 25, 25, 50);
    outputVar.addTerm("MEDIUM", 25, 50, 50, 75);
    outputVar.addTerm("HIGH", 50, 75, 75, 100);
    fuzzy.setOutputVariable(outputVar);

    FuzzyVariable inputVar1("Work", range2);
    inputVar1.addTerm("SMALL", -5, 25, 25, 50);
    inputVar1.addTerm("NORMAL", 25, 100, 100, 125);
    inputVar1.addTerm("LARGE", 100, 150, 150, 200);
    inputVar1.setValue(30);

    FuzzyVariable inputVar2("Time", range3);
    inputVar2.addTerm("SHORT", 0, 10, 10, 20);
    inputVar2.addTerm("AVERAGELY", 10, 30, 30, 40);
    inputVar2.addTerm("LONG", 30, 40, 40, 50);
    inputVar2.setValue(15);

    fuzzy.setInputVariables(inputVar1, inputVar2);

    for (int i = 0; i < parser.size(); ++i)
        fuzzy.addRule(parser.get(i).arg1, parser.get(i).arg2, parser.get(i).outcome);

    fuzzy.setConclusionMIN();

    std::cout << "Last of maximum: " <<fuzzy.getLOMValue() << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        fuzzy.draw(window);
        window.display();
    }
}
