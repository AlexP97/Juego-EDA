#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv4


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
  
  typedef vector< vector<bool> > Mvis;
  
  bool posicio_valida_w(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    return true;
  }
  
  bool no_mata_unitat(int i, int j, Mvis m) {
    bool aliat = false;
    vector<int> is = {1,2,1,1,0,0,0,0,-1,-1,-1,-2};
    vector<int> js = {0,0,1,-1,1,2,-1,-2,1,-1,0,0};
    for(int k = 0; k < 12 and not aliat; k++) {
      if(cell(i+is[k],j+js[k]).id != -1 && m[i+is[k]][j+js[k]]) aliat = true;
    }
    if(aliat) return false;
    else return true;
  }
  
  Pos moviment_w(int x, int y, Mvis m) {
   queue<Pos> p;
   bool trobat = false;
   Mvis m2(37,vector<bool>(37,false));
   vector<int> is = {1,-1,0,0};
   vector<int> js = {0,0,1,-1};
   p.push({x,y});
   Pos pos;
   while(not p.empty() && not trobat) {
     pos = p.front();
     p.pop();
     int i = pos.i;
     int j = pos.j;
     if(cell(i,j).id != -1 && unit(cell(i,j).id).player != 0 && unit(cell(i,j).id).type != Witch && no_mata_unitat(i,j,m)) {
      trobat = true; 
     }
     for(int k = 0; k < 4; k++) {
	if(posicio_valida_w(i+is[k],j+js[k]) && not m2[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m2[i+is[k]][j+js[k]] = true;
	}
      }
   }
   if(trobat) 
     return pos;
   else 
     return {-1,-1};
  }
  
  Dir direccio_w(Pos old_pos, Pos new_pos, Mvis& m) {
    int x = (new_pos.i) - (old_pos.i);
    int y = (new_pos.j) - (old_pos.j);
    if(y != 0) {
      if(y > 0) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
      }
	
      if(y < 0) {
	m[old_pos.i][old_pos.j-1] = true;
	return Left;
      }
    }
    if(x != 0) {
      if(x > 0) {
	m[old_pos.i+1][old_pos.j] = true;
	return Bottom;
      }
      if(x < 0) {
	m[old_pos.i-1][old_pos.j] = true;
	return Top;
      }
    }
    m[old_pos.i][old_pos.j] = true;
    return None;
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
  
  Dir direccio_f(Pos old_pos, Pos new_pos, Mvis& m) {
    int x = (new_pos.i) - (old_pos.i);
    int y = (new_pos.j) - (old_pos.j);
    if(y != 0) {
      if(y > 0) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
      }
	
      if(y < 0) {
	m[old_pos.i][old_pos.j-1] = true;
	return Left;
      }
    }
    if(x != 0) {
      if(x > 0) {
	m[old_pos.i+1][old_pos.j] = true;
	return Bottom;
      }
      if(x < 0) {
	m[old_pos.i-1][old_pos.j] = true;
	return Top;
      }
    }
    m[old_pos.i][old_pos.j] = true;
    return None;
  }
  
  bool posicio_valida_k(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  Dir direccio_k(Pos old_pos, Pos new_pos, Mvis& m) {
    int x = new_pos.i - old_pos.i;
    int y = new_pos.j - old_pos.j;
    if(x != 0 && y != 0) {
     if(x < 0 && y < 0) {
       m[old_pos.i-1][old_pos.j-1] = true;
       return TL;
     }
     if(x > 0 && y > 0) {
       m[old_pos.i+1][old_pos.j+1] = true;
       return BR;
     }
     if(x > 0 && y < 0) {
       m[old_pos.i-1][old_pos.j+1] = true;
       return LB;
     }
     if(x < 0 && y > 0) {
       m[old_pos.i+1][old_pos.j-1] = true;
       return RT;
     }
    }
    if(y != 0) {
      if(y > 0) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
      }
	
      if(y < 0) {
	m[old_pos.i][old_pos.j-1] = true;
	return Left;
      }
    }
    if(x != 0) {
      if(x > 0) {
	m[old_pos.i+1][old_pos.j] = true;
	return Bottom;
      }
      if(x < 0) {
	m[old_pos.i-1][old_pos.j] = true;
	return Top;
      }
    }
    m[old_pos.i][old_pos.j] = true;
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

    Mvis m(37, vector<bool> (37,false));
    vector<int> vf = farmers(0);
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_f(pos.i, pos.j); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_f(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_k(pos.i, pos.j); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_k(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
    vector<int> vw = witches(0);
    for(int id : vw) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_w(pos.i, pos.j, m);
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_w(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
