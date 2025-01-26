
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStates.h"
#include "Audio.h"
#include "Text.h"
#include "GameObject.h"
#include "TileMap.h"


class Game
{
	public:
		Game(sf::RenderWindow& window);
		~Game();
		bool init();
		void update(float dt);
		void render();
		void mouseClicked(sf::Event event);
		void mouseReleased(sf::Event event);
		void keyPressed(sf::Event event);
		void keyReleased(sf::Event event);
		void mouseEntered(sf::Event event);
		int random_number(int min, int max);
		void bubble_spawn();
		void bubble_release(float position_x, float position_y);

		/*INITS*/
		TileMap map;
		sf::View view1;
		sf::View view2;

		int view_counter = 0;

		//PLAYER
		sf::Clock animation_clock;
		GameObject player;
		float distance_travelled = 0.0;
		int bends_timer = 0;
		sf::Clock bends_clock;
		bool get_bends = false;

		//OXYGEN
		float oxygen_bar = 1000;
		sf::RectangleShape oxygen_tank;
		sf::Texture oxygen_tank_texture;
		sf::RectangleShape oxygen;
		sf::Clock oxygen_timer;

		//BUBBLES
		int player_bubbles = 0;
		std::vector<std::shared_ptr<GameObject>> vec_bubbles;
		GameObject bubble;
		int bubble_speed_multiplier = 0;
		sf::Clock bubble_spawn_timer;

		//BENDS
		sf::RectangleShape bends_indicator;
		sf::RectangleShape death_indicator;

		sf::Clock bubble_audio_timer;

		/*GAME PLAY FUNCTIONS*/

		bool win = false;

	private:
		sf::RenderWindow& window;
		GameState game_state = GameState::MENU;

		//TEXT OBJECT STORES ALL TEXT ELEMENTS
		std::unique_ptr<Text> text;
		//REPEAT USE AUDIO CLASS OBJECT
		std::unique_ptr<Audio> audio;

		//GAME PLAY SPECIFICS
		//MOUSE
		std::shared_ptr<sf::Vector2f> mouse_position;
		std::shared_ptr<sf::Vector2f> click;
		std::shared_ptr<sf::Vector2f> left_click;
		sf::FloatRect mouse_pointer;

};
