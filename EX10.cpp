#include "test.h"

class EX10 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	EX10() {
		// Aqui no construtor você inicializa a cena

		CreateFloor();
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
		return new EX10;
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
		b2PolygonShape shape;
		shape.SetAsBox(13.0f, 0.25f);

		b2BodyDef bd;
		bd.position.Set(-4.0f, 22.0f);
		bd.angle = -0.25f;

		b2Body* ground = m_world->CreateBody(&bd);
		ground->CreateFixture(&shape, 0.0f);
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_B:
			if (fric < 1 && fric != 0)
			{
				fric += 0.1f;
				CreateBox(-4.5f, 25.0f, 1.0f, 1.0f, 1.0f, fric, 0.0f);
			}
			else if (fric < 1 && fric == 0)
			{
				CreateBox(-4.5f, 25.0f, 1.0f, 1.0f, 1.0f, fric, 0.0f);
				fric += 0.1f;
			}
			else if (fric == 1) {
				CreateBox(-4.5f, 25.0f, 1.0f, 1.0f, 1.0f, fric, 0.0f);
			}
			break;
		}
	}

	float fric = 0.0f;
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "EX10", EX10::Create);