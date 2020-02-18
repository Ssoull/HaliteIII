#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "state.hpp"

class IdleState : public State
{
private:
public:
  virtual void update(Ship *shipToUpdate) override;
  virtual void onStateEnter() override;
  virtual void onStateExit() override;
};

#endif