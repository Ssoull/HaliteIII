/* Dstar.cpp
 * James Neufeld (neufeld@cs.ualberta.ca)
 * Compilation fixed by Arek Sredzki (arek@sredzki.com)
 * Source : https://github.com/ArekSredzki/dstar-lite
 */

#include "dstar.hpp"
#include "../utils/log.hpp"

/* void Dstar::Dstar()
 * --------------------------
 * Constructor sets constants.
 */
Dstar::Dstar(int map_size_x, int map_size_y)
{
  mapSizeX = map_size_x;
  mapSizeY = map_size_y;
  maxSteps = 80000; // node expansions before we give up
  C1 = 1;           // cost of an unseen cell
}

/* float Dstar::keyHashCode(state u)
 * --------------------------
 * Returns the key hash code for the state u, this is used to compare
 * a state that have been updated
 */
float Dstar::keyHashCode(state u)
{

  return (float)(u.k.first + 1193 * u.k.second);
}

/* bool Dstar::isValid(state u)
 * --------------------------
 * Returns true if state u is on the open list or not by checking if
 * it is in the hash table.
 */
bool Dstar::isValid(state u)
{

  ds_oh::iterator cur = openHash.find(u);
  if (cur == openHash.end())
    return false;
  if (!close(keyHashCode(u), cur->second))
    return false;
  return true;
}

/* void Dstar::getPath()
 * --------------------------
 * Returns the path created by replan()
 */
list<state> Dstar::getPath()
{
  // std::list<state>::iterator it;
  // for(it = path.begin(); it != path.end()  ; ++it){
  //     hlt::log::log("[Dstar::getPath] Path element n° : x : "+ to_string(it->x)+", y : "+to_string(it->y));
  // }

  return path;
}

/* bool Dstar::occupied(state u)
 * --------------------------
 * returns true if the cell is occupied (non-traversable), false
 * otherwise. non-traversable are marked with a cost < 0.
 */
bool Dstar::occupied(state u)
{

  ds_ch::iterator cur = cellHash.find(u);
  // custom_logger::log("Occupied " + std::to_string(cur == cellHash.end()) + "coord " + std::to_string(u.x) + "," + std::to_string(u.y));
  if (cur == cellHash.end())
    return false;
  return (cur->second.cost < 0);
}

/* void Dstar::init(Position startPos, Position goalPos)
 * --------------------------
 * Init dstar with start and goal position
 * Use the default init at the end :D
 */
void Dstar::init(Position startPos, Position goalPos)
{
  // custom_logger::log("[Dstar::init] StartPos : " + startPos.to_string() + "; GoalPos : " + goalPos.to_string());
  init(startPos.getXCoord(), startPos.getYCoord(), goalPos.getXCoord(), goalPos.getYCoord());
}

/* void Dstar::init(int sX, int sY, int gX, int gY)
 * --------------------------
 * Init dstar with start and goal coordinates, rest is as per
 * [S. Koenig, 2002]
 */
void Dstar::init(int sX, int sY, int gX, int gY)
{

  cellHash.clear();
  path.clear();
  openHash.clear();
  while (!openList.empty())
    openList.pop();

  k_m = 0;

  s_start.x = sX;
  s_start.y = sY;
  s_goal.x = gX;
  s_goal.y = gY;

  cellInfo tmp;
  tmp.g = tmp.rhs = 0;
  tmp.cost = C1;

  cellHash[s_goal] = tmp;

  tmp.g = tmp.rhs = heuristic(s_start, s_goal);
  tmp.cost = C1;
  cellHash[s_start] = tmp;
  s_start = calculateKey(s_start);

  s_last = s_start;
}
/* void Dstar::makeNewCell(state u)
 * --------------------------
 * Checks if a cell is in the hash table, if not it adds it in.
 */
void Dstar::makeNewCell(state u)
{

  if (cellHash.find(u) != cellHash.end())
    return;

  cellInfo tmp;
  tmp.g = tmp.rhs = heuristic(u, s_goal);
  tmp.cost = C1;
  cellHash[u] = tmp;
}

/* double Dstar::getG(state u)
 * --------------------------
 * Returns the G value for state u.
 */
double Dstar::getG(state u)
{

  if (cellHash.find(u) == cellHash.end())
    return heuristic(u, s_goal);
  return cellHash[u].g;
}

/* double Dstar::getRHS(state u)
 * --------------------------
 * Returns the rhs value for state u.
 */
double Dstar::getRHS(state u)
{

  if (u == s_goal)
    return 0;

  if (cellHash.find(u) == cellHash.end())
    return heuristic(u, s_goal);
  return cellHash[u].rhs;
}

/* void Dstar::setG(state u, double g)
 * --------------------------
 * Sets the G value for state u
 */
