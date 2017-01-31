#include "Player.hh"
#include <cmath>
using namespace std;

#define PLAYER_NAME SirFacman

struct PLAYER_NAME : public Player {
  
  static Player* factory () {
    return new PLAYER_NAME;
  }
  
  virtual void play () {

    Pos p = pacman(me()).pos;

    // move PacMan

    if (pacman(me()).type == PacMan) vamos_pacman(p);

   // move PowerPacMan

    else if (pacman(me()).type == PowerPacMan) yeah_pacman(p);

    // move Ghosts

    for (int i = 0; i < nb_ghosts(); ++i) {

      Pos q = ghost(me(),i).pos;

      vamos_casper(q,i);
    
    }

  }

  inline bool pac_can_move (Pos p, Dir d) {
    CType t = cell(dest(p, d)).type;
    if (t == Wall or t == Gate) return false;        
    if (pacman(me()).type == PacMan and cell(dest(p, d)).id != -1) return false;
    return true;
  }
  
  inline bool ghost_can_move (Pos p, Dir d) {
    CType t = cell(dest(p, d)).type;
    if (t == Wall) return false;        
    int r = cell(dest(p, d)).id;
    if (r == -1) return true;
    if (robot(r).type==Ghost) return false;
    return true;
  }

  inline void vamos_pacman(Pos p) {
    
    vector< vector<int> > W(rows(),vector<int>(cols(),-1));

    Dir v[] = {Top,Bottom,Right,Left};

    Dir muevete = None;

    queue<Pos> C;

    C.push(p);

    W[p.i][p.j] = 0;

    bool found = false;

    while (not C.empty()) { // Primer BFS

      Pos c = C.front();

      C.pop();

      if (found) {

	 Pos aux;

	 while (W[c.i][c.j] != 0) {

	   for (int j = 0; j < 4; ++j) {

	     aux = dest(c,v[j]);

	     if (W[aux.i][aux.j] > -1 and W[c.i][c.j] > W[aux.i][aux.j]) c = aux;

	     if (W[c.i][c.j] == 0) {

	       if (v[j] == Top) muevete = Bottom;

	       else if (v[j] == Bottom) muevete = Top;

	       else if (v[j] == Right) muevete = Left;

	       else muevete = Right;

	       j = 4; // para salir del for

	     }

	   }

	 }

      }

      else {

	for (int i = 0; i < 4; ++i) {

	  if (pac_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	    Pos c2 = dest(c,v[i]);
   
	    if ( (cell(c2).type == Hammer or cell(c2).type == Mushroom or cell(c2).type == Pill) and (cell(c2).id == -1) ) {

	      // plan A: buscar Hammer, Mushroom o Pill
	      
	      found = true;
	      
	      i = 4; // para que salga del for

	      while (not C.empty()) C.pop();

	      C.push(c2);

	      W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	    }
	    
	    else {
	      
	      C.push(c2);
	      
	      W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	    }

	  }

	}

      }

    } // cierra al while (not C.empty())

    if (muevete == None) { // Segundo BFS

      W = vector< vector<int> > (rows(),vector<int>(cols(),-1));

      C.push(p);

      W[p.i][p.j] = 0;

      bool found2 = false;

      while (not C.empty()) {

	Pos c = C.front();

	C.pop();

	if (found2) {

	  Pos aux;

	  while (W[c.i][c.j] != 0) {

	    for (int j = 0; j < 4; ++j) {

	      aux = dest(c,v[j]);

	      if (W[aux.i][aux.j] > -1 and W[c.i][c.j] > W[aux.i][aux.j]) c = aux;

	      if (W[c.i][c.j] == 0) {

		if (v[j] == Top) muevete = Bottom;

		else if (v[j] == Bottom) muevete = Top;

		else if (v[j] == Right) muevete = Left;

		else muevete = Right;

		j = 4; // para salir del for

	      }

	    }

	  }

	}

	else {

	  for (int i = 0; i < 4; ++i) {

	    if (pac_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	      Pos c2 = dest(c,v[i]);
   
	      if (cell(c2).type == Dot or cell(c2).type == Bonus) {

		// plan B: buscar Dots o Bonus
	      
		found2 = true;
	      
		i = 4; // para que salga del for

		while (not C.empty()) C.pop();

		C.push(c2);

		W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	      }
	    
	      else {
	      
		C.push(c2);
	      
		W[c2.i][c2.j] = W[c.i][c.j]+1;

	      }

	    }

	  }

	}

      }

    }

    move_my_pacman(muevete);

  }

