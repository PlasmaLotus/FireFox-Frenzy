#include "PlayerDrawable.h"
#include "../States/StateManager.h"
#include "../Game/Shield.h"
#include "../Game/GameLogic.h"
#include <math.h>
PlayerDrawable::PlayerDrawable() {

}
PlayerDrawable::PlayerDrawable(Player *pl) :
	player(pl)
	//m_shaderLoaded(false)
{
	playerShape.setFillColor(sf::Color::Blue);
	int width = GameLogic::PLAYER_COLLISION_HITBOX_WIDTH;
	int height = GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT;
	playerShape.setSize(sf::Vector2f(width, height));

	cursorShape.setFillColor(sf::Color::Cyan);
	cursorShape.setRadius(2);
	playerColor = sf::Color::Cyan;
	posX = player->posX;
	posY = player->posY;
	int dashOffsetNumber{ 5 };
	for (int i = 0; i <= dashOffsetNumber; i++) {
		sf::RectangleShape r(sf::Vector2f(player->width, player->height));
		r.setFillColor(playerColor);
		//r.setPosition(sf::Vector2f(posX - player->width / 2, posY - player->height / 2));
		r.setPosition(sf::Vector2f(posX , posY ));

		dashOffsetShapes.push_back(r);
	}
	
	if (!rTexture.loadFromFile("./Assets/Images/player2.png")) {
		printf("Unable to load Player PNG\n");
	}

	if (!m_font.loadFromFile("./Assets/fonts/Minecraft.ttf")) {
		printf("Unable to load Minecraft Font\n");
	}
	m_hpText = sf::Text("HP", m_font, 12);
	m_dashText = sf::Text("Dash", m_font, 12);
	m_ammoText = sf::Text("Ammo", m_font, 12);
	m_shotText = sf::Text("Shot", m_font, 12);
	m_hpText.setFillColor(sf::Color::Red);
	m_dashText.setFillColor(sf::Color::Cyan);
	m_shotText.setFillColor(sf::Color::Green);
	m_ammoText.setFillColor(sf::Color::Cyan);

	sprite.setTexture(rTexture);
	sprite.setOrigin(sf::Vector2f(1.0f *sprite.getGlobalBounds().width/2, 1.0f * sprite.getGlobalBounds().height / 2));
	sprite.setScale(sf::Vector2f(1.0f* GameLogic::PLAYER_DISPLAY_HITBOX_WIDTH / rTexture.getSize().x , 1.0 * GameLogic::PLAYER_DISPLAY_HITBOX_HEIGHT / rTexture.getSize().y ));
	//sprite.setColor(sf::Color::Magenta);
	// Load the shader
	/*
	if (m_shader.loadFromFile("Assets/Shaders/bloom.frag", sf::Shader::Fragment)) {
		m_shader.setUniform("frag_ScreenResolution", sf::Vector2i(StateManager::getWindowWidth(), StateManager::getWindowHeight()));
		m_shaderLoaded = true;
	}
	*/
		//return false;
	//m_shader.setUniform("texture", sf::Shader::CurrentTexture);

}
PlayerDrawable::~PlayerDrawable() {

}

void PlayerDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//sf::RenderStates state;
	//states.blendMode = sf::BlendAdd;
	//states.shader = &m_shader;
	//states.texture = playerShape.getTexture();
	target.draw(playerShape);
	target.draw(sprite);
	target.draw(cursorShape);

	if (player->state == PlayerState::Dashing) {
		for (int i = dashOffsetShapes.size() - 1; i >= 0; i--) {
			sf::RectangleShape r = dashOffsetShapes.at(i);
			if (i == dashOffsetShapes.size() - 1){
				r.setPosition(posX, posY);
			}
			if (i > 0) {
				sf::RectangleShape r2 = dashOffsetShapes.at(i - 1);
				sf::Vector2f v = r2.getPosition();
				r.setPosition(v.x, v.y);
			}
			target.draw(r);
		}

	} 
	else{
		sf::RectangleShape r = dashOffsetShapes.at(0);
		r.setPosition(posX, posY);

	}

	//Shield Display
	//if (player->shieldActive) {
	if (player->state == PlayerState::Shielding){
		printf(" --- Player Shield Active ---\n");
		int shieldHitboxExtension = 10;
		sf::CircleShape shieldShape;
		//Projectile &sh{ player->_shield };
		shieldShape.setFillColor(sf::Color(100,200,100,100));
		shieldShape.setRadius(player->_shield.width);
		//shieldShape.setPo
		//shieldShape.setPosition(sf::Vector2f(sh.posX - ((sh.width + shieldHitboxExtension) / 2), sh.posY - ((sh.width + shieldHitboxExtension) / 2)));
		//shieldShape.setPosition(sf::Vector2f(sh.posX - sh.width - player->width/2, sh.posY  - sh.height- player->height/2));
		shieldShape.setPosition(sf::Vector2f(player->_shield.posX - (player->_shield.width ) , 
			player->_shield.posY - (player->_shield.width ) ));

		target.draw(shieldShape);
	}
	target.draw(m_hpText);
	target.draw(m_ammoText);
	if (isChargingShot) {
		target.draw(m_shotText);
	}
	if (isChargingDash) {
		target.draw(m_dashText);
	}
	for (const PlayerDrawableAlert& alert : m_alerts)
		target.draw(alert, states);
}

bool PlayerDrawable::onLoad()
{
	return false;
}

void PlayerDrawable::update()
{
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
	/*Shader initialisatidwaon*/
	/*
	sf::Glsl::Ivec3 color{ playerShape.getFillColor().r, playerShape.getFillColor().g, playerShape.getFillColor().b };
	//m_shader.setUniform();
	//sf::Shader::se
	//m_shader.setParameter("wave_phase", 10);
	m_shader.setUniform("frag_LightOrigin", playerShape.getPosition());
	m_shader.setUniform("frag_LightColor", color);
	m_shader.setUniform("frag_LightAttenuation", 50);
	*/
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
		if (player->_shotChargeHeldTime >= GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME) {
			isChargingShot = true;
			std::string s;
			s += std::to_string(player->_shotChargeHeldTime);
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
