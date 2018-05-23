#include "PlayerUIDrawable.h"
#include "../States/StateManager.h"
#include "../Game/Shield.h"
#include "../Game/GameLogic.h"
#include <math.h>

/*
PlayerDrawable::PlayerDrawable():
	rTexture() {
	//rTexture = sf::Texture();
}
*/
PlayerUIDrawable::PlayerUIDrawable(GameLogic* game, Player *pl,Player* pl2,Player* pl3, Player* pl4, sf::Texture& tx, sf::Font ft, sf::View* view) :
	player(pl),
	player2(pl2),
	player3(pl3),
	player4(pl4),
	game(game),
	rTexture(tx),
	view(view)
	//m_font(ft)
	//m_shaderLoaded(false)
{
	if (pl != nullptr) {
		_players.push_back(pl);
	}
	if (pl2 != nullptr) {
		_players.push_back(pl2);
	}
	if (pl3 != nullptr) {
		_players.push_back(pl3);
	}
	if (pl4 != nullptr) {
		_players.push_back(pl4);
	}
	/*Player 3-4*/


	/*
	playerShape.setFillColor(sf::Color(0,0,255,150));
	playerShape.setOutlineColor(sf::Color::Blue);
	playerShape.setOutlineThickness(2);
	int width = GameLogic::PLAYER_COLLISION_HITBOX_WIDTH;
	int height = GameLogic::PLAYER_COLLISION_HITBOX_HEIGHT;
	playerShape.setSize(sf::Vector2f(width, height));

	cursorShape.setFillColor(sf::Color::Cyan);
	cursorShape.setRadius(2);
	playerColor = sf::Color::Cyan;
	if (player != nullptr) {
		posX = player->posX;
		posY = player->posY;
	}
	int dashOffsetNumber{ 5 };
	for (int i = 0; i <= dashOffsetNumber; i++) {
		sf::RectangleShape r(sf::Vector2f(player->width, player->height));
		r.setFillColor(playerColor);
		//r.setPosition(sf::Vector2f(posX - player->width / 2, posY - player->height / 2));
		r.setPosition(sf::Vector2f(posX , posY ));

		dashOffsetShapes.push_back(r);
	}
	
	*/
	/*
	if (!rTexture.loadFromFile("./Assets/Images/player2.png")) {
		printf("Unable to load Player PNG\n");
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

	sprite.setTexture(rTexture);
	sprite.setOrigin(sf::Vector2f(1.0f *sprite.getGlobalBounds().width/2, 1.0f * sprite.getGlobalBounds().height / 2));
	sprite.setScale(sf::Vector2f(1.0f* GameLogic::PLAYER_DISPLAY_HITBOX_WIDTH / rTexture.getSize().x , 1.0 * GameLogic::PLAYER_DISPLAY_HITBOX_HEIGHT / rTexture.getSize().y ));
	*/

}
PlayerUIDrawable::~PlayerUIDrawable() {

}

void PlayerUIDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//target.getView().get
	//sf::Vector2f targetSize = target.getView().getSize();
	//sf::Vector2f targetCenter = target.getView().getCenter();
	sf::Vector2f targetSize = view->getSize();
	sf::Vector2f targetCenter = view->getCenter();
	float fontSize = targetSize.x / 75;
	sf::Vector2f UIBackgroundSize( targetSize.x / 3.f, targetSize.y / 6.f );
	//sf::Vector2f _tab[4]{ {targetCenter.x - targetCenter.x / 2} };
	std::vector<sf::Vector2f> UIBackgroundPositions;
	UIBackgroundPositions.push_back(sf::Vector2f(targetCenter.x - targetSize.x / 2, targetCenter.y - targetSize.y / 2));
	UIBackgroundPositions.push_back(sf::Vector2f(targetCenter.x + targetSize.x / 2, targetCenter.y - targetSize.y / 2));
	UIBackgroundPositions.push_back(sf::Vector2f(targetCenter.x - targetSize.x / 2, targetCenter.y + targetSize.y / 2));
	UIBackgroundPositions.push_back(sf::Vector2f(targetCenter.x + targetSize.x / 2, targetCenter.y + targetSize.y / 2));



	std::vector<sf::RectangleShape> UIBackgroundShapes;
	for (int i = 0; i < _players.size(); ++i) {
		Player* player{ _players.at(i) };
		if (player != nullptr) {
			sf::RectangleShape UIBackground(UIBackgroundSize);
			sf::Vector2f pos = UIBackgroundPositions.at(i);
			if (i == 1) {
				pos.x = pos.x - UIBackground.getSize().x;
			}
			else if (i == 2) {
				pos.y = pos.y - UIBackground.getSize().y;
			}
			else if (i == 3) {
				pos.x = pos.x - UIBackground.getSize().x;
				pos.y = pos.y - UIBackground.getSize().y;
			}

			UIBackground.setPosition(pos);
			//UIBackground.setFillColor(sf::Color(155, 105, 105, 105));
			//playerColor = sf::Color(player->color.r, player->color.g, player->color.b, player->color.a);
			UIBackground.setFillColor(sf::Color(player->color.r, player->color.g, player->color.b, 105));
			UIBackground.setOutlineColor(sf::Color(player->color.r, player->color.g, player->color.b, player->color.a));

			UIBackground.setOutlineColor(sf::Color::Black);
			UIBackground.setOutlineThickness(3);
			target.draw(UIBackground);


			/*HP*/

			//_hp = player->HP;
			std::string sh = "HP: ";
			sh += std::to_string(player->HP);
			sh += "/";
			sh += std::to_string(GameLogic::PLAYER_BASE_HP);
			sf::Text m_hpText(sh, m_font, fontSize);
			m_hpText.setPosition(pos.x + UIBackground.getSize().x / 4, pos.y + UIBackground.getSize().y / 10);
			target.draw(m_hpText);

			/*Ammo*/
			std::string ammoS = "Ammo: ";
			ammoS += std::to_string(player->ammo);
			sf::Text m_ammo(ammoS, m_font, fontSize);
			m_ammo.setPosition(pos.x + UIBackground.getSize().x / 4, pos.y + UIBackground.getSize().y / 3);
			target.draw(m_ammo);

			/*Shooting*/
			if (player->_shotChargeHeldTimeAlt >= GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME) {
				//isChargingShot = true;
				std::string s;
				s += std::to_string(player->_shotChargeHeldTimeAlt);
				s += "/";
				s += std::to_string(GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME);
				sf::Text m_shotText(s, m_font, fontSize);
				m_shotText.setPosition(pos.x + UIBackground.getSize().x / 4, pos.y + UIBackground.getSize().y / 3 + fontSize);
				target.draw(m_shotText);
			}

			/*Dashing*/
			if (player->_dashChargeHeldTime >= GameLogic::PLAYER_DASH_MINIMUM_CHARGE_TIME) {
				//isChargingDash = true;
				std::string s;
				s += std::to_string(player->_dashChargeHeldTime);
				s += "/";
				s += std::to_string(GameLogic::PLAYER_DASH_MAXIMUM_CHARGE_TIME);
				//m_dashText.setString(s);
				sf::Text m_dashText(s, m_font, fontSize);
				m_dashText.setPosition(pos.x + UIBackground.getSize().x / 4, pos.y + UIBackground.getSize().y / 3 + fontSize * 2);
				target.draw(m_dashText);
			}
		}

		/*Timer*/
		if (game != nullptr) {
			std::string timerString = "";
			if (game->gameState == GameCurrentState::COUNTDOWN) {
				int seconds = game->countdownTimer / 1000 + 1;
				timerString += "Countdown: ";
				timerString += std::to_string(seconds);
				//timerString += std::to_string(game->_countdownIt);
			}
			else if (game->gameState == GameCurrentState::RUNNING) {
				int timeLeft = game->GAME_MAXIMUM_GAME_TIME - game->_totalDT;
				int totalSeconds = timeLeft / 1000;
				int minutes = std::floor(totalSeconds / 60);
				int seconds = (totalSeconds - minutes * 60);
				timerString += "Time: ";
				timerString += std::to_string(minutes);
				timerString += ":";
				timerString += std::to_string(seconds);
			}
			else if (game->gameState == GameCurrentState::ENDED) {
				timerString += "Game Over!";
			}
			
			sf::Text timerText(timerString, m_font, fontSize * 2);
			timerText.setFillColor(sf::Color::Yellow);
			//UIBackgroundPositions.push_back(sf::Vector2f(targetCenter.x - targetSize.x / 2, targetCenter.y - targetSize.y / 2));

			timerText.setPosition(targetCenter.x - timerText.getGlobalBounds().width / 2, targetCenter.y - targetSize.y / 2 + targetSize.y / 16);//timerText.getGlobalBounds().width / 2
			target.draw(timerText);
		}



		/*
		target.draw(m_hpText);
		target.draw(m_ammoText);
		if (isChargingShot) {
			target.draw(m_shotText);
		}
		if (isChargingDash) {
			target.draw(m_dashText);
		}
		*/
		//UIBackgroundShapes.push_back(sf::RectangleShape(UIBackgroundSize));
	}
	/*
	sf::RectangleShape UIBackground1(UIBackgroundSize);
	sf::RectangleShape UIBackground2(UIBackgroundSize);
	sf::RectangleShape UIBackground3(UIBackgroundSize);
	sf::RectangleShape UIBackground4(UIBackgroundSize);
	*/

	/*
	target.draw(playerShape);
	target.draw(sprite);
	target.draw(cursorShape);

	if (player->state == PlayerState::Dashing) {
		for (const PlayerDrawableDashPosition& dashPos : m_dashPositions) {
			sf::RectangleShape rect;
			rect.setPosition(dashPos.posX, dashPos.posY);
			rect.setPosition(player->width, player->height);
			rect.setFillColor(sf::Color::Cyan);
			target.draw(rect);
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
	*/
}

bool PlayerUIDrawable::onLoad()
{
	return true;
}

void PlayerUIDrawable::update()
{

}

void PlayerUIDrawable::setPlayer(Player * p, int pint)
{
}


/*
void PlayerDrawable::addAlert(std::string text){

	PlayerDrawableAlert a(text, m_font, 10);
	a.setPosition(posX, posY - 30);
	if (m_alerts.size() > 10) {
		m_alerts.erase(m_alerts.begin());
	}
	m_alerts.push_back(a);
	//updateAlertsPlacement();
	
}

void PlayerDrawable::setDisplayHitboxes(bool display)
{
	_displayHitboxes = display;
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
*/
