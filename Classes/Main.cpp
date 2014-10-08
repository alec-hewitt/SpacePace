#include "HelloWorldScene.h"
#include "Main.h"
#include "Results.h"
#include <base/CCUserDefault.h>

#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

USING_NS_CC;

Scene* Main::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Main::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");

    _SCORE ="key1";

    CCUserDefault *def=CCUserDefault::sharedUserDefault();
    def-> setIntegerForKey("_SCORE", score);
    def->flush();

    //particles
    emitter = CCParticleSystemQuad::create();
    emitter = CCParticleRain::create();
    emitter->setSpeed(800.0);
    this->addChild(emitter);

    //update
    this->scheduleUpdate(); //start update function
    //score
    score = 0;
    //score ui
    scoreLabel = LabelTTF::create("Hello World", "galaxy.ttf", 150);
    scoreLabel->setPosition(Point(visibleSize.width/2 - 75, origin.y + visibleSize.height - scoreLabel->getContentSize().height - 65));
    scoreLabel->setAnchorPoint(Point(0.0f, 0.0f));
    this->addChild(scoreLabel);

    //player
    alive = true;
    player = Sprite::create("player.png");
    player->setPosition(Point(visibleSize.width/2, 300));
    player->setScale(visibleSize.width/5*.00135);
    this->addChild(player);
    hps = player->getContentSize().width/2;

    //enemies initial spawn
    enemy1 = Sprite::create("enemy.png");
    randX = CCRANDOM_0_1()*visibleSize.width;
    enemy1->setPosition(Point(randX, 5000));
    enemy1->setScale(visibleSize.width/5*.001);
    this->addChild(enemy1);

      enemy2 = Sprite::create("enemy.png");
      randX = CCRANDOM_0_1()*visibleSize.width;
      enemy2->setPosition(Point(randX, 6000));
      enemy2->setScale(visibleSize.width/5*.001);
      this->addChild(enemy2);

        enemy3 = Sprite::create("enemy.png");
        randX = CCRANDOM_0_1()*visibleSize.width;
        enemy3->setPosition(Point(randX, 7000));
        enemy3->setScale(visibleSize.width/5*.001);
        this->addChild(enemy3);

    //accelerometer
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Main::OnAcceleration,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void Main::OnAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event){
	//move player by acc
	if(alive == true){
	cocos2d::Size win_size = Director::getInstance()->getWinSize();
	int w = win_size.width;
	int h = win_size.height;
	int x = this->player->getPositionX();
	x = x + (acc->x * w * 0.1);
	this->player->setPosition(x, 300);
	}
}

//frame update
void Main::update(float dt){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vec2 origin = Director::getInstance()->getVisibleOrigin();

 CCLOG("UPDATE GAME");
 if(alive == true){
	 //move enemies down
	 this->enemy1->setPositionY(this->enemy1->getPositionY() - visibleSize.width/25);
	 this->enemy2->setPositionY(this->enemy2->getPositionY() - visibleSize.width/25);
	 this->enemy3->setPositionY(this->enemy3->getPositionY() - visibleSize.width/25);
 }
 //player wall boundary
 if(player->getPositionX() <= 0){ //left
	player->setPositionX(visibleSize.width - visibleSize.width);
 }
 if(player->getPositionX() >= visibleSize.width){ //right
 	player->setPositionX(visibleSize.width);
  }

 //respawn enemies
 if(this->enemy1->getPositionY() <= -100){
	 score++;
	 randX = CCRANDOM_0_1()*visibleSize.width;
	 this->enemy1->setPosition(Point(randX, 3000));
 }
 if(this->enemy2->getPositionY() <= -100){
	 score++;
	 randX = CCRANDOM_0_1()*visibleSize.width;
 	 this->enemy2->setPosition(Point(randX, 3000));
  }
 if(this->enemy3->getPositionY() <= -100){
	 score++;
	 randX = CCRANDOM_0_1()*visibleSize.width;
 	 this->enemy3->setPosition(Point(randX, 3000));
  }
 //label
 scoreLabel->setString(ccsf("%d", score));

 //check collision
  //enemy1-player
  float one = getDistance(this->enemy1->getPositionX(), this->enemy1->getPositionY(), this->player->getPositionX(), this->player->getPositionY());
  if(one < visibleSize.width/6){ //collision
	  alive = false;
	  CCUserDefault *def=CCUserDefault::sharedUserDefault();
	  def-> setIntegerForKey("_SCORE", score);
	  def->flush();
	  //replace scene fade out
	  auto scene = Results::createScene(); //new scene instance of class to push
	  Director::getInstance()->replaceScene(TransitionFade::create(1, scene)); //push the created scene
  }
  float two = getDistance(this->enemy2->getPositionX(), this->enemy2->getPositionY(), this->player->getPositionX(), this->player->getPositionY());
  if(two < visibleSize.width/6){ //collision
	  alive = false;
	  CCUserDefault *def=CCUserDefault::sharedUserDefault();
	  def-> setIntegerForKey("_SCORE", score);
	  def->flush();
	  //replace scene fade out
	  auto scene = Results::createScene(); //new scene instance of class to push
	  Director::getInstance()->replaceScene(TransitionFade::create(1, scene)); //push the created scene
  }
  float three = getDistance(this->enemy3->getPositionX(), this->enemy3->getPositionY(), this->player->getPositionX(), this->player->getPositionY());
  if(three < visibleSize.width/6){ //collision
	  alive = false;
	  CCUserDefault *def=CCUserDefault::sharedUserDefault();
	  def-> setIntegerForKey("_SCORE", score);
	  def->flush();
	  //replace scene fade out
	  auto scene = Results::createScene(); //new scene instance of class to push
	  Director::getInstance()->replaceScene(TransitionFade::create(1, scene)); //push the created scene
  }

} //update

float Main::getDistance(float enemyx, float enemyy, float playerx, float playery){
	float distance;
	float xValue = (enemyx - playerx) * (enemyx - playerx);
	float yValue = (enemyy - playery) * (enemyy - playery);
	float xySum = xValue + yValue;
	distance = sqrt(xySum);
	return distance;
}
