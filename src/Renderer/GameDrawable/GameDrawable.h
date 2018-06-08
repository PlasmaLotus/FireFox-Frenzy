/*
Created by PlasmaLotus
Updated Juin 7, 2018
*/

#ifndef __Game_General_Drawable__
#define __Game_General_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

//class GameRenderer;
class GameDrawable : public sf::Drawable {
public:

	GameDrawable(bool hitboxDisplay = true);
	~GameDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	virtual bool onLoad();
	virtual void update();
	void setViewSettings( sf::Vector2f const & viewCenter, sf::Vector2f const & viewSize);
	void setDisplayHitboxes(bool display);
protected:
	sf::Vector2f mViewSize;
	sf::Vector2f mViewCenter;
	bool _displayHitboxes;
	//std::string mDrawableName;
};


#endif // !__Game_General_Drawable__
