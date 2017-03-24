#include "level.h"
#include "collision.h"
#include "maze.h"


Level::Level(Player *pl)
{
    curr_map = new Map();
    int mazeWidth = 50;
    int mazeHeight = 50;
    int wallWidth = 200;
    int wallHeight = 200;
    Maze maze (mazeWidth,mazeHeight);
    int **map = maze.getMap();
    this->pl=pl;
    bool done = false;
    for (int i=0; i<mazeWidth; i++){
        for (int j=0; j<mazeHeight; j++){
            if(1 == map[i][j])
            {
                curr_map->addWall(Wall(QVector2D(wallWidth*j,wallHeight*i), wallWidth,wallHeight));
            }
            if(-1 == map[i][j] && !done)
            {

                this->pl->setPosition(QVector2D(wallWidth*j,wallHeight*i));
                done=true;
            }
        }
     }
}

void Level::draw(GameWidget *obg)
{
    curr_map->draw(obg);
}

void Level::checkCollision(GameWidget *paint)
{
    QVector2D save = QVector2D(0,0);
    foreach (Wall curr_wall, curr_map->walls) {
        save +=collisionCircleAndRectangle(&curr_wall, this->pl, paint);
    }
    this->pl->setForce(save);
}