void Dstar::setG(state u, double g)
{

  makeNewCell(u);
  cellHash[u].g = g;
}

/* void Dstar::setRHS(state u, double rhs)
 * --------------------------
 * Sets the rhs value for state u
 */
void Dstar::setRHS(state u, double rhs)
{

  makeNewCell(u);
  cellHash[u].rhs = rhs;
}

/* double Dstar::eightCondist(state a, state b)
 * --------------------------
 * Returns the 8-way distance between state a and state b.
 */
double Dstar::eightCondist(state a, state b)
{
  // Working on a solution to implement toroidal distance
  int dx = std::abs(b.x - a.x);
  int dy = std::abs(b.y - a.y);
  if (dx > (mapSizeX + 1) / 2)
  {
    dx = mapSizeX + 1 - dx;
  }
  if (dy > (mapSizeY + 1) / 2)
  {
    dy = mapSizeY + 1 - dy;
  }

  return std::sqrt((dx * dx) + (dy * dy));
}

/* int Dstar::computeShortestPath()
 * --------------------------
 * As per [S. Koenig, 2002] except for 2 main modifications:
 * 1. We stop planning after a number of steps, 'maxsteps' we do this
 *    because this algorithm can plan forever if the start is
 *    surrounded by obstacles.
 * 2. We lazily remove states from the open list so we never have to
 *    iterate through it.
 */
int Dstar::computeShortestPath()
{

  list<state> s;
  list<state>::iterator i;

  if (openList.empty())
    return 1;

  int k = 0;
  while ((!openList.empty()) &&
             (openList.top() < (s_start = calculateKey(s_start))) ||
         (getRHS(s_start) != getG(s_start)))
  {

    if (k++ > maxSteps)
    {
      // custom_logger::log("[Dstar::computeShortestPath] At maxsteps");
      return -1;
    }

    state u;

    bool test = (getRHS(s_start) != getG(s_start));

    // lazy remove
    while (1)
    {
      if (openList.empty())
        return 1;
      u = openList.top();
      openList.pop();

      if (!isValid(u))
        continue;
      if (!(u < s_start) && (!test))
        return 2;
      break;
    }

    ds_oh::iterator cur = openHash.find(u);
    openHash.erase(cur);

    state k_old = u;

    if (k_old < calculateKey(u))
    { // u is out of date
      insert(u);
    }
    else if (getG(u) > getRHS(u))
    { // needs update (got better)
      setG(u, getRHS(u));
      getPred(u, s);
      for (i = s.begin(); i != s.end(); i++)
      {
        updateVertex(*i);
      }
    }
    else
    { // g <= rhs, state has got worse
      setG(u, INFINITY);
      getPred(u, s);
      for (i = s.begin(); i != s.end(); i++)
      {
        updateVertex(*i);
      }
      updateVertex(u);
    }
  }
  return 0;
}

/* bool Dstar::close(double x, double y)
 * --------------------------
 * Returns true if x and y are within 10E-5, false otherwise
 */
bool Dstar::close(double x, double y)
{

  if (isinf(x) && isinf(y))
    return true;
  return (fabs(x - y) < 0.00001);
}

/* void Dstar::updateVertex(state u)
 * --------------------------
 * As per [S. Koenig, 2002]
 */
void Dstar::updateVertex(state u)
{

  list<state> s;
  list<state>::iterator i;

  if (u != s_goal)
  {
    getSucc(u, s);
    double tmp = INFINITY;
    double tmp2;

    for (i = s.begin(); i != s.end(); i++)
    {
      tmp2 = getG(*i) + cost(u, *i);
      if (tmp2 < tmp)
        tmp = tmp2;
    }
    if (!close(getRHS(u), tmp))
      setRHS(u, tmp);
  }

  if (!close(getG(u), getRHS(u)))
    insert(u);
}

/* void Dstar::insert(state u)
 * --------------------------
 * Inserts state u into openList and openHash.
 */
void Dstar::insert(state u)
{

  ds_oh::iterator cur;
  float csum;

  u = calculateKey(u);
  cur = openHash.find(u);
  csum = keyHashCode(u);
  // return if cell is already in list. TODO: this should be
  // uncommented except it introduces a bug, I suspect that there is a
  // bug somewhere else and having duplicates in the openList queue
  // hides the problem...
  // if ((cur != openHash.end()) && (close(csum, cur->second))) return;

  openHash[u] = csum;
  openList.push(u);
}

/* void Dstar::remove(state u)
 * --------------------------
 * Removes state u from openHash. The state is removed from the
 * openList lazilily (in replan) to save computation.
 */
void Dstar::remove(state u)
{

  ds_oh::iterator cur = openHash.find(u);
  if (cur == openHash.end())
    return;
  openHash.erase(cur);
}

