#include "test.h"

class EX13 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	EX13() {
		// Aqui no construtor você inicializa a cena

		CreateFloor();

        CriaPato(0.0, 20.0f, 2);
		
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
		return new EX13;
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

    b2Body* CriaPato(float posX, float posY, float scaleFactor)
    {
        b2Body* novoObjeto;
        //Primeiro, criamos a definição do corpo
        b2BodyDef bodyDef;
        bodyDef.position.Set(posX, posY);
        bodyDef.type = b2_dynamicBody;
        b2PolygonShape* formas = new b2PolygonShape[3]; 
        b2FixtureDef* partes = new b2FixtureDef[3]; 

		//lamina
		b2Vec2* lamina = new b2Vec2[5];
		lamina[0] = b2Vec2(-1 * scaleFactor, 10 * scaleFactor);
		lamina[1] = b2Vec2(-1 * scaleFactor, -0.5 * scaleFactor);
		lamina[2] = b2Vec2(0 * scaleFactor, -2 * scaleFactor);
		lamina[3] = b2Vec2(1 * scaleFactor, -0.5 * scaleFactor);
		lamina[4] = b2Vec2(1 * scaleFactor, 10 * scaleFactor);
		formas[0].Set(lamina, 5);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[0].shape = &formas[0];
		//Setamos outras propriedades da fixture
		partes[0].density = 10.0;
		partes[0].friction = 0.5;
		partes[0].restitution = 0.5;


		//guarda
		b2Vec2* guarda = new b2Vec2[4];
		guarda[0] = b2Vec2(-2.5 * scaleFactor, 11 * scaleFactor);
		guarda[1] = b2Vec2(-2.5 * scaleFactor, 10 * scaleFactor);
		guarda[2] = b2Vec2(2.5 * scaleFactor, 10 * scaleFactor);
		guarda[3] = b2Vec2(2.5 * scaleFactor, 11 * scaleFactor);
		formas[1].Set(guarda, 4);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[1].shape = &formas[1];
		//Setamos outras propriedades da fixture
		partes[1].density = 10.0;
		partes[1].friction = 0.5;
		partes[1].restitution = 0.5;


		//cabo
		b2Vec2* cabo = new b2Vec2[4];
		cabo[0] = b2Vec2(-0.5 * scaleFactor, 15 * scaleFactor);
		cabo[1] = b2Vec2(-0.5 * scaleFactor, 11 * scaleFactor);
		cabo[2] = b2Vec2(0.5 * scaleFactor, 11 * scaleFactor);
		cabo[3] = b2Vec2(0.5 * scaleFactor, 15 * scaleFactor);
		formas[2].Set(cabo, 4);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[2].shape = &formas[2];
		//Setamos outras propriedades da fixture
		partes[2].density = 10.0;
		partes[2].friction = 0.5;
		partes[2].restitution = 0.5;
        
		novoObjeto = m_world->CreateBody(&bodyDef);
		//... e criamos a fixture do corpo  
		for (int i = 0; i < 3; i++)
			novoObjeto->CreateFixture(&partes[i]);
		return novoObjeto;
    }
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "EX13", EX13::Create);