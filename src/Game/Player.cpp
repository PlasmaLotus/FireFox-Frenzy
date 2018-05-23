#include <math.h>
#include <cmath>
#include "Player.h"
#include "../Main.h"
#include "GameLogic.h"
#include "Enemy\Enemy.h"
#include "../States/StateManager.h"

Player::Player():
	Player(nullptr){
}

Player::Player(GameLogic * g, Vector2 v) :
	Player(g, v.x, v.y) {
}

Player::Player(GameLogic *g) :
	Player(g, 0, 0) {
}

Player::Player(GameLogic * g, float x, float y):
	SquareEntity(x, y, GameLogic::PLAYER_COLLISION_HITBOX_WIDTH, GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT),
	_game(g),
	HP(GameLogic::PLAYER_BASE_HP),
	ammo(GameLogic::PLAYER_BASE_AMMO),
	dashVelocity(GameLogic::PLAYER_DASH_VELOCITY),
	state(PlayerState::Moving),
	ability(new NormalPowerUp(g)),
	color(0,0,0,0){
	velocityX = 0.f;
	velocityY = 0.f;
	orientation = 0.f;
	orientationX = 0.f;
	orientationY = 0.f;
	cursorOrientation = 0.f;
	cursorOrientationX = 0.f;
	cursorOrientationY = 0.f;
	shootHeld = false;
	//dashVelocity = 5.0f;
	dashTime = 0;
	//dashAmmo = 3;
	shieldActive = false;
	_shieldActive = false;
	_shieldActiveDuration = 0;
	_shield.width = GameLogic::PLAYER_SHIELD_RADIUS;
	_shield.height = GameLogic::PLAYER_SHIELD_RADIUS;
}

Player::~Player()
{
}

void Player::setGame(GameLogic * g)
{
	_game = g;
}

GameLogic * Player::getGame()
{
	return _game;
}

bool Player::isAlive() {
	return true;
}
void Player::update(int32_t dt)
{
	SquareEntity::update(dt);
	handleAbility(dt);
	_handleMovement(dt);
	/*Projectiles*/
	//handleProjectiles(dt);
	shootHeld = false;
	shootHeldAlt = false;
	/*
	shootCooldownTime--;
	if (shootCooldownTime <= 0) {
		canShoot = true;
	}
	*/
	handleShooting(dt);
	handleShootingAlt(dt);
	/*Recharging ammo*/
	handleAmmo(dt);
	/*Shield*/
	handleShield(dt);
	handleDash(dt);
}

void Player::setPlayerOrienation(float x, float y)
{
	orientation = std::atan2(x, y);
	orientationX = x;
	orientationY = y;
}

void Player::setDashOrientation(float x, float y)
{
	if (abs(x) > 10 && abs(y) > 10) {
		dashOrientation = std::atan2(x, y);
		dashOrientationX = x;
		dashOrientationY = y;
	}
}

/*Enables autoFire*/
void Player::setCursorOrientation(float x, float y)
{
	cursorOrientation = std::atan2(x, y);
	cursorOrientationX = x;
	cursorOrientationY = y;

	if ( std::abs(x) > 50 || std::abs(y) > 50) {
		_shootHeld = true;
	}
	else {
		_shootHeld = false;
	}
}

void Player::setCursorOrientationFromMouse(int x, int y)
{
	//printf("MousePos: %d, %d\n", x, y);
	setCursorOrientation( x - posX , y - posY);
}

bool Player::testCollision(Entity * e)
{
	if (shieldActive || state == PlayerState::Shielding) {
		//Test Collision with Player's Shield instead of Player
		return _shield.testCollision(e);
	}
	else {
		//Test Collision with Player
		if (e != nullptr) {
			CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
			SquareEntity* se = dynamic_cast<SquareEntity*>(e);
			Player* pe = dynamic_cast<Player*>(e);
			Projectile *pre = dynamic_cast<Projectile*>(e);
			if (pe != nullptr) {
				return (collidableWith(pe) ? SquareEntity::testCollision(*pe) : false);
			}
			else if (pre != nullptr) {
				return (collidableWith(pre) ? SquareEntity::testCollision(*pre) : false);
			}
			else if (ce != nullptr) {
				return SquareEntity::testCollision(*ce);
			}
			else if (se != nullptr) {
				return SquareEntity::testCollision(*se);
			} 
			else{
				return (collidableWith(e) ? SquareEntity::testCollision(*e) : false);
			}
		}
		else
			return false;
	}

}

