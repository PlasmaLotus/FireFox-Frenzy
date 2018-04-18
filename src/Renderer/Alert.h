#ifndef __ALERT__
#define __ALERT__

#include <SFML\Graphics.hpp>


class Alerts;
class Alert : public sf::Text {
public:
	Alert(const std::string& text, const sf::Font& font, float fontSize);
	//void setPosition(const sf::Vector2f& position) = sf;
private:
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int timer;
	friend Alerts;
};

class Alerts : public sf::Drawable, sf::Transformable {
public:
	Alerts(const std::string & fileLocation, float tileSize, sf::Vector2u windowSize);
	void addAlert(std::string text);
	//void addAlert(std::string text, sf::Color color);
	void removeAlert(unsigned int i);
	void update();
	void setFontSize(float size);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateAlertsPlacement();
	//sf::Text
	float fontSize;
	sf::Font m_font;
	sf::Vector2u windowSize;
	std::string location;
	std::vector<Alert> m_alerts;
	const int MAX_ALERT_NUMBER{ 6 };
	std::string _controls1;
	std::string _controls2;
	std::string _controls3;
};

#endif