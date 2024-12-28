//
// Created by Correia, Jose Bastos on 03/12/2024.
//

#include "Buffer.h"
#include <ostream>
#include <iostream>

using namespace std;

int Buffer::getIndex(int lines, int column) const
{
    return lines * columns + column;
}

Buffer::Buffer(int lines, int columns):
lines(lines),
columns(columns),
columnPos(0),
linePos(0)
{
    buffer = new char[lines * columns];
    clear();
}

Buffer::Buffer() {}

Buffer::~Buffer()
{
    delete[] buffer;
    delete[] name;
}

Buffer::Buffer(const Buffer& other)
    : lines(other.lines),
      columns(other.columns),
      columnPos(other.columnPos),
      linePos(other.linePos),
      buffer(new char[other.lines * other.columns]),
      name(other.name ? strdup(other.name) : nullptr) // Duplicate name
{
    // Copy buffer content
    memcpy(buffer, other.buffer, lines * columns);
}

Buffer& Buffer::operator=(const Buffer& other)
{
    if (this == &other) return *this;

    // Clean up existing resources
    delete[] buffer;
    delete[] name;

    // Copy attributes
    lines = other.lines;
    columns = other.columns;
    columnPos = other.columnPos;
    linePos = other.linePos;

    // Allocate and copy buffer
    buffer = new char[lines * columns];
    memcpy(buffer, other.buffer, lines * columns);

    // Copy name
    name = other.name ? strdup(other.name) : nullptr;

    return *this;
}

void Buffer::setName(char * name)
{
    this->name = name;
    cout << "NEW NAME " << this->name << endl;
}

const char * Buffer::getName()
{
    return name;
}


void Buffer::clear()
{
    fill_n(buffer, lines * columns, '.');
}

void Buffer::render() const
{
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << buffer[getIndex(i, j)];
        }
        cout << '\n';
    }
}

void Buffer::moveCursor(int line, int column)
{
    if (line >= 0 && column < lines && column >= 0 && column < columns) {
        linePos = line;
        columnPos = column;
    }
}

void Buffer::insertChar(char c)
{
    if (linePos >= 0 && linePos < lines && columnPos >= 0 && columnPos < columns) {
        buffer[getIndex(linePos, columnPos)] = c;
        ++columnPos;
    }
}

void Buffer::insertString(const char* str)
{
    while (*str)
    {
        insertChar(*str++);
    }
}

void Buffer::insertNum(int num)
{
    string str = to_string(num); //precisa de cast
    insertString(str.c_str());
}

Buffer & Buffer::operator<<(char c)
{
    insertChar(c);
    return *this;
}

Buffer& Buffer::operator<<(const char* str)
{
    insertString(str);
    return *this;
}

Buffer& Buffer::operator<<(int num)
{
    insertNum(num);
    return *this;
}


