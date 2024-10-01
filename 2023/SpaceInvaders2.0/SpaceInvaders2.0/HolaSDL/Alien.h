#pragma once
#include "SceneObject.h"
#include "Mothership.h"

class Alien : public SceneObject
{
protected:
	int indice;						//Tipo de alien
	Mothership* mother;				//Puntero a Mothership
	int frame;						//Para decidir que frame de los dos tenemos que renderizar
	int margenAlien;				//Margen del sprite para el rebote de la pantalla
	bool bajado = false;			//Comprueba si los aliens han bajado de fila
	double speed = 20;				//Velocidad a la que se mueve el alien

	int AlienScore = 30;			//Puntos que se suman cuando se mata un alien

public:
	//Constructora vacía
	Alien() : SceneObject() {
		indice = 0;
		mother = nullptr;
		frame = 0;
		margenAlien = 0;
	}

	//Constructora
	Alien(Game* gam, Point2D<double> p, Texture* t, Mothership* m, int v, int i, int f)
		: SceneObject(gam, p, t, v) 
	{
		indice = i;
		frame = f; 
		mother = m;
		margenAlien = t->getFrameWidth() / 2;
	}

	void Render() const override;
	
	virtual void Update() override;
	
	void save(std::ostream& out) const override;

	bool Hit(const SDL_Rect* r, bool o) override;

	//Tal vez habría que ponerlo también en el SceneObject en vez de aquí
	int MargenAlien() { return margenAlien; }

	bool Bajado() { return bajado; }

	void SetMothership(Mothership* m) { mother = m; }

	

};

