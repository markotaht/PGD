#include "leaf.h"
#include <stdio.h>
Leaf::Leaf(int x, int y, int width, int height) :
_x(x),
_y(y),
_width(width),
_height(height)
{}

bool Leaf::split(){
	srand(time(NULL));
	if (leftChild != NULL || rightChild != NULL)
		return false;

	bool splitH = rand() > 0.5;
	//Split horisontalli if width is 25% bigger than height else random split
	if (_width > _height && _width / _height >= 1.25) splitH = false;
	if (_height > _width && _height / _width >= 1.25) splitH = true;

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
		int sizeX = rand() % (_width - 5) + 3;
		int sizeY = rand() % (_height - 5) + 3;

		int posX = rand() % (_width - sizeX - 2) + 1;
		int posY = rand() % (_height - sizeY - 2) + 1;
		room = new Room(_x +posX, _y + posY, sizeX, sizeY);
	}
}

void Leaf::createHall(Room* l, Room* r){
	srand(time(NULL));
	// Ei t;;ta veel

	SDL_Point temp1{ getRandom(l->getX1() + 1, l->getX2() - 2), getRandom(l->getY1(), l->getY2()) };
	SDL_Point temp2{ getRandom(r->getX1() + 1, r->getX2() - 2), getRandom(r->getY1(), r->getY2()) };
		int w = temp1.x - temp2.x;
		int h = temp1.y - temp2.y;

		if (w < 0){
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
		else if (w>0){
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
		}
	
}

Room* Leaf::getRandomChildRoom(){
	srand(time(NULL));
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
		else if (rand() > 0.5) return lroom;
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
	srand(time(NULL));
	if (max - min == 0) return min;
	return rand() % (max - min) + min;
}