void Player::handleCollision(){
}

void Player::_handleCollision(PowerUpItem p) {
	/*PowerUpÎtem*/
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerPickupPowerUp, this));

	ability = p.powerUp;
	//p.handleCollision();
}

void Player::_handleCollision(Projectile p){
	/*Projectile hits the player*/
	if (shieldActive) {
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::ShieldHit, this));
		_loseAmmo(p.power *GameLogic::GAME_SHIELD_ENERGY_LOSS_MULTIPLYER);
	}
	else {
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerHit, this));
		HP -= p.power;
		//HP -= 1;
	}
}

void Player::_handleCollision(Energy e){

	/*Energy Pack hits the player*/
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerPickupEnergy, this));
	ammo += e.aura;
	if (ammo > GameLogic::PLAYER_MAX_AMMO) {
		ammo = GameLogic::PLAYER_MAX_AMMO;
	}
}

/*
void Player::_handleCollision(Enemy e) {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerHit, this));
	if (shieldActive) {
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::ShieldHit, this));
		_loseAmmo(e.power *GameLogic::GAME_SHIELD_ENERGY_LOSS_MULTIPLYER);
	}
	else {
		HP -= e.power;
		//HP -= 1;
	}
}
*/

void Player::handleCollision(Entity * e){
	try{
		Player *p = dynamic_cast<Player *>(e);
		if (p != nullptr) {
			//handlecollisoin with player;
		}
	}
	catch (const std::bad_cast& cast){
	}

	try{
		Projectile *p = dynamic_cast<Projectile *>(e);
		if (p != nullptr) {
			//handlecollisoin with Projectile;
			bool handle = true;
			//If projectile isnt generated by this
 			if (p->getPlayerID() != getID()) {
				//Check if projectile hasnt colllided with this before
				for (int i = _collisions.size()-1; i >= 0; i--){
					CollisionStack stack = _collisions.at(i);
					if (stack._id == p->getID()) {
						if (stack.delay >= 0) {
							handle = false;
						}
					}
				}
				if (handle) {
					CollisionStack stack{ p->getID(), p->_collisionDelay };
					_collisions.push_back(stack);
					_handleCollision(*p);
				}
			}

		}
	}
	catch (const std::bad_cast& cast){
	}
	
	try{
		Energy *p = dynamic_cast<Energy *>(e);
		if (p != nullptr) {
			//handlecollisoin with player;
			if (p->state == ItemState::ItemActive) {
				_handleCollision(*p);
				p->handleCollision();
			}
		}
	}
	catch (const std::bad_cast& cast) {
	}
	
	try {
		PowerUpItem *p = dynamic_cast<PowerUpItem *>(e);
		if (p != nullptr) {
			//handlecollisoin with player;
			_handleCollision(*p);
			p->handleCollision();
		}
	}
	catch (const std::bad_cast& cast) {
	}
	
}

bool Player::collidableWith(Entity* e){
	return true;
}

bool Player::collidableWith(Projectile* e){
	return (e->getPlayerID() != getID());
}

bool Player::collidableWith(Player* e){
	return (e->getID() != getID());
}



