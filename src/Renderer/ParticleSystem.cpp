#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(750),
	m_emitter(0, 0)
{
}

ParticleSystem::~ParticleSystem()
{
	m_particles.clear();
}

void ParticleSystem::update(int dt)
{
	m_lifetime -= dt;
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= dt;

		// if the particle is dead, respawn it
		if (p.lifetime <= 0)
			resetParticle(i);

		// update the position of the corresponding vertex
		sf::Vector2f vec(p.velocity.x * dt, p.velocity.y * dt);//   p.velocity * dt;
		m_vertices[i].position += sf::Vector2f(p.velocity.x * dt, p.velocity.y * dt);//   p.velocity * dt;

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio;
		if (m_lifetime > 0) {
			ratio = p.lifetime / m_lifetime;
		}
		else {
			ratio = 0;
		}
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		m_vertices[i].color.r = static_cast<sf::Uint8>(sin(p.lifetime) * 255);
		m_vertices[i].color.g = static_cast<sf::Uint8>(cos(p.lifetime) * 255);
		m_vertices[i].color.b = static_cast<sf::Uint8>(tan(p.lifetime) * 255);
	}
}
bool ParticleSystem::isAlive() {
	return m_lifetime > 0;
}



void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}