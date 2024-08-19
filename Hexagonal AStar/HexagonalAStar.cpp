#include <list>
#include <vector>
#include <algorithm>
#include <any>
#include "point.h"
#include "node.h"
using namespace std;

/// @brief An implementation of the A* pathfinding algorithm for hexagonal grids.
/// @param start The coordinate of the start hexagonal cell.
/// @param end The coordinate of the desired end hexagonal cell.
/// @return The coordinates, in order, of the path from the start point to the end point (or point found closest to endpoint)
list<Point> HexagonalAStar(Point start, Point end)
{
    // keep necessary memory cleanup in one list
    vector<Node*> cleanup = vector<Node*>();

    // need this to end algorithm
    Node* goal = NULL;
    // if we can't find a path/end the algorithm with finding the goal then we'll just use the closest node
    Node* failsafe = NULL;

    // initialize open and closed nodes lists
    list<Node*> open = list<Node*>();
    list<Node*> closed = list<Node*>();

    // add starting node
    Node* startNode = new Node(start,0,0,0,NULL);
    open.push_back(startNode);
    cleanup.push_back(startNode);
    // while there are open nodes
    while (open.size() > 0)
    {
        // pop node with least f
        sort(open.begin(), open.end(), sortNodeFPointer);
        Node* currentQueryNode = open.front();
        open.pop_front();

        // if we end up not being able to find the desired endpoint, we will use the progress we currently have here as a failsafe.
        if (failsafe == NULL) failsafe = currentQueryNode;
        else if ((failsafe->tilePos.magnitude - end.magnitude) > (currentQueryNode->tilePos.magnitude - end.magnitude)) failsafe = currentQueryNode;

        // generate currentQueryNode's successors
        list<Point> currentQueryNodeSuccessors = list<Point>();
        // find all neighboring cells
        // the exact coordinates for the diagonals depends on the row (for this particular grid system)
        vector<Point> possibleNeighbors = vector<Point>();
        possibleNeighbors.push_back(Point(0,1));
        possibleNeighbors.push_back(Point(0,-1));
        possibleNeighbors.push_back(Point(-1,0));
        possibleNeighbors.push_back(Point(1,0));
        if (currentQueryNode->tilePos.y % 2 == 0)
        {
            possibleNeighbors.push_back(Point(-1, -1));
            possibleNeighbors.push_back(Point(-1, 1));
        }
        else
        {
            possibleNeighbors.push_back(Point(1, -1));
            possibleNeighbors.push_back(Point(1, 1));
        }
        // iterate through each successor
        for (int i = 0; i < possibleNeighbors.size(); i++)
        {
            // calculate current position of current successor
            Point newPos = possibleNeighbors[i] + currentQueryNode->tilePos;

            // the specifics of this determination is not important to the algorithm's implementation, so it has been omitted for simplicity.
            // basically, we need to navigate around walls
            if (isPartOfWall(newPos))
            {
                continue;
            }

            // calculate f
            // each neighbor cell has a distance of 1 from each other
            float g = currentQueryNode->g + 1.0;
            // the specifics of this determination is not important to the algorithm's implementation, so it has been omitted for simplicity.
            float h = Heuristic(newPos);
            float f = g + h;

            // we can stop if we find the desired endpoint
            if (newPos == end)
            {
                goal = new Node(newPos, f, g, h, currentQueryNode);
                cleanup.push_back(goal);
                break;
            }

            // if a node exists at the same position but with a better f, don't replace it (ignore current successor)
            auto lessF = [newPos, f](Node* n) {n->tilePos == newPos && n->f <= f;};
            if (find_if(open.begin(),open.end(), lessF) != open.end() || find_if(closed.begin(), closed.end(), lessF) != closed.end())
            {
                continue;
            }
            else // otherwise replace exisitng nodes if they exist or just add it
            {
                auto samePos = [newPos](Node* n) {n->tilePos == newPos;};
                open.remove_if(samePos);
                closed.remove_if(samePos);
                Node* nextNode = new Node(newPos, f, g, h, currentQueryNode);

                // add/update new explore option
                open.push_back(nextNode);
                cleanup.push_back(nextNode);
            }
        }

        // finished exploring current node
        closed.push_back(currentQueryNode);
        if (goal != NULL) break;
    }

    // return Node closest to goal if not goal
    Node* result = NULL;
    if (goal == NULL)
    {
        result = failsafe;
    }
    else
    {
        result = goal;
    }

    // create path
    list<Point> path = list<Point>();
    Node* pathNode = result;
    while(pathNode != NULL) {
        path.push_front(pathNode->tilePos);
        pathNode = pathNode->parent;
    }

    // memory cleanup
    for (int i = 0; i < cleanup.size(); i++) {
        if (cleanup[i] != NULL) delete cleanup[i];
        cleanup[i] = NULL;
    }

    return path;
};

bool isPartOfWall(Point p) { /*see above call*/ return false; }

float Heuristic(Point p) { /*see above call*/ return 0; }