void Player::handleDash(int dt)
{
	dashHeld = _dashHeld;

	dashCooldownTime -= dt;
	if (dashCooldownTime <= 0) {
		canDash = true;
		dashCooldownTime = 0;
	}

	if (dashHeld && canDash) {
		_dashChargeHeldTime += dt;
		if (_dashChargeHeldTime >= GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME) {
			_dashChargeHeldTime = GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME;
		}
	}
	else {
		if (_dashChargeHeldTime > 0) {
			//shootHeld = false;
			canDash = false;
			dashCooldownTime = DASH_COOLDOWN;
			if (_dashChargeHeldTime >= GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME) {
				_dashChargeHeldTime = GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME;
			}
			if (state == PlayerState::Moving || PlayerState::Shielding) {
				if (ammo >= GameLogic::PLAYER_DASH_MINIMUM_CHARGE_TIME) {
					int dashPower = 1.0f * _dashChargeHeldTime / GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME * GameLogic::PLAYER_DASH_MAXIMUM_ENERGY_COST;
					_loseAmmo(dashPower);
					state = PlayerState::Dashing;
					
					if (orientation == 0.f) {
						dashOrientation = orientation;
						dashOrientationX = orientationX;
						dashOrientationY = orientationY;
					}
					else {
						//dashOrientation = dashAngle ;
						dashOrientationX = sin(dashAngle) * 100;
						dashOrientationY = cos(dashAngle) * 100;
					}
					
					


					dashTime = GameLogic::PLAYER_DASH_DURATION;
					dashVelocity = GameLogic::PLAYER_DASH_VELOCITY * _dashChargeHeldTime / GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME + GameLogic::PLAYER_MINIMUM_DASH_VELOCITY;
				}
				else {
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::OutOfAmmo, this));
				}
			}
			_dashChargeHeldTime = 0;
			dashHeld = false;
		}
		dashHeld = false;
	}
	_dashHeld = false;
}

void Player::handleAmmo(int dt)
{
	/*
	if (ammo < 0) {
		ammo = 0;
	}
	*/
	_ammoRechargeProgress += dt;
	if (ammo >= GameLogic::PLAYER_MAX_AMMO) {
		ammo = GameLogic::PLAYER_MAX_AMMO;
		_ammoRechargeProgress = 0;
	}
	else {
		if (_ammoRechargeProgress >= GameLogic::PLAYER_AMMO_RECHARGE_COOLDOWN) {
			while (_ammoRechargeProgress >= GameLogic::PLAYER_AMMO_RECHARGE_COOLDOWN) {
				if (ammo < GameLogic::PLAYER_MAX_AMMO) {
					_ammoRechargeProgress -= GameLogic::PLAYER_AMMO_RECHARGE_COOLDOWN;
					_gainAmmo(1);
				}
			}
		}
	}
}

void Player::handleShooting(int dt)
{
	/*Rapid FIRE*/
	if (_shootHeld) {
		shootHeld = true;
	}
	shootCooldownTime-= dt;
	if (shootCooldownTime <= 0) {
		canShoot = true; 
		shootCooldownTime = 0;
	}

	/*AutoFire*/
	/*
	if (_autoFire && _shotChargeHeldTime >= GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME) {
		shootHeld = false;
	}
	*/

	if (ammo > 0) {
		if (shootHeld && canShoot) {
			/*
			if (_shotChargeHeldTime <= 0) {
				//StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStart, this));
			}

			else if (_shotChargeHeldTime >= (GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME / 2)) {
				if (_shotChargeHeldTime >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStartMax, this));
				}
				else {
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStartMid, this));
				}
			}
			*/


			_shotChargeHeldTime += dt;
			if (_shotChargeHeldTime >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
				_shotChargeHeldTime = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
			}
		}
			if (_shootHeld) {
				if (_shotChargeHeldTime > 0 && _shotChargeHeldTime >= ability->minimumChargeTime) {
					//shootHeld = false;
					canShoot = false;
					shootCooldownTime = GameLogic::PLAYER_SHOOT_COOLDOWN;
					if (_shotChargeHeldTime >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
						_shotChargeHeldTime = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
					}
					//float ratio = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
					int projectilePower = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME * GameLogic::PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST;

					if (ammo > 0) {
						_handleShooting(projectilePower);//spanws projectile with properties

					}
					else {
						shootHeld = false;
						StateManager::getInstance().eventManager.queueEvent(Event(EventType::OutOfAmmo, this));
						StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeEnd, this));
					}

				}
			}
		
	}
		shootHeld = false;
	
	_shootHeld = false;
}

