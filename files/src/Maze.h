#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

class Maze {
private:
    std::vector<std::vector<std::pair<bool, bool>>>* _maze;
    int _width;
    int _height;
    std::pair<int, int> findInSet(std::pair<int, int> i, std::vector<std::vector<std::pair<int, int>>>& set);
    void mergeSets(std::pair<int, int> i, std::pair<int, int> j, std::vector<std::vector<std::pair<int, int>>>& set);
    void carveExit();
    void carveWalls(std::pair<int, int> current, std::pair<int, int> neighbor);
    bool wallBetween(std::pair<int, int> current, std::pair<int, int> neighbor);

public:
    Maze() : _height(0), _width(0), _maze(nullptr) {}
    void setNewDimensions(int height, int width);
    void resetMaze();
    void randomizedDFS();
    void randomizedKruskal();
    void randomizedPrim();
    void binaryTree();
    std::vector<std::vector<bool>> convertToBinaryMatrix();
};

// sets new dimensions for the maze
void Maze::setNewDimensions(int height, int width)
{
    delete _maze;

    _height = height;
    _width = width;

    // initializes the maze with four walls around all cells
    _maze = new std::vector<std::vector<std::pair<bool, bool>>>
            (height + 1,std::vector<std::pair<bool, bool>>(width + 1, {true, true}));
}

// resets the maze to its original state (four walls around all cells)
void Maze::resetMaze()
{
    delete _maze;

    _maze = new std::vector<std::vector<std::pair<bool, bool>>>
            (_height + 1,std::vector<std::pair<bool, bool>>(_width + 1, {true, true}));
}

/* Performs the iterative implementation with stacks of randomized depth-first search for the
 * generation of mazes, based on pseudocode discussed in the following link:
 * https://en.wikipedia.org/wiki/Maze_generation_algorithm */
void Maze::randomizedDFS()
{
    int i = 0, j = 0;
    std::vector<int> di = {1, -1, 0, 0};
    std::vector<int> dj = {0, 0, 1, -1};

    std::vector<std::vector<bool>> visited(_height, std::vector<bool>(_width, false));
    std::stack<std::pair<int, int>> stk;

    // choose an initial cell, mark it as visited and push it to the stack
    visited[i][j] = true;
    stk.push({i, j});

    while(!stk.empty())
    {
        std::vector<std::pair<int, int>> unvisited_neighbors;

        // pop a cell from the stack and make it a current cell
        i = stk.top().first;
        j = stk.top().second;
        stk.pop();

        for (int counter = 0; counter < 4; ++counter)
        {
            int ni = i + di[counter];
            int nj = j + dj[counter];

            if (ni < 0 || nj < 0 || ni > _height - 1 || nj > _width - 1)
            {
                continue;
            }

            if (!visited[ni][nj])
            {
                unvisited_neighbors.emplace_back(ni, nj);
            }
        }

        if (!unvisited_neighbors.empty())
        {
            // if the current cell has any neighbors which have not been visited, push the current cell into the stack
            stk.push({i, j});

            // choose one of the unvisited neighbors
            std::shuffle(unvisited_neighbors.begin(), unvisited_neighbors.end(), std::mt19937(std::random_device()()));

            i = unvisited_neighbors[0].first;
            j = unvisited_neighbors[0].second;

            // remove the wall between the chosen neighbor and the current cell
            carveWalls(stk.top(), unvisited_neighbors[0]);

            // mark the chosen neighbor as visited and push it into the stack
            visited[i][j] = true;
            stk.push({i, j});
        }
    }

    carveExit();
}

// finds the parent of an element in a disjoint set
std::pair<int, int> Maze::findInSet(std::pair<int, int> i, std::vector<std::vector<std::pair<int, int>>>& set)
{
    if (set[i.first][i.second].first == -1 && set[i.first][i.second].second == -1)
    {
        return i;
    }
    else
    {
        return findInSet(set[i.first][i.second], set);
    }
}