  inline void yeah_pacman(Pos p) { 

    vector< vector<int> > W(rows(),vector<int>(cols(),-1));

    Dir v[] = {Top,Bottom,Right,Left};

    Dir muevete = None;

    queue<Pos> C;

    C.push(p);

    W[p.i][p.j] = 0;

    bool found = false;

    while (not C.empty()) { // Primer BFS

      Pos c = C.front();

      C.pop();

      if (found) {

	 Pos aux;

	 while (W[c.i][c.j] != 0) {

	   for (int j = 0; j < 4; ++j) {

	     aux = dest(c,v[j]);

	     if (W[aux.i][aux.j] > -1 and W[c.i][c.j] > W[aux.i][aux.j]) c = aux;

	     if (W[c.i][c.j] == 0) {

	       if (v[j] == Top) muevete = Bottom;

	       else if (v[j] == Bottom) muevete = Top;

	       else if (v[j] == Right) muevete = Left;

	       else muevete = Right;

	       j = 4; // para salir del for

	     }

	   }

	 }

      }

      else {

	for (int i = 0; i < 4; ++i) {

	  if (pac_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	    Pos c2 = dest(c,v[i]);

	    bool hay_casper = false;

	    bool my_casper = false;

	    if ( (cell(c2).id != -1 and robot(cell(c2).id).type == Ghost) ) { // para no perseguir a mis ghosts

	      hay_casper = true;

	      int g = 0;

	      while (g < nb_ghosts() and not my_casper) {

		if (cell(c2).id == ghost(me(),g).id) my_casper = true;

		++g;

	      }

	    }

	    if ( (hay_casper and not my_casper) or (cell(c2).type == Hammer) ) {

	      // plan A: buscar fantasma rival o Hammer
	      
	      found = true;
	      
	      i = 4; // para que salga del for

	      while (not C.empty()) C.pop();

	      C.push(c2);

	      W[c2.i][c2.j] = W[c.i][c.j]+1;

	    }
	      
	    else {
	      
	      C.push(c2);
	      
	      W[c2.i][c2.j] = W[c.i][c.j]+1;

	    }

	  }

	}

      }

    } // cierra al while (not C.empty())

    if (muevete == None) { // Segundo BFS

      W = vector< vector<int> > (rows(),vector<int>(cols(),-1));

      C.push(p);

      W[p.i][p.j] = 0;

      bool found2 = false;

      while (not C.empty()) {

	Pos c = C.front();

	C.pop();

	if (found2) {

	  Pos aux;

	  while (W[c.i][c.j] != 0) {

	    for (int j = 0; j < 4; ++j) {

	      aux = dest(c,v[j]);

	      if (W[aux.i][aux.j] > -1 and W[c.i][c.j] > W[aux.i][aux.j]) c = aux;

	      if (W[c.i][c.j] == 0) {

		if (v[j] == Top) muevete = Bottom;

		else if (v[j] == Bottom) muevete = Top;

		else if (v[j] == Right) muevete = Left;

		else muevete = Right;

		j = 4; // para salir del for

	      }

	    }

	  }

	}

	else {

	  for (int i = 0; i < 4; ++i) {

	    if (pac_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	      Pos c2 = dest(c,v[i]);

	      if (cell(c2).type == Pill) {

		found2 = true;

		i = 4; // para que salga del for

		while (not C.empty()) C.pop();

		C.push(c2);

		W[c2.i][c2.j] = W[c.i][c.j]+1;

	      }

	      else {

		C.push(c2);
	      
		W[c2.i][c2.j] = W[c.i][c.j]+1;

	      }

	    }

	  }

	}

      }

    }

    if (muevete == None) { // plan C: muevete random

      int random = rand()%4;

      while (not ghost_can_move(p,v[random])) random = rand()%4;

      muevete = v[random];

    }

    move_my_pacman(muevete);

  }

