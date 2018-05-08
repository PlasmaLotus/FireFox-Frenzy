#ifndef __PARTICLE_SYSTEM__
#define __PARTICLE_SYSTEM__

#include <SFML\Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count);
	~ParticleSystem();

	void setEmitter(sf::Vector2f position);

	void update(int dt);
	
	bool isAlive();
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

private:

	struct Particle
	{
		sf::Vector2f velocity;
		int lifetime;
	};

	void resetParticle(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		//float speed = (std::rand() % 25) + 0.3f;
		float speed = 0.5f;
		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = (std::rand() % 2000 + 1000);

		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	int m_lifetime;
	sf::Vector2f m_emitter;
};


#endif // !__PARTICLE_SYSTEM__