// union of two disjoint sets
void Maze::mergeSets(std::pair<int, int> i, std::pair<int, int> j, std::vector<std::vector<std::pair<int, int>>>& set)
{
    std::pair<int, int> pi = findInSet(i, set);
    std::pair<int, int> pj = findInSet(j, set);
    set[pi.first][pi.second] = pj;
}

// returns a boolean that represents whether a wall exist between two cells
bool Maze::wallBetween(std::pair<int, int> current, std::pair<int, int> neighbor)
{
    if (current.first == neighbor.first)
    {
        if (current.second > neighbor.second)
        {
            if ((*_maze)[current.first][current.second].first)
            {
                return true;
            }
        }
        else
        {
            if ((*_maze)[neighbor.first][neighbor.second].first)
            {
                return true;
            }
        }
    }
    else
    {
        if (current.first > neighbor.first)
        {
            if ((*_maze)[current.first][current.second].second)
            {
                return true;
            }
        }
        else
        {
            if ((*_maze)[neighbor.first][neighbor.second].second)
            {
                return true;
            }
        }
    }
    return false;
}

/* performs the iterative randomized kruskal's algorithm for maze generation
 * based on pseudocode discussed in the following link:
 * https://courses.cs.washington.edu/courses/cse326/07su/prj2/kruskal.html */
void Maze::randomizedKruskal()
{
    std::vector<std::vector<std::pair<int, int>>> set(_height, std::vector<std::pair<int, int>>(_width, {-1, -1}));
    std::vector<std::pair<int, int>> cells_with_neighbors;

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            cells_with_neighbors.emplace_back(i, j);
        }
    }

    std::vector<int> di = {1, -1, 0, 0};
    std::vector<int> dj = {0, 0, 1, -1};
    int walls_down = 0;

    while (walls_down < _width * _height - 1)
    {
        // choose random cell current
        std::shuffle(cells_with_neighbors.begin(), cells_with_neighbors.end(), std::mt19937(std::random_device()()));
        int curr_i = cells_with_neighbors[0].first;
        int curr_j = cells_with_neighbors[0].second;

        std::pair<int, int> current = {curr_i, curr_j};
        std::vector<std::pair<int, int>> neighbors;

        for (int counter = 0; counter < 4; ++counter)
        {
            int ni = curr_i + di[counter];
            int nj = curr_j + dj[counter];

            if (ni < 0 || nj < 0 || ni > _height - 1 || nj > _width - 1)
            {
                continue;
            }

            std::pair<int, int> neighbor = {ni, nj};

            if (wallBetween(current, neighbor))
            {
                neighbors.emplace_back(ni, nj);
            }
        }

        // choose a random neighbor of current that has a wall between it and current
        if (!neighbors.empty())
        {
            std::shuffle(neighbors.begin(), neighbors.end(), std::mt19937(std::random_device()()));

            // find the parents of current and neighbor
            if (findInSet(neighbors[0], set) != findInSet({curr_i, curr_j}, set))
            {
                // if they are different, union them, knock down the wall, and add to walls_down
                mergeSets(neighbors[0], {curr_i, curr_j}, set);

                carveWalls(current, neighbors[0]);

                ++walls_down;
            }
        }
        else
        {
            cells_with_neighbors.erase(cells_with_neighbors.begin());
        }
    }

    carveExit();
}

/* performs the randomized prim's algorithm for maze generation, based on pseudocode and definitions discussed in
 * the following links: https://courses.cs.washington.edu/courses/cse326/07su/prj2/kruskal.html
 * https://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm */
