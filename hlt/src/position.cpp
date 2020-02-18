#include "position.hpp"

#include <string>

Position::Position() : m_coordX(0), m_coordY(0) {}

Position::Position(const int x, const int y) : m_coordX(x), m_coordY(y) {}

void Position::updatePos(const Position &new_pos)
{
  m_coordX = new_pos.m_coordX;
  m_coordY = new_pos.m_coordY;
}

std::string Position::to_string() const
{
  return "(" + std::to_string(m_coordX) + "," + std::to_string(m_coordY) + ")";
}

// Getter
Position Position::getPos() const
{
  return Position(m_coordX, m_coordY);
}

int Position::getXCoord() const
{
  return m_coordX;
}

int Position::getYCoord() const
{
  return m_coordY;
}

// Operator
bool Position::operator==(const Position &other) const
{
  return m_coordX == other.m_coordX && m_coordY == other.m_coordY;
}

bool Position::operator!=(const Position &other) const
{
  return m_coordX != other.m_coordX || m_coordY != other.m_coordY;
}

std::ostream &Position::operator<<(std::ostream &out)
{
  out << m_coordX << ' ' << m_coordY;

  return out;
}

std::istream &Position::operator>>(std::istream &in)
{
  in >> m_coordX >> m_coordY;

  return in;
}