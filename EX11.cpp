#include "test.h"

extern B2_API bool g_blockSolve;

class EX11 : public Test //você cria a sua classe derivada da classe base Test
{
public:

	enum
	{
		linhas = 6,
		colunas = 1,
		circulos = 6
	};

	EX11() {
		// Aqui no construtor você inicializa a cena

		CreateFloor();

		//CreateBox(0.0f, 40.0f, 1.0f, 1.0f, 1.0f, 0.3f, 0.75f);

		//CreateCircle(-20.0f, 40.0f, 1.5f, 1.0f, 0.3f, 0.5f);

		for (int i = 0; i < 6; i++)
		{
			CreateBox(3.5f, (5.0f + 1.1f * i), 1.0f, 1.0f, 1.0f, 0.3f, 0.0f);
			CreateCircle(-20.0f, (4.0f + 3.0f * i), 1.5f, 1.0f, 0.3f, 0.0f);
		}

		Caixas();
		Circulos();
		
	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new EX11;
	}


	void CreateCircle(float x, float y, float radius,
		float density, float friction, float restitution) //compound shapes
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x,y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2CircleShape circle;
		circle.m_radius = radius;
		//circle.m_p.Set(0.0f, 2.0f); ???

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;

		fixtureDef.density = density;

		fixtureDef.friction = friction;

		fixtureDef.restitution = restitution;

		body->CreateFixture(&fixtureDef);
	}

	void CreateBox(float x, float y, float width, float height, 
		float density, float friction, float restitution)
	{
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x,y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(width, height);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = density;

		// Override the default friction.
		fixtureDef.friction = friction;

		//bounciness
		fixtureDef.restitution = restitution;

		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);
	}

	void CreateFloor()
	{
		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;

		// The extents are the half-widths of the box.
		groundBox.SetAsBox(50.0f, 10.0f);

		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);
	}

	void Caixas() {
		float xs[5] = { 0.0f, -10.0f, -5.0f, 5.0f, 10.0f };

		for (int32 j = 0; j < colunas; ++j)
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f,0.5f);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 1.0f;
			fd.friction = 0.3f;

			for (int i = 0; i < linhas; ++i)
			{
				b2BodyDef bd;
				bd.type = b2_dynamicBody;

				int32 n = j * linhas + i;
				b2Assert(n < linhas* colunas);
				m_indices[n] = n;
				bd.userData.pointer = n;

				float x = 0.0f;
				//float x = RandomFloat(-0.02f, 0.02f);
				//float x = i % 2 == 0 ? -0.01f : 0.01f;
				bd.position.Set(xs[j] + x, 0.55f + 1.1f * i);
				b2Body* body = m_world->CreateBody(&bd);

				m_bodies[n] = body;

				body->CreateFixture(&fd);
			}
		}

		m_bullet = NULL;
	}

	void Circulos() {
		b2CircleShape shape;
		shape.m_radius = 1.0f;

		for (int32 i = 0; i < circulos; ++i)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-10.0, 4.0f + 3.0f * i);

			m_bodies[i] = m_world->CreateBody(&bd);

			m_bodies[i]->CreateFixture(&shape, 1.0f);

			m_bodies[i]->SetLinearVelocity(b2Vec2(0.0f, -50.0f));
		}
	}

	b2Body* m_bullet;
	b2Body* m_bodies[linhas*colunas];
	int32 m_indices[linhas * colunas];
	b2Body* m_bodies2[circulos];
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "EX11", EX11::Create);