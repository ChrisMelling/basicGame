#include "Quadtree.h"
#include "Entity.h"
#include <iostream>
#include <sstream>

using namespace std;

Quadtree::Quadtree( float _x, float _y, float _width, float _height, int _level, int _maxLevel ) :
	x		( _x ),
	y		( _y ),
	width	( _width ),
	height	( _height ),
	level	( _level ),
	maxLevel( _maxLevel )
{
	shape.setPosition( x, y );
	shape.setSize( sf::Vector2f( width, height ) );
	shape.setFillColor( sf::Color( 0, 0, 0, 0 ) );
	shape.setOutlineThickness( 1.0f );
	shape.setOutlineColor( sf::Color( 64, 128, 255 ) );
	text.setPosition( x, y + level * 16 );
	text.setCharacterSize( 12 );

	if ( level == maxLevel ) {
		return;
	}

	NW = new Quadtree( x, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	NE = new Quadtree( x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SW = new Quadtree( x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SE = new Quadtree( x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
}

void Quadtree::AddObject( Entity *object ) {
	if ( level == maxLevel ) {
		objects.push_back( object );
		return;
	}
	if ( Contains( NW, object ) ) {
		NW->AddObject( object ); return;
	} else if ( Contains( NE, object ) ) {
		NE->AddObject( object ); return;
	} else if ( Contains( SW, object ) ) {
		SW->AddObject( object ); return;
	} else if ( Contains( SE, object ) ) {
		SE->AddObject( object ); return;
	}
	if ( Contains( this, object ) ) {
		objects.push_back( object );
	}
}

vector<Entity*> Quadtree::GetObjectsAt( float _x, float _y ) {
	if ( level == maxLevel ) {
		return objects;
	}
	
	vector<Entity*> returnObjects, childReturnObjects;
	if ( !objects.empty() ) {
		returnObjects = objects;
	}
	if ( _x > x + width / 2.0f && _x < x + width ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SE->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NE->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	} else if ( _x > x && _x <= x + width / 2.0f ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SW->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NW->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	}
	return returnObjects;
}

void Quadtree::Clear() {
	if ( level == maxLevel ) {
		objects.clear();
		return;
	} else {
		NW->Clear();
		NE->Clear();
		SW->Clear();
		SE->Clear();
	}
	if ( !objects.empty() ) {
		objects.clear();
	}
}

void Quadtree::SetFont( const sf::Font &font ) {
	text.setFont( font );
	if ( level != maxLevel ) {
		NW->SetFont( font );
		NE->SetFont( font );
		SW->SetFont( font );
		SE->SetFont( font );
	}
}

void Quadtree::Draw( sf::RenderTarget &canvas ) {
	stringstream ss;
	ss << objects.size();
	string numObjectsStr = ss.str();
	text.setString( numObjectsStr );
	canvas.draw( shape );
	canvas.draw( text );

	if ( level != maxLevel ) {
		NW->Draw( canvas );
		NE->Draw( canvas );
		SW->Draw( canvas );
		SE->Draw( canvas );
	}
}

bool Quadtree::Contains( Quadtree *child, Entity *object ) {
	return	 !( object->GetPosition().x < child->x ||
				object->GetPosition().y < child->y ||
				object->GetPosition().x > child->x + child->width  ||
				object->GetPosition().y > child->y + child->height ||
				object->GetPosition().x + object->GetBoundingRect().width < child->x ||
				object->GetPosition().y + object->GetBoundingRect().height < child->y ||
				object->GetPosition().x + object->GetBoundingRect().width > child->x + child->width ||
				object->GetPosition().y + object->GetBoundingRect().height > child->y + child->height );
}