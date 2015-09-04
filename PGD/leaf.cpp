#include "leaf.h"
#include <stdio.h>
Leaf::Leaf(int x, int y, int width, int height) :
_x(x),
_y(y),
_width(width),
_height(height)
{}

bool Leaf::split(){
	if (leftChild != NULL || rightChild != NULL)
		return false;

	bool splitH = rand() % 10 > 5;
	if (_width - MIN_ROOM_SIZE <= MIN_ROOM_SIZE) splitH = true;
	if ( _height - MIN_ROOM_SIZE <= MIN_ROOM_SIZE) splitH = false;

/*	//Split horisontalli if width is 25% bigger than height else random split
	if (_width > _height && _width / _height >= 1.25) splitH = false;
	if (_height > _width && _height / _width >= 1.25) splitH = true;
	*/
	int max = (splitH ? _height : _width) - MIN_ROOM_SIZE;
	if (max <= MIN_ROOM_SIZE) return false;
	

	int split = rand() % (max - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
	if (splitH){
		leftChild = new Leaf(_x, _y, _width, split);
		rightChild = new Leaf(_x, _y + split, _width, _height - split);
	}
	else{
		leftChild = new Leaf(_x, _y, split, _height);
		rightChild = new Leaf(_x + split, _y, _width - split, _height);
	}

	return true;
}

void Leaf::createRoom(){
	if (leftChild != NULL || rightChild != NULL){
		if (leftChild != NULL)leftChild->createRoom();
		if (rightChild != NULL)rightChild->createRoom();
		if (leftChild != NULL && rightChild != NULL){
			createHall(leftChild->getRandomChildRoom(), rightChild->getRandomChildRoom());
		}
	}else{
	//	int sizeX = (_width);
	//	int sizeY = (_height );

	//	int posX = (_width - sizeX);
	//	int posY = (_height - sizeY);
		int sizeX = rand() % (_width - 5) + 3;
		int sizeY = rand() % (_height - 5) + 3;

		int posX = rand() % (_width - sizeX - 2) + 1;
		int posY = rand() % (_height - sizeY - 2) + 1;
		room = new Room(_x +posX, _y + posY, sizeX, sizeY);
	}
}

void Leaf::createHall(Room* l, Room* r){
	if (l->checkConnection(r)) return;
	//Room 1 upper left and lower right corner
	int R1ULCX = l->getX1();
	int R1ULCY = l->getY1();
	int R1LRCX = l->getX2();
	int R1LRCY = l->getY2();

	//Room 2 upper left and lower right corner

	int R2ULCX = r->getX1();
	int R2ULCY = r->getY1();
	int R2LRCX = r->getX2();
	int R2LRCY = r->getY2();

	//point where the hall will begin
	int randomX, randomY;
	int w, h;

	if (R1LRCX <= R2ULCX){
		if (R1LRCY < R2ULCY){
			// Right and down
			if (rand() % 10 < 5){
				randomY = getRandom(R1ULCY, R1LRCY);
				randomX = getRandom(R2ULCX, R2LRCX);
				w = randomX - R1LRCX;
				h = R2ULCY - randomY;
				halls.push_back(new Hall(R1LRCX, randomY, w, 1));
				halls.push_back(new Hall(randomX, randomY, 1, h));
			}
			else{ // Down and right
				randomY = getRandom(R2ULCY, R2LRCY);
				randomX = getRandom(R1ULCX, R1LRCX);
				w = R2ULCX - randomX;
				h = randomY - R1LRCY;
				halls.push_back(new Hall(randomX, R1LRCY, 1, h));
				halls.push_back(new Hall(randomX, randomY, w, 1));
			}
		}
		else if (R1ULCY >= R2LRCY){
			//right and up
			if (rand() % 10 < 5){
				randomY = getRandom(R1ULCY, R1LRCY);
				randomX = getRandom(R2ULCX, R2LRCX);
				w = randomX - R1LRCX+1;
				h = randomY - R2LRCY;
				std::cout << w << std::endl;
				halls.push_back(new Hall(R1LRCX, randomY, w, 1));
				halls.push_back(new Hall(randomX, R2LRCY, 1, h));
			}
			else{ // up and right
				randomY = getRandom(R2ULCY, R2LRCY);
				randomX = getRandom(R1ULCX, R1LRCX);
				w = R2ULCX - randomX;
				h = R1ULCY - randomY;
				halls.push_back(new Hall(randomX, randomY, 1, h));
				halls.push_back(new Hall(randomX, randomY, w, 1));
			}
		}
		else{
			randomY = getRandom((R1ULCY > R2ULCY) ? R1ULCY : R2ULCY, (R1LRCY < R2LRCY) ? R1LRCY : R2LRCY);
			w = abs(R1LRCX - R2ULCX);
			halls.push_back(new Hall(R1LRCX, randomY, w, 1));
			std::cout << w << std::endl;
		}
	}
	else if (R1ULCX >= R2LRCX){
		if (R1LRCY < R2ULCY){
			// left and down
			if (rand() % 10 < 5){
				randomY = getRandom(R1ULCY, R1LRCY);
				randomX = getRandom(R2ULCX, R2LRCX);
				w = R1ULCX - randomX;
				h = R2ULCY - randomY;
				halls.push_back(new Hall(randomX, randomY, w, 1));
				halls.push_back(new Hall(randomX, randomY, 1, h));
			}
			else{ // down and left
				randomX = getRandom(R1ULCX, R1LRCX);
				randomY = getRandom(R2ULCY, R2LRCY);
				w = randomX - R2LRCX;
				h = randomY - R1LRCY+1;
				halls.push_back(new Hall(randomX, R1LRCY, 1, h));
				halls.push_back(new Hall(R2LRCX, randomY, w, 1));
			}
		}
		else if (R1ULCY > R2LRCY){
			// up and left
			if (rand() % 10 < 5){
				randomY = getRandom(R2ULCY, R2LRCY);
				randomX = getRandom(R1ULCX, R1LRCX);
				w = randomX - R2LRCX;
				h = R1ULCY - randomY;
				halls.push_back(new Hall(randomX, randomY, 1, h));
				halls.push_back(new Hall(R2LRCX, randomY, w, 1));
			}
			else{ // left and up
				randomY = getRandom(R1ULCY, R1LRCY);
				randomX = getRandom(R2ULCX, R2LRCX);
				w = R1ULCX - randomX;
				h = randomY - R2LRCY;
				halls.push_back(new Hall(randomX, randomY, w, 1));
				halls.push_back(new Hall(randomX, R2LRCY, 1, h));
			}
		}
		else{
			randomY = getRandom((R1ULCY < R2ULCY) ? R1ULCY : R2ULCY, (R1LRCY < R2LRCY) ? R1LRCY : R2LRCY);
			w = R1ULCX - R2LRCX;
			halls.push_back(new Hall(R2LRCX, randomY, w, 1));
			
		}
	}
	else{
		if (R1LRCY < R2ULCY){
			randomX = getRandom((R1ULCX > R2ULCX) ? R1ULCX : R2ULCX, (R1LRCX < R2LRCX) ? R1LRCX : R2LRCX);
			h = R2ULCY - R1LRCY;
			halls.push_back(new Hall(randomX, R1LRCY, 1, h));
		}
		else if (R1ULCY > R2LRCY){
			randomX = getRandom((R1ULCX > R2ULCX) ? R1ULCX : R2ULCX, (R1LRCX < R2LRCX) ? R1LRCX : R2LRCX);
			h = R1ULCY - R2LRCY;
			halls.push_back(new Hall(randomX, R2LRCY, 1, h));
		}
	}

	
	/**
	SDL_Point temp1{ getRandom(l->getX1() + 1, l->getX2() - 2), getRandom(l->getY1()+1, l->getY2()-2) };
	SDL_Point temp2{ getRandom(r->getX1() + 1, r->getX2() - 2), getRandom(r->getY1()+1, r->getY2()-2) };
		int w = temp1.x - temp2.x;
		int h = temp1.y - temp2.y;

		if (w > 0){
			if (h < 0){
				if (rand() < 0.5){
					halls.push_back(new Hall(temp2.x, temp1.y, abs(w), 1));
					halls.push_back(new Hall(temp2.x, temp2.y, 1, abs(h)));
				}
				else{
					halls.push_back(new Hall(temp2.x, temp2.y, abs(w), 1));
					halls.push_back(new Hall(temp1.x, temp2.y, 1, abs(h)));
				}
			}
			else if (h > 0){
				if (rand() < 0.5){
					halls.push_back(new Hall(temp2.x, temp1.y, abs(w), 1));
					halls.push_back(new Hall(temp2.x, temp1.y, 1, abs(h)));
				}
				else{
					halls.push_back(new Hall(temp2.x, temp2.y, abs(w), 1));
					halls.push_back(new Hall(temp1.x, temp1.y, 1, abs(h)));
				}
			}
			else{
				halls.push_back(new Hall(temp2.x, temp2.y, abs(w), 1));
			}
		}
		else if (w<0){
			if (h < 0){
				if (rand() < 0.5){
					halls.push_back(new Hall(temp1.x, temp2.y, abs(w), 1));
					halls.push_back(new Hall(temp1.x, temp2.y, 1, abs(h)));
				}
				else{
					halls.push_back(new Hall(temp1.x, temp1.y, abs(w), 1));
					halls.push_back(new Hall(temp2.x, temp2.y, 1, abs(h)));
				}
			}
			else if (h > 0){
				if (rand() < 0.5){
					halls.push_back(new Hall(temp1.x, temp1.y, abs(w), 1));
					halls.push_back(new Hall(temp2.x, temp1.y, 1, abs(h)));
				}
				else{
					halls.push_back(new Hall(temp1.x, temp2.y, abs(w), 1));
					halls.push_back(new Hall(temp1.x, temp1.y, 1, abs(h)));
				}
			}
			else{
				halls.push_back(new Hall(temp1.x, temp1.y, abs(w), 1));
			}
		}
		else{
			if (h > 0){
				halls.push_back(new Hall(temp2.x, temp2.y, 1, abs(h)));
			}
			else if (h < 0){
				halls.push_back(new Hall(temp1.x, temp1.y, 1, abs(h)));
			}
		}*/
	
}

Room* Leaf::getRandomChildRoom(){
	if (room != NULL){
		return room;
	}
	else{
		Room* lroom = NULL;
		Room* rroom = NULL;
		if (leftChild != NULL) lroom = leftChild->getRandomChildRoom();
		if (rightChild != NULL) rroom = rightChild->getRandomChildRoom();

		if (lroom == NULL && rroom == NULL){
			return NULL;
		}
		else if (rroom == NULL) return lroom;
		else if (lroom == NULL) return rroom;
		else if (rand() % 10 > 5) return lroom;
		else return rroom;
	}
}

Leaf* Leaf::getLeft(){
	return leftChild;
}

Leaf* Leaf::getRight(){
	return rightChild;
}

Room* Leaf::getRoom(){
	return room;
}

int Leaf::getWidth(){
	return _width;
}

int Leaf::getHeight(){
	return _height;
}

std::vector<Hall*> Leaf::getHall(){
	return halls;
}

int Leaf::getRandom(int min, int max){
	if (max - min == 0) return min;
	return rand() % (max - min) + min;
}

