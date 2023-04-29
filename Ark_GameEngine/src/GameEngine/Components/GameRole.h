#pragma once

namespace Ark {

	enum Role {
		Player = 0,
		Hazard = 1,
		Goal = 2
	};

	class GameRole
	{
	public:
		GameRole();
		GameRole(Role type, float collisionRadius);

		void SetType(Role newType);
		Role GetType();

		void SetRadius(float newRadius);
		float GetRadius();
		

	private:
		Role m_role;
		float m_collisionRadius;
	};
}


