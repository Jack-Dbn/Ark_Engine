#pragma once

namespace Ark {

	//Available Roles
	enum Role {
		Player = 0,
		Hazard = 1,
		Goal = 2
	};

	class GameRole
	{
	public:
		//Constructor
		GameRole();
		//Constructor - User specifies properties
		GameRole(Role type, float collisionRadius);

		//Role - Setter and Getter
		void SetRole(Role newType);
		Role GetRole();

		//Collision Radius - Setter and Getter
		void SetRadius(float newRadius);
		float GetRadius();
		

	private:
		//Fields
		Role m_role;
		float m_collisionRadius;
	};
}


