#include "Alert.h"
#include <iostream>
Alerts::Alerts(const std::string & fileLocation, float fontSize, sf::Vector2u windowSize)
{
	this->location = fileLocation;

	if (!m_font.loadFromFile(fileLocation))
		std::cout << "Error, file is unavailable" << std::endl;

	this->fontSize = fontSize;
	this->windowSize = windowSize;

	_controls1 = "Use mouse click to select a Tile and edit its settings.";
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

void Alerts::removeAlert(unsigned int i)
{
}

void Alerts::update()
{
	for (int i = m_alerts.size() - 1; i >= 0; --i) {
		Alert& alert{ m_alerts.at(i) };
		--(alert.timer);
		if (alert.timer < 0) {
			m_alerts.erase(m_alerts.begin()+ i);
			updateAlertsPlacement();
		}
	}


}

void Alerts::setFontSize(float size){
	fontSize = size;
}

void Alerts::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Text textControls1(_controls1, m_font, 12);
	textControls1.setPosition(75, windowSize.y - 100);
	target.draw(textControls1, states);


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
		alert.setPosition(sf::Vector2f((windowSize.x - textSize) / 2, textPos));
	}
}



Alert::Alert(const std::string & text, const sf::Font & font, float fontSize):
	sf::Text(text, font, fontSize),
	timer{250}{
	setFillColor(sf::Color::Cyan);
}
