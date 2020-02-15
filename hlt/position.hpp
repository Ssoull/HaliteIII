#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position
{
private:
  int m_coordX, m_coordY;

public:
  Position();
  Position(const int x, const int y);

  void updatePos(const Position &new_pos);

  std::string to_string() const;

  // Getter
  Position getPos() const;
  int getXCoord() const;
  int getYCoord() const;

  // Operator
  bool operator==(const Position &other) const;
  bool operator!=(const Position &other) const;
  std::ostream &operator<<(std::ostream &out);
  std::istream &operator>>(std::istream &in);
};

#endif