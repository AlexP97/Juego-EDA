#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv3


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
  
  bool posicio_valida_w(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    return true;
  }
  
   
  bool posicio_valida_f(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
	 
  Pos moviment_f(int x, int y) {
    queue<Pos> p;
    bool trobat = false;
    Mvis m(37, vector<bool> (37,false));
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    m[x][y] = true;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id == -1 && cell(i,j).owner != 0)  
	trobat = true;
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat)
      return pos;
    else 
      return {-1,-1};
  }
  
  Dir direccio_f(Pos old_pos, Pos new_pos) {
    int x = (new_pos.i) - (old_pos.i);
    int y = (new_pos.j) - (old_pos.j);
    if(y != 0) {
      if(y > 0) 
	  return Right;
	
      if(y < 0)
	return Left;
    }
    if(x != 0) {
      if(x > 0)
	return Bottom;
      if(x < 0)
	return Top;
    }
    return None;
  }
  
  typedef vector< vector<bool> > Mvis;
  
  bool posicio_valida_k(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  Dir direccio_k(Pos old_pos, Pos new_pos) {
    int x = new_pos.i - old_pos.i;
    int y = new_pos.j - old_pos.j;
    if(x != 0 && y != 0) {
     if(x < 0 && y < 0) 
       return TL;
     if(x > 0 && y > 0)
       return BR;
     if(x > 0 && y < 0)
       return LB;
     if(x < 0 && y > 0)
       return RT;
    }
    if(y != 0) {
      if(y > 0) 
	  return Right;
      if(y < 0)
	return Left;
    }
    if(x != 0) {
      if(x > 0)
	return Bottom;
      if(x < 0)
	return Top;
    }
    return None;
  }
  
   Pos moviment_k(int x, int y) {
    queue<Pos> p;
    Mvis m(37, vector<bool> (37,false));
    vector<int> is = {1,-1,0,0,1,-1,-1,1};
    vector<int> js = {0,0,1,-1,1,-1,1,-1};
    bool trobat = false;
    p.push({x,y});
    m[x][y] = true;
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
	if(posicio_valida_k(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat) return pos;
    else return {-1,-1};
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

    
   /* vector<int> vw = witches(0);
    for(int id : vw) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_w(pos.i, pos.j);
    }*/
    
    vector<int> vf = farmers(0);
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_f(pos.i, pos.j); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_f(pos,new_pos);
	command(id,dir_nm);
      }
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_k(pos.i, pos.j); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_k(pos,new_pos);
	command(id,dir_nm);
      }
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
