#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITO


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  
  typedef vector< vector<int> > Mdist;
  typedef vector< vector<bool> > Mvis;
  
  bool posicio_valida_f(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  int moviment_f(int x, int y, Mdist& md, Mvis mf, Pos& ps) {
    queue<Pos> p;
    bool trobat = false;
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      int i = pos.i;
      int j = pos.j;
      if(posicio_valida_f(i,j) && cell(i,j).id == -1 && cell(i,j).owner != 0 && not mf[i][j]) {
	trobat = true;
	ps = pos;
      }
      else if(not posicio_valida_f(i,j) or cell(i,j).id != -1)
	p.pop();
      else {
	p.pop();
	for(int k = 0; k < 4; k++) {
	  if(md[i+is[k]][j+js[k]] == 999) {
	    p.push({i+is[k],j+js[k]});
	    md[i+is[k]][j+js[k]] = md[i][j]+1;
	  }
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_f(Pos pos, Mvis& mf) {
      vector<int> d(4,999);
      vector<int> is = {1,0,-1,0};
      vector<int> js = {0,1,0,-1};
      vector<Pos> p(4);
      for(int k = 0; k < 4; k++) {
	Mdist md(37, vector<int>(37,999));
	d[k] = moviment_f(pos.i+is[k], pos.j+js[k], md, mf, p[k]);
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(min == d[0] && min != 999) {
	  mf[p[0].i][p[0].j] = true;
	  return Bottom;
      }
      else if(min == d[1] && min != 999) {
	  mf[p[1].i][p[1].j] = true;
	  return Right;
      }
      else if(min == d[2] && min != 999) {
	  mf[p[2].i][p[2].j] = true;
	  return Top;
      }
      else if(min == d[3] && min != 999) {
	  mf[p[3].i][p[3].j] = true;
	  return Left;
      }
      else 
	  return None;
  }
  
  bool posicio_valida_k(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  int moviment_k(int x, int y, Mdist& md) {
    queue<Pos> p;
    bool trobat = false;
    vector<int> is = {1,-1,0,0,1,1,-1,-1};
    vector<int> js = {0,0,1,-1,1,-1,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      int i = pos.i;
      int j = pos.j;
      if(posicio_valida_k(i,j) && cell(i,j).id != -1 && unit(cell(i,j).id).type != Witch && unit(cell(i,j).id).player != 0) { 
	trobat = true;
      }
      else if(not posicio_valida_k(i,j) or cell(i,j).id != -1)
	p.pop();
      else {
	p.pop();
	for(int k = 0; k < 8; k++) {
	  if(md[i+is[k]][j+js[k]] == 999) {
	    p.push({i+is[k],j+js[k]});
	    md[i+is[k]][j+js[k]] = md[pos.i][pos.j]+1;
	  }
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_k(Pos pos) {
      vector<int> d(8,999);
      vector<int> is = {1,1,0,-1,-1,-1,0,1};
      vector<int> js = {0,1,1,1,0,-1,-1,-1};
      vector<Pos> p(8);
      for(int k = 0; k < 8; k++) {
	Mdist md(37, vector<int>(37,999));
	d[k] = moviment_k(pos.i+is[k], pos.j+js[k], md);
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(min == d[0] && min != 999) {
	  return Bottom;
      }
      else if(min == d[1] && min != 999) {
	  return BR;
      }
      else if(min == d[2] && min != 999) {
	  return Right;
      }
      else if(min == d[3] && min != 999) {
	  return RT;
      }
      else if(min == d[4] && min != 999) {
	  return Top;
      }
      else if(min == d[5] && min != 999) {
	  return TL;
      }
      else if(min == d[6] && min != 999) {
	  return Left;
      }
      else if(min == d[7] && min != 999) {
	  return LB;
      }
      else 
	  return None;
  }
  
  bool posicio_valida_w(int i, int j) {
    if(cell(i,j).type == Wall) 
      return false;
    return true;
  }
  
  int moviment_w(int x, int y, Mdist& md, Mvis mw, Pos& ps) {
    queue<Pos> p;
    bool trobat = false;
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      int i = pos.i;
      int j = pos.j;
      if(posicio_valida_w(i,j) && cell(i,j).id != -1 && cell(i,j).owner != 0 && unit(cell(i,j).id).player != 0 && unit(cell(i,j).id).type == Knight && not mw[i][j]) { 
	trobat = true;
	ps = pos;
      }
      else if(not posicio_valida_w(i,j) or (cell(i,j).id != -1 && unit(cell(i,j).id).player == 0))
	p.pop();
      else {
	p.pop();
	for(int k = 0; k < 4; k++) {
	  if(md[i+is[k]][j+js[k]] == 999) {
	    p.push({i+is[k],j+js[k]});
	    md[i+is[k]][j+js[k]] = md[pos.i][pos.j]+1;
	  }
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_w(Pos pos, Mvis& mw, int num) {
      vector<int> d(4,999);
      vector<int> is = {1,0,-1,0};
      vector<int> js = {0,1,0,-1};
      vector<Pos> p(4);
      for(int k = 0; k < 4; k++) {
	Mdist md(37, vector<int>(37,999));
	d[k] = moviment_w(pos.i+is[k], pos.j+js[k], md, mw, p[k]);
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(num == 1) {
	if(min == d[0]) {
	  mw[p[0].i][p[0].j] = true;
	  return Bottom;
	}
	else if(min == d[1]) {
	  mw[p[1].i][p[1].j] = true;
	  return Right;
	}
	else if(min == d[2]) {
	  mw[p[2].i][p[2].j] = true;
	  return Top;
	}
	else if(min == d[3]) {
	  mw[p[3].i][p[3].j] = true;
	  return Left;
	}
	else {
	  return None;
	}
      }
      if(num == 2) {
	if(min == d[2]) {
	  mw[p[2].i][p[2].j] = true;
	  return Top;
	}
	else if(min == d[3]) {
	  mw[p[3].i][p[3].j] = true;
	  return Left;
	}
	else if(min == d[1]) {
	  mw[p[1].i][p[1].j] = true;
	  return Right;
	}
	else if(min == d[0]) {
	  mw[p[0].i][p[0].j] = true;
	  return Bottom;
	}
	else {
	  return None;
	}
      }
      return None;
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    vector<int> vf = farmers(0);
    Mvis mf(37, vector<bool>(37,false));
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Dir dir_nm = direccio_f(pos,mf);
      command(id,dir_nm);
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Dir dir_nm = direccio_k(pos);
      command(id,dir_nm);
    }
    vector<int> vw = witches(0);
    int witch1 = vw[0];
    int witch2 = vw[1];
    Pos pos1 = unit(witch1).pos;
    Pos pos2 = unit(witch2).pos;
    if(round() <= 7) {
      int difi, difj;
      
      if(pos1.j <= pos2.j) {
	difj = pos2.j - pos1.j;
	if(pos1.i <= pos2.i) {
	  difi = pos2.i - pos1.i;
	  if(difi >= difj) {
	   command(witch1,Dir(Right)); 
	   command(witch2,Dir(Bottom));
	  }
	  else {
	   command(witch1,Dir(Bottom)); 
	   command(witch2,Dir(Right)); 
	  }
	}
	else {
	  command(witch1,Dir(Bottom)); 
	  command(witch2,Dir(Right)); 
	}
      }
      else {
	difj = pos1.j - pos2.j;
	if(pos1.i >= pos2.i) {
	  difi = pos1.i - pos2.i;
	  if(difi >= difj) {
	   command(witch1, Dir(Bottom));
	   command(witch2, Dir(Right));
	  }
	  else {
	   command(witch1,Dir(Right)); 
	   command(witch2,Dir(Bottom));
	  }
	}
	else {
	  command(witch1,Dir(Right)); 
	  command(witch2,Dir(Bottom));
	}
      }
	
    }
    else if(round() > 7) {
      Mvis mw(37, vector<bool>(37,false));
      Dir dir_nm = direccio_w(pos1,mw,1); 
      command(witch1, dir_nm);
      dir_nm = direccio_w(pos2,mw,2);
      command(witch2, dir_nm);
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
