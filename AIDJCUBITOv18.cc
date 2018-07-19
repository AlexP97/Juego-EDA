#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv18


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
  typedef vector< vector<bool> > Mocup;
  typedef vector< vector<bool> > Mvis;
  
  bool posicio_valida_f(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  int moviment_f(int x, int y, Mdist& md, Mocup mo, Pos& ps) {
    queue<Pos> p;
    bool trobat = false;
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id == -1 && cell(i,j).owner != 0 && not mo[pos.i][pos.j]) {
	trobat = true;
	ps = pos;
      }
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && md[i+is[k]][j+js[k]] == 999) {
	  p.push({i+is[k],j+js[k]});
	  md[i+is[k]][j+js[k]] = md[pos.i][pos.j]+1;
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_f(Pos pos, Mvis& mv, Mocup& mo) {
      vector<int> d(4,999);
      vector<int> is = {1,-1,0,0};
      vector<int> js = {0,0,1,-1};
      vector<Pos> p(4);
      for(int k = 0; k < 4; k++) {
	Mdist md(37, vector<int>(37,999));
	if(posicio_valida_f(pos.i+is[k],pos.j+js[k]) && not mv[pos.i+is[k]][pos.j+js[k]]) {
	  d[k] = moviment_f(pos.i+is[k], pos.j+js[k], md, mo, p[k]);
	}
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(min == d[0]) {
	  mv[pos.i+1][pos.j] = true;
	  mo[p[0].i][p[0].j] = true;
	  return Bottom;
      }
      else if(min == d[1]) {
	  mv[pos.i-1][pos.j] = true;
	  mo[p[1].i][p[1].j] = true;
	  return Top;
      }
      else if(min == d[2]) {
	  mv[pos.i][pos.j+1] = true;
	  mo[p[2].i][p[2].j] = true;
	  return Right;
      }
      else if(min == d[3]) {
	  mv[pos.i][pos.j-1] = true;
	  mo[p[3].i][p[3].j] = true;
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
    vector<int> is = {1,-1,0,0,1,-1,-1,1};
    vector<int> js = {0,0,1,-1,1,-1,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id != -1 && unit(cell(i,j).id).type != Witch && unit(cell(i,j).id).player != 0) { 
	trobat = true;
      }
      for(int k = 0; k < 8; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && md[i+is[k]][j+js[k]] == 999) {
	  p.push({i+is[k],j+js[k]});
	  md[i+is[k]][j+js[k]] = md[pos.i][pos.j]+1;
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_k(Pos pos, Mvis& mv) {
      vector<int> d(8,999);
      vector<int> is = {1,-1,0,0,1,-1,-1,1};
      vector<int> js = {0,0,1,-1,1,-1,1,-1};
      for(int k = 0; k < 8; k++) {
	Mdist md(37, vector<int>(37,999));
	if(posicio_valida_k(pos.i+is[k],pos.j+js[k]) && not mv[pos.i+is[k]][pos.j+js[k]]) {
	  d[k] = moviment_k(pos.i+is[k], pos.j+js[k], md);
	}
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(min == d[0]) {
	  mv[pos.i+1][pos.j] = true;
	  return Bottom;
      }
      else if(min == d[1]) {
	  mv[pos.i-1][pos.j] = true;
	  return Top;
      }
      else if(min == d[2]) {
	  mv[pos.i][pos.j+1] = true;
	  return Right;
      }
      else if(min == d[3]) {
	  mv[pos.i][pos.j-1] = true;
	  return Left;
      }
      else if(min == d[4]) {
	  mv[pos.i+1][pos.j+1] = true;
	  return BR;
      }
      else if(min == d[5]) {
	  mv[pos.i-1][pos.j-1] = true;
	  return TL;
      }
      else if(min == d[6]) {
	  mv[pos.i-1][pos.j+1] = true;
	  return RT;
      }
      else if(min == d[7]) {
	  mv[pos.i+1][pos.j-1] = true;
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
  
  bool no_mata_unitat(int i, int j, Mvis mv) {
    bool aliat = false;
    vector<int> is = {1,2,1,1,0,0,0,0,-1,-1,-1,-2};
    vector<int> js = {0,0,1,-1,1,2,-1,-2,1,-1,0,0};
    for(int k = 0; k < 12 and not aliat; k++) {
      if(i+is[k] >= 0 && i+is[k] < 37 && j+js[k] >= 0 && j+js[k] < 37 && mv[i+is[k]][j+js[k]]) aliat = true;
    }
    if(aliat) return false;
    else return true;
  }
  
  
  
  int moviment_w(int x, int y, Mdist& md, Mvis mv, Mocup mw, Pos& ps) {
    queue<Pos> p;
    bool trobat = false;
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    md[x][y] = 0;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id != -1 && unit(cell(i,j).id).player != 0 && unit(cell(i,j).id).type == Knight && no_mata_unitat(i,j,mv) && not mv[i][j] && not mw[i][j]) { 
	trobat = true;
	ps = pos;
      }
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_w(i+is[k],j+js[k]) && md[i+is[k]][j+js[k]] == 999) {
	  p.push({i+is[k],j+js[k]});
	  md[i+is[k]][j+js[k]] = md[pos.i][pos.j]+1;
	}
      }
    }
    if(trobat)
      return md[pos.i][pos.j];
    else 
      return 999;
  }
  
  Dir direccio_w(Pos pos, Mvis& mv, Mocup& mw) {
      vector<int> d(4,999);
      vector<int> is = {1,-1,0,0};
      vector<int> js = {0,0,1,-1};
      vector<Pos> p(4);
      for(int k = 0; k < 4; k++) {
	Mdist md(37, vector<int>(37,999));
	if(posicio_valida_w(pos.i+is[k],pos.j+js[k]) && no_mata_unitat(pos.i+is[k],pos.j+js[k],mv)) {
	  d[k] = moviment_w(pos.i+is[k], pos.j+js[k], md, mv, mw, p[k]);
	}
      }
      int min = d[0];
      for(unsigned int i = 1; i < d.size(); i++) {
	if(d[i] < min) min = d[i];
      }
      if(min == d[0]) {
	  mv[pos.i+1][pos.j] = true;
	  mw[p[0].i][p[0].j] = true;
	  return Bottom;
      }
      else if(min == d[1]) {
	  mv[pos.i-1][pos.j] = true;
	  mw[p[1].i][p[1].j] = true;
	  return Top;
      }
      else if(min == d[2]) {
	  mv[pos.i][pos.j+1] = true;
	  mw[p[2].i][p[2].j] = true;
	  return Right;
      }
      else if(min == d[3]) {
	  mv[pos.i][pos.j-1] = true;
	  mw[p[3].i][p[3].j] = true;
	  return Left;
      }
      else {
	  mv[pos.i][pos.j] = true;
	  return None;
      }
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    Mvis mv(37,vector<bool>(37,false));
    Mocup mo(37,vector<bool>(37,false));
    vector<int> vf = farmers(0);
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Dir dir_nm = direccio_f(pos,mv,mo);
      command(id,dir_nm);
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Dir dir_nm = direccio_k(pos,mv);
      command(id,dir_nm);
    }
    Mocup mw(37,vector<bool>(37,false));
    vector<int> vw = witches(0);
    for(int id : vw) {
      Pos pos = unit(id).pos;
      Dir dir_nm = direccio_w(pos,mv,mw);
      command(id,dir_nm);
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
