#include "PlayerDrawable.h"
#include "../../States/StateManager.h"
#include "../../Game/Shield.h"
#include "../../Game/GameLogic.h"
#include <math.h>
#include "../GameRenderer.h"


PlayerDrawable::PlayerDrawable(Player *pl, GameRenderer* renderer, sf::Texture& tx, sf::Font ft) :
	GameDrawable(),
	player(pl),
	renderer(renderer),
	rTexture(tx)
	//m_font(ft)
	//m_shaderLoaded(false)
{
	playerShape.setFillColor(sf::Color(0,0,255,150));
	playerShape.setOutlineColor(sf::Color::Blue);
	playerShape.setOutlineThickness(2);
	int width = GameLogic::PLAYER_COLLISION_HITBOX_WIDTH;
	int height = GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT;
	playerShape.setSize(sf::Vector2f(width, height));

	cursorShape.setRadius(2);
	playerColor = sf::Color::Cyan;
	if (player != nullptr) {
		playerColor = sf::Color(player->color.r, player->color.g, player->color.b, player->color.a);
		posX = player->posX;
		posY = player->posY;
	}
	cursorShape.setFillColor(playerColor);
	/*
	int dashOffsetNumber{ 5 };
	for (int i = 0; i <= dashOffsetNumber; i++) {
		sf::RectangleShape r(sf::Vector2f(player->width, player->height));
		r.setFillColor(playerColor);
		//r.setPosition(sf::Vector2f(posX - player->width / 2, posY - player->height / 2));
		r.setPosition(sf::Vector2f(posX , posY ));

		dashOffsetShapes.push_back(r);
	}
	*/

	//m__font = sf::Font(m_font);
	//if (!m_font.loadFromFile("Assets/Fonts/Minecraft.ttf")) {
	if (!m_font.loadFromFile("Assets/Fonts/arial.ttf")) {
		printf("Unable to load Font \n");
	}
	/*
	m_hpText = sf::Text("HP", m_font, 12);
	m_dashText = sf::Text("Dash", m_font, 12);
	m_ammoText = sf::Text("Ammo", m_font, 12);
	m_shotText = sf::Text("Shot", m_font, 12);
	m_hpText.setFillColor(sf::Color::Red);
	m_dashText.setFillColor(sf::Color::Cyan);
	m_shotText.setFillColor(sf::Color::Green);
	m_ammoText.setFillColor(sf::Color::Cyan);
	*/
	sprite.setTexture(rTexture);
	sprite.setOrigin(sf::Vector2f(1.0f *sprite.getGlobalBounds().width/2, 1.0f * sprite.getGlobalBounds().height / 2));
	sprite.setScale(sf::Vector2f(1.0f* GameLogic::PLAYER_DISPLAY_HITBOX_WIDTH / rTexture.getSize().x , 1.0 * GameLogic::PLAYER_DISPLAY_HITBOX_HEIGHT / rTexture.getSize().y ));
	sprite.setColor(playerColor);
}
PlayerDrawable::~PlayerDrawable() {

}

void PlayerDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const{

	if (player != nullptr){
		target.draw(sprite);
		target.draw(cursorShape);

		if (_displayHitboxes) {
			target.draw(playerShape);
		}
		/*
		if (renderer != nullptr) {
			if (renderer->_displayHitboxes) {
				target.draw(playerShape);
			}
		}
		*/

		//Shield Display
		//if (player->shieldActive) {
		if (player->state == PlayerState::Shielding) {
			printf(" --- Player Shield Active ---\n");
			int shieldHitboxExtension = 10;
			sf::CircleShape shieldShape;
			//Projectile &sh{ player->_shield };
			shieldShape.setFillColor(sf::Color(100, 200, 100, 100));
			shieldShape.setRadius(player->_shield.width);
			//shieldShape.setPosition(sf::Vector2f(sh.posX - ((sh.width + shieldHitboxExtension) / 2), sh.posY - ((sh.width + shieldHitboxExtension) / 2)));
			//shieldShape.setPosition(sf::Vector2f(sh.posX - sh.width - player->width/2, sh.posY  - sh.height- player->height/2));
			shieldShape.setPosition(sf::Vector2f(player->_shield.posX - (player->_shield.width),
				player->_shield.posY - (player->_shield.width)));

			target.draw(shieldShape);
		}

		for (const PlayerDrawableAlert& alert : m_alerts)
			target.draw(alert, states);
	}

}