/* double Dstar::trueDist(state a, state b)
 * --------------------------
 * Euclidean cost between state a and state b.
 */
double Dstar::trueDist(state a, state b)
{
  int dx = std::abs(b.x - a.x);
  int dy = std::abs(b.y - a.y);
  if (dx > (mapSizeX + 1) / 2)
  {
    dx = mapSizeX + 1 - dx;
  }
  if (dy > (mapSizeY + 1) / 2)
  {
    dy = mapSizeY + 1 - dy;
  }

  return std::sqrt((dx * dx) + (dy * dy));
  // float x = a.x - b.x;
  // float y = a.y - b.y;
  // return sqrt(x * x + y * y);
}

/* double Dstar::heuristic(state a, state b)
 * --------------------------
 * Pretty self explanitory, the heristic we use is the 8-way distance
 * scaled by a constant C1 (should be set to <= min cost).
 */
double Dstar::heuristic(state a, state b)
{
  return eightCondist(a, b) * C1;
}

/* state Dstar::calculateKey(state u)
 * --------------------------
 * As per [S. Koenig, 2002]
 */
state Dstar::calculateKey(state u)
{

  double val = fmin(getRHS(u), getG(u));

  u.k.first = val + heuristic(u, s_start) + k_m;
  u.k.second = val;

  return u;
}

/* double Dstar::cost(state a, state b)
 * --------------------------
 * Returns the cost of moving from state a to state b. This could be
 * either the cost of moving off state a or onto state b, we went with
 * the former. This is also the 8-way cost.
 */
double Dstar::cost(state a, state b)
{

  int xd = fabs(a.x - b.x);
  int yd = fabs(a.y - b.y);
  double scale = 1;

  if (xd + yd > 1)
    scale = M_SQRT2;

  if (cellHash.count(a) == 0)
    return scale * C1;
  return scale * cellHash[a].cost;
}

/*void Dstar::updateCell(const Position &pos, double val)
 * --------------------------
 * Overload updateCell(int x, int y, double val)
 */
void Dstar::updateCell(const Position &pos, double val)
{
  updateCell(pos.getXCoord(), pos.getYCoord(), val);
}

/* void Dstar::updateCell(int x, int y, double val)
 * --------------------------
 * As per [S. Koenig, 2002]
 */
void Dstar::updateCell(int x, int y, double val)
{
  state u;

  u.x = x;
  u.y = y;

  if ((u == s_start) || (u == s_goal))
    return;

  makeNewCell(u);
  cellHash[u].cost = val;

  updateVertex(u);
}

/* void Dstar::moduloSucc(state u)
 * --------------------------
 * Returns a list of successor states for state u, since this is an
 * 4-way graph this list contains all of a cells neighbours. Unless
 * the cell is occupied in which case it has no successors.
 */
state Dstar::moduloSucc(state u, int x, int y)
{
  if (u.x + x < 0) // Left
  {
    u.x = u.x + x + mapSizeX;
  }
  else // Right
  {
    u.x = (u.x + x) % mapSizeX;
  }

  if (u.y + y < 0) // Up
  {
    u.y = u.y + y + mapSizeY;
  }
  else // Down
  {
    u.y = (u.y + y) % mapSizeX;
  }

  return u;
}

/* void Dstar::getSucc(state u,list<state> &s)
 * --------------------------
 * Returns a list of successor states for state u, since this is an
 * 4-way graph this list contains all of a cells neighbours. Unless
 * the cell is occupied in which case it has no successors.
 */
void Dstar::getSucc(state u, list<state> &s)
{

  s.clear();
  u.k.first = -1;
  u.k.second = -1;

  if (occupied(u))
    return;

  u = moduloSucc(u, 1, 0);
  s.push_front(u);

  u = moduloSucc(u, -1, 1);
  s.push_front(u);

  u = moduloSucc(u, -1, -1);
  s.push_front(u);

  u = moduloSucc(u, 1, -1);
  s.push_front(u);
}

/* void Dstar::getPred(state u,list<state> &s)
 * --------------------------
 * Returns a list of all the predecessor states for state u. Since
 * this is for an 4-way connected graph the list contails all the
 * neighbours for state u. Occupied neighbours are not added to the
 * list.
 */
void Dstar::getPred(state u, list<state> &s)
{

  s.clear();
  u.k.first = -1;
  u.k.second = -1;

  u.x += 1;
  if (!occupied(u))
    s.push_front(u);
  u.x -= 1;
  u.y += 1;
  if (!occupied(u))
    s.push_front(u);
  u.x -= 1;
  u.y -= 1;
  if (!occupied(u))
    s.push_front(u);
  u.x += 1;
  u.y -= 1;
  if (!occupied(u))
    s.push_front(u);
}

