#pragma once

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