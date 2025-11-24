#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

class Feedback {
    std::string message;

public:
    void input();
    void show() const;
};

#endif