void Maze::randomizedPrim()
{
    std::vector<std::vector<bool>> visited(_height, std::vector<bool>(_width, false));
    std::vector<std::pair<int, int>> frontier;
    std::vector<int> di = {1, -1, 0, 0};
    std::vector<int> dj = {0, 0, 1, -1};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_i(0,_height-1);
    std::uniform_int_distribution<std::mt19937::result_type> dist_j(0,_width-1);

    int curr_i = (int)dist_i(rng);
    int curr_j = (int)dist_j(rng);

    // choose a random cell, mark it visited and add it to frontier
    visited[curr_i][curr_j] = true;
    frontier.emplace_back(curr_i, curr_j);

    while (!frontier.empty())
    {
        std::vector<std::pair<int, int>> neighbors;

        std::shuffle(frontier.begin(), frontier.end(), std::mt19937(std::random_device()()));

        // pick a cell off frontier
        curr_i = frontier[0].first;
        curr_j = frontier[0].second;

        std::pair<int, int> current = {curr_i, curr_j};
        frontier.erase(frontier.begin());

        for (int counter = 0; counter < 4; ++counter)
        {
            int ni = curr_i + di[counter];
            int nj = curr_j + dj[counter];

            if (ni < 0 || nj < 0 || ni > _height - 1 || nj > _width - 1)
            {
                continue;
            }

            std::pair<int, int> n = {ni, nj};

            // add the unvisited neighbors of current, that are not already a part of frontier, to frontier
            if (!visited[ni][nj] && std::find(frontier.begin(), frontier.end(), n) == frontier.end())
            {
                frontier.emplace_back(ni, nj);
            }
            else
            {
                if (visited[ni][nj])
                {
                    neighbors.emplace_back(ni, nj);
                }
            }
        }

        if (!neighbors.empty())
        {
            // knock down a wall between the current cell and a random visited neighbor
            std::shuffle(neighbors.begin(), neighbors.end(), std::mt19937(std::random_device()()));

            carveWalls(current, neighbors[0]);

            // mark current as visited
            visited[curr_i][curr_j] = true;
        }
    }

    carveExit();
}

/* performs the "binary tree" algorithm for maze generation, based on the definition discussed in the
 * following link: https://en.wikipedia.org/wiki/Maze_generation_algorithm */
void Maze::binaryTree()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,1);

    for (int i = 1; i < _height; ++i)
    {
        for (int j = 1; j < _width; ++j)
        {
            unsigned int random = dist(rng);

            if (random == 0)
            {
                (*_maze)[i][j].first = false;
            }
            else
            {
                (*_maze)[i][j].second = false;
            }
        }
    }

    for (int i = 0; i <= _height; ++i)
    {
        (*_maze)[i][_width].second = false;
        (*_maze)[i][0].second = false;
    }

    for (int j = 0; j <= _width; ++j)
    {
        (*_maze)[_height][j].first = false;
        (*_maze)[0][j].first = false;
    }

    (*_maze)[0][0].first = true;
    (*_maze)[0][_width].first = true;
    (*_maze)[_height][0].second = true;

    (*_maze)[0][0].second = false;
    (*_maze)[_height][_width-1].second = false;
}

// removes the appropriate wall between two cells
void Maze::carveWalls(std::pair<int, int> current, std::pair<int, int> neighbor)
{
    if (current.first == neighbor.first)
    {
        if (current.second > neighbor.second)
        {
            (*_maze)[current.first][current.second].first = false;
        }
        else
        {
            (*_maze)[neighbor.first][neighbor.second].first = false;
        }
    }
    else
    {
        if (current.first > neighbor.first)
        {
            (*_maze)[current.first][current.second].second = false;
        }
        else
        {
            (*_maze)[neighbor.first][neighbor.second].second = false;
        }
    }
}

// creates the exit of the maze and removes extra walls
void Maze::carveExit()
{
    for (int x = 0; x <= _height; ++x)
    {
        (*_maze)[x][_width].second = false;
    }

    for (int y = 0; y <= _width; ++y)
    {
        (*_maze)[_height][y].first = false;
    }

    (*_maze)[_height][_width-1].second = false;
}

// converts the maze into a binary matrix (wall = 1, open space = 0)
std::vector<std::vector<bool>> Maze::convertToBinaryMatrix()
{
    std::vector<std::vector<bool>> map(2*_height+1, std::vector<bool>(2*_width+1, true));

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            map[1+2*i][1+2*j] = false;

            if (!(*_maze)[i][j].first)
            {
                map[1+2*i][2*j] = false;
            }

            if (!(*_maze)[i][j].second)
            {
                map[2*i][1+2*j] = false;
            }
        }
    }

    map[0][1] = true;
    map[2*_height][2*_width-1] = false;

    return map;
}
