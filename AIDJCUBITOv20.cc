#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv20


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
  
  struct estat {
    bool b;
    Dir dir;
  };
  
  
  typedef vector< vector<bool> > Mocup;
  typedef vector< vector<estat> > Mest;
  

  bool posicio_valida_f(Pos pos, bool primer) {
    if((primer && cell(pos.i,pos.j).type != Wall && cell(pos.i,pos.j).id == -1 && not cell(pos.i,pos.j).haunted) || (not primer && cell(pos.i,pos.j).type != Wall && not cell(pos.i,pos.j).haunted))
      return true;
    else 
      return false;
  }
  
  Dir moviment_f(Pos pos, Mocup& mf) {
    Mest m(37, vector<estat>(37,{false,None}));
    queue<Pos> q;
    bool trobat = false;
    bool primer = true;
    m[pos.i][pos.j].b = true;
    q.push(pos);
    vector<int> direc(4);
    for(int i = 0; i < 4; i++)
      direc[i] = i*2;
    vector<int> per = random_permutation(4);
    while(not q.empty() && not trobat) {
      Pos act = q.front();
      q.pop();
      for(int i = 0; i < 4 && not trobat; i++) {
	Pos seg = act + Dir(direc[i]);
	if(not trobat && posicio_valida_f(seg,primer) && not m[seg.i][seg.j].b) {
	  q.push(seg);
	  m[seg.i][seg.j].b = true;
	  if(primer)
	    m[seg.i][seg.j].dir = Dir(per[i]*2);
	  else 
	    m[seg.i][seg.j].dir = m[act.i][act.j].dir;
	  if(cell(seg.i,seg.j).owner != 0 && not mf[seg.i][seg.j]) {
	   trobat = true;
	   mf[seg.i][seg.j] = true;
	  }
	}
      }
      primer = false;
    }
    if(trobat) {
     Pos p = q.back();
     return m[p.i][p.j].dir;
    }
    return None;
  }
  
  bool posicio_valida_k(Pos pos, Unit u, bool& enemy) {
    if(cell(pos.i,pos.j).id != -1) {
     enemy = true;
     if(cell(pos.i,pos.j).type != Wall && unit(cell(pos.i,pos.j).id).player != 0 && not cell(pos.i,pos.j).haunted && unit(cell(pos.i,pos.j).id).type != Witch)
       return true;
     else 
       return false;
    }
    else {
     if(cell(pos.i,pos.j).type != Wall && not cell(pos.i,pos.j).haunted)
       return true;
     else 
       return false;
    }
  }
  
  Dir moviment_k(Pos pos, Unit u) {
    Mest m(37, vector<estat>(37,{false,None}));
    queue<Pos> q;
    bool trobat = false;
    bool enemy = false;
    bool primer = true;
    m[pos.i][pos.j].b = true;
    q.push(pos);
    while(not q.empty() && not trobat) {
      Pos act = q.front();
      q.pop();
      vector<int> per = random_permutation(8);
      for(int i = 0; i < 8 && not trobat; i++) {
	Pos seg = act + Dir(per[i]);
	if(not trobat && posicio_valida_k(seg,u,enemy) && not m[seg.i][seg.j].b) {
	  q.push(seg);
	  m[seg.i][seg.j].b = true;
	  if(primer)
	    m[seg.i][seg.j].dir = Dir(per[i]);
	  else
	    m[seg.i][seg.j].dir = m[act.i][act.j].dir;
	  if(enemy)
	    trobat = true;
	}
	enemy = false;
      }
      primer = false;
    }
    if(trobat) {
      Pos p = q.back();
      return m[p.i][p.j].dir;
    }
    return None;
  }
  
  bool posicio_valida_w(Pos pos, bool& enemy) {
    if(cell(pos.i,pos.j).id != -1) {
      enemy = true;
      if(cell(pos.i,pos.j).type != Wall && unit(cell(pos.i,pos.j).id).player != 0 && unit(cell(pos.i,pos.j).id).type == Knight) 
	return true;
      else
	return false;
    }
    else {
     if(cell(pos.i,pos.j).type != Wall)
       return true;
     else 
       return false;
    }
  }
  
  Dir moviment_w(Pos pos, Mocup& mw) {
    Mest m(37, vector<estat>(37,{false,None}));
    queue<Pos> q;
    bool trobat = false;
    bool enemy = false;
    bool primer = true;
    m[pos.i][pos.j].b = true;
    q.push(pos);
    vector<int> direc(4);
    for(int i = 0; i < 4; i++)
      direc[i] = i*2;
    vector<int> per = random_permutation(4);
    
    while(not q.empty() && not trobat) {
     Pos act = q.front();
     q.pop();
     for(int i = 0; i < 4 && not trobat; i++) {
      Pos seg = act + Dir(per[i]*2);
      if(not trobat && posicio_valida_w(seg, enemy) && not m[seg.i][seg.j].b) {
	q.push(seg);
	m[seg.i][seg.j].b = true;
	if(primer) 
	  m[seg.i][seg.j].dir = Dir(per[i]*2);
	else 
	  m[seg.i][seg.j].dir = m[act.i][act.j].dir;
	if(enemy && mw[seg.i][seg.j] != true) {
	  trobat = true;
	  mw[seg.i][seg.j] = true;
	}
      }
      enemy = false;
     }
     primer = false;
    }
    if(trobat) {
      Pos p = q.back();
      return m[p.i][p.j].dir;
    }
    return None;
  }
  
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    vector<int> vf = farmers(0);
    Mocup mf(37, vector<bool>(37,false));
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Dir dir_nm = moviment_f(pos,mf);
      command(id,dir_nm);
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Dir dir_nm = moviment_k(pos,unit(id));
      command(id,dir_nm);
    }
    Mocup mw(37, vector<bool>(37,false));
    vector<int> vw = witches(0);
    for(int id : vw) {
      Pos pos = unit(id).pos;
      Dir dir_nm = moviment_w(pos,mw);
      command(id,dir_nm);
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);