void PlayerDrawable::update(){
	if (player != nullptr) {
		posX = player->posX;
		posY = player->posY;

		playerShape.setPosition(sf::Vector2f(1.0f *posX - player->width / 2, 1.0f*posY - player->height / 2));

		cursorShape.setPosition(sf::Vector2f(1.0f* posX + player->cursorOrientationX, 1.0f* posY + player->cursorOrientationY));

		/*Withouth set Origin*/
		//sprite.setPosition(sf::Vector2f(posX - sprite.getGlobalBounds().width / 2, posY - sprite.getGlobalBounds().height / 2));
		sprite.setPosition(sf::Vector2f(posX, posY));

		/*Updating Alerts*/
		for (int i = m_alerts.size() - 1; i >= 0; --i) {
			PlayerDrawableAlert& alert{ m_alerts.at(i) };
			--(alert.timer);
			if (alert.timer < 0) {
				m_alerts.erase(m_alerts.begin() + i);
				//updateAlertsPlacement();
			}
		}

		/*Updating Dash*/
		/*
		if (player->state == PlayerState::Dashing) {
			m_dashPositions.push_back(PlayerDrawableDashPosition(posX, posY));
		}
		for (int i = m_dashPositions.size() - 1; i >= 0; --i) {
			PlayerDrawableDashPosition& d{ m_dashPositions.at(i) };
			--(d.timer);
			if (d.timer < 0) {
				m_dashPositions.erase(m_dashPositions.begin() + i);
			}
		}
		*/

		//sprite.setRotation(std::asin(player->orientationX / player->orientationY));
		//PI = atan(1)*4
		//180* = atan(1)*4

		if (player->orientation == 0.f) {
		}
		else {
			angleDeg = std::atan2(player->orientationX, -player->orientationY) * 180 / (atan(1) * 4);
		}
		//sprite.setScale(sf::Vector2f(1.0f* GameLogic::PLAYER_DISPLAY_HITBOX_WIDTH / rTexture.getSize().x, 1.0 * GameLogic::PLAYER_DISPLAY_HITBOX_HEIGHT / rTexture.getSize().y));
		//sprite.setOrigin(sf::Vector2f(1.0f *sprite.getGlobalBounds().width / 2, 1.0f * sprite.getGlobalBounds().height / 2));
		sprite.setRotation(angleDeg);

		
		if (player != nullptr) {
			/*Ammo*/
			std::string ammoS = "Ammo: ";
			ammoS += std::to_string(player->ammo);
			m_ammoText.setString(ammoS);

			/*HP*/
			if (_hp != player->HP) {
				_hp = player->HP;
				std::string s = "HP: ";
				s += std::to_string(_hp);
				s += "/";
				s += std::to_string(GameLogic::PLAYER_BASE_HP);
				m_hpText.setString(s);
			}
			/*Shooting*/
			if (player->_shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME) {
				isChargingShot = true;
				std::string s;
				s += std::to_string(player->_shotChargeHeldTimeAlt);
				s += "/";
				s += std::to_string(GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME);
				m_shotText.setString(s);
			}
			else {
				isChargingShot = false;
			}
			/*Dashing*/
			if (player->_dashChargeHeldTime >= GameLogic::PLAYER_DASH_MINIMUM_CHARGE_TIME) {
				isChargingDash = true;
				std::string s;
				s += std::to_string(player->_dashChargeHeldTime);
				s += "/";
				s += std::to_string(GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME);
				m_dashText.setString(s);
			}
			else {
				isChargingDash = false;
			}
		}

		m_hpText.setPosition(posX - m_hpText.getGlobalBounds().width / 2, posY - player->height - 10);
		m_ammoText.setPosition(posX - m_hpText.getGlobalBounds().width / 2, posY - player->height - 20);
		m_dashText.setPosition(posX - m_hpText.getGlobalBounds().width / 2, posY + player->height + 10);
		m_shotText.setPosition(posX - m_hpText.getGlobalBounds().width / 2, posY + player->height + 20);
	}
	
}

void PlayerDrawable::setPlayer(Player *p){
	player = p;
}

void PlayerDrawable::addAlert(std::string text){

	PlayerDrawableAlert a(text, m_font, 10);
	a.setPosition(posX, posY - 30);
	if (m_alerts.size() > 10) {
		m_alerts.erase(m_alerts.begin());
	}
	m_alerts.push_back(a);
	//updateAlertsPlacement();
	
}

PlayerDrawableAlert::PlayerDrawableAlert(const std::string & text, const sf::Font & font, float fontSize):
sf::Text(text, font, fontSize),
timer(250){
	setFillColor(sf::Color::Magenta);
}

PlayerDrawableDashPosition::PlayerDrawableDashPosition(float x, float y):
posX(x),
posY(y),
timer(250){
}