  inline void vamos_casper(Pos p, int i) {
    
    vector< vector<int> > W(rows(),vector<int>(cols(),-1));

    Dir v[] = {Top,Bottom,Right,Left};

    Dir muevete = None;

    queue<Pos> C;

    C.push(p);

    W[p.i][p.j] = 0;

    bool found = false;

    bool plan_b = false;

    bool salida_plan_b = false;

    while (not C.empty()) {

      Pos c = C.front();

      C.pop();

      if (found) {

	 Pos aux;

	 while (W[c.i][c.j] != 0) {

	   for (int j = 0; j < 4; ++j) {

	     aux = dest(c,v[j]);

	     if (W[aux.i][aux.j] > -1 and W[c.i][c.j] > W[aux.i][aux.j]) c = aux;

	     if (W[c.i][c.j] == 0) {

	       if (v[j] == Top) muevete = Bottom;

	       else if (v[j] == Bottom) muevete = Top;

	       else if (v[j] == Right) muevete = Left;

	       else muevete = Right;

	       j = 4; // para salir del for

	     }

	   }

	 }

      }

      else if (plan_b) {

	while (not C.empty()) C.pop();

	W = vector< vector<int> > (rows(),vector<int>(cols(),-1));

	W[p.i][p.j] = 0;

	C.push(p);

	while (not C.empty() and not salida_plan_b) {

	  c = C.front();

	  C.pop();

	  for (int i = 0; i < 4; ++i) {

	    if (ghost_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	      Pos c2 = dest(c,v[i]);

	      if ((cell(c2).id == -1) and (cell(c2).type == Gate)) {

		// si no hay Pacmans rivales a 80 pasos, ir a una Gate

		found = true;

		plan_b = false;

		salida_plan_b = true;
	      
		i = 4; // para que salga del for

		while (not C.empty()) C.pop();

		C.push(c2);

		W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	      }

	      else {
	      
		C.push(c2);
	      
		W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	      }

	    }

	  }

	}

      }

      else {

	for (int i = 0; i < 4; ++i) {

	  if (ghost_can_move(c,v[i]) and pos_ok(dest(c,v[i])) and W[(dest(c,v[i])).i][(dest(c,v[i])).j] == -1) {
	    
	    Pos c2 = dest(c,v[i]);
   
	    if ( (cell(c2).id != -1) and (robot(cell(c2).id).type == PacMan) and (cell(c2).id != pacman(me()).id) ) {

	      // plan A: buscar Pacmans rivales
	      
	      found = true;
	      
	      i = 4; // para que salga del for

	      while (not C.empty()) C.pop();

	      C.push(c2);

	      W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	    }
	    
	    else if (W[c.i][c.j]+1 > 50) {

	      // plan B: si a 50 pasos no hay Pacmans rivales, ves a una Gate
	      
	      plan_b = true;
	      
	      i = 4; // para que salga del for
	      
	    }
	    
	    else {
	      
	      C.push(c2);
	      
	      W[c2.i][c2.j] = W[c.i][c.j]+1;
	      
	    }

	  }

	}

      }

    } // cierra al while (not C.empty())

    if (muevete != None) {

      Pos next = dest(p,muevete);

      if ( (cell(next).id != -1) and (robot(cell(next).id).type == PacMan or robot(cell(next).id).type == PowerPacMan) and (cell(next).id == pacman(me()).id) ) {

	if (muevete == Right) {

	  if (ghost_can_move(p,Top) and pos_ok(dest(p,Top))) muevete = Top;

	  else if (ghost_can_move(p,Bottom) and pos_ok(dest(p,Bottom))) muevete = Bottom;

	  else if (ghost_can_move(p,Left) and pos_ok(dest(p,Left))) muevete = Left;

	}

	else if (muevete == Left) {

	  if (ghost_can_move(p,Top) and pos_ok(dest(p,Top))) muevete = Top;

	  else if (ghost_can_move(p,Bottom) and pos_ok(dest(p,Bottom))) muevete = Bottom;

	  else if (ghost_can_move(p,Right) and pos_ok(dest(p,Right))) muevete = Right;

	}
	
	else if (muevete == Top) {

	  if (ghost_can_move(p,Right) and pos_ok(dest(p,Right))) muevete = Right;

	  else if (ghost_can_move(p,Left) and pos_ok(dest(p,Left))) muevete = Left;

	  else if (ghost_can_move(p,Bottom) and pos_ok(dest(p,Bottom))) muevete = Bottom;
	  
	}

	else { // muevete = Bottom

	  if (ghost_can_move(p,Right) and pos_ok(dest(p,Right))) muevete = Right;

	  else if (ghost_can_move(p,Left) and pos_ok(dest(p,Left))) muevete = Left;

	  else if (ghost_can_move(p,Top) and pos_ok(dest(p,Top))) muevete = Top;

	}

      }

    }

    move_my_ghost(i,muevete);

  }

};

/** * Do not modify the following line. */
RegisterPlayer(PLAYER_NAME);
