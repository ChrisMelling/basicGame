
#include "Application.h"

#include <iostream>
#include <stdio.h>

#include <conio.h>
#include <windows.h>

using namespace std;
#include <list>
#include <map>


struct Vector3
{
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f)
	{}

	float x, y, z;
};

enum eMessageType
{
	SetPosition,
	GetPosition,    
	DrawMessage,
	updateMessage,
};

class BaseMessage
{
protected: // Abstract class, constructor is protected
	BaseMessage(int destinationObjectID, eMessageType messageTypeID) 
		: m_destObjectID(destinationObjectID)
		, m_messageTypeID(messageTypeID)
	{}

public: // Normally this isn't public, just doing it to keep code small
	int m_destObjectID;
	eMessageType m_messageTypeID;
};

class Draw : public BaseMessage
{
public: // Abstract class, constructor is protected
	Draw(int destinationObjectID)
		: BaseMessage(destinationObjectID, DrawMessage)
	{

	}
};

class Update : public BaseMessage
{
public: // Abstract class, constructor is protected
	Update(int destinationObjectID)
		: BaseMessage(destinationObjectID, updateMessage)
	{

	}
};

class PositionMessage : public BaseMessage
{
protected: // Abstract class, constructor is protected
	PositionMessage(int destinationObjectID, eMessageType messageTypeID, 
		float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
		: BaseMessage(destinationObjectID, messageTypeID)
		, x(X)
		, y(Y)
		, z(Z)
	{

	}

public:
	float x, y, z;
};

class MsgSetPosition : public PositionMessage
{
public:
	MsgSetPosition(int destinationObjectID, float X, float Y, float Z)
		: PositionMessage(destinationObjectID, SetPosition, X, Y, Z)
	{}
};

class MsgGetPosition : public PositionMessage
{
public:
	MsgGetPosition(int destinationObjectID)
		: PositionMessage(destinationObjectID, GetPosition)
	{}
};

class BaseComponent
{
public:
	virtual bool SendMessage(BaseMessage* msg) { return false; }
};

class PlayerInputComponent : public BaseComponent
{
public:

	PlayerInputComponent(sf::RenderWindow* renderWindow)
		: BaseComponent()
	{
		window = renderWindow;
	}

		bool SendMessage(BaseMessage* msg)
		{
			// Object has a switch for any messages it cares about
			switch(msg->m_messageTypeID)
			{

			case updateMessage:
				{               
					cout << "Input handled \n";
				}
				break;

			default:
				return BaseComponent::SendMessage(msg);
			}

			return true;
		}

	sf::RenderWindow *window;
};


class RenderComponent : public BaseComponent
{
public:

	RenderComponent(sf::RenderWindow* renderWindow)
		: BaseComponent()
	{
		window = renderWindow;
	}

	void loadTexture(std::string filename)
	{
		if(_texture.loadFromFile(filename) == false)
		{

		}
		else
		{
			_sprite.setTexture(_texture);

			std::cout << "Texture loaded\n";
		}
	}


	bool SendMessage(BaseMessage* msg)
	{
		// Object has a switch for any messages it cares about
		switch(msg->m_messageTypeID)
		{

		case SetPosition:
			{               
				MsgSetPosition* msgSetPos = static_cast<MsgSetPosition*>(msg);
				m_Position.x = msgSetPos->x;
				m_Position.y = msgSetPos->y;
				m_Position.z = msgSetPos->z;

				cout << "RenderComponent handled SetPosition\n";
			}
			break;
		case GetPosition:
			{
				MsgGetPosition* msgSetPos = static_cast<MsgGetPosition*>(msg);
				msgSetPos->x = m_Position.x;
				msgSetPos->y = m_Position.y;
				msgSetPos->z = m_Position.z;

				cout << "RenderComponent handling GetPosition\n";
			}
			break;

		case DrawMessage:
			{                   
				window->draw(_sprite);
			}
			break;

		case updateMessage:
				{               
					cout << "RenderComponent Input handled \n";
				}
				break;

		default:
			return BaseComponent::SendMessage(msg);
		}

		return true;
	}