/* void Dstar::updateStart(int x, int y)
 * --------------------------
 * Update the position of the robot, this does not force a replan.
 */
void Dstar::updateStart(int x, int y)
{

  s_start.x = x;
  s_start.y = y;

  k_m += heuristic(s_last, s_start);

  s_start = calculateKey(s_start);
  s_last = s_start;
}

/* void Dstar::updateGoal(int x, int y)
 * --------------------------
 * This is somewhat of a hack, to change the position of the goal we
 * first save all of the non-empty on the map, clear the map, move the
 * goal, and re-add all of non-empty cells. Since most of these cells
 * are not between the start and goal this does not seem to hurt
 * performance too much. Also it free's up a good deal of memory we
 * likely no longer use.
 */
void Dstar::updateGoal(int x, int y)
{

  list<pair<ipoint2, double>> toAdd;
  pair<ipoint2, double> tp;

  ds_ch::iterator i;
  list<pair<ipoint2, double>>::iterator kk;

  for (i = cellHash.begin(); i != cellHash.end(); i++)
  {
    if (!close(i->second.cost, C1))
    {
      tp.first.x = i->first.x;
      tp.first.y = i->first.y;
      tp.second = i->second.cost;
      toAdd.push_back(tp);
    }
  }

  cellHash.clear();
  openHash.clear();

  while (!openList.empty())
    openList.pop();

  k_m = 0;

  s_goal.x = x;
  s_goal.y = y;

  cellInfo tmp;
  tmp.g = tmp.rhs = 0;
  tmp.cost = C1;

  cellHash[s_goal] = tmp;

  tmp.g = tmp.rhs = heuristic(s_start, s_goal);
  tmp.cost = C1;
  cellHash[s_start] = tmp;
  s_start = calculateKey(s_start);

  s_last = s_start;

  for (kk = toAdd.begin(); kk != toAdd.end(); kk++)
  {
    updateCell(kk->first.x, kk->first.y, kk->second);
  }
}

/* bool Dstar::replan()
 * --------------------------
 * Updates the costs for all cells and computes the shortest path to
 * goal. Returns true if a path is found, false otherwise. The path is
 * computed by doing a greedy search over the cost+g values in each
 * cells. In order to get around the problem of the robot taking a
 * path that is near a 45 degree angle to goal we break ties based on
 * the metric euclidean(state, goal) + euclidean(state,start).
 */
bool Dstar::replan()
{

  path.clear();

  int res = computeShortestPath();
  //printf("res: %d ols: %d ohs: %d tk: [%f %f] sk: [%f %f] sgr: (%f,%f)\n",res,openList.size(),openHash.size(),openList.top().k.first,openList.top().k.second, s_start.k.first, s_start.k.second,getRHS(s_start),getG(s_start));
  if (res < 0)
  {
    // custom_logger::log("[Dstar::replan] NO PATH TO GOAL, REASON : RES < 0");
    return false;
  }
  list<state> n;
  list<state>::iterator i;

  state cur = s_start;

  if (isinf(getG(s_start)))
  {
    // custom_logger::log("[Dstar::replan] NO PATH TO GOAL REASON : G VALUE");
    return false;
  }

  bool partiallyFound = false;
  while (cur != s_goal && !partiallyFound)
  {
    path.push_back(cur);
    getSucc(cur, n);

    if (n.empty())
    {
      // custom_logger::log("[Dstar::replan] NO PATH TO GOAL REASON : EMPTY");
      return false;
    }

    double cmin = INFINITY;
    double tmin;
    state smin;

    //! Heavy custom_logger !
    // custom_logger::log("Current pos " + std::to_string(cur.x) + "-" + std::to_string(cur.y));
    int count = 0;
    for (i = n.begin(); i != n.end(); i++)
    {
      // custom_logger::log("Possible coord " + std::to_string(i->x) + "-" + std::to_string(i->y) + " check " + std::to_string(*i == cur));
      auto it = std::find(path.begin(), path.end(), *i);
      if (occupied(*i) || path.end() != it)
      {
        // custom_logger::log("Is occupied continue");
        if (++count == 4)
        {
          // custom_logger::log("Patially found");
          partiallyFound = true;
        }
        continue;
      }

      else
      {
        double val = cost(cur, *i);
        double val2 = trueDist(*i, s_goal) + trueDist(s_start, *i); // (Euclidean) cost to goal + cost to pred
        val += getG(*i);

        if (close(val, cmin))
        {
          if (tmin > val2)
          {
            tmin = val2;
            cmin = val;
            smin = *i;
          }
        }
        else if (val < cmin)
        {
          tmin = val2;
          cmin = val;
          smin = *i;
        }
      }
    }
    n.clear();
    cur = smin;
  }
  path.push_back(s_goal);
  return true;
}
