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
	
	if (!rTexture.loadFromFile("./Assets/Images/spaceship.png")) {
		printf("Unable to load Spaceship PNG\n");
	}

	if (!m_font.loadFromFile("./Assets/fonts/Minecraft.ttf")) {
		printf("Unable to load Minecraft Font\n");
	}
	m_hpText = sf::Text("HP", m_font, 12);
	m_hpText.setFillColor(sf::Color::Red);

	float f = 1.0 * GameLogic::PLAYER_COLLISION_HITBOX_WIDTH / rTexture.getSize().x * 1.0;
	float f2 = 1.0 * GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT / rTexture.getSize().y * 1.0;
	sprite.setTexture(rTexture);
	sprite.setScale(sf::Vector2f(1.0* GameLogic::PLAYER_COLLISION_HITBOX_WIDTH / rTexture.getSize().x , 1.0 * GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT / rTexture.getSize().y ));
	

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
}

bool PlayerDrawable::onLoad()
{
	return false;
}

void PlayerDrawable::update()
{
	posX = player->posX;
	posY = player->posY;
	playerShape.setPosition(sf::Vector2f(posX - player->width / 2, posY - player->height / 2));

	cursorShape.setPosition(sf::Vector2f(posX + player->cursorOrientationX, posY + player->cursorOrientationY));
	sprite.setPosition(sf::Vector2f(posX - player->width / 2, posY - player->height / 2));
	
	
	//sprite.setRotation(std::abs(player->orientation * std::acos(-1) / std::atan(1) * 4));
	//sprite.setRotation(std::asin(player->orientationX / player->orientationY));
	//PI = atan(1)*4
	//180* = atan(1)*4
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
	if (_hp != player->HP) {
		_hp = player->HP;
		std::string s;
		s += std::to_string(_hp);
		s += "/";
		s += std::to_string(GameLogic::PLAYER_BASE_HP);
		m_hpText.setString(s);
	}
	m_hpText.setPosition(posX - m_hpText.getGlobalBounds().width / 2, posY + player->height + 10);

}