	sf::RenderWindow *window;
	sf::Sprite _sprite;
	sf::Texture _texture;
	Vector3 m_Position;
};

class Object
{
public:
	Object(sf::RenderWindow &renderWindow ,int uniqueID)
		: m_UniqueID(uniqueID)
	{
	}

	int GetObjectID() const { return m_UniqueID; }

	void AddComponent(BaseComponent* comp)
	{
		m_Components.push_back(comp);
	}

	bool SendMessage(BaseMessage* msg)
	{
		bool messageHandled = false;

		// Object has a switch for any messages it cares about
		switch(msg->m_messageTypeID)
		{

		default:
			return PassMessageToComponents(msg);
		}

		// If the object didn't handle the message but the component
		// did, we return true to signify it was handled by something.
		messageHandled |= PassMessageToComponents(msg);

		return messageHandled;
	}

private: // Methods
	bool PassMessageToComponents(BaseMessage* msg)
	{
		bool messageHandled = false;

		std::list<BaseComponent*>::iterator compIt = m_Components.begin();
		for ( compIt; compIt != m_Components.end(); ++compIt )
		{
			messageHandled |= (*compIt)->SendMessage(msg);
		}

		return messageHandled;
	}

private: // Members
	int m_UniqueID;
	std::list<BaseComponent*> m_Components;

};

class SceneManager
{
public: 
	// Returns true if the object or any components handled the message
	bool SendMessage(BaseMessage* msg)
	{
		// We look for the object in the scene by its ID
		std::map<int, Object*>::iterator objIt = m_Objects.find(msg->m_destObjectID);       
		if ( objIt != m_Objects.end() )
		{           
			// Object was found, so send it the message
			return objIt->second->SendMessage(msg);
		}

		// Object with the specified ID wasn't found
		return false;
	}

	Object* CreateObject(sf::RenderWindow &renderWindow)
	{
		Object* newObj = new Object(renderWindow,nextObjectID++);
		m_Objects[newObj->GetObjectID()] = newObj;

		return newObj;
	}

private:
	std::map<int, Object*> m_Objects;
	static int nextObjectID;
};

// Initialize our static unique objectID generator
int SceneManager::nextObjectID = 0;




int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

			// Create a scene manager
	SceneManager sceneMgr;

	// Have scene manager create an object for us, which
	// automatically puts the object into the scene as well
	Object* myObj = sceneMgr.CreateObject(window);

	PlayerInputComponent* inputComp = new PlayerInputComponent(&window);
	RenderComponent* renderComp = new RenderComponent(&window);

	renderComp->loadTexture("Content/ball.png");
	// Attach render component to the object we made
	myObj->AddComponent(renderComp);

	myObj->AddComponent(inputComp);

	// Set 'myObj' position to (1, 2, 3)
	MsgSetPosition msgSetPos(myObj->GetObjectID(), 1.0f, 2.0f, 3.0f);
	sceneMgr.SendMessage(&msgSetPos);
	cout << "Position set to (1, 2, 3) on object with ID: " << myObj->GetObjectID() << '\n';

	cout << "Retreiving position from object with ID: " << myObj->GetObjectID() << '\n';

	// Get 'myObj' position to verify it was set properly
	MsgGetPosition msgGetPos(myObj->GetObjectID());
	sceneMgr.SendMessage(&msgGetPos);
	cout << "X: " << msgGetPos.x << '\n';
	cout << "Y: " << msgGetPos.y << '\n';
	cout << "Z: " << msgGetPos.z << '\n';

	// Fake update method


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        
		Draw msgDraw(myObj->GetObjectID());

		sceneMgr.SendMessage(&msgDraw);

		Update msgUpdate(myObj->GetObjectID());

		sceneMgr.SendMessage(&msgUpdate);

        window.display();
    }

    return 0;
}