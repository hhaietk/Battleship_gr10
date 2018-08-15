/**
  * @file button.hpp
  * @brief Header of class Button
  * @author J. Hager
  * */


#ifndef BUTTON_H
#define BUTTON_H

#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <vector>


/// @brief Class Button
class Button : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructor: initializes Button
     * @param x: x coordinate
     * @param y: y coordinate
     */
    Button(int x, int y);

    /// @brief Declaration of friend class: BoardSquare
    friend class BoardSquare;

    /// @param public member x_pos for x coordinate
    int x_pos;

    /// @param public member y_pos for y coordinate
    int y_pos;

};

#endif // BUTTON_H
