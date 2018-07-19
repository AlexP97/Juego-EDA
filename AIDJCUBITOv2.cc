#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv2


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
  
   
  bool posicio_valida_f(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
	 
  Pos moviment_f(int x, int y) {
    queue<Cell> q;
    queue<Pos> p;
    bool trobat = false;
    Mvis m(37, vector<bool> (37,false));
    q.push(cell(x,y));
    p.push({x,y});
    m[x][y] = true;
    Cell cact;
    Pos pos;
    while(not q.empty() && not trobat) {
      cact = q.front();
      pos = p.front();
      p.pop();
      q.pop();
      if(cact.id == -1 && cact.owner != 0)  
	trobat = true;
      if(posicio_valida_f((pos.i+1),pos.j) && not m[(pos.i+1)][pos.j]) {
	q.push(cell((pos.i+1),pos.j));
	p.push({pos.i+1,pos.j});
	m[pos.i+1][pos.j] = true;
      }
      if(posicio_valida_f(pos.i-1,pos.j) && not m[(pos.i-1)][pos.j]) {
	q.push(cell((pos.i-1),pos.j));
	p.push({(pos.i-1),pos.j});
	m[pos.i-1][pos.j] = true;
      }
      if(posicio_valida_f(pos.i,pos.j+1) && not m[(pos.i)][pos.j+1]) {
	q.push(cell(pos.i,(pos.j+1)));
	p.push({pos.i,(pos.j+1)});
	m[pos.i][pos.j+1] = true;
      }
		
      if(posicio_valida_f(pos.i,(pos.j-1)) && not m[(pos.i)][pos.j-1]) {
	q.push(cell(pos.i,(pos.j-1)));
	p.push({pos.i,(pos.j-1)});
	m[pos.i][pos.j-1] = true;	
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
    queue<Cell> q;
    queue<Pos> p;
    Mvis m(37, vector<bool> (37,false));
    bool trobat = false;
    q.push(cell(x,y));
    p.push({x,y});
    m[x][y] = true;
    Cell cact;
    Pos pos;
    while(not q.empty() && not trobat) {
      cact = q.front();
      pos = p.front();
      q.pop();
      p.pop();
      if(cact.id != -1 && unit(cact.id).type != Witch && unit(cact.id).player != 0) {
	trobat = true;
      }
      if(posicio_valida_k((pos.i+1),pos.j) && not m[(pos.i+1)][pos.j]) {
	q.push(cell((pos.i+1),pos.j));
	p.push({(pos.i+1),pos.j});
	m[pos.i+1][pos.j] = true;
      }
      if(posicio_valida_k((pos.i-1),pos.j) && not m[(pos.i-1)][pos.j]) {
	q.push(cell((pos.i-1),pos.j));
	p.push({(pos.i-1),pos.j});
	m[pos.i-1][pos.j] = true;
      }
      if(posicio_valida_k(pos.i,(pos.j+1)) && not m[pos.i][(pos.j+1)]) {
	q.push(cell(pos.i,(pos.j+1)));
	p.push({pos.i,(pos.j+1)});
	m[pos.i][pos.j+1] = true;
      }
		
      if(posicio_valida_k(pos.i,(pos.j-1)) && not m[pos.i][(pos.j-1)]) {
	q.push(cell(pos.i,(pos.j-1)));
	p.push({pos.i,(pos.j-1)});	
	m[pos.i][pos.j-1] = true;
      }		
      if(posicio_valida_k((pos.i+1),pos.j+1) && not m[(pos.i+1)][pos.j+1]) {
	q.push(cell((pos.i+1),pos.j+1));
	p.push({(pos.i+1),pos.j+1});
	m[pos.i+1][pos.j+1] = true;
      }
      if(posicio_valida_k((pos.i-1),pos.j-1) && not m[(pos.i-1)][pos.j-1]) {
	q.push(cell((pos.i-1),pos.j-1));
	p.push({(pos.i-1),pos.j-1});
	m[pos.i-1][pos.j-1] = true;
      }
      if(posicio_valida_k(pos.i-1,(pos.j+1)) && not m[pos.i-1][(pos.j+1)]) {
	q.push(cell(pos.i-1,(pos.j+1)));
	p.push({pos.i-1,(pos.j+1)});
	m[pos.i-1][pos.j+1] = true;
      }
      if(posicio_valida_k(pos.i+1,(pos.j-1)) && not m[pos.i+1][(pos.j-1)]) {
	q.push(cell(pos.i+1,(pos.j-1)));
	p.push({pos.i+1,(pos.j-1)});
	m[pos.i+1][pos.j-1] = true;
      }		
    }
    if(trobat) 
      return pos;
    else 
      return {-1,-1};	
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    
    vector<int> vf = farmers(0);
    for (int id : vf) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_f(pos.i, pos.j); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_f(pos,new_pos);
	command(id,dir_nm);
      }
    }
    vector<int> vk = knights(0);
    for (int id : vk) {
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