void Player::handleShootingAlt(int dt)
{

	if (_shootHeldAlt) {
		shootHeldAlt = true;
	}
	shootCooldownTimeAlt -= dt;
	if (shootCooldownTimeAlt <= 0) {
		canShootAlt = true;
		shootCooldownTimeAlt = 0;
	}

	if (canShootAlt) {
		if (shootHeldAlt) {
			/*
			if (_shotChargeHeldTimeAlt <= 0) {
				//StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStart, this));
				//change event
			}
			else if (_shotChargeHeldTimeAlt >= (GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME / 2)) {
				if (_shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStartMax, this));
				}
				else {
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeStartMid, this));
				}
			}
			*/

			_shotChargeHeldTimeAlt += dt;
			if (_shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
				_shotChargeHeldTimeAlt = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
			}
		}
		else {
			if (_shotChargeHeldTimeAlt > 0 && _shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME) {
				canShootAlt = false;
				shootCooldownTimeAlt = GameLogic::PLAYER_SHOOT_COOLDOWN;
				if (_shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME) {
					_shotChargeHeldTimeAlt = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
				}

				//float ratio = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
				int projectilePower = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME * GameLogic::PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST;

				if (ammo > 0) {
					_handleShootingAlt(projectilePower);//spanws projectile with properties

				}
				else {
					shootHeldAlt = false;
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::OutOfAmmo, this));
					StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeEnd, this));
				}

			}
			shootHeldAlt = false;
		}
	}
	
	_shootHeldAlt = false;
}



void Player::_handleShooting(int power) {
	/*RAPID FIRE*/
	float ratio = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
	//int projectilePower = 1.0f * _shotChargeHeldTime / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME * GameLogic::PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST;
	
	if (power <= 0) {
		power = 1;
	}
	_loseAmmo(power);
	/*
	for (int i = 0; i < ability._projectilesToSpawnThisTick; ++i) {
		//Create Projectile
		Projectile *p = ability.getProjectile(getID(), posX, posY, cursorOrientation);
		//p->orientation = cursorOrientation;
		//p->orientationX = cursorOrientationX;
		//p->orientationY = cursorOrientationY;
		p->velocityX = (GameLogic::PROJECTILE_SPEED_MAXIMUM - GameLogic::PROJECTILE_SPEED_MINIMUM) * ratio + GameLogic::PROJECTILE_SPEED_MINIMUM;
		p->velocityY = (GameLogic::PROJECTILE_SPEED_MAXIMUM - GameLogic::PROJECTILE_SPEED_MINIMUM) * ratio + GameLogic::PROJECTILE_SPEED_MINIMUM;
		p->setRadius((GameLogic::PROJECTILE_HITBOX_RADIUS_MAXIMUM - GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM) * ratio + GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM);
		p->power = power;
		_game->addEntity(p);

		//Spawn//
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::ProjectileSpawn, p));
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeEnd, this));
	}
	*/
	ability->spawnProjectile(getID(), posX, posY, cursorOrientation);
	//StateManager::getInstance().eventManager.queueEvent(Event(EventType::ProjectileSpawn));
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeEnd, this));

	shootHeld = false;
	_shotChargeHeldTime = 0;
}

