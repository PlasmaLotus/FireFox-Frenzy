#include "Alert.h"
#include <iostream>
Alerts::Alerts(const std::string & fileLocation, float fontSize, sf::Vector2f windowSize)
{
	this->location = fileLocation;

	if (!m_font.loadFromFile(fileLocation))
		std::cout << "Error, file is unavailable" << std::endl;

	this->fontSize = fontSize;
	this->windowSize = windowSize;

}

void Alerts::addAlert(std::string text){
	
	m_alerts.push_back(Alert(text, m_font, fontSize));
	if (m_alerts.size() >= MAX_ALERT_NUMBER) {
		m_alerts.erase(m_alerts.begin());
	}
	updateAlertsPlacement();
}
/*
void Alerts::addAlert(std::string text, sf::Color color)
{
}
*/

void Alerts::removeAlert(unsigned int i){
}

void Alerts::update(int dt, const sf::RenderWindow& window)
{
	windowSize = window.getView().getSize();
	fontSize = windowSize.x / 75;
	float windowY = window.getView().getCenter().y - window.getView().getSize().y / 2;
	float windowX = window.getView().getCenter().x - window.getView().getSize().x / 2;
	windowDimensions = sf::Vector2f(windowY, windowX);
	//m_font()

	for (int i = m_alerts.size() - 1; i >= 0; --i) {
		Alert& alert{ m_alerts.at(i) };
		--(alert.timer);
		if (alert.timer < 0) {
			m_alerts.erase(m_alerts.begin()+ i);
			updateAlertsPlacement();
		}
		else {
			//sf::Font font = alert.getFont()
			alert.setCharacterSize(fontSize);
		}
	}

}

void Alerts::setFontSize(float size){
	fontSize = size;
}

void Alerts::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	/*
	sf::Text textControls1(_controls1, m_font, 12);
	textControls1.setPosition(75, windowSize.y - 100);
	target.draw(textControls1, states);
	*/
	for (const Alert& alert : m_alerts)
		target.draw(alert, states);
}

void Alerts::updateAlertsPlacement()
{
	for (int i = 0; i < m_alerts.size(); ++i) {
		Alert& alert{ m_alerts.at(i) };
		//float textSize = alert.getCharacterSize() * alert.getString().getSize();
		float textSize = alert.getGlobalBounds().width;
		float textPos = windowSize.y - 50 - alert.getCharacterSize() * i;
		alert.setPosition(sf::Vector2f((windowDimensions.x + windowSize.x - textSize) / 2, windowDimensions.y + textPos));
		//alert.setPosition(sf::Vector2f(0, textPos));

	}
}

Alert::Alert(const std::string & text, const sf::Font & font, float fontSize):
	sf::Text(text, font, fontSize),
	timer{250}{
	setFillColor(sf::Color::Cyan);
}
