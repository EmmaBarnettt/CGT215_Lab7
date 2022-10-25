#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
	//Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	//Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	//Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	//Left Wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 1200));
	leftWall.setCenter(Vector2f(10, 590));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	//Right Wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 1200));
	rightWall.setCenter(Vector2f(790, 590));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	//Roof
	PhysicsRectangle roof;
	roof.setSize(Vector2f(800, 20));
	roof.setCenter(Vector2f(400, 10));
	roof.setStatic(true);
	world.AddPhysicsBody(roof);

	//Square Target
	PhysicsRectangle target;
	target.setSize(Vector2f(100, 100));
	target.setCenter(Vector2f(400, 245));
	target.setStatic(true);
	world.AddPhysicsBody(target);
	bool hit = false;
	target.onCollision = [&hit](PhysicsBodyCollisionResult result) {
		hit = true;
	};

	//Counts when hitting floor
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	//Counts when hitting target
	int hitCount(0);
	target.onCollision = [&hitCount](PhysicsBodyCollisionResult result) {
		cout << "hit " << hitCount << endl;
		hitCount++;
		if (hitCount == 3) {
			exit(1);
		}
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		//calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}


		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(roof);
		window.draw(target);
		window.display();
	}
}
