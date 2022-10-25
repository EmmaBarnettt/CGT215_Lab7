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
	rightWall.setSize(Vector2f(20, 500));
	rightWall.setCenter(Vector2f(300, 590));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
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
		window.display();
	}
}
