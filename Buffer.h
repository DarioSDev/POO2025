//
// Created by Correia, Jose Bastos on 03/12/2024.
//

#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
    char * buffer;
    int lines;
    int columns;
    int linePos;
    int columnPos;

    int getIndex(int lines, int column) const;

public:

    Buffer(int lines, int columns);

    Buffer();

    ~Buffer();

    void clear();

    void render() const;

    void moveCursor(int line, int column);

    // TODO: MAKE OVERLOAD LATER
    void insertChar(char c);

    // TODO: MAKE OVERLOAD LATER
    void insertString(const char *str);

    // TODO: MAKE OVERLOAD LATER
    void insertNum(int num);

    // TODO: MAKE OVERLOAD LATER
    Buffer& operator<<(char c);

    // TODO: MAKE OVERLOAD LATER
    Buffer& operator<<(const char* str);

    // TODO: MAKE OVERLOAD LATER
    Buffer& operator<<(int num);

};

#endif //BUFFER_H