void Player::_handleShootingAlt(int power) {
	float ratio = 1.0f * _shotChargeHeldTimeAlt / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
	//int projectilePower = 1.0f * _shotChargeHeldTimeAlt / GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME * GameLogic::PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST;
	
	if (power <= 0) {
		power = 1;
	}
	_loseAmmo(power);
	//Create Projectile
	Projectile *p = ability->getProjectileAlt(getID(), posX, posY, cursorOrientation);
	//p->orientation = cursorOrientation;
	//p->orientationX = cursorOrientationX;
	//p->orientationY = cursorOrientationY;
	p->velocityX = (GameLogic::PROJECTILE_SPEED_MAXIMUM - GameLogic::PROJECTILE_SPEED_MINIMUM) * ratio + GameLogic::PROJECTILE_SPEED_MINIMUM;
	p->velocityY = (GameLogic::PROJECTILE_SPEED_MAXIMUM - GameLogic::PROJECTILE_SPEED_MINIMUM) * ratio + GameLogic::PROJECTILE_SPEED_MINIMUM;
	p->setRadius((GameLogic::PROJECTILE_HITBOX_RADIUS_MAXIMUM - GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM) * ratio + GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM);
	p->power = power;

	_shotChargeHeldTimeAlt = 0;
	shootHeldAlt = false;

	/*Spawn*/
	_game->addEntity(p);
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::ProjectileSpawn, p));
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerShotChargeEnd, this));
	//change events
}

void Player::handleAbility(int dt){
	if (ability == nullptr) {
		ability = new NormalPowerUp(_game);
	}
	if (dynamic_cast<NormalPowerUp*>(ability) == nullptr) {
		if (!ability->isAlive()) {
			delete ability;
			//if (ability )
			ability = new NormalPowerUp(_game);
			StateManager::getInstance().eventManager.queueEvent(Event(EventType::PlayerPowerUpLoss, this));
		}
	}
	
	ability->update(dt);
}

void Player::handleShield(int dt)
{
	//shieldActive = _shieldActive;
	if (!_shieldActive) {
		if (shieldActive) {
			StateManager::getInstance().eventManager.queueEvent(Event(EventType::ShieldOff, this));
		}
		shieldActive = false;
		_shieldActiveDuration = 0;
		state = Moving;
	}
	else {
		if (!shieldActive) {
			StateManager::getInstance().eventManager.queueEvent(Event(EventType::ShieldOn, this));
		}
		_shieldActiveDuration++;
		shieldActive = true;
	}

	_shieldActive = false;
	if (shieldActive) {
		state = Shielding;
	}

	_shield.update(dt);
	_shield.posX = posX;
	_shield.posY = posY;
}


/*Handle when Player presses the Shoot command*/
void Player::commandShootAlt() {

	_shootHeldAlt = true;
}

void Player::commandDash() {
	_dashHeld = true;
	dashOrientation = orientation;
	dashOrientationX = orientationX;
	dashOrientationY = orientationY;
}

void Player::commandShield(){
	_shieldActive = true;
}

void Player::_gainAmmo(int nb){
	ammo += nb;
	//StateManager::getInstance().eventManager.queueEvent(Event(EventType::GainAmmo, this));
}

void Player::_loseAmmo(int nb){
	ammo -= nb;
	if (ammo < 0) {
		nb += ammo;
	}
	double energyConstant = 0.50;
	if (nb * energyConstant >= GameLogic::ENERGY_MINIMUM_AURA) {
		Energy *e{ new Energy(posX, posY, nb * energyConstant) };
		_game->addEntity(e); 
	}
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::LoseAmmo, this));
}

//move the 
void Player::commandMove(float x, float y) {
	_moveEngaged = true;
}

