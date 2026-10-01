#include "gameBoard.h"

/* contructer for gameboard class
*  PARAMS: uint8_t pin
*          takes in a pin and creates a new NeoMatrix object 
*/
GameBoard::GameBoard(uint8_t pin)
{
    matrix = new Adafruit_NeoMatrix(
        8, 8, pin,
        NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
        NEO_GRB + NEO_KHZ800);
}

/* DECONSTRUCTER */
GameBoard ::~GameBoard()
{
    delete matrix;
}

/* 
*   PURPOSE: clear the entire board, set the matrix to have no boats that are "hit"
*/
void GameBoard::clearBoard()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            board[row][col] = 0;
        }
    }
}

/*
*   PURPOSE: checking if a boat is already in place and the other boats are not near it
*/
bool GameBoard::canPlaceBoat()
{
    for (int i = 0; i < currentBoat.length; i++)
    {
        int r = currentBoat.row;
        int c = currentBoat.col;

        if (currentBoat.isHorizontal)
            c += i;
        else
            r += i;

        if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE)
            return false;

        if (board[r][c] != 0)
            return false;

        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                int nr = r + dr;
                int nc = c + dc;

                if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE)
                {
                    if (board[nr][nc] != 0)
                        return false;
                }
            }
        }
    }

    return true;
}

void GameBoard::placeBoat(const Boat &boat)
{
    for (int i = 0; i < boat.length; i++)
    {
        int r = boat.row;
        int c = boat.col;

        if (boat.isHorizontal) c += i;
        else r += i;
        board[r][c] = 1;
    }
    // ??
    fullBoatList[currentBoatIndex] = boat;
}

void GameBoard::loadNextBoat()
{
    currentBoatIndex++;

    if (currentBoatIndex < 4)
    {
        currentBoat = Boat(boatSizes[currentBoatIndex]);
    }
    else
    {
        allBoatsPlaced = true;
    }
}

void GameBoard::drawBoardAndPreview()
{
    matrix->fillScreen(0);

    //placed boats = blue
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (board[row][col] == 1)
            {
                matrix->drawPixel(col, row, matrix->Color(0, 0, 255));
            }
            if(board[row][col] == 2){
                matrix->drawPixel(col, row, matrix->Color(255, 0, 0));
            }
        }
    }
    

    // current preview = cyan
    if (!allBoatsPlaced)
    {
        for (int i = 0; i < currentBoat.length; i++)
        {
            int row = currentBoat.row + (currentBoat.isHorizontal ? 0 : i);
            int col = currentBoat.col + (currentBoat.isHorizontal ? i : 0);

            matrix->drawPixel(col, row, matrix->Color(0, 245, 220));
        }
    }

    matrix->show();
}

void GameBoard::flashColor(uint16_t color, int ms)
{
    matrix->fillScreen(color);
    matrix->show();
    delay(ms);
}

bool GameBoard::getPlacementBool()
{
    return allBoatsPlaced;
}

Boat& GameBoard::getBoat()
{
    return currentBoat;
}

int GameBoard::getBoard(int row, int col)
{
    return board[row][col];
}

bool GameBoard::getPlaceHit(){
    return placingHit;
}

bool GameBoard::getDeadBoats(){
    return allDeadBoats;
}

void GameBoard::setBoatsPlaced(bool status){
    allBoatsPlaced = status;
}

void GameBoard::setPlaceHit(bool status){
    placingHit = status;
}

bool GameBoard::checkHit2(int hitRow, int hitCol){
    if(board[hitRow][hitCol] == 1){
        board[hitRow][hitCol] = 2;

        for(int i = 0; i < 4; i++){
            Boat &b = fullBoatList[i];
            bool hit = false;
            if (b.isHorizontal) {
                if (hitRow == b.row && hitCol >= b.col && hitCol < b.col + b.length){
                    hit = true;
                }
            } else {
                if (hitCol == b.col && hitRow >= b.row && hitRow < b.row + b.length){
                    hit = true;
                } 
            }
            if (hit) {
                b.decreaseAlive();
                break;
            }
        }
 
        bool tempAllDead = true;
        for (int i = 0; i < 4; i++) {
            if (fullBoatList[i].getNumAlive() > 0) { 
                tempAllDead = false;
                break;
            }
        }
        allDeadBoats = tempAllDead;
        return true;
    } 
    return false;
}

void GameBoard::reset(){
    clearBoard();
    allBoatsPlaced = false;
    allDeadBoats = false;
    currentBoatIndex = 0;
    placingHit = false;
    currentBoat = Boat(boatSizes[0]);
}