void Player::_handleMovement(int dt) {
	/*Movement*/
	prevPosX = posX;
	prevPosY = posY;
	if (orientation == 0.f) {
		if (std::abs(velocityX) > GameLogic::PLAYER_VELOCITY_DEAD_ZONE && std::abs(velocityY) > GameLogic::PLAYER_VELOCITY_DEAD_ZONE) {

			dashAngle = std::atan2(velocityX, velocityY) ;
		}
	}
	float orienX = orientationX / 100;
	float orienY = orientationY / 100;
	//printf("PLAYER STATE:: %d\n", state);
	switch (state) {
	case::PlayerState::Moving: {
		if (_moveEngaged) {
			int reducethespeedaittle = 100;
			velocityX += orienX * GameLogic::PLAYER_ACCELERATION_RATE;
			velocityY += orienY * GameLogic::PLAYER_ACCELERATION_RATE;
		}
		else {
			/*Redeploy orientation*/
			orientation = std::atan2(velocityX, velocityY);
			orientationX = velocityX;
			orientationY = velocityY;
		}
		bool vXPositif = true;
		bool vYPositif = true;
		if (velocityX < 0.0f) {
			vXPositif = false;
		}
		if (velocityY < 0.0f) {
			vYPositif = false;
		}

		/// Friction ///
		if (std::abs(velocityX) <= GameLogic::PLAYER_VELOCITY_DEAD_ZONE) {
			velocityX = 0.0f;
		}
		else {
			velocityX *= GameLogic::PLAYER_FRICTION;
			//velocityX *= std::pow(GameLogic::PLAYER_FRICTION, 1/dt);
		}

		if (std::abs(velocityY) <= GameLogic::PLAYER_VELOCITY_DEAD_ZONE) {
			velocityY = 0.0f;
		}
		else {
			velocityY *= GameLogic::PLAYER_FRICTION;
			//velocityY *= std::pow(GameLogic::PLAYER_FRICTION, 1/dt);
		}

		/// Reduce Velocity when exceeding max ///
		if (std::abs(velocityX) > GameLogic::PLAYER_DASH_VELOCITY) {
			velocityX += orienX * -1.0f * GameLogic::PLAYER_MAX_VELOCITY_DECREASE_RATE;
		}
		/*
		if (std::abs(velocityX) > GameLogic::PLAYER_MAX_VELOCITY) {
			velocityX += orienX * -1.0f * GameLogic::PLAYER_MAX_VELOCITY_DECREASE_RATE ;
		}
		*/

		if (std::abs(velocityY) > GameLogic::PLAYER_DASH_VELOCITY) {
			velocityY += orienY * -1.0f * GameLogic::PLAYER_MAX_VELOCITY_DECREASE_RATE;
		}
		/*
		if (std::abs(velocityY) > GameLogic::PLAYER_MAX_VELOCITY) {
			velocityY += orienY * -1.0f * GameLogic::PLAYER_MAX_VELOCITY_DECREASE_RATE ;
		}
		*/
		/*
		posX += velocityX;
		posY += velocityY;
		*/
		break;
	}
	case::PlayerState::Dashing: {
		handleDash(dt);
		dashTime -= dt;

		float dashOriX = dashOrientationX / 100.f;
		float dashOriY = dashOrientationY / 100.f;
		//velocityX = dashOriX * GameLogic::PLAYER_DASH_VELOCITY;
		//velocityY = dashOriY * GameLogic::PLAYER_DASH_VELOCITY;
		velocityX = dashOriX * dashVelocity;
		velocityY = dashOriY * dashVelocity;
		/*
		posX += std::sin(dashOrientation) * (50) / 10 * dashVelocity;
		posY += std::cos(dashOrientation) * (50) / 10 * dashVelocity;
		*/

		if (dashTime <= 0) {
			state = PlayerState::Moving;
		}
		/*
		posX += velocityX;
		posY += velocityY;
		*/
		break;
	}
	case::PlayerState::Shielding: {
		/// FRICTION ON SHIELD ///
		if (std::abs(velocityX) <= GameLogic::PLAYER_VELOCITY_DEAD_ZONE) {
			velocityX = 0.0f;
		}
		else {
			velocityX *= GameLogic::PLAYER_SHIELD_FRICTION;
		}

		if (std::abs(velocityY) <= GameLogic::PLAYER_VELOCITY_DEAD_ZONE) {
			velocityY = 0.0f;
		}
		else {
			velocityY *= GameLogic::PLAYER_SHIELD_FRICTION;
		}
		/*
		posX += velocityX;
		posY += velocityY;
		*/
		break;
	}
	default:break;
	}
	posX += dt * velocityX;
	posY += dt * velocityY;



	_moveEngaged = false;
}